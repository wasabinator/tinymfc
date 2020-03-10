#ifndef WNDCLASS_H
#define WNDCLASS_H

#include <windows.h>

class CWndClass
{
	WNDCLASSEX wcex;
public:
   CWndClass(LPCTSTR lpszClassName, HINSTANCE hInst);
   ~CWndClass();

   void SetStyle(UINT style);
   void SetWndProc(WNDPROC lpfnWndProc);
   void SetClsExtra(int cbClsExtra);
   void SetWndExtra(int cbWndExtra);
   void SetIcon(HICON hIcon);
   void SetCursor(HCURSOR hCursor);
   void SetBackground(HBRUSH hbrBackGround);
   void SetMenuName(LPCTSTR lpszMenuName);
   void SetIconSm(HICON hIconSm);

   // Register the associated class
   ATOM Register();

	// Get methods

//   UINT 	  GetStyle();
//   WNDPROC GetWndProc();
//   int 	  GetClsExtra();
//   int     GetWndExtra();
   HANDLE  GetInstance();
//   HICON   GetIcon();
//   HCURSOR GetCursor();
//   HBRUSH  GetBackground();
//   LPCTSTR GetMenuName();
   LPCTSTR GetClassName();
//   HICON	  GetIconSm();
};

// Inlines
inline void CWndClass::SetStyle(UINT style) {
	wcex.style = style;
}

inline void CWndClass::SetWndProc(WNDPROC lpfnWndProc) {
	wcex.lpfnWndProc = lpfnWndProc;
}

inline void CWndClass::SetClsExtra(int cbClsExtra) {
	wcex.cbClsExtra = cbClsExtra;
}

inline void CWndClass::SetWndExtra(int cbWndExtra) {
	wcex.cbWndExtra = cbWndExtra;
}

inline void CWndClass::SetIcon(HICON hIcon) {
	wcex.hIcon = hIcon;
}

inline void CWndClass::SetCursor(HCURSOR hCursor) {
	wcex.hCursor = hCursor;
}

inline void CWndClass::SetBackground(HBRUSH hbrBackGround) {
	wcex.hbrBackground = hbrBackGround;
}

inline void CWndClass::SetMenuName(LPCTSTR lpszMenuName) {
	wcex.lpszMenuName = lpszMenuName;
}

inline void CWndClass::SetIconSm(HICON hIconSm) {
	wcex.hIconSm = hIconSm;
}

inline HANDLE CWndClass::GetInstance() {
	return wcex.hInstance;
}

inline LPCTSTR CWndClass::GetClassName() {
	return wcex.lpszClassName;
}

#endif // WNDCLASS_H
