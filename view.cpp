#include "mainwnd.h"
#include "view.h"
#include "wndclass.h"
//#include "resource.h"
#include "dc.h"
#include "rect.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>

#include <tchar.h>

CView::CView()
      :m_pwndContainer(NULL),
       m_bDocked(TRUE),
       m_bBackground(FALSE)
{
}

CView::~CView()
{
}

// Message handlers
BOOL CView::Create(HINSTANCE hInstance,
                   HWND      hWndParent)
{
    CWndClass wc(_T("TFC_View"), hInstance);  // Window class for view window

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

//    m_bDocked = TRUE;

    return CWnd::Create(wc, NULL, hWndParent, WS_CHILD|WS_VISIBLE, 0, 0, 0, 0, 0);
}

void CView::DrawWindow(CDC dc)
{
    CRect rect = GetClientRect();

    HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_3DSHADOW));

    DrawEdge(dc, rect, EDGE_SUNKEN, BF_RECT);
    rect.Inflate(-2, -2);
    FillRect(dc, rect, hBrush);

    DeleteObject((HGDIOBJ)hBrush);
}

// Message handlers
BOOL CView::OnPaint(HDC hDC)
{
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(m_hWnd, &ps);

    DrawWindow(dc);

    EndPaint(m_hWnd, &ps);

    return TRUE;
}

BOOL CView::OnEraseBkgnd(HDC hDC)
{
    return TRUE;
}
