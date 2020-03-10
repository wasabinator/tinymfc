//#include "stdafx.h"

#include "tabctl.h"

CTabCtl::CTabCtl()
        :m_nTabs(0)
{
}

BOOL CTabCtl::Create(HINSTANCE hInstance,
                     HWND      hWndParent,
                     int       x,
                     int       y,
                     int       nWidth,
                     int       nHeight,
                     DWORD     dwStyle,
                     DWORD     dwExStyle)
{
    BOOL bRC = CWnd::Create(WC_TABCONTROL, 
                            hInstance,
                            "",
                            hWndParent,
                            dwStyle, dwExStyle,
                            x, y, nWidth, nHeight);

    if (bRC) SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

    return bRC;
}

void CTabCtl::AddTab(LPSTR pszText)
{
    TC_ITEM item;

    item.mask = TCIF_TEXT;
    item.pszText = pszText;

    TabCtrl_InsertItem(m_hWnd, m_nTabs++, &item);
}
