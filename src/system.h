#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#ifdef WIN32
#include "win32.h"
#endif

#include "basic_types.h"

class ActionEvent;
class Event;
class CloseEvent;
class ContextMenuEvent;
class MoveEvent;
class PaintEvent;
class ResizeEvent;
class ShowEvent;
class WheelEvent;

class Size2
{
public:
	int width, height;
};

class ResizeEvent
{
public:
	Size2 OldSize;
	Size2 NewSize;
};

typedef enum KeyCodes
{
	Key_F1 = 0,
	Key_F2,
};

class KeyEvent
{
public:
	uint16 KeyCode;
};

class MouseEvent
{
	int x, y, z;
	bool LButton, MButton, RButton;

	bool isLButtonDown() { return LButton; }
	bool isMButtonDown() { return MButton; }
	bool isRButtonDown() { return RButton; }
};

class MessageHandler;

class Application
{
private:
	LocalhostContext* m_lhctx;
	WindowContext* m_wctx;
	MessageHandler* m_msghandler;
public:
	Application();
	~Application();

	bool createWindow(char* title, int x, int y, int width, int height);
	bool createFullscreenWindow(char* title, int width, int height);

	bool changeToFullscreenWindow();
	
	WindowContext* winContext()
	{
		return m_wctx;
	}

	LocalhostContext* localhostContext()
	{
		return m_lhctx;
	}

	WinID winID() {
		if(m_wctx != NULL) {
			return m_wctx->hwnd;
		}
		return 0x0;
	}

	void registerMessageHandler(MessageHandler* handler)
	{
		m_msghandler = handler;
	}

	void exec();
};

class MessageHandler
{
public:
	MessageHandler();
	~MessageHandler();

	virtual void	actionEvent ( ActionEvent * event )
	{UNREF_PARAM(event);}
	virtual void	changeEvent ( Event * event )
	{UNREF_PARAM(event);}
	virtual void	closeEvent ( CloseEvent * event )
	{UNREF_PARAM(event);}
	virtual void	contextMenuEvent ( ContextMenuEvent * event )
	{UNREF_PARAM(event);}

	virtual void	keyPressEvent ( KeyEvent * event )
	{UNREF_PARAM(event);}
	virtual void	keyReleaseEvent ( KeyEvent * event ) 
	{UNREF_PARAM(event);}
	virtual void	leaveEvent ( Event * event ) 
	{UNREF_PARAM(event);}

	virtual void	mouseDoubleClickEvent ( MouseEvent * event ) 
	{UNREF_PARAM(event);}
	virtual void	mouseMoveEvent ( MouseEvent * event ) 
	{UNREF_PARAM(event);}
	virtual void	mousePressEvent ( MouseEvent * event ) 
	{UNREF_PARAM(event);}
	virtual void	mouseReleaseEvent ( MouseEvent * event ) 
	{UNREF_PARAM(event);}

	virtual void	moveEvent ( MoveEvent * event ) 
	{ UNREF_PARAM(event); }
	virtual void	paintEvent ( PaintEvent * event )
	{UNREF_PARAM(event);}

	virtual void	resizeEvent ( ResizeEvent * event ) 
	{UNREF_PARAM(event);}
	virtual void	showEvent ( ShowEvent * event ) 
	{UNREF_PARAM(event);}

	virtual void	wheelEvent ( WheelEvent * event ) 
	{UNREF_PARAM(event);}

//Platform specifier handlers
#ifdef COCOA
	virtual bool	macEvent ( EventHandlerCallRef caller, EventRef event );
#elif WIN32
	virtual bool	winEvent ( MSG * message, long * result ) 
	{
		UNREF_PARAM(message);
		UNREF_PARAM(result);
		return true;
	}
#elif X11
	virtual bool	x11Event ( XEvent * event );
#endif
};

#endif