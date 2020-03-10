#ifndef TREEVIEW_H
#define TREEVIEW_H

#include "window.h"
#include <commctrl.h>

class CTreeView : public CWnd
{
public:
    CTreeView();

    virtual BOOL Create(HINSTANCE hInstance,
                        HWND      hWndParent,
                        int       x,
                        int       y,
                        int       nWidth,
                        int       nHeight,
                        DWORD     dwStyle=WS_CHILD|WS_BORDER|WS_VISIBLE|
                                          TVS_EDITLABELS|TVS_HASBUTTONS|
                                          TVS_HASLINES|TVS_LINESATROOT,
                        DWORD     dwExStyle=WS_EX_CLIENTEDGE);
};

#endif // TREEVIEW_H