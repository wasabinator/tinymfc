// Main window class
#include "window.h"
#include <windows.h>
#include "GFX.h"

class CMainWindow : public CWnd
{
public:
    BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

inline BOOL CMainWindow::OnCommand(WPARAM wParam, LPARAM lParam)
{
    switch(LOWORD(wParam))
    {
        case IDM_FILEEXIT:
            PostQuitMessage(0);
            return TRUE;
    }

    return FALSE;
}
