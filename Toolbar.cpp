//#include "stdafx.h"

#include <windows.h>
#include "toolbar.h"
#include <commctrl.h>
//#include <values.h> // for MAXINT

BOOL CToolBar::Create(HINSTANCE hInstance,
                      HWND      hWndParent,
                      DWORD     dwStyle,
                      HMENU     idTool)
{
    BOOL bRC;

    // TODO: Replace with call to CreateToolbarEx()
    if ((bRC = CWnd::Create(TOOLBARCLASSNAME, hInstance,
                            "",
                            hWndParent, dwStyle, 0,
                            0, 0, 0, 0,
                            idTool))==TRUE)
    {
        // Create ok, so send size of TBBUTTON to let Windows know
        // which version of the toolbar we are expecting
        SendMessage(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
    }

    return bRC;
}

void CToolBar::SetButtonSize(int nWidth, int nHeight)
{
    SendMessage(TB_SETBUTTONSIZE, 0, MAKELONG(nWidth, nHeight));
}

BOOL CToolBar::AddButton(int iIndex, int idButton, BYTE fsStyle, BYTE fsState)
{
    // Setup the TBBUTTON struct
    tbb.iBitmap = iIndex;
    tbb.idCommand = idButton;
    tbb.fsState = fsState;
    tbb.fsStyle = fsStyle;
    tbb.iString = iIndex;

    return (BOOL)SendMessage(TB_INSERTBUTTON, -1/*MAXINT*/, (LPARAM)&tbb);
}

BOOL CToolBar::AddSeparator(int nWidth)
{
    tbb.iBitmap = nWidth;
    tbb.idCommand = 0;
    tbb.fsState = 0;
    tbb.fsStyle = TBSTYLE_SEP;
    tbb.iString = 0;

    return (BOOL)SendMessage(TB_INSERTBUTTON, -1/*MAXINT*/, (LPARAM)&tbb);
}

BOOL CToolBar::OnEraseBkgnd(HDC hDC)
{
    return TRUE;
}

/*#include <windows.h>
#include "toolbar.h"
#include <commctrl.h>
//#include <values.h> // for MAXINT

BOOL CToolBar::Create(HANDLE  hInstance,
                      HWND    hWndParent,
                      DWORD   dwStyle,
                      HMENU   idTool)
{
    BOOL bRC;

    if ((bRC = CWindow::Create(TOOLBARCLASSNAME, hInstance,
                               "",
                               hWndParent, dwStyle, 0,
                               0, 0, 0, 0,
                               idTool))==TRUE)
    {
        // Create ok, so send size of TBBUTTON to let Windows know
        // which version of the toolbar we are expecting
        SendMessage(TB_BUTTONSTRUCTSIZE, sizeof(TBBUTTON), 0);
    }

    return bRC;
}

void CToolBar::SetButtonSize(int nWidth, int nHeight)
{
    SendMessage(TB_SETBUTTONSIZE, 0, MAKELONG(nWidth, nHeight));
}

BOOL CToolBar::AddButton(int iIndex, int idButton, BYTE fsStyle, BYTE fsState)
{
    // Setup the TBBUTTON struct
    tbb.iBitmap = iIndex;
    tbb.idCommand = idButton;
    tbb.fsState = fsState;
    tbb.fsStyle = fsStyle;
    tbb.iString = iIndex;

    return (BOOL)SendMessage(TB_INSERTBUTTON, -1, (LPARAM)&tbb);
}

BOOL CToolBar::AddSeparator(int nWidth)
{
    tbb.iBitmap = nWidth;
    tbb.idCommand = 0;
    tbb.fsState = 0;
    tbb.fsStyle = TBSTYLE_SEP;
    tbb.iString = 0;

    return (BOOL)SendMessage(TB_INSERTBUTTON, -1, (LPARAM)&tbb);
}
*/
