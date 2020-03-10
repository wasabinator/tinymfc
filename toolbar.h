#ifndef TOOLBAR_H
#define TOOLBAR_H

#include "window.h"
#include <commctrl.h>

class CToolBar : public CWnd
{
    TBBUTTON tbb;  // Used for adding toolbar buttons

public:
    CToolBar();

    virtual BOOL Create(HINSTANCE hInstance,
                        HWND      hWndParent,
                        DWORD     dwStyle=WS_CHILD|WS_VISIBLE|TBSTYLE_TOOLTIPS|TBSTYLE_WRAPABLE, //WS_BORDER
                        HMENU     idTool=NULL);
    //TBSTYLE_FLAT|

//TBSTYLE_FLAT,WS_CHILD|WS_VISIBLE|CBRS_TOP 
//  |CBRS_GRIPPER|CBRS_TOOLTIPS|CBRS_FLYBY|CBRS_SIZE_DYNAMIC

    void SetButtonSize(int nWidth, int nHeight);

    BOOL AddButton(int iIndex, int idButton, BYTE fsStyle=(BYTE)TBSTYLE_BUTTON, BYTE fsState=(BYTE)TB_ENABLEBUTTON);
    BOOL AddSeparator(int nWidth);
    virtual BOOL OnEraseBkgnd(HDC hDC);
};

inline CToolBar::CToolBar()
{
    tbb.dwData = NULL;
}

#endif // TOOLBAR_H
