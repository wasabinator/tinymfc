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

   void SetOrigin(POINT &pt);
   void SetOrigin(LONG nLeft, LONG nTop);

   operator LPRECT();

   const CRect& CRect::operator=(const CRect &rectSrc);
};

inline CRect::CRect()
{
	left = top = right = bottom = 0;
}

inline LONG CRect::GetWidth()
{
	return right - left;
}

inline LONG CRect::GetHeight()
{
	return bottom - top;
}

inline void CRect::SetWidth(LONG nWidth)
{
	right = left + nWidth;
}

inline void CRect::SetHeight(LONG nHeight)
{
	bottom = top + nHeight;
}

inline CRect::operator LPRECT()
{
	return this;
}

#endif // RECT_H
