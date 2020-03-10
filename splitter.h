#ifndef SPLITTER_H
#define SPLITTER_H

#include "window.h"
#include "view.h"
#include "rect.h"

#include <list> // Include STL list

#define SPLITTER_SIZE 5
#define SPLITTER_HORZ 0
#define SPLITTER_VERT 1

using namespace std;

typedef list<CView *> CViewList;
typedef list<int> CSizeList;

class CDC;

class CSplitterWnd : public CView
{
protected:
    CViewList m_listViews;

    //CWnd *m_pViews[2];
    int m_nOrientation;
    //int m_nSplit,      // split index no
    int m_nSplitPos,   // pos of split bar
        m_nDragOrigin, // start position of dragbar
        m_nDragPos;    // pixel position (x or y depending on orientation) where 
                       // mouse started dragging
    CViewList::iterator m_iSplitPane1, m_iSplitPane2; // for panes selected for splitting
    int m_nMinDragSize,
        m_nMaxDragSize;

    virtual void SetSize(int nSize);
    CRect m_nDragRect;
    int m_nLastBackgroundAdjust; // value used for adjusting size of background window when
                                 // windows are docked and undocked around it
    //short m_nXDrag, m_nYDrag, m_nSplitDrag;

public:
    CSplitterWnd();
    ~CSplitterWnd();

    BOOL Create(HINSTANCE  hInstance,
                HWND       hWndParent,
                int        nOrientation=SPLITTER_HORZ);

    BOOL AddView(CView *pwndView, int nSize, CView *pwndRelativeView=NULL, BOOL bAfter=TRUE);
    static BOOL SplitView(CView *pwndView, CView *pwndNewView, int nSize, int nOrientation, BOOL bAfter=TRUE);

#ifdef _DEBUG
    virtual char *GetClassName();
#endif

    virtual void Dock();
    virtual void UnDock();
    virtual BOOL IsBackground();

    void DrawFocusRect(LPRECT lpRect, int nSize);
    void Layout();
    int ValidateLayout(CSizeList &listSizes, int nSquash);
    int DockedViews(); // returns count of docked views
    CView *GetChildFromPoint(int x, int y, CView *pwndViewToSkip = NULL);
    void RemoveView(CView *pwndView);
    void RemoveSplitter(CSplitterWnd *pwndSplitter);

    virtual void DrawWindow(CDC hDC);
    virtual int GetMinWidth();
    virtual int GetMinHeight();

    // Message handlers
    virtual BOOL OnKeyDown(WORD vKeyCode, WORD nRepeat);
    virtual BOOL OnLButtonDown(short x, short y, WORD vKeys);
    virtual BOOL OnLButtonUp(short x, short y, WORD vKeys);
    virtual BOOL OnMouseMove(short x, short y, WORD vKeys);
    virtual BOOL OnSetCursor(WORD wHitTest, WORD wIdentifier);
};

#ifdef _DEBUG
inline char *CSplitterWnd::GetClassName()
{
    return "CSplitterWnd";
}
#endif

#endif // SPLITTER_H