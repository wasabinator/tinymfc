#include "mainwnd.h"
#include "dockview.h"
#include "wndclass.h"
//#include "resource.h"
#include "dc.h"
#include "rect.h"
#include "globals.h"
#include <tchar.h>

//#define NDEBUG // Use for non-debug version
#include <assert.h>

CDockView::CDockView()
          :m_bClosePressed(FALSE),
           m_pwndDragView(NULL)
{
}

CDockView::~CDockView()
{
}

// Message handlers
BOOL CDockView::Create(HINSTANCE hInstance,
                       HWND      hWndParent,
                       LPTSTR    lpszCaption,
                       DWORD     dwStyle,
                       DWORD     dwExStyle)
{
    CWndClass wc(_T("TFC_DockView"), hInstance);  // Window class for view window

    wc.SetStyle(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
    wc.SetWndProc((WNDPROC)::WndProc);
    wc.SetCursor(LoadCursor(NULL, IDC_ARROW)); // Use standard arrow cursor
    //wc.SetBackground((HBRUSH)GetStockObject(WHITE_BRUSH));
    //wc.SetBackground(CreateSolidBrush(GetSysColor(COLOR_3DFACE)));
    //wc.SetBackground(CreateSolidBrush(GetSysColor(COLOR_3DSHADOW)));
    //wc.SetMenuName(MAKEINTRESOURCE(IDR_MAIN));
    //wc.SetIconSm(LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));

	// Attempt to register the class
    wc.Register();
    //if (wc.Register() == 0)
    //    return FALSE;

    return CWnd::Create(wc, lpszCaption, hWndParent, dwStyle, dwExStyle, 0, 0, 0, 0);
}

void CDockView::DrawWindow(CDC dc)
{
    CRect rect = GetClientRect();

    rect.SetHeight(GetSystemMetrics(SM_CYSMCAPTION));

    m_rectClose.right = rect.right-1;
    m_rectClose.left = m_rectClose.right - (GetSystemMetrics(SM_CXSMSIZE)-2);
    m_rectClose.top = rect.top + ((rect.GetHeight() - (GetSystemMetrics(SM_CYSMSIZE)-3))>>1);
    m_rectClose.bottom = m_rectClose.top + (GetSystemMetrics(SM_CYSMSIZE)-3);
    DrawFrameControl(dc, m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE|(m_bClosePressed?DFCS_PUSHED:0));

    // Exclude the close button from painting
    ExcludeClipRect(dc, m_rectClose.left, m_rectClose.top, m_rectClose.right, m_rectClose.bottom);

    DrawCaption(m_hWnd, dc, rect, (m_bDocked?0:0x0020)|DC_SMALLCAP|DC_TEXT|(HasFocus()?DC_ACTIVE:0)); // 0x0020 is DC_GRADIENT for versions of win32 that support it

    rect.top = rect.bottom;
    rect.bottom = GetClientRect().bottom;
    DrawWindow(dc, rect);
}

// calculates client area for subclass painting
CRect CDockView::CalcClientRect()
{
    CRect rect = GetClientRect();

    rect.top += GetSystemMetrics(SM_CYCAPTION);
    
    return rect;
}

void CDockView::DrawWindow(CDC dc, CRect rect)
{
    HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));

    FillRect(dc, rect, hBrush);

    DeleteObject((HGDIOBJ)hBrush);
}

int CDockView::GetMinWidth()
{
    return 15;
}

int CDockView::GetMinHeight()
{
    return GetSystemMetrics(SM_CYCAPTION)-3;
}

BOOL CDockView::OnLButtonDblClk(short x, short y, WORD vKeys)
{
    ReleaseCapture();

    if (y <= GetSystemMetrics(SM_CYSMCAPTION))
    {
        if (m_bDocked)
        {
            SetParent(::GetDesktopWindow());
            SetWindowLong(GWL_HWNDPARENT, (long)g_pwndMain->m_hWnd);

            SetWindowLong(GWL_STYLE, WS_POPUPWINDOW|WS_THICKFRAME|WS_VISIBLE);//WS_OVERLAPPEDWINDOW|WS_VISIBLE);//WS_POPUPWINDOW|WS_VISIBLE|WS_CLIPSIBLINGS|WS_CLIPCHILDREN|WS_OVERLAPPED);//WS_CHILD|WS_CAPTION|WS_BORDER|WS_VISIBLE);
            SetWindowLong(GWL_EXSTYLE, WS_EX_PALETTEWINDOW|WS_EX_TOPMOST);//WS_EX_TOOLWINDOW|WS_EX_TOPMOST);

            MoveWindow(50, 50, 200, 100);
            m_bDocked = FALSE;
            m_pwndContainer->UnDock();
        }
        else
        {
            SetParent(m_pwndContainer->GetHWnd());
            SetWindowLong(GWL_HWNDPARENT, (long)m_pwndContainer->GetHWnd());

            SetWindowLong(GWL_STYLE, WS_CHILD|WS_VISIBLE);
            SetWindowLong(GWL_EXSTYLE, 0);

            m_bDocked = TRUE;
            m_pwndContainer->Dock();
        }
    }

    return TRUE;
}

BOOL CDockView::OnLButtonDown(short x, short y, WORD vKeys)
{
    SetFocus();
    
    if (m_rectClose.PtInRect(x, y))
    {
        SetCapture();

        m_bClosePressed = TRUE;

        CDC dc = GetDC();
        //DrawWindow(dc);
        DrawFrameControl(dc, m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE|DFCS_PUSHED);
        ReleaseDC(dc);
    }
    else
    if (y <= GetSystemMetrics(SM_CYSMCAPTION))
    {
        SetCapture();

        m_rectDrag = GetWindowRect();
        m_nXDrag = x;
        m_nYDrag = y;
        m_nXOrigin = m_rectDrag.left;
        m_nYOrigin = m_rectDrag.top;
        
        if (m_bDocked)
        {
            m_nDragSize = 2; //1;
            DrawFocusRect(m_rectDrag, m_nDragSize);
        }
        else // window is a floating toolwindow
        {
            m_nDragSize = 4;
            DrawFocusRect(m_rectDrag, m_nDragSize);
        }
    }

    return TRUE;
}

BOOL CDockView::OnLButtonUp(short x, short y, WORD vKeys)
{
    if (HasCapture())
    {
        ReleaseCapture();

        if (m_bClosePressed)
        {
            m_bClosePressed = FALSE;

            CDC dc = GetDC();
            DrawFrameControl(dc, m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE);
            ReleaseDC(dc);

            if (m_rectClose.PtInRect(x, y) && CanClose())
            {
                // close the window
                ((CSplitterWnd*)m_pwndContainer)->RemoveView(this);
                delete this;
            }
        }
        else
        {
            if (m_bDocked)
            {
                DrawFocusRect(m_rectDrag, m_nDragSize); // undo previous rect

                CRect rect = GetWindowRect();

                if ((m_pwndDragView) && (m_pwndDragView != this))
                {
                    //Hide();
                    ((CSplitterWnd*)m_pwndContainer)->RemoveView(this);
                    CSplitterWnd::SplitView(m_pwndDragView, this, m_nSize, m_nDragOrientation, m_bDragAfter);
                    //Show();
                }
            }
            else
            {
                DrawFocusRect(m_rectDrag, m_nDragSize);
            }
        }
    }
    return TRUE;
}

BOOL CDockView::OnKeyDown(WORD vKeyCode, WORD nRepeat)
{
    if (vKeyCode == VK_ESCAPE && HasCapture())
    {
        DrawFocusRect(m_rectDrag, m_nDragSize); // undo previous rect
        ReleaseCapture();
        ReleaseFocus();

        return TRUE;
    }
    else
        return FALSE;
}

BOOL CDockView::OnMouseMove(short x, short y, WORD vKeys)
{
    if (HasCapture())
    {
        if (m_bClosePressed)
        {
            CDC dc = GetDC();
            DrawFrameControl(dc, m_rectClose, DFC_CAPTION, DFCS_CAPTIONCLOSE|((m_rectClose.PtInRect(x, y))?DFCS_PUSHED:0));
            ReleaseDC(dc);
        }
        else
        {
            DrawFocusRect(m_rectDrag, m_nDragSize); // remove previous focus rect

            CRect rect = GetWindowRect();
            m_pwndDragView = g_pwndMain->GetSplitter()->GetChildFromPoint(rect.left+x, rect.top+y, this);

            if (m_pwndDragView)
            {
                int nThreshholdX, nThreshholdY;

                m_rectDrag = m_pwndDragView->GetWindowRect();
                nThreshholdX = m_rectDrag.GetWidth()>>2;  // dock width position
                nThreshholdY = m_rectDrag.GetHeight()>>2; // dock height position
                m_nDragSize = 2; //1;

                if (m_pwndDragView != this) // mouse over this window so display dock rectanlge the size of this window
                {
                    if (rect.left + x <= (m_rectDrag.left + nThreshholdX))
                    {
                        // docking to left
                        m_bDragAfter = FALSE;
                        m_nDragOrientation = SPLITTER_VERT;
                        m_nDockSize = rect.GetWidth();
                        m_rectDrag.SetWidth(nThreshholdX);
                    }
                    else
                    if (rect.left + x >= m_rectDrag.right - nThreshholdX)
                    {
                        // docking to right
                        m_bDragAfter = TRUE;
                        m_nDragOrientation = SPLITTER_VERT;
                        m_rectDrag.SetOrigin(m_rectDrag.right-nThreshholdX,
                                             m_rectDrag.top);
                        m_nDockSize = rect.GetWidth();
                        m_rectDrag.SetWidth(nThreshholdX);
                    }
                    else
                    if (rect.top + y <= m_rectDrag.top + nThreshholdY)
                    {
                        // docking to top
                        m_bDragAfter = FALSE;
                        m_nDragOrientation = SPLITTER_HORZ;
                        m_nDockSize = rect.GetHeight();
                        m_rectDrag.SetHeight(nThreshholdY);
                    }
                    else
                    if (rect.top + y >= m_rectDrag.bottom - nThreshholdY)
                    {
                        // docking to bottom
                        m_bDragAfter = TRUE;
                        m_nDragOrientation = SPLITTER_HORZ;
                        m_rectDrag.SetOrigin(m_rectDrag.left,
                                             m_rectDrag.bottom-nThreshholdY);
                        m_nDockSize = rect.GetHeight();
                        m_rectDrag.SetHeight(nThreshholdY);
                    }
                    else
                    {
                        m_rectDrag.SetRect(m_nXOrigin + (x-m_nXDrag),
                                           m_nYOrigin + (y-m_nYDrag),
                                           m_nXOrigin + (x-m_nXDrag) + rect.GetWidth(),
                                           m_nYOrigin + (y-m_nYDrag) + rect.GetHeight());
                        m_nDragSize = 4;
                    }
                }
            }
            else
            {
                m_rectDrag.SetRect(m_nXOrigin + (x-m_nXDrag),
                                   m_nYOrigin + (y-m_nYDrag),
                                   m_nXOrigin + (x-m_nXDrag) + rect.GetWidth(),
                                   m_nYOrigin + (y-m_nYDrag) + rect.GetHeight());
                m_nDragSize = 4;
            }

            DrawFocusRect(m_rectDrag, m_nDragSize); // redraw new rect
        }

        return TRUE;
    }
    else
        return FALSE;
}

BOOL CDockView::OnKillFocus(HWND hWnd)
{
    CDC dc = GetDC();
    DrawWindow(dc);
    ReleaseDC(dc);

    return TRUE;
}

BOOL CDockView::OnSetFocus(HWND hWnd)
{
    CDC dc = GetDC();
    DrawWindow(dc);
    ReleaseDC(dc);

    return TRUE;
}

void CDockView::DrawFocusRect(LPRECT lpRect, int nSize)
{
    CRect rect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    CDC dc = ::GetWindowDC(GetDesktopWindow());

    HBRUSH  hBrush, hOldBrush ;
    HBITMAP hBitmap;

    static WORD Dots[] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa}; 

    hBitmap = CreateBitmap(8, 8, 1, 1, (LPSTR) Dots);
    if (hBitmap == NULL) ::MessageBeep(0); // TODO

    hBrush = CreatePatternBrush(hBitmap);
    if (hBrush == NULL) ::MessageBeep(0); // TODO

    hOldBrush = (HBRUSH)SelectObject(dc, hBrush);

    PatBlt(dc, rect.left, rect.top, rect.GetWidth(), nSize, PATINVERT);
    PatBlt(dc, rect.left, rect.top+nSize, nSize, rect.GetHeight()-nSize-nSize, PATINVERT);
    PatBlt(dc, rect.right-nSize, rect.top+nSize, nSize, rect.GetHeight()-nSize-nSize, PATINVERT);
    PatBlt(dc, rect.left, rect.bottom-nSize, rect.GetWidth(), nSize, PATINVERT);

    SelectObject(dc, hOldBrush);
    DeleteObject(hBrush);
    DeleteObject(hBitmap);
}
