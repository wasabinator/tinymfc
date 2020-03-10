#ifndef WINDOW_H
#define WINDOW_H


#include <windows.h>
#include <winuser.h>
#include "rect.h"
#include <assert.h>
#include <dbt.h> // PDEV_BROADCAST_HDR

#define PROP_ID   "TinyMFC_id"
#define PROP_THIS "TinyMFC_this"

extern LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class CWndClass;

class CWnd
{
protected:
//    HWND m_hWndCapture;
    HWND m_hWndFocus;
//    BOOL m_bCapture;

// attributes
public:
    HWND m_hWnd;
    WNDPROC m_pfnOldWndProc; // used for subclassing

// methods
public:
    CWnd();
    virtual ~CWnd();

    CWnd(HWND hWnd);

    static CWnd *GetThis(HWND hWnd);

    virtual BOOL Create(CWndClass &wndClass,
                        LPCTSTR   lpWindowName=NULL,
                        HWND  	  hWndParent=NULL,
                        DWORD     dwStyle=WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                        DWORD     dwExStyle=WS_EX_CONTROLPARENT|WS_EX_NOPARENTNOTIFY,
                        int  	  x=CW_USEDEFAULT,
                        int  	  y=CW_USEDEFAULT,
                        int  	  nWidth=CW_USEDEFAULT,
                        int		  nHeight=CW_USEDEFAULT,
                        HMENU	  hMenu=NULL);

    virtual BOOL Create(LPCTSTR   lpClassName,
                        HINSTANCE hInstance,
                        LPCTSTR   lpWindowName=NULL,
                        HWND      hWndParent=NULL,
                        DWORD     dwStyle=WS_OVERLAPPEDWINDOW|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                        DWORD     dwExStyle=WS_EX_CONTROLPARENT|WS_EX_NOPARENTNOTIFY,
                        int  	  x=CW_USEDEFAULT,
                        int  	  y=CW_USEDEFAULT,
                        int  	  nWidth=CW_USEDEFAULT,
                        int  	  nHeight=CW_USEDEFAULT,
                        HMENU     hMenu=NULL);

    BOOL Destroy();

    void Subclass();

    HWND GetHWnd();
    BOOL IsWindow();

    BOOL Show();
    BOOL Hide();

    HDC GetDC();
    HDC GetWindowDC();
    int ReleaseDC(HDC hDC);

    HINSTANCE GetInstance();

    BOOL GetWindowRect(LPRECT lpRect);
    CRect GetWindowRect();

    BOOL GetClientRect(LPRECT lpRect);
    CRect GetClientRect();

    HWND GetParent();

    BOOL ScreenToClient(LPPOINT lpPoint);
    BOOL ClientToScreen(LPPOINT lpPoint);
    BOOL ScreenToClient(LPRECT  lpRect);
    BOOL ClientToScreen(LPRECT  lpRect);

    LONG  GetWindowLong(int nIndex);
    LONG  SetWindowLong(int nIndex, LONG lNewLong);

    DWORD GetClassLong(int nIndex);
    int GetClassName(LPTSTR lpClassName, int nClassName);

    int GetWindowText(LPTSTR lpString, int nMaxCount);

    BOOL MoveWindow(int x, int y, int cx, int cy, BOOL fRepaint=TRUE);

    LRESULT DefWindowProc(UINT Msg, WPARAM wParam, LPARAM lParam);

    LRESULT SendMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);

    HWND GetCapture();
    BOOL HasCapture();
    HWND SetCapture();
    BOOL ReleaseCapture();
    HWND GetFocus();
    BOOL HasFocus();
    HWND SetFocus();
    void ReleaseFocus();
    HWND SetParent(HWND hwndNewParent);
    HWND SetParent(CWnd &wndNewParent);
    HWND GetDlgItem(int idControl);

    void LockWindowUpdate();
    void UnLockWindowUpdate();

    void SetId(LONG lId);
    LONG GetId();

    void SetProp(LPCTSTR lpszName, LONG lValue);
    LONG GetProp(LPCTSTR lpszName);
    void RemoveProp(LPCTSTR lpszName);

    virtual BOOL WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

    virtual void OnPreSubclassWindow();

    // Message Handlers
    virtual BOOL ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam); 
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnCreate(LPCREATESTRUCT lpcs);
    virtual BOOL OnDestroy();
    virtual BOOL OnDeviceChange(WORD wEvent, PDEV_BROADCAST_HDR pDevBroadcastHdr);
    virtual BOOL OnDrawItem(UINT idCtrl, LPDRAWITEMSTRUCT lpdis);
    virtual BOOL OnEnterIdle(WORD wEvent, HWND hWnd);
    virtual BOOL OnEnterSizeMove();
    virtual BOOL OnEraseBkgnd(HDC hDC);
    virtual BOOL OnExitSizeMove();
    virtual BOOL OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo);
    virtual BOOL OnKeyDown(WORD vKeyCode, WORD nRepeat);
    virtual BOOL OnKillFocus(HWND hWnd);
    virtual BOOL OnLButtonDblClk(short x, short y, WORD vKeys);
    virtual BOOL OnLButtonDown(short x, short y, WORD vKeys);
    virtual BOOL OnLButtonUp(short x, short y, WORD vKeys);
    virtual BOOL OnMenuSelect(UINT nItem, UINT uFlags, HMENU hMenu);
    virtual BOOL OnMouseMove(short x, short y, WORD vKeys);
    virtual BOOL OnMove(short x, short y);
    virtual BOOL OnMoving(LPRECT lpRect, WORD wFlags);
    virtual BOOL OnNCLButtonDblClk(WORD wItem, POINTS pts);
    virtual BOOL OnNCLButtonDown(WORD wItem, POINTS pts); 
    virtual BOOL OnNCLButtonUp(WORD wItem, POINTS pts); 
    virtual BOOL OnNotify(UINT idFrom, LPNMHDR lpNmHdr);
    //virtual BOOL OnNotify(HWND hwndFrom, UINT idFrom, UINT code);
    virtual BOOL OnPaint(HDC hDC);
    virtual BOOL OnSetCursor(WORD wHitTest, WORD wIdentifier);
    virtual BOOL OnSetFocus(HWND hWnd);
    virtual BOOL OnSize(UINT nType, WORD nWidth, WORD nHeight);
    virtual BOOL OnSysCommand(WPARAM wParam, LPARAM lParam);
    virtual BOOL OnWindowPosChanged(LPWINDOWPOS lpWindowPos);
};

inline CWnd::CWnd()
//            :m_bCapture(FALSE),
            :m_hWnd(NULL),
             m_pfnOldWndProc(NULL)
{
}

inline CWnd::~CWnd()
{
    if (::IsWindow(m_hWnd))
        Destroy();  // Delete the window associated with this class
}

inline CWnd::CWnd(HWND hWnd)
{
    assert(::IsWindow(hWnd));
    m_hWnd = hWnd;
}

inline BOOL CWnd::Destroy()
{
    assert(::IsWindow(m_hWnd));

    // No need to set m_hWnd to NULL here, since it is tested with IsWindow
    // rather than compared against NULL in the rest of the code
    return ::DestroyWindow(m_hWnd);
}

inline HWND CWnd::GetHWnd()
{
    return m_hWnd;
}

inline BOOL CWnd::IsWindow()
{
    return ::IsWindow(m_hWnd);
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

inline HINSTANCE CWnd::GetInstance()
{
    return (HINSTANCE)GetWindowLong(GWL_HINSTANCE);
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
    ::GetWindowRect(m_hWnd, (LPRECT)rect);
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
    ::GetClientRect(m_hWnd, (LPRECT)rect);
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

inline HWND CWnd::GetParent()
{
    return ::GetParent(m_hWnd);
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

inline int CWnd::GetClassName(LPTSTR lpClassName, int nClassName)
{
    assert(::IsWindow(m_hWnd));
    return ::GetClassName(m_hWnd, lpClassName, nClassName);
}

inline LONG CWnd::GetWindowLong(int nIndex)
{
    assert(::IsWindow(m_hWnd));
    return ::GetWindowLong(m_hWnd, nIndex);
}

inline LONG CWnd::SetWindowLong(int nIndex, LONG lNewLong)
{
    assert(::IsWindow(m_hWnd));
    return ::SetWindowLong(m_hWnd, nIndex, lNewLong);
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

inline HWND CWnd::GetCapture()
{
    assert(::IsWindow(m_hWnd));
    return ::GetCapture();
}

inline BOOL CWnd::HasCapture()
{
    assert(::IsWindow(m_hWnd));
    //return m_bCapture;
    return ::GetCapture() == m_hWnd;
}

inline HWND CWnd::SetCapture()
{
    assert(::IsWindow(m_hWnd));
//    m_hWndCapture = ::SetCapture(m_hWnd);
    
//    m_bCapture = TRUE;
//    return m_hWndCapture;
    return ::SetCapture(m_hWnd);
}

inline BOOL CWnd::ReleaseCapture()
{
    assert(::IsWindow(m_hWnd));
    BOOL bRC = ::ReleaseCapture();
//    ::SetCapture(m_hWndCapture);
//    m_bCapture = FALSE;
    return bRC;
}

inline HWND CWnd::GetFocus()
{
    assert(::IsWindow(m_hWnd));
    return ::GetFocus();
}

inline BOOL CWnd::HasFocus()
{
    assert(::IsWindow(m_hWnd));
    return ::GetFocus() == m_hWnd;
}

inline HWND CWnd::SetFocus()
{
    assert(::IsWindow(m_hWnd));
    m_hWndFocus = ::SetFocus(m_hWnd);
    return m_hWndFocus;
}

inline HWND CWnd::GetDlgItem(int idControl)
{
    assert(::IsWindow(m_hWnd));
    return ::GetDlgItem(m_hWnd, idControl);
}

inline void CWnd::ReleaseFocus()
{
    assert(::IsWindow(m_hWnd));
    ::SetFocus(m_hWndFocus);
}

inline HWND CWnd::SetParent(HWND hwndNewParent)
{
    assert(::IsWindow(m_hWnd));
    assert(::IsWindow(hwndNewParent));
    return ::SetParent(m_hWnd, hwndNewParent);
}

inline HWND CWnd::SetParent(CWnd &wndNewParent)
{
    assert(::IsWindow(m_hWnd));
    assert(::IsWindow(wndNewParent.GetHWnd()));
    return ::SetParent(m_hWnd, wndNewParent.GetHWnd());
}

inline void CWnd::LockWindowUpdate()
{
    assert(::IsWindow(m_hWnd));
    ::LockWindowUpdate(m_hWnd);
}
    
inline void CWnd::UnLockWindowUpdate()
{
    assert(::IsWindow(m_hWnd));
    ::LockWindowUpdate(NULL);
}

inline void CWnd::SetProp(LPCTSTR lpszName, LONG lValue)
{
    assert(::IsWindow(m_hWnd));
    ::SetProp(m_hWnd, lpszName, (HANDLE)lValue);
}

inline LONG CWnd::GetProp(LPCTSTR lpszName)
{
    assert(::IsWindow(m_hWnd));
    return (LONG)::GetProp(m_hWnd, lpszName);
}

inline void CWnd::RemoveProp(LPCTSTR lpszName)
{
    ::RemoveProp(m_hWnd, lpszName);
}

//////////////////////////////////////////////////////////////
// Default message handler defnintions

inline BOOL CWnd::ProcessMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

inline BOOL CWnd::OnCommand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

inline BOOL CWnd::OnCreate(LPCREATESTRUCT lpcs)
{
    return FALSE;
}

inline BOOL CWnd::OnDestroy()
{
    return FALSE;
}

inline BOOL CWnd::OnDeviceChange(WORD wEvent, PDEV_BROADCAST_HDR pDevBroadcastHdr)
{
    return FALSE;
}

inline BOOL CWnd::OnDrawItem(UINT idCtrl, LPDRAWITEMSTRUCT lpdis)
{
    return FALSE;
}

inline BOOL CWnd::OnEnterIdle(WORD wEvent, HWND hWnd)
{
    return FALSE;
}

inline BOOL CWnd::OnEnterSizeMove()
{
    return FALSE;
}

inline BOOL CWnd::OnEraseBkgnd(HDC hDC)
{
    return FALSE;
}

inline BOOL CWnd::OnExitSizeMove()
{
    return FALSE;
}

inline BOOL CWnd::OnGetMinMaxInfo(LPMINMAXINFO lpMinMaxInfo)
{
    return FALSE;
}

inline BOOL CWnd::OnKeyDown(WORD vKeyCode, WORD nRepeat)
{
    return FALSE;
}

inline BOOL CWnd::OnKillFocus(HWND hWnd)
{
    return FALSE;
}

inline BOOL CWnd::OnLButtonDblClk(short x, short y, WORD vKeys)
{
    return FALSE;
}

inline BOOL CWnd::OnLButtonDown(short x, short y, WORD vKeys)
{
    return FALSE;
}

inline BOOL CWnd::OnLButtonUp(short x, short y, WORD vKeys)
{
    return FALSE;
}

inline BOOL CWnd::OnMenuSelect(UINT nItem, UINT uFlags, HMENU hMenu)
{
    return FALSE;
}

inline BOOL CWnd::OnMouseMove(short x, short y, WORD vKeys)
{
    return FALSE;
}

inline BOOL CWnd::OnMove(short x, short y)
{
    return FALSE;
}

inline BOOL CWnd::OnMoving(LPRECT lpRect, WORD wFlags)
{
    return FALSE;
}

inline BOOL CWnd::OnNCLButtonDblClk(WORD wItem, POINTS pts)
{
    return FALSE;
}

inline BOOL CWnd::OnNCLButtonDown(WORD wItem, POINTS pts)
{
    return FALSE;
}

inline BOOL CWnd::OnNCLButtonUp(WORD wItem, POINTS pts)
{
    return FALSE;
}

//inline BOOL CWnd::OnNotify(HWND hwndFrom, UINT idFrom, UINT code)
inline BOOL CWnd::OnNotify(UINT idFrom, LPNMHDR lpNmHdr)
{
    return FALSE;
}

inline BOOL CWnd::OnPaint(HDC hDC)
{
    return FALSE;
}

inline BOOL CWnd::OnSetCursor(WORD wHitTest, WORD wIdentifier)
{
    return FALSE;
}

inline BOOL CWnd::OnSetFocus(HWND hWnd)
{
    return FALSE;
}

inline BOOL CWnd::OnSize(UINT nType, WORD nWidth, WORD nHeight)
{
    return FALSE;
}

inline BOOL CWnd::OnSysCommand(WPARAM wParam, LPARAM lParam)
{
    return FALSE;
}

inline BOOL CWnd::OnWindowPosChanged(LPWINDOWPOS lpWindowPos)
{
    return FALSE;
}

#endif // WINDOW_H
