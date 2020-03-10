//#include "stdafx.h"

#include "mainwnd.h"
#include "dc.h"
#include <tchar.h>
//#include "resource.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>

CMainWnd::CMainWnd()
         :m_pToolBar(NULL),
//          m_pDockFrame(NULL),
          m_pStatusBar(NULL),
          m_pSplitterWnd(NULL)
{
}

CMainWnd::~CMainWnd()
{
//    if (m_pToolBar)
//        delete m_pToolBar;

//    if (m_pStatusBar)
//        delete m_pStatusBar;
}

void CMainWnd::SetToolBar(CToolBar &toolBar)
{
    m_pToolBar = &toolBar;
}

void CMainWnd::SetStatusBar(CStatusBar &statusBar)
{
    m_pStatusBar = &statusBar;
}

void CMainWnd::SetSplitter(CSplitterWnd &splitter)
{
    m_pSplitterWnd = &splitter;
}

//void CMainWnd::SetDockFrame(CDockFrame &wndDockFrame)
//{
//    m_pDockFrame = &wndDockFrame;
//}

// Message handlers

BOOL CMainWnd::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
/*    switch(uMsg)
    case WM_MENUSELECT:
        // No need to trap OnMenuSelect as we want the raw wparam & lparam values
        MenuHelp(uMsg, wParam, lParam, hMenu, hInst, wndStatus.GetWnd()
*/    
    return FALSE;
}

BOOL CMainWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
    ::MessageBeep(0);
    return FALSE;
}

BOOL CMainWnd::OnCreate(LPCREATESTRUCT lpcs)
{
//    m_pButton = new CButton();
//    m_pButton->Create(GetInstance(), "OK 123", m_hWnd, 10, 10, 100, 100);

    return TRUE;
}

BOOL CMainWnd::OnDestroy()
{
    PostQuitMessage(0);
    return FALSE;
}

BOOL CMainWnd::OnEraseBkgnd(HDC hDC)
{
/*
    CDC dc(hDC);
    CRect rect;

//    int nControlIds[] = {
//        IDR_MAIN, 0,
//        m_pToolBar->GetId(), 0,
//        m_pStatusBar->GetId(), 0,
//        0, 0                                //  First zero marks end of data
//    };
//
//        GetEffectiveClientRect(GetHWnd(), &rect, nControlIds);

    // Ensure that we are not erasing the toolbar & statusbar
    // as this will create nasty flickering under NT4 while
    // the window is being resized.
    if (m_pToolBar)
    {
        rect = m_pToolBar->GetWindowRect();
        ScreenToClient(rect);
        ExcludeClipRect(hDC, rect.left, rect.top, rect.right, rect.bottom);
    }

    if (m_pStatusBar)
    {
        rect = m_pStatusBar->GetWindowRect();
        ScreenToClient(rect);
        ExcludeClipRect(hDC, rect.left, rect.top, rect.right, rect.bottom);
    }

//    return FALSE;  // Allow default handler to execute
*/
    return TRUE;
}

BOOL CMainWnd::OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo)
{
    CRect rectWindow = GetWindowRect(),
          rectClient = GetClientRect();

    rectClient.ClientToScreen(GetHWnd());
    int nMinX = rectWindow.GetWidth() - rectClient.GetWidth(),
        nMinY = rectWindow.GetHeight() - rectClient.GetHeight();

    if (m_pToolBar)
    {
        nMinY += m_pToolBar->GetWindowRect().GetHeight();
    }

    if (m_pStatusBar)
    {
        nMinY += m_pStatusBar->GetWindowRect().GetHeight();
    }

    if (m_pSplitterWnd)
    {
        int test = m_pSplitterWnd->GetMinHeight();
        nMinX += m_pSplitterWnd->GetMinWidth();
        nMinY += m_pSplitterWnd->GetMinHeight();
    }

    lpMinMaxInfo->ptMinTrackSize.x = nMinX;
    lpMinMaxInfo->ptMinTrackSize.y = nMinY;

    return TRUE;
}

BOOL CMainWnd::OnMenuSelect(UINT nItem, UINT uFlags, HMENU hMenu)
{
    if (m_pStatusBar)
    {
        TCHAR strBuffer[160];

        if (uFlags == 0xFFFF && hMenu == NULL)
            m_pStatusBar->SetNormalMode();
        else if ((uFlags & MFT_SEPARATOR) ||
                 (uFlags & MF_POPUP) ||
                 (uFlags & MF_SYSMENU))
            m_pStatusBar->SetStatusText(_T(""));
	    else
        {
            strBuffer[0]='\0';
            LoadString(GetInstance(),
                       nItem,
                       strBuffer,
                       sizeof(strBuffer));
            m_pStatusBar->SetSimpleMode();
            m_pStatusBar->SetStatusText(strBuffer);
        }
        return TRUE;
    }
    else
        return FALSE;
}

BOOL CMainWnd::OnSize(UINT nType, WORD nWidth, WORD nHeight)
{
    CRect rect;
    int nTop=0;

    if (m_pToolBar)
        m_pToolBar->SendMessage(WM_SIZE, (WPARAM)nType, MAKELONG(nHeight, nWidth));

    if (m_pStatusBar)
        m_pStatusBar->SendMessage(WM_SIZE, (WPARAM)nType, MAKELONG(nHeight, nWidth));

    if (m_pToolBar)
    {
        rect = m_pToolBar->GetWindowRect();
        ScreenToClient(rect);
        nTop += rect.GetHeight()-1;
        nHeight -= (WORD)rect.GetHeight();
    }

    if (m_pStatusBar)
    {
        rect = m_pStatusBar->GetWindowRect();
        ScreenToClient(rect);
        nHeight -= (WORD)rect.GetHeight()-1;
    }

    if (m_pSplitterWnd)
        m_pSplitterWnd->MoveWindow(0, nTop, nWidth, nHeight);

//    if (m_pDockFrame)
//        m_pDockFrame->MoveWindow(0, nTop, nWidth, nHeight);

    return TRUE;
}
