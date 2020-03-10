#include <windows.h>
#include "wndclass.h"
//#include "rect.h"
#include "mainwnd.h"

#include "GFX.h"

#include "DirectDraw.h"

static LPCTSTR lpszAppName = "GFX - Game Framework";
static LPCTSTR WND_CLASS = "GFXWndClass";
TCHAR strBuffer[160];

HINSTANCE hInst;

CMainWindow wndMain;

int APIENTRY WinMain(HINSTANCE hInstance,
							HINSTANCE hPrevInstance,
                     LPSTR		 lpCmdLine,
                     int		 nCmdShow)
{
    MSG		 msg; // Current message
    CWndClass wc(WND_CLASS, hInstance);  // Window class for main window

    // Save instance handle
    hInst = hInstance;

    // Under Win95/NT, hPrevInstance will always be NULL
    if (!hPrevInstance)
    {
        wc.SetStyle(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
        wc.SetWndProc((WNDPROC)WndProc);
        wc.SetCursor(LoadCursor(NULL, IDC_ARROW)); // Use standard arrow cursor
        wc.SetBackground(GetStockObject(WHITE_BRUSH));
        wc.SetMenuName(MAKEINTRESOURCE(IDM_APPMENU));
        wc.SetIconSm(LoadIcon(hInst, MAKEINTRESOURCE(IDI_APPICON)));

        // Attempt to register the class
        if (wc.Register() == 0)
            return FALSE;
    }

    // Create main application window
    if (wndMain.Create(wc, lpszAppName)==NULL)
    {
        ::MessageBox(NULL,"Cannot create main window", "Error", MB_ICONERROR |MB_OK);
        return FALSE;
    }

    // Show the window
    wndMain.Show();

    // Setup DirectDraw display
	CDirectDraw *m_pDirectDraw = new CDirectDraw();
	if (m_pDirectDraw->Create())
	{
//		if (m_bFullScreen)
//        {
            ASSERT(m_pDirectDraw->SetCooperativeLevel(&wndMain));
	    	ASSERT(m_pDirectDraw->SetDisplayMode(640, 480, 16));
//        }
        ASSERT(m_pDirectDraw->CreateSurface());
	}

    // Process application message until it closes
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}

