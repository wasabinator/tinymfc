#ifndef GLOBALS_H
#define GLOBALS_H

//class CMainWnd;
#include "mainwnd.h"

#include <shlobj.h>


extern HINSTANCE g_hInstance;
extern CMainWnd *g_pwndMain;
extern LPMALLOC g_Malloc;

extern void TFC_SetMainWindow(CMainWnd *pwndMain);
extern CMainWnd *TFC_GetMainWindow();
extern BOOL TFC_Init();
extern void TFC_Exit();
extern LPVOID SHMalloc(UINT cbSize);
extern void SHFree(LPVOID lpVoid);

#ifdef _DEBUG
#define OutputDebug(a, b)           \
{                                   \
    char strDebug[255];             \
                                    \
    wsprintf(strDebug, a, b);       \
    OutputDebugString(strDebug);    \
}

#define ShowHResult(hr)             \
{                                   \
    switch(hr)                          \
    {                                   \
    case S_OK:                          \
        OutputDebugString("*** SUCCESS ***\n"); \
        break;                                  \
                                                \
    case VFW_S_NOPREVIEWPIN:                    \
        OutputDebugString("*** Preview was rendered through a Smart Tee filter. ***\n"); \
        break;                                  \
                                                \
    case E_FAIL:                                \
        OutputDebugString("*** Failure ***\n"); \
        break;                                  \
                                                \
    case E_INVALIDARG:                          \
        OutputDebugString("*** Invalid argument ***\n"); \
        break;                                  \
                                                \
    case E_POINTER:                             \
        OutputDebugString("*** EPOINTER ***\n"); \
        break;                                  \
    }                                           \
}

#endif

#endif // GLOBALS_H