#include <windows.h>

//System specific interface

/* window style flags */

#define WINDOWPROP_STANDARD       0x00000001
#define WINDOWPROP_POPUP          0x00000002
#define WINDOWPROP_NODRESSING     0x00000004
#define WINDOWPROP_STYLECLRMASK   0xFFFFFF00

/* window border style flags */

#define WINDOWPROP_NOBORDER       0x00000100
#define WINDOWPROP_THINBORDER     0x00000200
#define WINDOWPROP_THICKBORDER    0x00000400
#define WINDOWPROP_BORDERCLRMASK  0xFFFFF0FF

typedef struct _LocalhostContext
{
	HINSTANCE moduleInstance;
	CHAR classname[50];
} LocalhostContext, *LPLocalhostContext;

typedef struct _WindowContext
{
	HWND hwnd;
	HDC hdc;
	HGLRC glrc;
	int style;
} WindowContext, *LPWindowContext;

typedef struct _GLContext
{
	PIXELFORMATDESCRIPTOR pfd;
	HGLRC glrc;
} GLContext, *LPGLContext;

typedef HWND WinID;

bool init_window_context(LocalhostContext* wctx);
void destroy_context(LocalhostContext* wctx);

void process_events(int count);

void create_window(LocalhostContext* wctx, WindowContext* wnd, 
				   char* title, 
				   int x, int y, int width, int height, int properties);

void destroy_window(WindowContext* wctx);

void set_window_data(WindowContext* wctx, int data);

void create_glcontext(WindowContext* wctx, GLContext* glctx);