#include "globals.h"

CMainWnd *g_pwndMain = NULL;
LPMALLOC g_pMalloc = NULL;

void TFC_SetMainWindow(CMainWnd *pwndMain)
{
    g_pwndMain = pwndMain;
}

CMainWnd *TFC_GetMainWindow()
{
    return g_pwndMain;
}

BOOL TFC_Init()
{
    BOOL bRC;

    bRC = SUCCEEDED(SHGetMalloc(&g_pMalloc));

    return bRC;
}

void TFC_Exit()
{
    if (g_pMalloc)
    {
        g_pMalloc->Release();
        g_pMalloc = NULL;
    }
}

LPVOID SHMalloc(UINT cbSize)
{
    if (g_pMalloc)
        return g_pMalloc->Alloc(cbSize);
    else
        return NULL;
}

void SHFree(LPVOID lpVoid)
{
    g_pMalloc->Free(lpVoid);
}
