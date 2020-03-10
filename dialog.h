#ifndef DIALOG_H
#define DIALOG_H

#include "window.h"

class CDialog : public CWnd
{
public:
    CDialog();

    int CreateModal(HINSTANCE hInstance,
                    LPCTSTR   lpszTemplate,
                    HWND      hWndParent);

    BOOL DlgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

    // Message Handlers
    virtual BOOL OnInitDialog(); 
};

//////////////////////////////////////////////////////////////
// Default message handler defnintions

inline BOOL CDialog::OnInitDialog()
{
    return FALSE;
}

#endif // DIALOG_H