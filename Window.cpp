#include "window.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>
#include "wndclass.h"
#include "rect.h"

#define PROP_THIS "TinyMFC_this"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static BOOL bActive = FALSE;
    BOOL bMsgProcessed = FALSE;

    CWnd *pWnd = (CWnd *)GetProp(hWnd, PROP_THIS);

    switch(uMsg)
    {
    case WM_COMMAND:
        bMsgProcessed = pWnd->OnCommand(wParam, lParam);
        break;

    case WM_ERASEBKGND:
        // don't want to do anything here...
        //return DefWindowProc(hWnd, uMsg, wParam, lParam);
        break;

    case WM_NCACTIVATE:
        bMsgProcessed = TRUE;
        pWnd->PaintWindowCaption(bActive = (BOOL)wParam);
        break;

    // For active window states, code falls through here
    case WM_NCPAINT:
        bMsgProcessed = TRUE;
        pWnd->PaintWindowCaption(bActive);
        break;

    case WM_DESTROY:
        bMsgProcessed = TRUE;
        PostQuitMessage(0);
        break;

    case WM_SIZE:
        // need to do something here...
        break;
   }

    if (!bMsgProcessed)
        return DefWindowProc(hWnd, uMsg, wParam, lParam);

    return 0L;
}

BOOL CWnd::Create(CWndClass &wc,
                  LPCTSTR   lpWindowName,
                  HWND  	   hWndParent,
                  DWORD     dwStyle,
                  int       x,
                  int       y,
                  int       nWidth,
                  int       nHeight,
                  HMENU     hMenu,
                  LPVOID    lpParam)
{
    BOOL bRC = ((m_hWnd = CreateWindow(wc.GetClassName(), lpWindowName,
                                       dwStyle,
                                       x, y, nWidth, nHeight,
                                       hWndParent, hMenu,
                                       wc.GetInstance(),
                                       lpParam))!=NULL);
    if (bRC)
        SetProp(m_hWnd, PROP_THIS, (HANDLE)this);

    return bRC;
}

BOOL CWnd::Create(LPCTSTR lpClassName,
                  HANDLE  hInstance,
                  LPCTSTR lpWindowName,
                  HWND    hWndParent,
                  DWORD   dwStyle,
                  int     x,
                  int     y,
                  int     nWidth,
                  int     nHeight,
                  HMENU   hMenu,
                  LPVOID  lpParam)
{
    BOOL bRC = ((m_hWnd = CreateWindow(lpClassName, lpWindowName,
                                       dwStyle,
                                       x, y, nWidth, nHeight,
                                       hWndParent, hMenu,
                                       hInstance, lpParam))!=NULL);
    if (bRC)
        SetProp(m_hWnd, PROP_THIS, (HANDLE)this);

    return bRC;
}

BOOL CWnd::ClientToScreen(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));

    POINT pt;
    pt.x = lpRect->left;
    pt.y = lpRect->top;
    BOOL bRC = ::ClientToScreen(m_hWnd, &pt);

    lpRect->right = (lpRect->right-lpRect->left)+pt.x;
    lpRect->left = pt.x;
    lpRect->bottom = (lpRect->bottom-lpRect->top)+pt.y;
    lpRect->top = pt.y;

    return bRC;
}

BOOL CWnd::ScreenToClient(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));

    POINT pt;
    pt.x = lpRect->left;
    pt.y = lpRect->top;
    BOOL bRC = ::ScreenToClient(m_hWnd, &pt);

    lpRect->right = (lpRect->right-lpRect->left)+pt.x;
    lpRect->left = pt.x;
    lpRect->bottom = (lpRect->bottom-lpRect->top)+pt.y;
    lpRect->top = pt.y;

    return bRC;
}

// Custom rendering of the Window caption
// which emulates the Office 95 look

void CWnd::PaintWindowCaption(BOOL bActive)
{
    // First get some dimensions
    int nCxFrame = GetSystemMetrics(SM_CXSIZEFRAME),
        nCyFrame = GetSystemMetrics(SM_CYSIZEFRAME),
        nCyCaption = GetSystemMetrics(SM_CYCAPTION),
        nCxSize = GetSystemMetrics(SM_CXSIZE),
        nCySize = GetSystemMetrics(SM_CYSIZE),
        nCxBorder = GetSystemMetrics(SM_CXBORDER),
        nCyBorder = GetSystemMetrics(SM_CYBORDER),
        nCxSmIcon = GetSystemMetrics(SM_CXSMICON),
        nCySmIcon = GetSystemMetrics(SM_CYSMICON);

    LONG xpos, ypos;

    HDC hDC = GetWindowDC(); // Get DC for entire window
    CRect rect = GetWindowRect(),
                 captionTextRect;

    xpos = rect.left;
    ypos = rect.top;

    HRGN hRgn1, hRgn2;
         hRgn1 = CreateRectRgnIndirect(rect);

    // Calculate bounding rectangle for caption area
    rect.left += nCxFrame;
    rect.top += nCyFrame;
    rect.right -= (nCxFrame + nCxBorder + nCxSize
                + (nCxSize<<1)
                +  nCxBorder);
    rect.bottom = rect.top + nCyCaption-1;
    hRgn2 = CreateRectRgnIndirect(rect);

    CombineRgn(hRgn1, hRgn1, hRgn2, RGN_XOR);
    DefWindowProc(WM_NCPAINT, (WPARAM)hRgn1, (LPARAM)0L);

    // Now paint the color fade
    int nWidth = rect.GetWidth();
    float fRectWidth = (float)nWidth/64.0;

    // Convert rect to window coordinates
    rect.top -= ypos;
    rect.bottom = rect.top + nCyCaption-1;
    rect.left -= xpos;
    rect.right -= xpos;

    // Calculate caption text rect for later
    captionTextRect.SetRect(rect.left + (nCxBorder<<1) + nCxSize,
                            rect.top,
                            rect.right,
                            rect.top+nCySize);

    float fRectLeft = (float)rect.left;

    rect.right = (LONG)(fRectLeft + fRectWidth);

    DWORD rgb = GetSysColor(bActive ? COLOR_ACTIVECAPTION
                                    : COLOR_INACTIVECAPTION);
    float fRInc = (float)GetRValue(rgb)/64.0,
          fGInc = (float)GetGValue(rgb)/64.0,
          fBInc = (float)GetBValue(rgb)/64.0,
          fRed = 0,
          fGreen = 0,
          fBlue = 0;

    xpos = rect.left;
    ypos = rect.top;

    LOGBRUSH logBrush;
    HBRUSH hBrush;
    logBrush.lbStyle = BS_SOLID;
    logBrush.lbHatch = 0;

    for (int i=0; i<64; i++)
    {
        logBrush.lbColor = RGB((BYTE)fRed, (BYTE)fGreen, (BYTE)fBlue);
        hBrush = CreateBrushIndirect(&logBrush);
        FillRect(hDC, rect, hBrush);
        DeleteObject(hBrush);

        // Increment colours
        fRed += fRInc;
        fGreen += fGInc;
        fBlue += fBInc;

        // Increment position
        fRectLeft += fRectWidth;
        rect.left = (LONG)fRectLeft;
        rect.right = (fRectLeft+fRectWidth);
    }

    HICON hIcon = (HICON)GetClassLong(GCL_HICONSM);

    // I'd rather use DrawCaption to do this, however it only supports
    // flat colour for background !

    if (!hIcon)
        hIcon = LoadIcon(NULL, IDI_WINLOGO);
    if (hIcon)
        DrawIconEx(hDC, xpos+nCxBorder, ypos+nCyBorder, hIcon,
                        nCxSmIcon, nCySmIcon,
                        0,NULL,DI_NORMAL);

    int iOldBkMode = SetBkMode(hDC, TRANSPARENT);

    // Use grey for disabled text color to ensure visibility
    COLORREF crOldTextColor = SetTextColor(hDC, bActive ? GetSysColor(COLOR_CAPTIONTEXT)
																: RGB(192, 192, 192)); //COLOR_INACTIVECAPTIONTEXT));
    NONCLIENTMETRICS ncMetrics;
    ncMetrics.cbSize = sizeof(NONCLIENTMETRICS);
    SystemParametersInfo(SPI_GETNONCLIENTMETRICS, 0, (PVOID)&ncMetrics, 0);
    HFONT hFont = CreateFontIndirect(&ncMetrics.lfCaptionFont);
    if (hFont)
    {
        HFONT hOldFont = SelectObject(hDC, hFont);
        TEXTMETRIC tm;
        GetTextMetrics(hDC, &tm);

        // Manually center the caption SINCE DraeTextEX's DT_VCENTER
        // SWITCH WON'T #$%#$% WORK !!
        captionTextRect.top += (((rect.bottom-rect.top)-tm.tmHeight)>>1);

        TCHAR lpCaption[100];
        int nChars = GetWindowText(lpCaption, sizeof(lpCaption)-1);
        if (nChars)
            DrawText(hDC, lpCaption, nChars, captionTextRect, DT_END_ELLIPSIS | DT_VCENTER);//, NULL);

        SelectObject(hDC, hOldFont);
        DeleteObject(hFont);
    }
    SetTextColor(hDC, crOldTextColor);
    SetBkMode(hDC, iOldBkMode);

    ReleaseDC(hDC);
}
