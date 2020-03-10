//#include "stdafx.h"

#include "button.h"

CButton::CButton()
{
}

BOOL CButton::Create(HINSTANCE hInstance,
                     LPCTSTR   lpCaption,
                     HWND      hWndParent,
                     int       x,
                     int       y,
                     int       nWidth,
                     int       nHeight,
                     DWORD     dwStyle)
{
    BOOL bRC = CWnd::Create("BUTTON", hInstance,
                            lpCaption,
                            hWndParent,
                           dwStyle, 0,
                            x, y, nWidth, nHeight);

    if (bRC) SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

    return bRC;
}

