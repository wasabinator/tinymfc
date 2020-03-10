//#include "stdafx.h"

#include "listview.h"

CListView::CListView()
          :m_nColumns(0)
{
}

BOOL CListView::Create(HINSTANCE hInstance,
                       HWND      hWndParent,
                       int       x,
                       int       y,
                       int       nWidth,
                       int       nHeight,
                       DWORD     dwStyle,
                       DWORD     dwExStyle)
{
    BOOL bRC = CWnd::Create(WC_LISTVIEW, 
                            hInstance,
                            "",
                            hWndParent,
                            dwStyle, dwExStyle,
                            x, y, nWidth, nHeight);

    if (bRC) SendMessage(WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), 0);

    return bRC;
}

void CListView::AddColumn(LPSTR pszText)
{
    LV_COLUMN column;

    column.mask = LVCF_TEXT;
    column.pszText = pszText;

    ListView_InsertColumn(m_hWnd, m_nColumns++, &column);
}
