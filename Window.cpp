/////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     //
//  TFC - Tiny Foundation Classes for Microsoft Windows                                //
//                                                                                     //
//  Copyright (c) 1999, 2000 Radix Software Pty Limited                                //
//                                                                                     //
//  This is an open source project.  Feel free to distribute and modify these classes  //
//  Please submit any changes you make to tfc@radix.com.au                             //
//                                                                                     //
/////////////////////////////////////////////////////////////////////////////////////////

//#include "stdafx.h"

#include "window.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>
#include "wndclass.h"
#include "rect.h"

CWnd *CWnd::GetThis(HWND hWnd)
{
    return (CWnd *)::GetProp(hWnd, PROP_THIS);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bMsgProcessed = FALSE;

    CWnd *pWnd = CWnd::GetThis(hWnd);

    if (pWnd)
        bMsgProcessed = pWnd->WndProc(uMsg, wParam, lParam);
    else
    {
        // Process any messages that can arrive before window associated with an object

        switch(uMsg)
        {
        case WM_CREATE:
            pWnd = (CWnd*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            pWnd->m_hWnd = hWnd;
            SetProp(hWnd, PROP_ID, 0);
            SetProp(hWnd, PROP_THIS, (LPVOID)pWnd);
            bMsgProcessed = pWnd->OnCreate((LPCREATESTRUCT)lParam);
            break;
        }
    }

    if (!bMsgProcessed)
    {
        if (pWnd && pWnd->m_pfnOldWndProc)
            return CallWindowProc(pWnd->m_pfnOldWndProc, hWnd, uMsg, wParam, lParam);
        else
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    else
        return TRUE;
}

BOOL CWnd::WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bMsgProcessed = FALSE;

    bMsgProcessed = ProcessMessage(uMsg, wParam, lParam);

    if (!bMsgProcessed)
    {
        switch(uMsg)
        {
        case WM_COMMAND:
            bMsgProcessed = OnCommand(wParam, lParam);
            break;

        case WM_DESTROY:
            bMsgProcessed = OnDestroy();
            RemoveProp(PROP_ID);
            RemoveProp(PROP_THIS);
            break;

        case WM_DEVICECHANGE:
            bMsgProcessed = OnDeviceChange(wParam, (PDEV_BROADCAST_HDR)lParam);
            break;

        case WM_DRAWITEM:
            bMsgProcessed = OnDrawItem((UINT)wParam, (LPDRAWITEMSTRUCT)lParam);
            if (((LPDRAWITEMSTRUCT)lParam)->hwndItem != m_hWnd)
                ::SendMessage(((LPDRAWITEMSTRUCT)lParam)->hwndItem, uMsg, wParam, lParam);
            break;

        case WM_ENTERIDLE:
            bMsgProcessed = OnEnterIdle(wParam, (HWND)lParam);
            if (wParam == MSGF_DIALOGBOX && (HWND)lParam != m_hWnd) // Allow dialog box to trap ENTERIDLE
                ::SendMessage((HWND)lParam, uMsg, wParam, lParam);
            break;

        case WM_ENTERSIZEMOVE:
            bMsgProcessed = OnEnterSizeMove();
            break;

        case WM_ERASEBKGND:
            bMsgProcessed = OnEraseBkgnd((HDC)wParam);
            break;

        case WM_EXITSIZEMOVE:
            bMsgProcessed = OnExitSizeMove();
            break;

        case WM_GETMINMAXINFO:
            bMsgProcessed = OnGetMinMaxInfo((LPMINMAXINFO)lParam);
            break;

        case WM_KEYDOWN:
            bMsgProcessed = OnKeyDown(wParam, (WORD)lParam&15);
            break;

        case WM_KILLFOCUS:
            bMsgProcessed = OnKillFocus((HWND)wParam);
            break;

        case WM_LBUTTONDBLCLK:
            bMsgProcessed = OnLButtonDblClk(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_LBUTTONDOWN:
            bMsgProcessed = OnLButtonDown(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_LBUTTONUP:
            bMsgProcessed = OnLButtonUp(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_MENUSELECT:
            bMsgProcessed = OnMenuSelect((UINT)LOWORD(wParam), // menu item or pop-up menu index
                                         (UINT)HIWORD(wParam), // menu flags
                                         (HMENU)lParam);       // handle of menu clicked
            break;

        case WM_MOUSEMOVE:
            bMsgProcessed = OnMouseMove(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_NCLBUTTONDBLCLK:
            bMsgProcessed = OnNCLButtonDblClk(wParam, MAKEPOINTS(lParam));
            break;

        case WM_NCLBUTTONDOWN:
            bMsgProcessed = OnNCLButtonDown(wParam, MAKEPOINTS(lParam));
            break;

        case WM_NCLBUTTONUP:
            bMsgProcessed = OnNCLButtonUp(wParam, MAKEPOINTS(lParam));
            break;

        case WM_NOTIFY:
            bMsgProcessed = OnNotify((UINT)wParam, (LPNMHDR)lParam);
            break;

        case WM_MOVE:
            bMsgProcessed = OnMove(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_MOVING:
            bMsgProcessed = OnMoving((LPRECT)lParam, wParam);
            break;

        case WM_PAINT:
            bMsgProcessed = OnPaint((HDC)wParam);
            break;

        case WM_SETCURSOR:
            if ((HWND)wParam == m_hWnd) // don't process of intended for child wnd
                bMsgProcessed = OnSetCursor(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_SETFOCUS:
            bMsgProcessed = OnSetFocus((HWND)wParam);
            break;

        case WM_SIZE:
            bMsgProcessed = OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_SYSCOMMAND:
            bMsgProcessed = OnSysCommand(wParam, lParam);
            break;

        case WM_WINDOWPOSCHANGED:
            bMsgProcessed = OnWindowPosChanged((LPWINDOWPOS)lParam);
            break;
        }
    }

    return bMsgProcessed;
}

BOOL CWnd::Create(CWndClass &wc,
                  LPCTSTR   lpWindowName,
                  HWND  	   hWndParent,
                  DWORD     dwStyle,
                  DWORD     dwExStyle,
                  int       x,
                  int       y,
                  int       nWidth,
                  int       nHeight,
                  HMENU     hMenu)
{
    BOOL bRC = ((m_hWnd = CreateWindowEx(dwExStyle, wc.GetClassName(), lpWindowName,
                                         dwStyle,
                                         x, y, nWidth, nHeight,
                                         hWndParent, hMenu,
                                         (HINSTANCE)wc.GetInstance(),
                                         (HANDLE)this))!=NULL);

    // dialog controls won't have window proc to set PROP_THIS
    SetProp(PROP_THIS, (LONG)this);

    return bRC;
}

BOOL CWnd::Create(LPCTSTR   lpClassName,
                  HINSTANCE hInstance,
                  LPCTSTR   lpWindowName,
                  HWND      hWndParent,
                  DWORD     dwStyle,
                  DWORD     dwExStyle,
                  int       x,
                  int       y,
                  int       nWidth,
                  int       nHeight,
                  HMENU     hMenu)
{
    BOOL bRC = ((m_hWnd = CreateWindowEx(dwExStyle, lpClassName, lpWindowName,
                                         dwStyle,
                                         x, y, nWidth, nHeight,
                                         hWndParent, hMenu,
                                         hInstance, (HANDLE)this))!=NULL);

    // dialog controls won't have window proc to set PROP_THIS
    SetProp(PROP_THIS, (LONG)this);

    return bRC;
}

void CWnd::Subclass()
{
    OnPreSubclassWindow();
    m_pfnOldWndProc = (WNDPROC)GetWindowLong(GWL_WNDPROC);
    SetWindowLong(GWL_WNDPROC, (LONG)::WndProc);
}

void CWnd::OnPreSubclassWindow()
{
}

BOOL CWnd::ClientToScreen(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));

    POINT pt;
    pt.x = lpRect->left;
    pt.y = lpRect->top;
    BOOL bRC = ::ClientToScreen(m_hWnd, &pt);

    lpRect->right = (lpRect->right-lpRect->left)+pt.x;
    lpRect->left = pt.x;
    lpRect->bottom = (lpRect->bottom-lpRect->top)+pt.y;
    lpRect->top = pt.y;

    return bRC;
}

BOOL CWnd::ScreenToClient(LPRECT lpRect)
{
    assert(::IsWindow(m_hWnd));

    POINT pt;
    pt.x = lpRect->left;
    pt.y = lpRect->top;
    BOOL bRC = ::ScreenToClient(m_hWnd, &pt);

    lpRect->right = (lpRect->right-lpRect->left)+pt.x;
    lpRect->left = pt.x;
    lpRect->bottom = (lpRect->bottom-lpRect->top)+pt.y;
    lpRect->top = pt.y;

    return bRC;
}

BOOL CWnd::MoveWindow(int x, int y, int cx, int cy, BOOL fRepaint)
{
    return ::MoveWindow(m_hWnd, x, y, cx, cy, fRepaint);
}

void CWnd::SetId(LONG lId)
{
    SetProp(PROP_ID, lId);
}

LONG CWnd::GetId()
{
    return GetProp(PROP_ID);
}

/*
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    BOOL bMsgProcessed = FALSE;

    CWnd *pWnd = (CWnd *)GetProp(hWnd, PROP_THIS);

    if (!(pWnd && pWnd->ProcessMessage(uMsg, wParam, lParam)))
    {
        switch(uMsg)
        {
        case WM_COMMAND:
            bMsgProcessed = pWnd->OnCommand(wParam, lParam);
            break;

        case WM_CREATE:
            pWnd = (CWnd*)((LPCREATESTRUCT)lParam)->lpCreateParams;
            pWnd->m_hWnd = hWnd;
            SetProp(hWnd, PROP_ID, 0);
            SetProp(hWnd, PROP_THIS, (LPVOID)pWnd);
            bMsgProcessed = pWnd->OnCreate((LPCREATESTRUCT)lParam);
            break;

        case WM_DESTROY:
            pWnd->RemoveProp(PROP_ID);
            pWnd->RemoveProp(PROP_THIS);
            bMsgProcessed = pWnd->OnDestroy();
            break;

        case WM_DEVICECHANGE:
            bMsgProcessed = pWnd->OnDeviceChange(wParam, (PDEV_BROADCAST_HDR)lParam);
            break;

        case WM_ENTERSIZEMOVE:
            bMsgProcessed = pWnd->OnEnterSizeMove();
            break;

        case WM_ERASEBKGND:
            bMsgProcessed = pWnd->OnEraseBkgnd((HDC)wParam);
            break;

        case WM_EXITSIZEMOVE:
            bMsgProcessed = pWnd->OnExitSizeMove();
            break;

        case WM_GETMINMAXINFO:
            if (pWnd) // need to check this since this message can arrive before WM_CREATE
                bMsgProcessed = pWnd->OnGetMinMaxInfo((LPMINMAXINFO)lParam);
            break;

        case WM_KEYDOWN:
            bMsgProcessed = pWnd->OnKeyDown(wParam, (WORD)lParam&15);
            break;

        case WM_KILLFOCUS:
            if (pWnd) // can happen after window destroyed
                bMsgProcessed = pWnd->OnKillFocus((HWND)wParam);
            break;

        case WM_LBUTTONDBLCLK:
            bMsgProcessed = pWnd->OnLButtonDblClk(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_LBUTTONDOWN:
            bMsgProcessed = pWnd->OnLButtonDown(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_LBUTTONUP:
            bMsgProcessed = pWnd->OnLButtonUp(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

        case WM_MENUSELECT:
            bMsgProcessed = pWnd->OnMenuSelect((UINT)LOWORD(wParam), // menu item or pop-up menu index
                                               (UINT)HIWORD(wParam), // menu flags
                                               (HMENU)lParam);       // handle of menu clicked
            break;

        case WM_MOUSEMOVE:
            bMsgProcessed = pWnd->OnMouseMove(LOWORD(lParam), HIWORD(lParam), wParam);
            break;

  //      case WM_NCCALCSIZE:
  //{
//
//            DefWindowProc(hWnd, uMsg, wParam, lParam);
//            NCCALCSIZE_PARAMS FAR *lpncp = (NCCALCSIZE_PARAMS FAR *) lParam;
  
//  RECT clientrect,diffrect;
// 
//  diffrect.left=lpncp->rgrc[1].left-lpncp->rgrc[2].left;
//  diffrect.top=lpncp->rgrc[1].top-lpncp->rgrc[2].top;
//  diffrect.right=lpncp->rgrc[1].right-lpncp->rgrc[2].right;
//  diffrect.bottom=lpncp->rgrc[1].bottom-lpncp->rgrc[2].bottom; 
 
//  lpncp->rgrc[0].left+=diffrect.left;
//  lpncp->rgrc[0].top+=diffrect.top;
//  lpncp->rgrc[0].right+=diffrect.right;
//  lpncp->rgrc[0].bottom+=diffrect.bottom;

//            lpncp->rgrc[0].left-=GetSystemMetrics(SM_CXFRAME);
            //lpncp->rgrc[0].right+=GetSystemMetrics(SM_CXBORDER);
            //lpncp->rgrc[1].left+=10;
            //lpncp->rgrc[2].left+=10;
//    return WVR_ALIGNLEFT|WVR_REDRAW|WVR_VALIDRECTS;;
//}

        case WM_NCLBUTTONDBLCLK:
            bMsgProcessed = pWnd->OnNCLButtonDblClk(wParam, MAKEPOINTS(lParam));
            break;

        case WM_NCLBUTTONDOWN:
            bMsgProcessed = pWnd->OnNCLButtonDown(wParam, MAKEPOINTS(lParam));
            break;

        case WM_NCLBUTTONUP:
            bMsgProcessed = pWnd->OnNCLButtonUp(wParam, MAKEPOINTS(lParam));
            break;

        case WM_MOVE:
            bMsgProcessed = pWnd->OnMove(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_MOVING:
            bMsgProcessed = pWnd->OnMoving((LPRECT)lParam, wParam);
            break;

        case WM_PAINT:
            bMsgProcessed = pWnd->OnPaint((HDC)wParam);
            break;

        case WM_SETCURSOR:
            if ((HWND)wParam == pWnd->GetHWnd()) // don't process of intended for child wnd
                bMsgProcessed = pWnd->OnSetCursor(LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_SETFOCUS:
            if (pWnd) // can happen after window class destroyed
                bMsgProcessed = pWnd->OnSetFocus((HWND)wParam);
            break;

        case WM_SIZE:
            bMsgProcessed = pWnd->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
            break;

        case WM_SYSCOMMAND:
            bMsgProcessed = pWnd->OnSysCommand(wParam, lParam);
            break;

        case WM_WINDOWPOSCHANGED:
            bMsgProcessed = pWnd->OnWindowPosChanged((LPWINDOWPOS)lParam);
            break;

        case WM_INITDIALOG:
            ::MessageBeep(0);
            //bMsgProcessed = pWnd->OnInitDialog();
            break;
        }

        if (!bMsgProcessed && pWnd)
        {
            if (!pWnd->m_bIsDialog)
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            else
                return DefDlgProc(hWnd, uMsg, wParam, lParam);
        }
    }

    return 0L;
}
*/
