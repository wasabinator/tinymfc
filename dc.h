#ifndef DC_H
#define DC_H

#include <windows.h>

class CDC
{
protected:
    HDC m_hDC;

public:
	CDC();
	CDC(HDC hDC);

    HDC GetHDC();

    int FillRect(CONST RECT *lprc, HBRUSH hbr);

    operator HDC();
};

inline CDC::CDC()
{
    m_hDC = NULL;
}

inline CDC::CDC(HDC hDC)
{
    m_hDC = hDC;
}

inline HDC CDC::GetHDC()
{
    return m_hDC;
}

inline CDC::operator HDC()
{
	return m_hDC;
}

#endif // DC_H