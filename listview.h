#ifndef LISTVIEW_H
#define LISTVIEW_H

#include "window.h"
#include <commctrl.h>

class CListView : public CWnd
{
protected:
    int m_nColumns;

public:
    CListView();

    virtual BOOL Create(HINSTANCE hInstance,
                        HWND      hWndParent,
                        int       x,
                        int       y,
                        int       nWidth,
                        int       nHeight,
                        DWORD     dwStyle=WS_CHILD|WS_BORDER|WS_VISIBLE|
                                          LVS_REPORT,
                        DWORD     dwExStyle=0);

    void AddColumn(LPSTR pszText);
};

#endif // LISTVIEW_H