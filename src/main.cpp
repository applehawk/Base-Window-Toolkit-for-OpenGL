//Standart headers
#include <iostream>
#include <fstream>
#include <string>

#include <process.h>

using namespace std;

//Own headers
#include "glcontext.h"
#include "system.h"

unsigned int __stdcall DrawSceneThread( void* lpParam );

class MyMessageHandler : public MessageHandler
{
public:
	void moveEvent(MouseEvent* event)
	{

	}
	void keyPressEvent ( KeyEvent* event )
	{
		if(event->KeyCode == VK_F1)
			printf("Press F1\n");
		if(event->KeyCode == 'Q')
			printf("Press Q\n");
	}
};

void init()
{

}

unsigned int __stdcall DrawSceneThread( void* lpParam )
{
	Application* app = reinterpret_cast<Application*>(lpParam);

	BufferFormat fmt;
	fmt.iBitsPerPixel = 32;
	fmt.iDepthBits = 32;
	fmt.iStencilBits = 0;
	fmt.bDoubleBuffer = true;

	OpenGLContext context(app->winContext(), &fmt, 3, 0); //OpenGL Context Thread specified
	context.PrintOpenGLVersion();
	context.PrintExtensions();

	init();
	//Prepare Rendering
	glViewport(0,0,800,600);
	glClearColor (0.2, 0.2, 0.2, 1.0);

	while(TRUE)
	{
		// clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		SwapBuffers(context.windowDC());
	}
}

int main(int argc, char** argv)
{
	Application app;

	MyMessageHandler handler;

	app.createWindow("My New Window", 100, 100, 1024, 768);
	app.registerMessageHandler(&handler);

	unsigned int DrawThreadId;
	uintptr_t hDrawThread = 
		_beginthreadex(NULL, 0, DrawSceneThread, &app, 0, &DrawThreadId);

	//Begin processing system events
	app.exec();

	_endthreadex(hDrawThread);
}