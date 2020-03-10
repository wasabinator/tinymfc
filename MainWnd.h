#ifndef MAINWND_H
#define MAINWND_H

#include "window.h"
#include "toolbar.h"
#include "statbar.h"
#include "splitter.h"

//#include "dockframe.h"

//#include "button.h"

class CMainWnd : public CWnd
{
    CToolBar *m_pToolBar;
    CStatusBar *m_pStatusBar;
//    CDockFrame *m_pDockFrame;
    CSplitterWnd *m_pSplitterWnd;

//    CButton *m_pButton;
public:
    CMainWnd();
    ~CMainWnd();
    void SetToolBar(CToolBar &toolBar);
    void SetStatusBar(CStatusBar &statusBar);
    void SetSplitter(CSplitterWnd &splitter);
    //void SetDockFrame(CDockFrame &wndDockFrame);

    CSplitterWnd *GetSplitter();

    // Message handlers
    virtual BOOL ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCreate(LPCREATESTRUCT lpcs);
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnDestroy();
    virtual BOOL OnEraseBkgnd(HDC hDC);
    virtual BOOL OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
    virtual BOOL OnMenuSelect(UINT nItem, UINT uFlags, HMENU hMenu);
    virtual BOOL OnSize(UINT nType, WORD nWidth, WORD nHeight);
};

inline CSplitterWnd *CMainWnd::GetSplitter()
{
    return m_pSplitterWnd;
}

#endif