#ifndef __GLCONTEXT_H__
#define __GLCONTEXT_H__

#include "system.h"

#include <map>

#include <GL/gl.h>
#include <GL/glext.h>

#ifdef _WIN32
#include <GL/wglext.h>
#endif

typedef struct
{
	int major;
	int minor;

	int glsl_major;
	int glsl_minor;

	char* glVendor;
	char* glVer;
	char* glslVer;
} GLVersion;

typedef struct 
{
	int iBitsPerPixel;
	int iDepthBits;
	int iStencilBits;
	bool bDoubleBuffer;
} BufferFormat;

//All Supported OpenGL Extensions
typedef enum {
	_GL_ARB_shader_objects = 0,
	_GL_ARB_vertex_buffer_object,
	_GL_ARB_vertex_array_object,
	_GL_ARB_uniform_buffer_object,
	_GL_ARB_separate_shader_objects,
	GL_Exts_Count,
} GL_Extension;

//All Supported Windows OpenGL Extensions
typedef enum {
	_WGL_ARB_pixel_format = 0,
	_WGL_ARB_create_context,
	_WGL_ARB_extensions_string,
	_WGL_ARB_pbuffer,

	WGL_Exts_Count,
} WGL_Extension;

//Describe WGL_ARB_create_context extension
extern PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB;
//Describe WGL_ARB_pixel_format extension
extern PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB;

//----------------
// Program
extern PFNGLCREATEPROGRAMPROC glCreateProgram;
extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
extern PFNGLUSEPROGRAMPROC glUseProgram;
extern PFNGLATTACHSHADERPROC glAttachShader;
extern PFNGLDETACHSHADERPROC glDetachShader;
extern PFNGLLINKPROGRAMPROC glLinkProgram;
extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
extern PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
extern PFNGLUNIFORM1IPROC glUniform1i;
extern PFNGLUNIFORM1IVPROC glUniform1iv;
extern PFNGLUNIFORM2IVPROC glUniform2iv;
extern PFNGLUNIFORM3IVPROC glUniform3iv;
extern PFNGLUNIFORM4IVPROC glUniform4iv;
extern PFNGLUNIFORM1FPROC glUniform1f;
extern PFNGLUNIFORM1FVPROC glUniform1fv;
extern PFNGLUNIFORM2FVPROC glUniform2fv;
extern PFNGLUNIFORM3FVPROC glUniform3fv;
extern PFNGLUNIFORM4FVPROC glUniform4fv;
extern PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
extern PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
extern PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
extern PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
extern PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
extern PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
extern PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
extern PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
extern PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;

// Shader
extern PFNGLCREATESHADERPROC glCreateShader;
extern PFNGLDELETESHADERPROC glDeleteShader;
extern PFNGLSHADERSOURCEPROC glShaderSource;
extern PFNGLCOMPILESHADERPROC glCompileShader;
extern PFNGLGETSHADERIVPROC glGetShaderiv;

// VBO
extern PFNGLGENBUFFERSPROC glGenBuffers;
extern PFNGLDELETEBUFFERSPROC glDeleteBuffers;
extern PFNGLBINDBUFFERPROC	glBindBuffer;
extern PFNGLBUFFERDATAPROC	glBufferData;
extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
extern PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttriblPointer;
extern PFNGLISBUFFERPROC glIsBuffer;
extern PFNGLMAPBUFFERPROC glMapBuffer;
extern PFNGLUNMAPBUFFERPROC glUnmapBuffer;

//GL_ARB_vertex_array_object
extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
extern PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays;
extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
extern PFNGLISVERTEXARRAYPROC glIsVertexArray;
//Platform specified
class OpenGLContext
{
private:
	WindowContext* m_wctx;
	GLContext* glctx;
	GLVersion version;

//System specific
#ifdef _WIN32
	bool wglExtsSupported[WGL_Exts_Count];
#endif
#ifdef X11
	bool xglExtsSupported[XGL_Exts_Count];
#endif

	bool glExtsSupported[GL_Exts_Count];
public:
	OpenGLContext(WindowContext* wctx, BufferFormat* fmt, int major, int minor);
	~OpenGLContext();

	HDC windowDC() 
	{ return m_wctx->hdc; }

	bool CreateGLContext(WindowContext* wndctx, BufferFormat* fmt, int major, int minor);
	void DestroyGLContext();

	//Extension supported by GLContext class and loaded in initExtension()
	bool isExtensionSupported(const char* extension);

	void PrintOpenGLVersion();
	void PrintExtensions(bool bSysExt = false);
	void GetGLVer(GLVersion* ver);

	int isExtensionSupportedByDriver(const char *extension); //Extension supported by OpenGL driver
protected:
	bool initExtensions();
	void extensionsMapped();
};


#endif