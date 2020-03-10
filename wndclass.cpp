#include "wndclass.h"

CWndClass::CWndClass(LPCTSTR lpszClassName, HINSTANCE hInst)
{
	// Default all entries to zero
	memset(&wcex, 0, sizeof(wcex));

   // Set size of WNDCLASSEX
	wcex.cbSize = sizeof(WNDCLASSEX);

   // Set class name and instance
   wcex.lpszClassName = lpszClassName;
   wcex.hInstance = hInst;
}

CWndClass::~CWndClass()
{
	// Unregister the associated window class -- don't care if fails
	UnregisterClass(wcex.lpszClassName, wcex.hInstance);
}

ATOM CWndClass::Register()
{
	return RegisterClassEx(&wcex);
}

