#include "splitter.h"
#include "wndclass.h"
#include "dc.h"
//#include "resource.h"

#include "mainwnd.h"
#include "globals.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>

#include <tchar.h>

CSplitterWnd::CSplitterWnd()
             :m_nLastBackgroundAdjust(0)
{
}

CSplitterWnd::~CSplitterWnd()
{
    int nChildren = m_listViews.size();

    //if (m_listViews.size() > 1) <-- now safe to delet all child cviews too
    //{
        // if splitter contains allocated splitters as children
        // (always the case if size > 1), then delete them

        CViewList::iterator i;

        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
            delete *i;
    //}

    // clear out the two lists
    m_listViews.clear();
    //m_listSizes.clear();
}

BOOL CSplitterWnd::AddView(CView *pwndView, int nSize, CView *pwndRelativeView, BOOL bAfter)
{
    BOOL bRC = FALSE;
    CSplitterWnd *pwndSplitter1, *pwndSplitter2;

    CViewList::iterator i;

    pwndView->SetSize(nSize);

    if (pwndRelativeView == NULL)
        i = m_listViews.end();
    else
    {
        // find position of the relative view
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
            if (*i == pwndRelativeView)
                break;

        assert (*i == pwndRelativeView);

        if (bAfter)
            ++i;
    }

    switch(m_listViews.size())
    {
    case 0:
        // splitter can contain one child view directly, otherwise must contain
        // splitters as children to house the views
        m_listViews.insert(m_listViews.end(), pwndView);
        pwndView->SetParent(*this);
        pwndView->SetContainer(this);

        bRC = TRUE;
        break;

    case 1:
        // if adding second view, then create 2 splitters as children and add child
        // views to these
        if ((pwndSplitter1 = new CSplitterWnd()) && 
            (pwndSplitter1->Create(g_hInstance, GetHWnd())) &&
            (pwndSplitter2 = new CSplitterWnd()) &&
            (pwndSplitter2->Create(g_hInstance, GetHWnd())))
        {
            if (bAfter)
            {
                pwndSplitter1->AddView(*m_listViews.begin(), (*m_listViews.begin())->GetSize());
                pwndSplitter1->SetSize((*m_listViews.begin())->GetSize());
                *m_listViews.begin() = pwndSplitter1;
                m_listViews.insert(m_listViews.end(), pwndSplitter2);
                pwndSplitter2->AddView(pwndView, nSize);
                pwndSplitter2->SetSize(nSize);
                pwndSplitter1->SetContainer(this);
                pwndSplitter2->SetContainer(this);
            }
            else
            {
                pwndSplitter2->AddView(*m_listViews.begin(), (*m_listViews.begin())->GetSize());
                pwndSplitter2->SetSize((*m_listViews.begin())->GetSize());
                *m_listViews.begin() = pwndSplitter1;
                m_listViews.insert(m_listViews.end(), pwndSplitter2);
                pwndSplitter1->AddView(pwndView, nSize);
                pwndSplitter1->SetSize(nSize);
                pwndSplitter1->SetContainer(this);
                pwndSplitter2->SetContainer(this);
            }

            bRC = TRUE;
        }
        else
        {
            if (pwndSplitter1) delete pwndSplitter1;
            if (pwndSplitter2) delete pwndSplitter2;
        }

        break;

    default:
        // add splitter into next pane and add view to this splitter
        if ((pwndSplitter1 = new CSplitterWnd()) && 
            (pwndSplitter1->Create(g_hInstance, GetHWnd())))
        {
            // Add splitter to end
            pwndSplitter1->SetSize(nSize);
            pwndSplitter1->AddView(pwndView, nSize);

            m_listViews.insert(i, pwndSplitter1);

            pwndSplitter1->SetContainer(this);
            bRC = TRUE;
        }
        else
            delete pwndSplitter1;

        break;
    }

    return bRC;
}

BOOL CSplitterWnd::SplitView(CView *pwndView, CView *pwndNewView, int nSize, int nOrientation, BOOL bAfter)
{    
    CSplitterWnd *pwndSplitter = (CSplitterWnd*)pwndView->GetContainer();

    pwndSplitter->m_nOrientation = nOrientation;

    if (pwndSplitter->m_listViews.size() == 1 && pwndSplitter->GetContainer() && 
        ((CSplitterWnd*)pwndSplitter->GetContainer())->m_nOrientation == nOrientation)
    {
        pwndView = pwndSplitter;
        pwndSplitter = (CSplitterWnd*)pwndSplitter->GetContainer();
    }

    return pwndSplitter->AddView(pwndNewView, nSize, pwndView, bAfter);
}

void CSplitterWnd::Dock()
{
    CView::Dock();

    Show();
    if (m_pwndContainer)
        ((CSplitterWnd*)m_pwndContainer)->Dock();

    Layout();
}

void CSplitterWnd::UnDock()
{
    CView::UnDock();

    Hide();
    if (m_pwndContainer)
    {
        if (((CSplitterWnd*)m_pwndContainer)->DockedViews() == 0)
            ((CSplitterWnd*)m_pwndContainer)->UnDock();
//        else
//            ((CSplitterWnd*)m_pwndContainer)->Layout();
    }
}

void CSplitterWnd::RemoveView(CView *pwndView)
{
    CViewList::iterator i;

    // find the view to delete
    for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        if ((*i) == pwndView)
        {
            (*i)->SetContainer(NULL);
            (*i)->SetParent(g_pwndMain->GetHWnd());
            m_listViews.erase(i);
            break;
        }

    if (m_listViews.size()==0)
    {
        if (m_pwndContainer)
            ((CSplitterWnd*)m_pwndContainer)->RemoveSplitter(this);

        delete this;
    }
}

void CSplitterWnd::RemoveSplitter(CSplitterWnd *pwndSplitter)
{
    CViewList::iterator i;

    for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        if ((*i) == pwndSplitter)
        {
            pwndSplitter->SetContainer(NULL);
            pwndSplitter->SetParent(g_pwndMain->GetHWnd());

            m_listViews.erase(i);
            break;
        }

    if (m_listViews.size() == 1)
    {
        pwndSplitter = (CSplitterWnd*)*m_listViews.begin();

        //SetWidth(pwndSplitter->GetWidth()); //50
        //SetHeight(pwndSplitter->GetHeight()); //50
        //SetSize(pwndSplitter->GetSize()); //100
        m_nOrientation = pwndSplitter->m_nOrientation;
        m_listViews.clear();

        // copy child's views

        for (i=pwndSplitter->m_listViews.begin(); i!=pwndSplitter->m_listViews.end(); ++i)
        {
            m_listViews.insert(m_listViews.end(), *i);
            (*i)->SetContainer(this); // move child to this container
            (*i)->SetParent(GetHWnd());
            //(*i)->SetSize(50);
        }
        
        // now clear the child splitter's view list (must do or it will delete the views)
        pwndSplitter->m_listViews.clear();
        pwndSplitter->SetContainer(NULL);
        delete pwndSplitter;
    }
}

BOOL CSplitterWnd::IsBackground()
{
    CViewList::iterator i;

    for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        if (((CView*)*i)->IsBackground())
            return TRUE;
    
    return FALSE;
}

int CSplitterWnd::DockedViews()
{
    int nCount = 0;
    CViewList::iterator i;

    for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        if ((*i)->IsDocked())
            nCount++;

    return nCount;
}

BOOL CSplitterWnd::Create(HINSTANCE hInstance,
                          HWND      hWndParent,
                          int       nOrientation)
{
    CWndClass wc((nOrientation==SPLITTER_HORZ)?_T("TFC_SplitterH"):_T("TFC_SplitterV"), hInstance);  // Window class for main window

    wc.SetStyle(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW);
    wc.SetWndProc((WNDPROC)::WndProc);
    //wc.SetCursor(LoadCursor(NULL, (nOrientation==SPLITTER_HORZ)?IDC_SIZENS:IDC_SIZEWE)); // Use standard sizing cursor
    //wc.SetBackground(CreateSolidBrush(GetSysColor(COLOR_3DFACE)));
    wc.Register(); // Attempt to register the class

    m_nOrientation = nOrientation;

    return CWnd::Create(wc, NULL, hWndParent, WS_CHILD|WS_VISIBLE|WS_CLIPSIBLINGS, 0);
}

// Message handlers
void CSplitterWnd::DrawWindow(CDC dc)
{
    CRect rect;

    // exclude child regions from painting area
    CViewList::iterator i;

    Layout();

    for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
    {
        if ((*i)->IsDocked())
        {
            rect = (*i)->GetWindowRect();
            ScreenToClient(rect);
            ExcludeClipRect(dc, rect.left, rect.top, rect.right, rect.bottom);
        }
    }

    HBRUSH hBrush = CreateSolidBrush(GetSysColor(COLOR_3DFACE));
        
    FillRect(dc, GetClientRect(), hBrush);

    DeleteObject((HGDIOBJ)hBrush);
}

int CSplitterWnd::GetMinWidth()
{
    int nMinWidth=0;

    CViewList::iterator i;

    if (m_nOrientation == SPLITTER_VERT)
    {
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        {
            if ((*i)->IsDocked())
                nMinWidth += (*i)->GetMinWidth() + SPLITTER_SIZE;
        }
        if (nMinWidth) // if there are any docked views
            nMinWidth -= SPLITTER_SIZE; // remove last one
    }
    else
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        {
            if ((*i)->IsDocked() && nMinWidth < (*i)->GetMinWidth())
                nMinWidth = (*i)->GetMinWidth();
        }

    return nMinWidth;
}

int CSplitterWnd::GetMinHeight()
{
    int nMinHeight=0;

    CViewList::iterator i;

    if (m_nOrientation == SPLITTER_HORZ)
    {
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        {
            if ((*i)->IsDocked())
                nMinHeight += (*i)->GetMinHeight() + SPLITTER_SIZE;
        }
        if (nMinHeight) // if there are any docked views
            nMinHeight -= SPLITTER_SIZE; // remove last one
    }
    else
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        {
            if ((*i)->IsDocked() && nMinHeight < (*i)->GetMinHeight())
                nMinHeight = (*i)->GetMinHeight();
        }

    return nMinHeight;
}

// message handlers
BOOL CSplitterWnd::OnKeyDown(WORD vKeyCode, WORD nRepeat)
{
    if (vKeyCode == VK_ESCAPE)
    {
//        m_nSplitPos = m_nSplitDrag;
//        Layout(m_nSplitPos);

        DrawFocusRect(m_nDragRect, SPLITTER_SIZE);
        ReleaseCapture();
        ReleaseFocus();

        return TRUE;
    }
    else
        return FALSE;
}

BOOL CSplitterWnd::OnLButtonDown(short x, short y, WORD vKeys)
{
    m_nDragRect = GetClientRect();

    CViewList::iterator i;

    int  m_nSplitPos=0;
    BOOL bFound=false;

    if (m_nOrientation == SPLITTER_HORZ)
    {
        m_nSplitPos = m_nDragRect.top;
        
        for (i=m_listViews.begin(); i!=m_listViews.end() && !bFound; ++i)
        {
            if ((*i)->IsDocked())
            {
                m_nSplitPos += (*i)->GetClientRect().GetHeight();

                if (y >= m_nSplitPos && y <= m_nSplitPos + SPLITTER_SIZE)
                {
                    bFound = true;
                    m_nDragRect.SetRect(0, m_nSplitPos, m_nDragRect.GetWidth(), SPLITTER_SIZE);
                    ClientToScreen(m_nDragRect);  // convert to screen coords
                    m_nDragPos = y;
                    m_nDragOrigin = m_nDragRect.top;

                    // Get minimum vertical dimensions
                    m_iSplitPane1 = i; // store current pane
                    m_nMinDragSize = (*i)->GetMinHeight() - (*i)->GetClientRect().GetHeight();

                    ++i;
                    while (i != m_listViews.end() // 1st clause should _never_ happen
                          && !(*i)->IsDocked())   // but is good practice
                    {                                
                        ++i; // go to second visible pane
                    }

                    // rounding errors in the splitter scaling code would cause this to assert
                    assert(i != m_listViews.end());

                    m_iSplitPane2 = i;
                    m_nMaxDragSize = (*i)->GetClientRect().GetHeight() - (*i)->GetMinHeight();
                }
                else
                    m_nSplitPos += SPLITTER_SIZE;
            }
        }
    }
    else
    {
        m_nSplitPos = m_nDragRect.left;

        for (i=m_listViews.begin(); i!=m_listViews.end() && !bFound; ++i)
        {
            if ((*i)->IsDocked())
            {
                m_nSplitPos += (*i)->GetClientRect().GetWidth();

                if (x >= m_nSplitPos && x <= m_nSplitPos + SPLITTER_SIZE)
                {
                    bFound = true;
                    m_nDragRect.SetRect(m_nSplitPos, 0, SPLITTER_SIZE, m_nDragRect.GetHeight());
                    ClientToScreen(m_nDragRect);  // convert to screen coords
                    m_nDragPos = x;
                    m_nDragOrigin = m_nDragRect.left;

                    // Get minimum vertical dimensions
                    m_iSplitPane1 = i; // store current pane
                    m_nMinDragSize = (*i)->GetMinWidth() - (*i)->GetClientRect().GetWidth();

                    ++i; // go to second pane
                    while (i != m_listViews.end() // 1st clause should _never_ happen
                          && !(*i)->IsDocked())   // but is good practice
                    {
                        ++i; // go to second visible pane
                    }

                    // rounding errors in the splitter scaling code would cause this to assert
                    assert(i != m_listViews.end());

                    m_iSplitPane2 = i;
                    m_nMaxDragSize = (*i)->GetClientRect().GetWidth() - (*i)->GetMinWidth();
                }
                else
                    m_nSplitPos += SPLITTER_SIZE;
            }
        }
    }

    if (bFound) // should always be the case with a splitter, but just to be sure...
    {
        SetCapture();
        SetFocus();

        DrawFocusRect(m_nDragRect, SPLITTER_SIZE);
    }

    return TRUE;
}

BOOL CSplitterWnd::OnLButtonUp(short x, short y, WORD vKeys)
{
    if (HasCapture())
    {
        DrawFocusRect(m_nDragRect, SPLITTER_SIZE);

        ReleaseCapture();
        ReleaseFocus();

        int pos;

        if (m_nOrientation == SPLITTER_HORZ)
            pos = y - m_nDragPos;
        else
            pos = x - m_nDragPos;

        if (pos < m_nMinDragSize)
            pos = m_nMinDragSize;
        else
        if (pos > m_nMaxDragSize)
            pos = m_nMaxDragSize;

        if (pos)
        {
            if (m_pwndContainer)
            {
                int s1, size;
                int total = (*m_iSplitPane1)->GetSize() +
                            (*m_iSplitPane2)->GetSize();

                if (m_nOrientation == SPLITTER_HORZ)
                {
                    size  = (*m_iSplitPane1)->GetClientRect().GetHeight() +
                            (*m_iSplitPane2)->GetClientRect().GetHeight();

                    s1 = (*m_iSplitPane1)->GetClientRect().GetHeight() + pos;
                }
                else
                {
                    size  = (*m_iSplitPane1)->GetClientRect().GetWidth() +
                            (*m_iSplitPane2)->GetClientRect().GetWidth();

                    s1 = (*m_iSplitPane1)->GetClientRect().GetWidth() + pos;
                }
                
                (*m_iSplitPane1)->SetSize((int)((float)s1 * ((float)(total) / (float)(size))+0.5));
                (*m_iSplitPane2)->SetSize(total - (*m_iSplitPane1)->GetSize());
            }
            else
            {
                (*m_iSplitPane1)->SetSize((*m_iSplitPane1)->GetSize() + pos);
                (*m_iSplitPane2)->SetSize((*m_iSplitPane2)->GetSize() - pos);
            }

            Layout();
        }
    }

    return TRUE;
}

BOOL CSplitterWnd::OnMouseMove(short x, short y, WORD vKeys)
{
    if (HasCapture())
    {
        DrawFocusRect(m_nDragRect, SPLITTER_SIZE);

        CRect rect = GetClientRect();
        int pos = m_nSplitPos;

        if (m_nOrientation == SPLITTER_HORZ)
        {
            pos = y - m_nDragPos;

            if (pos < m_nMinDragSize)
                pos = m_nMinDragSize;
            else
            if (pos > m_nMaxDragSize)
                pos = m_nMaxDragSize;

            m_nDragRect.SetOrigin(m_nDragRect.left, m_nDragOrigin + pos);
        }
        else
        {
            pos = x - m_nDragPos;

            if (pos < m_nMinDragSize)
                pos = m_nMinDragSize;
            else
            if (pos > m_nMaxDragSize)
                pos = m_nMaxDragSize;

            m_nDragRect.SetOrigin(m_nDragOrigin + pos, m_nDragRect.top);
        }

        DrawFocusRect(m_nDragRect, SPLITTER_SIZE);

        return TRUE;
    }

    return FALSE;
}

BOOL CSplitterWnd::OnSetCursor(WORD wHitTest, WORD wIdentifier)
{
    SetCursor(LoadCursor(NULL, (m_nOrientation==SPLITTER_HORZ)?IDC_SIZENS:IDC_SIZEWE));

    return TRUE;
}

void CSplitterWnd::Layout()
{
    CViewList::iterator i;
    CSizeList::iterator j;

    int size, total=0, extra, pos=0, nVisible=0;
    int nSquash=0; // used when views are shrunken below minmums
    CSizeList listSizes;

    CRect rect = GetClientRect();

    for (i=m_listViews.begin(), j=listSizes.begin(); i!=m_listViews.end(); ++i, ++j)
    {
        if ((*i)->IsDocked())
        {
            total += (*i)->GetSize();
            nVisible++;
        }
        listSizes.insert(listSizes.end(), (*i)->GetSize());
    }

    if (m_nOrientation == SPLITTER_HORZ)
        size = rect.GetHeight() - ((nVisible-1) * SPLITTER_SIZE);
    else
        size = rect.GetWidth() - ((nVisible-1) * SPLITTER_SIZE);

    if (!m_pwndContainer) // if top level, allocate any left over space to background
    {
        for (i=m_listViews.begin(), j=listSizes.begin(); i!=m_listViews.end(); ++i, ++j)
            if ((*i)->IsBackground())
            {
                (*j) = (*i)->GetSize() + size - total;
                break;
            }
    }
    else
    {
        // scale all windows
        extra = size;

        for (i=m_listViews.begin(), j=listSizes.begin(); i!=m_listViews.end(); ++i, ++j)
            if ((*i)->IsDocked())
            {
                (*j) = (int)(((float)(*j) * ((float)(size) / (float)(total)))+0.5);
                extra -= (*j);
            }

        if (extra)
        {
            do
            {
                --i; --j;
                if ((*i)->IsDocked())
                {
                    *j += extra;
                    break;
                }

                --i; --j;
            }
            while (i != m_listViews.begin());
        }
    }

    // make sure all windows fullfill minimum size criteria
    nSquash = ValidateLayout(listSizes, nSquash);

    // call second time to shrink leading windows
    nSquash = ValidateLayout(listSizes, nSquash);

    if (nSquash) ::MessageBeep(0); // shouldn't get this

    HDWP hdwp = BeginDeferWindowPos(nVisible);

    for (i=m_listViews.begin(), j=listSizes.begin(); i!=m_listViews.end(); ++i, ++j)
    {
        if ((*i)->IsDocked())
        {
            if (m_nOrientation == SPLITTER_HORZ)
            {
                ::DeferWindowPos(hdwp, (*i)->GetHWnd(), NULL,
                                 0, pos, rect.GetWidth(), (*j),
                                 SWP_NOACTIVATE | SWP_NOZORDER);
            }
            else
            {
                ::DeferWindowPos(hdwp, (*i)->GetHWnd(), NULL,
                                 pos, 0, (*j), rect.GetHeight(),
                                 SWP_NOACTIVATE | SWP_NOZORDER);
            }

            pos += (*j) + SPLITTER_SIZE;
        }
    }

    EndDeferWindowPos(hdwp);

    if (m_listViews.size() > 1)
        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
            ((CSplitterWnd*)(*i))->Layout();
}

int CSplitterWnd::ValidateLayout(CSizeList &listSizes, int nSquash)
{
    CViewList::iterator i;
    CSizeList::iterator j;

    int viewsize;
    int nMinWidth;
    int nMinHeight;

    for (i=m_listViews.begin(), j=listSizes.begin(); i!=m_listViews.end(); ++i, ++j)
    {
        viewsize = (*j);

        // check to make sure this isn't below view's minimum size
        if (m_nOrientation == SPLITTER_VERT)
        {
            nMinWidth = (*i)->GetMinWidth();
            if (viewsize < nMinWidth)
            {
                nSquash += (nMinWidth - viewsize);
                viewsize = nMinWidth;
            }
            else
            if (nSquash)
            {
                if ((viewsize - nMinWidth) > nSquash)
                {
                    viewsize -= nSquash;
                    nSquash = 0;
                }
                else
                {
                    nSquash -= (viewsize - nMinWidth);
                    viewsize = nMinWidth;
                }
            }
        }
        else
        {
            nMinHeight = (*i)->GetMinHeight();
            if (viewsize < nMinHeight)
            {
                nSquash += (nMinHeight - viewsize);
                viewsize = nMinHeight;
            }
            else
            if (nSquash)
            {
                if ((viewsize - nMinHeight) > nSquash)
                {
                    viewsize -= nSquash;
                    nSquash = 0;
                }
                else
                {
                    nSquash -= (viewsize - nMinHeight);
                    viewsize = nMinHeight;
                }
            }
        }
        (*j) = viewsize;
    }

    return nSquash;
}

void CSplitterWnd::DrawFocusRect(LPRECT lpRect, int nSize)
{
    CRect rect(lpRect->left, lpRect->top, lpRect->right, lpRect->bottom);
    CDC dc = ::GetWindowDC(GetDesktopWindow());

    HBRUSH  hBrush, hOBrush ;
    HBITMAP hBitmap;

    static WORD Dots[] = {0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa}; 

    hBitmap = CreateBitmap( 8, 8, 1, 1, ( LPSTR ) Dots );
    hBrush = CreatePatternBrush( hBitmap );

    hOBrush = (HBRUSH)SelectObject(dc, hBrush);

    if (m_nOrientation == SPLITTER_HORZ)
        PatBlt(dc, rect.left, rect.top, rect.GetWidth(), nSize, PATINVERT);
    else
        PatBlt(dc, rect.left, rect.top, nSize, rect.GetHeight(), PATINVERT);

    SelectObject(dc, hOBrush);
    DeleteObject(hBrush);
    DeleteObject(hBitmap);
}

// TODO: change to GetChildFromPoint(int x, int y, view viewToSkip //= NULL) 
// get child from point
// this is where the docking code all starts.  determines which child is at a given screen coord
CView *CSplitterWnd::GetChildFromPoint(int x, int y, CView *pwndViewToSkip)
{
    CRect rect = GetWindowRect();

    if (rect.PtInRect(x, y)) // x, y in window?  investigate further
    {
        CViewList::iterator i;
        int nSplitPos=0;

        for (i=m_listViews.begin(); i!=m_listViews.end(); ++i)
        {
            if ((*i)->IsDocked())// && ((*i) != pwndViewToSkip))
            {
                //nSplitPos += (*i)->GetSize();

                if (m_nOrientation == SPLITTER_HORZ)
                {
                    nSplitPos += (*i)->GetClientRect().GetHeight();
                    if (y <= rect.top + nSplitPos)
                    {
                        if (m_listViews.size() > 1)
                            return ((CSplitterWnd*)(*i))->GetChildFromPoint(x, y, pwndViewToSkip); // child is splitter
                        else
                            return (*i); // return reference to child
                    }
                    else
                    if (y <= rect.top + nSplitPos + SPLITTER_SIZE) // mouse over splitter frame
                    {
                        if (m_listViews.size() > 1)
                            return ((CSplitterWnd*)(*i))->GetChildFromPoint(x, y-SPLITTER_SIZE, pwndViewToSkip); // child is splitter
                        else
                            return (*i); // return reference to child
                    }
                }
                else
                {
                    nSplitPos += (*i)->GetClientRect().GetWidth();
                    if (x <= rect.left + nSplitPos)
                    {
                        if (m_listViews.size() > 1)
                            return ((CSplitterWnd*)(*i))->GetChildFromPoint(x, y, pwndViewToSkip); // child is splitter
                        else
                            return (*i); // return reference to child
                    }
                    else
                    if (x <= rect.left + nSplitPos + SPLITTER_SIZE) // mouse over splitter frame
                    {
                        if (m_listViews.size() > 1)
                            return ((CSplitterWnd*)(*i))->GetChildFromPoint(x-SPLITTER_SIZE, y, pwndViewToSkip); // child is splitter
                        else
                            return (*i); // return reference to child
                    }
                }

                nSplitPos += SPLITTER_SIZE;
            }
        }
    }

    return NULL;
}   

void CSplitterWnd::SetSize(int nSize)
{
    if (m_listViews.size()==1)
    {
        // this is a container splitter, so set child views dimensions as well

        if (m_nOrientation == SPLITTER_HORZ)
            (*m_listViews.begin())->SetHeight(nSize);
        else
            (*m_listViews.begin())->SetWidth(nSize);        

        (*m_listViews.begin())->SetSize(nSize);
    }

    CView::SetSize(nSize);
}