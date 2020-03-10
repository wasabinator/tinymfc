#ifndef RECT_H
#define RECT_H

#include <windows.h>

class CRect : public RECT
{
public:
    CRect();
    CRect(LONG left, LONG top, LONG right, LONG bottom);

    void SetRect(LONG left, LONG top, LONG right, LONG bottom);

    LONG GetWidth();
    LONG GetHeight();
    void SetWidth(LONG nWidth);
    void SetHeight(LONG nHeight);

    POINT GetTopLeft();
    POINT GetBottomLeft();
    POINT GetTopRight();
    POINT GetBottomRight();

    void Inflate(int dx, int dy);
    void UnionRect(LPRECT lpRect);
    void ClientToScreen(HWND hWnd);

    void SetOrigin(POINT &pt);
    void SetOrigin(LONG nLeft, LONG nTop);

    void OffsetRect(POINT &pt);
    void OffsetRect(LONG dx, LONG dy);

    BOOL PtInRect(POINT aPoint);
    BOOL PtInRect(int x, int y);

    operator LPRECT();

    const CRect& CRect::operator=(const CRect &rectSrc);
};

inline CRect::CRect()
{
	left = top = right = bottom = 0;
}

inline CRect::CRect(LONG left, LONG top, LONG right, LONG bottom)
{
    this->left = left;
    this->top = top;
    this->right = right;
    this->bottom = bottom;
}

inline LONG CRect::GetWidth()
{
	return right - left;
}

inline LONG CRect::GetHeight()
{
	return bottom - top;
}

inline void CRect::Inflate(int dx, int dy)
{
    InflateRect(this, dx, dy);
}

inline void CRect::ClientToScreen(HWND hWnd)
{
    POINT pt1 = GetTopLeft(),
          pt2 = GetBottomRight();

    ::ClientToScreen(hWnd, &pt1);
    ::ClientToScreen(hWnd, &pt2);

    left = pt1.x;
    top = pt1.y;
    right = pt2.x;
    bottom = pt2.y;
}

inline void CRect::SetWidth(LONG nWidth)
{
	right = left + nWidth;
}

inline void CRect::SetHeight(LONG nHeight)
{
	bottom = top + nHeight;
}

inline BOOL CRect::PtInRect(POINT aPoint)
{
    return ::PtInRect(this, aPoint);
}

inline CRect::operator LPRECT()
{
	return this;
}

#endif // RECT_H
