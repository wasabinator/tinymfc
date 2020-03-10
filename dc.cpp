//#include "stdafx.h"

#include "dc.h"

//#define NDEBUG // Use for non-debug version
#include <assert.h>

int CDC::FillRect(CONST RECT *lprc, HBRUSH hbr)
{
    assert(m_hDC!=NULL);
    return ::FillRect(m_hDC, lprc, hbr);
}
