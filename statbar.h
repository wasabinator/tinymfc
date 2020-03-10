#ifndef STATBAR_H
#define STATBAR_H

#include "window.h"

#include <windows.h>
#include <commctrl.h>

class CStatusBar : public CWnd
{
public:
    CStatusBar();

    virtual BOOL Create(HINSTANCE  hInstance,
                        LPCTSTR lpPaneText,
                        HWND 	  hWndParent,
                        DWORD   dwStyle=WS_CHILD|WS_VISIBLE,
                        HMENU   idStatus=NULL);

    void SetSimpleMode();
    void SetNormalMode();
    void SetText(LPCTSTR lpPaneText, int nPane=0, UINT uType=0);
    void SetStatusText(LPCTSTR lpStatusText);
};

inline CStatusBar::CStatusBar()
{
}

inline void CStatusBar::SetSimpleMode()
{
    SendMessage(SB_SIMPLE, (WPARAM)TRUE, 0L);
}

inline void CStatusBar::SetNormalMode()
{
    SendMessage(SB_SIMPLE, (WPARAM)FALSE, 0L);
}

inline void CStatusBar::SetText(LPCTSTR lpPaneText, int iPane, UINT uType)
{
    SendMessage(SB_SETTEXT, (WPARAM)iPane | uType, (LPARAM)lpPaneText);
}

inline void CStatusBar::SetStatusText(LPCTSTR lpStatusText)
{
    SetText(lpStatusText, 255, 0);
}

#endif // STATBAR_H
