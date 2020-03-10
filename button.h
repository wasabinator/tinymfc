#ifndef BUTTON_H
#define BUTTON_H

#include "window.h"

class CButton : public CWnd
{
public:
    CButton();

    virtual BOOL Create(HINSTANCE hInstance,
                        LPCTSTR   lpCaption,
                        HWND      hWndParent,
                        int       x,
                        int       y,
                        int       nWidth,
                        int       nHeight,
                        DWORD     dwStyle=WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON|BS_TEXT);
};

#endif // BUTTON_H