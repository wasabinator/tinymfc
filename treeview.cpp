//#include "stdafx.h"

#include "treeview.h"

CTreeView::CTreeView()
{
}

BOOL CTreeView::Create(HINSTANCE hInstance,
                       HWND      hWndParent,
                       int       x,
                       int       y,
                       int       nWidth,
                       int       nHeight,
                       DWORD     dwStyle,
                       DWORD     dwExStyle)
{
    BOOL bRC = CWnd::Create(WC_TREEVIEW, 
                            hInstance,
                            "",
                            hWndParent,
                            dwStyle, dwExStyle,
                            x, y, nWidth, nHeight);

    if (bRC) SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

    return bRC;
}
