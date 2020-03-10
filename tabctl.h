#ifndef TABCTL_H
#define TABCTL_H

#include "window.h"
#include <commctrl.h>

class CTabCtl : public CWnd
{
protected:
    int m_nTabs;

public:
    CTabCtl();

    virtual BOOL Create(HINSTANCE hInstance,
                        HWND      hWndParent,
                        int       x,
                        int       y,
                        int       nWidth,
                        int       nHeight,
                        DWORD     dwStyle=WS_CHILD|WS_CLIPSIBLINGS|
                                          TCS_TABS|TCS_SINGLELINE|TCS_FORCELABELLEFT,
                        DWORD     dwExStyle=0);

    void AddTab(LPSTR lpszName);
};

#endif // TABCTL_H