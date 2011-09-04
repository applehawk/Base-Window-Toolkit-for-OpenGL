#include <stdio.h>
#include <stdlib.h>

#include "basic_types.h"
#include "system.h"

#define WIN32_CLASSNAME "XCEWin32WndClass"

static LONG WINAPI WindowProc ( HWND hWnd, UINT iMsg, 
															 WPARAM wParam, LPARAM lParam );

static uint32 classregistercount = 1;

static uint16 key_code_map[] =
{
	Key_F1,//
};

bool init_window_context(LocalhostContext* lhctx)
{
	WNDCLASSEXA wcex; 

	memset(lhctx, 0, sizeof( LocalhostContext ) );
	memset(&wcex, 0, sizeof(WNDCLASSEX));

	lhctx->moduleInstance = GetModuleHandle(NULL);
	sprintf( lhctx->classname, "%s%d", WIN32_CLASSNAME, classregistercount );
	classregistercount++;

	// Register the window class for the main window. 
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_OWNDC; 
	wcex.lpfnWndProc = (WNDPROC)WindowProc; 
	wcex.cbClsExtra = 32; 
	wcex.cbWndExtra = 32; 
	wcex.hInstance = lhctx->moduleInstance; 
	wcex.hIcon = LoadIcon((HINSTANCE) NULL, IDI_APPLICATION); 
	wcex.hCursor = LoadCursor((HINSTANCE) NULL, IDC_ARROW); 
	wcex.hbrBackground = NULL; 
	wcex.lpszMenuName = "MainMenu"; 
	wcex.lpszClassName = lhctx->classname; 

	if( !RegisterClassExA( &wcex ) ) {
		return false;
	}

	return true;
}

void destroy_context(LocalhostContext* wctx)
{
	UnregisterClassA(wctx->classname, wctx->moduleInstance);
}

void destroy_window(WindowContext* wnd)
{
	DestroyWindow(wnd->hwnd);
}

void create_window(LocalhostContext* wctx, WindowContext* wnd, char* title, int x, int y, int width, int height, int properties)
{
   HWND      hwnd;
   HMENU	 hmenu;
   RECT      rect;
   DWORD	 wintype;

   hmenu = NULL;
   /* set window style properties */

   if ( properties & WINDOWPROP_STANDARD ) {
	   wintype = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		   | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
   } else if ( properties & WINDOWPROP_POPUP ) {
	   wintype = WS_POPUP;
   } else if ( properties & WINDOWPROP_NODRESSING ) {
	   wintype = WS_OVERLAPPED | WS_CAPTION;
   } else {
	   wintype = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		   | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
   }

   /* set window border style properties */

   if ( properties & WINDOWPROP_THICKBORDER ) {
	   wintype = wintype | WS_THICKFRAME;
   } else if ( properties & WINDOWPROP_THINBORDER ) {
	   wintype = wintype | WS_BORDER;
   } else if ( properties & WINDOWPROP_NOBORDER ) {
   } else {
	   wintype = wintype | WS_THICKFRAME;
   }

   rect.left   = 0;
   rect.top    = 0;
   rect.right  = width;
   rect.bottom = height;

   AdjustWindowRect( &rect, wintype, NULL );

   rect.right = rect.right+abs(rect.left);
   rect.bottom = rect.bottom+abs(rect.top);

   rect.left   = x;
   rect.top    = y;
/*
	 LPCWSTR wsTitle, wsClassName;
	 INT iSize, iMultiByteSize;

	 iSize = mbstowcs(NULL, title, 0);
	 wsTitle = (WCHAR*)malloc((iSize + 1)*sizeof( wchar_t ));
	 mbstowcs((wchar_t*)wsTitle, title, iSize + 1);

	 iSize = mbstowcs(NULL, wctx->classname, 0);
	 wsClassName = (WCHAR*)malloc((iSize + 1)*sizeof( wchar_t ));
	 mbstowcs((wchar_t*)wsClassName, wctx->classname, iSize + 1);*/

   hwnd = CreateWindow(
	   wctx->classname,              /* pointer to registered class name */
	   title,                         /* pointer to window name */
	   wintype,                       /* window style */
	   rect.left,                     /* horizontal position of window */
	   rect.top,                      /* vertical position of window */
	   rect.right,                    /* window width */
	   rect.bottom,                   /* window height */
	   0,                             /* handle to parent or owner window */
	   hmenu,                         /* handle to menu */
	   wctx->moduleInstance,          /* handle to application instance */
	   0                              /* pointer to window-creation data */
	   );

   /* store the cpw context pointer with the class */

   //SetClassLongPtr( hwnd, 0, (LONG_PTR) wctx );

   /* store the cpw window id with the window */

   ShowWindow( hwnd, SW_SHOW );
   SetForegroundWindow( hwnd );

   wnd->hwnd = hwnd;
	 wnd->style = properties;
	 wnd->hdc = GetDC(hwnd);
}

void process_events(uint32 count)
{
	MSG event;
	while(count > 0)
	{
		if(PeekMessage(&event, NULL,  0, 0, PM_REMOVE)) 
		{
			//ToDo
		}
		--count;
	}
}

static LRESULT WINAPI WindowProc ( HWND hWnd, UINT iMsg, 
							   WPARAM wParam, LPARAM lParam )
{
	return DefWindowProc( hWnd, iMsg, wParam, lParam );
}

void set_window_data( WindowContext* wctx, int data )
{
	SetWindowLongPtr(wctx->hwnd, GWLP_USERDATA, data);
}