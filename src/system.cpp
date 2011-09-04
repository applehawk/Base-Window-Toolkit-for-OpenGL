#include "assert.h"
#include "system.h"

Application::Application() : m_msghandler(NULL), m_wctx(NULL)
{
	m_lhctx = new LocalhostContext();
	init_window_context(m_lhctx);
}


Application::~Application()
{
	if(m_wctx) {
		destroy_window(m_wctx);
		delete m_wctx;
	}
	destroy_context(m_lhctx);
	delete m_lhctx;
}

void Application::exec()
{
	MSG msg;
	while (TRUE) 
	{ 
		if(msg.message == WM_QUIT)
			break;
		if( PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) )
		{
			switch(msg.message) 
			{
			case WM_KEYDOWN: {
				KeyEvent evnt;
				evnt.KeyCode = msg.wParam;
				m_msghandler->keyPressEvent(&evnt);
						}

			default: {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
							 }
			}
		}
	}
}

MessageHandler::MessageHandler()
{

}

MessageHandler::~MessageHandler()
{

}

bool Application::createWindow( char* title, int x, int y, int width, int height )
{
	ASSERT(!m_lhctx, "Localhost Context not initialized!");
	ASSERT(m_wctx, "Window Context already initialized!");

	if(!m_lhctx || m_wctx) //If Localhost Context initialized
		return false;

	m_wctx = new WindowContext();
	create_window(m_lhctx, m_wctx, title, x, y, width, height, WINDOWPROP_STANDARD);

	set_window_data(m_wctx, reinterpret_cast<int>(this));

	return true;
}

bool Application::createFullscreenWindow( char* title, int width, int height )
{
	ASSERT(!m_lhctx, "Localhost Context not initialized!");
	ASSERT(m_wctx, "Window Context already initialized!");

	if(!m_lhctx || m_wctx) //If Localhost Context initialized
		return false;

	m_wctx = new WindowContext();
	create_window(m_lhctx, m_wctx, title, 0, 0, width, height, 
		WINDOWPROP_POPUP | WINDOWPROP_NOBORDER);
	
	return true;
}

bool Application::changeToFullscreenWindow()
{
	return true;
}