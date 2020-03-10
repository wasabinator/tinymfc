#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include "rect.h"
#include <assert.h>

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class CWndClass;

class CWnd
{
// attributes
public:
    HWND m_hWnd;

// methods
public:
    CWnd();
    CWnd(HWND hWindow);

    BOOL Create(CWndClass &wndClass,
                LPCTSTR   lpWindowName=NULL,
                HWND  	  hWndParent=NULL,
                DWORD     dwStyle=WS_OVERLAPPEDWINDOW,
                int  	  x=CW_USEDEFAULT,
                int  	  y=CW_USEDEFAULT,
                int  	  nWidth=CW_USEDEFAULT,
                int		  nHeight=CW_USEDEFAULT,
                HMENU	  hMenu=NULL,
                LPVOID    lpParam=NULL);

    BOOL Create(LPCTSTR lpClassName,
                HANDLE  hInstance,
                LPCTSTR lpWindowName=NULL,
                HWND    hWndParent=NULL,
                DWORD   dwStyle=WS_OVERLAPPEDWINDOW,
                int  	x=CW_USEDEFAULT,
                int  	y=CW_USEDEFAULT,
                int  	nWidth=CW_USEDEFAULT,
                int  	nHeight=CW_USEDEFAULT,
                HMENU   hMenu=NULL,
                LPVOID  lpParam=NULL);

    BOOL Destroy();

    HDC GetHWnd();

    BOOL Show();
    BOOL Hide();

    HDC GetDC();
    HDC GetWindowDC();
    int ReleaseDC(HDC hDC);

    BOOL GetWindowRect(LPRECT lpRect);
    CRect GetWindowRect();

    BOOL GetClientRect(LPRECT lpRect);
    CRect GetClientRect();

    BOOL ScreenToClient(LPPOINT lpPoint);
    BOOL ClientToScreen(LPPOINT lpPoint);
    BOOL ScreenToClient(LPRECT  lpRect);
    BOOL ClientToScreen(LPRECT  lpRect);

    DWORD GetClassLong(int nIndex);

    int GetWindowText(LPTSTR lpString, int nMaxCount);

    LRESULT DefWindowProc(UINT Msg, WPARAM wParam, LPARAM lParam);

    LRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

	// Custom rendering of the window caption area
    // for that Office 95 look you've been looking for !
    void PaintWindowCaption(BOOL bActive);

    // Message Handlers
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};

inline CWnd::CWnd()
{
    m_hWnd = NULL;
}

inline CWnd::CWnd(HWND hWindow)
{
    assert(::IsWindow(hWindow));
    m_hWnd = hWindow;
}

inline BOOL CWnd::Destroy()
{
    assert(::IsWindow(m_hWnd));
    return ::DestroyWindow(m_hWnd);
}

inline HDC CWnd::GetHWnd()
{
    assert(::IsWindow(m_hWnd));
    return m_hWnd;
}

inline BOOL CWnd::Show()
{
    assert(::IsWindow(m_hWnd));
    return ::ShowWindow(m_hWnd, SW_SHOW);
}

inline BOOL CWnd::Hide()
{
    assert(::IsWindow(m_hWnd));
    return ::ShowWindow(m_hWnd, SW_HIDE);
}

inline HDC CWnd::GetDC()
{
    assert(::IsWindow(m_hWnd));
    return ::GetDC(m_hWnd);
}

inline HDC CWnd::GetWindowDC()
{
    assert(::IsWindow(m_hWnd));
    return ::GetWindowDC(m_hWnd);
}

inline int CWnd::ReleaseDC(HDC hDC)
{
    assert(::IsWindow(m_hWnd));
    return ::ReleaseDC(m_hWnd, hDC);
}

inline BOOL CWnd::GetWindowRect(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));
    return ::GetWindowRect(m_hWnd, lpRect);
}

inline CRect CWnd::GetWindowRect()
{
    CRect rect;
    assert(::IsWindow(m_hWnd));
    assert(::GetWindowRect(m_hWnd, (LPRECT)rect));
    return rect;
}

inline BOOL CWnd::GetClientRect(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));
    return ::GetClientRect(m_hWnd, lpRect);
}

inline CRect CWnd::GetClientRect()
{
    CRect rect;
    assert(::IsWindow(m_hWnd));
    assert(::GetClientRect(m_hWnd, (LPRECT)rect));
    return rect;
}

inline BOOL CWnd::ClientToScreen(LPPOINT lpPoint)
{
    assert(::IsWindow(m_hWnd));
    return ::ClientToScreen(m_hWnd, lpPoint);
}

inline BOOL CWnd::ScreenToClient(LPPOINT lpPoint)
{
    assert(::IsWindow(m_hWnd));
    return ::ScreenToClient(m_hWnd, lpPoint);
}

inline LRESULT CWnd::DefWindowProc(UINT   Msg,
                                   WPARAM wParam,
                                   LPARAM lParam)
{
    assert(::IsWindow(m_hWnd));
    return ::DefWindowProc(m_hWnd, Msg, wParam, lParam);
}

inline DWORD CWnd::GetClassLong(int nIndex)
{
    assert(::IsWindow(m_hWnd));
    return ::GetClassLong(m_hWnd, nIndex);
}

inline int CWnd::GetWindowText(LPTSTR lpString, int nMaxCount)
{
    assert(::IsWindow(m_hWnd));
    return ::GetWindowText(m_hWnd, lpString, nMaxCount);
}

inline LRESULT CWnd::SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    assert(::IsWindow(m_hWnd));
    return ::SendMessage(m_hWnd, uMsg, wParam, lParam);
}

//////////////////////////////////////////////////////////////
// Default message handler defnintions

inline BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
    // Default implementation does nothing
    return FALSE;
}

#endif // WINDOW_H
