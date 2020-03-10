//#include "stdafx.h"

#include "statbar.h"

BOOL CStatusBar::Create(HINSTANCE  hInstance,
                        LPCTSTR lpPaneText,
                        HWND 	  hWndParent,
                        DWORD   dwStyle,
                        HMENU   idStatus)
{
    // TODO: Replace with call to CreateStatusBar()
    return CWnd::Create(STATUSCLASSNAME, hInstance,
                        lpPaneText,
                        hWndParent, dwStyle, 0,
                        0, 0, 0, 0,
                        idStatus);
}
