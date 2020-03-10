#ifndef DOCKVIEW_H
#define DOCKVIEW_H

#include "view.h"

class CDC;

class CDockView : public CView
{
protected:
    CRect  m_rectDrag,
           m_rectClose; // rectangle for close button
    int    m_nXDrag, m_nYDrag, m_nDragSize, m_nDockSize, m_nDragOrientation;
    CView *m_pwndDragView;
    LONG   m_nXOrigin, m_nYOrigin;
    BOOL   m_bClosePressed, // user clicked the close button
           m_bDragAfter;

public:
    CDockView();
    ~CDockView();

    virtual BOOL Create(HINSTANCE  hInstance,
                        HWND 	   hWndParent,
                        LPTSTR     lpszCaption=NULL,
                        DWORD      dwStyle=WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN|WS_CLIPSIBLINGS,
                        DWORD      dwExStyle=0);//=WS_EX_CLIENTEDGE);

#ifdef _DEBUG
    virtual char *GetClassName();
#endif

//    virtual void Dock();
//    virtual BOOL IsDocked();
//    virtual void UnDock();

    virtual void DrawWindow(CDC hDC);
    virtual void DrawWindow(CDC dc, CRect rect);
    CRect CalcClientRect();

    virtual int GetMinWidth();
    virtual int GetMinHeight();

    void DrawFocusRect(LPRECT lpRect, int nSize);

    // Message handlers
    virtual BOOL OnKeyDown(WORD vKeyCode, WORD nRepeat);
    virtual BOOL OnKillFocus(HWND hWnd);
    virtual BOOL OnLButtonDblClk(short x, short y, WORD vKeys);
    virtual BOOL OnLButtonDown(short x, short y, WORD vKeys);
    virtual BOOL OnLButtonUp(short x, short y, WORD vKeys);
    virtual BOOL OnMouseMove(short x, short y, WORD vKeys);
//    virtual BOOL OnEraseBkgnd(HDC hDC);
//    virtual BOOL OnPaint(HDC hDC);
    virtual BOOL OnSetFocus(HWND hWnd);
};

#ifdef _DEBUG
inline char *CDockView::GetClassName()
{
    return "CDockView";
}
#endif

#endif // DOCVIEW_H