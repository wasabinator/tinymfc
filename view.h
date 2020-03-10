#ifndef VIEW_H
#define VIEW_H

#include "window.h"

class CDC;

class CView : public CWnd
{
protected:
    CView *m_pwndContainer;
    BOOL m_bDocked;
    BOOL m_bBackground; // is background window (other windows are docked about this one)
    int m_nWidth, m_nHeight; // used when not docked
    int m_nSize; // used when docked

public:
    CView();
    ~CView();

    void SetContainer(CView *pwndContainer);
    CView *GetContainer();

    BOOL Create(HINSTANCE  hInstance,
                HWND 	   hWndParent);

    int GetWidth();
    void SetWidth(int nWidth);
    int GetHeight();
    void SetHeight(int nHeight);
    int GetSize();
    virtual void SetSize(int nSize);

#ifdef _DEBUG
    virtual char *GetClassName();
#endif

    virtual void Dock();
    virtual BOOL IsDocked();
    virtual void UnDock();
    virtual BOOL CanClose();

    virtual BOOL IsBackground();
    void SetBackground();

    virtual void DrawWindow(CDC hDC);
    virtual int GetMinWidth();
    virtual int GetMinHeight();

    // Message handlers
    virtual BOOL OnEraseBkgnd(HDC hDC);
    virtual BOOL OnPaint(HDC hDC);
};

#ifdef _DEBUG
inline char *CView::GetClassName()
{
    return "CView";
}
#endif

inline void CView::SetContainer(CView *pwndContainer)
{
    m_pwndContainer = pwndContainer;
}

inline CView *CView::GetContainer()
{
    return m_pwndContainer;
}

inline int CView::GetWidth()
{
    return m_nWidth;
}

inline void CView::SetWidth(int nWidth)
{
    m_nWidth = nWidth;
}

inline int CView::GetHeight()
{
    return m_nHeight;
}

inline void CView::SetHeight(int nHeight)
{
    m_nHeight = nHeight;
}

inline int CView::GetSize()
{
    return m_nSize;
}

inline void CView::SetSize(int nSize)
{
    m_nSize = nSize;
}

inline int CView::GetMinWidth()
{
    return 0;//4;
}

inline int CView::GetMinHeight()
{
    return 0;//4;
}

inline void CView::Dock()
{
    m_bDocked = TRUE;
}

inline BOOL CView::IsDocked()
{
    return m_bDocked;
}

inline void CView::UnDock()
{
    m_bDocked = FALSE;
}

inline BOOL CView::CanClose()
{
    return TRUE;
}

inline BOOL CView::IsBackground()
{
    return m_bBackground;
}

inline void CView::SetBackground()
{
    m_bBackground = TRUE;
}

#endif // VIEW_H