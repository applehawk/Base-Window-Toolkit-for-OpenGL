#include "assert.h"
#include "glcontext.h"

#include <map>
#include <iostream>

// WGLExtensions
PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = NULL;
PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = NULL;
PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB = NULL;
// WGL_ARB_pbuffer
PFNWGLCREATEPBUFFERARBPROC wglCreatePbufferARB = NULL;
PFNWGLGETPBUFFERDCARBPROC wglGetPbufferDCARB = NULL;
PFNWGLRELEASEPBUFFERDCARBPROC wglReleasePbufferDCARB = NULL;
PFNWGLDESTROYPBUFFERARBPROC wglDestroyPbufferARB = NULL;
PFNWGLQUERYPBUFFERARBPROC wglQueryPbufferARB = NULL;

// Program GL_ARB_shader_objects
PFNGLCREATEPROGRAMPROC glCreateProgram = NULL;
PFNGLDELETEPROGRAMPROC glDeleteProgram = NULL;
PFNGLUSEPROGRAMPROC glUseProgram = NULL;
PFNGLATTACHSHADERPROC glAttachShader = NULL;
PFNGLDETACHSHADERPROC glDetachShader = NULL;
PFNGLLINKPROGRAMPROC glLinkProgram = NULL;
PFNGLGETPROGRAMIVPROC glGetProgramiv = NULL;
PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = NULL;
PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = NULL;
PFNGLUNIFORM1IPROC glUniform1i = NULL;
PFNGLUNIFORM1IVPROC glUniform1iv = NULL;
PFNGLUNIFORM2IVPROC glUniform2iv = NULL;
PFNGLUNIFORM3IVPROC glUniform3iv = NULL;
PFNGLUNIFORM4IVPROC glUniform4iv = NULL;
PFNGLUNIFORM1FPROC glUniform1f = NULL;
PFNGLUNIFORM1FVPROC glUniform1fv = NULL;
PFNGLUNIFORM2FVPROC glUniform2fv = NULL;
PFNGLUNIFORM3FVPROC glUniform3fv = NULL;
PFNGLUNIFORM4FVPROC glUniform4fv = NULL;
PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = NULL;
PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = NULL;
PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = NULL;
PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = NULL;
PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = NULL;
PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = NULL;
PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = NULL;
PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = NULL;
PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = NULL;
PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = NULL;
PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = NULL;
PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = NULL;
PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = NULL;

// Shader
PFNGLCREATESHADERPROC glCreateShader = NULL;
PFNGLDELETESHADERPROC glDeleteShader = NULL;
PFNGLSHADERSOURCEPROC glShaderSource = NULL;
PFNGLCOMPILESHADERPROC glCompileShader = NULL;
PFNGLGETSHADERIVPROC glGetShaderiv = NULL;

// VBO GL_ARB_vertex_buffer_object
PFNGLGENBUFFERSPROC glGenBuffers = NULL;
PFNGLDELETEBUFFERSPROC glDeleteBuffers = NULL;
PFNGLBINDBUFFERPROC	glBindBuffer = NULL;
PFNGLBUFFERDATAPROC	glBufferData = NULL;
PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = NULL;
PFNGLVERTEXATTRIBLPOINTERPROC glVertexAttriblPointer = NULL;
PFNGLISBUFFERPROC glIsBuffer = NULL;
PFNGLMAPBUFFERPROC glMapBuffer = NULL;
PFNGLUNMAPBUFFERPROC glUnmapBuffer = NULL;

// Vertex Arrays GL_ARB_vertex_array_object
PFNGLBINDVERTEXARRAYPROC glBindVertexArray = NULL;
PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = NULL;
PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = NULL;
PFNGLISVERTEXARRAYPROC glIsVertexArray = NULL;

PFNGLGETSTRINGIPROC glGetStringi;

#define GL_SUPPORTED(GLExtName) glExtsSupported[GLExtName]
#define WGL_SUPPORTED(WGLExtName) wglExtsSupported[WGLExtName]

//All Supported XWindows OpenGL Extensions
enum {
	_XGL_Exts_Count,

} XGL_Extension;

struct StrCompare : public std::binary_function<const char*, const char*, bool> {
public:
	bool operator() (const char* str1, const char* str2) const
	{ return std::strcmp(str1, str2) < 0; }
};

typedef std::map<const char*, int, StrCompare> ExtMap;
ExtMap m_glExtMap;

void OpenGLContext::extensionsMapped()
{
	m_glExtMap["WGL_ARB_create_context"] = _WGL_ARB_create_context;
	m_glExtMap["WGL_ARB_pixel_format"] = _WGL_ARB_pixel_format;
	m_glExtMap["WGL_ARB_extensions_string"] = _WGL_ARB_extensions_string;

	m_glExtMap["GL_ARB_shader_objects"] = _GL_ARB_shader_objects;
	m_glExtMap["GL_ARB_vertex_buffer_object"] = _GL_ARB_vertex_buffer_object;
	m_glExtMap["GL_ARB_vertex_array_object"] = _GL_ARB_vertex_array_object;
}

bool OpenGLContext::initExtensions()
{
	extensionsMapped();

	ASSERT(!glctx, "OpenGL Context isn't created!\n");
	if(!glctx)
		return false;

#ifdef _WIN32
	wglCreateContextAttribsARB = 
		reinterpret_cast<PFNWGLCREATECONTEXTATTRIBSARBPROC>(wglGetProcAddress("wglCreateContextAttribsARB"));
	WGL_SUPPORTED(_WGL_ARB_create_context) = (wglCreateContextAttribsARB != NULL);

	wglChoosePixelFormatARB = 
		reinterpret_cast<PFNWGLCHOOSEPIXELFORMATARBPROC>(wglGetProcAddress("wglChoosePixelFormatARB"));
	WGL_SUPPORTED(_WGL_ARB_pixel_format) = (wglChoosePixelFormatARB != NULL);

	wglGetExtensionsStringARB =
		reinterpret_cast<PFNWGLGETEXTENSIONSSTRINGARBPROC>(wglGetProcAddress("wglGetExtensionsStringARB"));
	WGL_SUPPORTED(_WGL_ARB_extensions_string) = (wglGetExtensionsStringARB != NULL);

//PBuffer
	wglCreatePbufferARB = 
		reinterpret_cast<PFNWGLCREATEPBUFFERARBPROC>(wglGetProcAddress("wglCreatePbufferARB"));

#endif

	glGetStringi = 
		reinterpret_cast<PFNGLGETSTRINGIPROC>(wglGetProcAddress("glGetStringi"));

	//GL_ARB_separate_shader_objects
	bool isSupport = isExtensionSupportedByDriver("GL_ARB_separate_shader_objects");
	// GL_ARB_shader_objects
	GL_SUPPORTED(_GL_ARB_shader_objects) = isExtensionSupportedByDriver("GL_ARB_shader_objects");
	if(GL_SUPPORTED(_GL_ARB_shader_objects) != false) 
	{	// Program
		glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
		glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
		glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
		glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
		glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
		glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
		glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
		glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
		glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
		glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
		glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
		glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
		glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
		glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
		glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
		glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
		glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
		glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
		glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
		glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
		glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
		glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
		glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)wglGetProcAddress("glVertexAttrib2f");
		glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)wglGetProcAddress("glVertexAttrib3f");
		glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
		glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
		glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
		glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
		glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
		glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
		// Shader
		glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
		glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
		glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
		glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
		glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	}

	// VBO GL_ARB_vertex_buffer_object
	GL_SUPPORTED(_GL_ARB_vertex_buffer_object) = isExtensionSupportedByDriver("GL_ARB_vertex_buffer_object");
	if(GL_SUPPORTED(_GL_ARB_vertex_buffer_object) != false) 
	{
		glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
		glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
		glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
		glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
		glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
		glVertexAttriblPointer = (PFNGLVERTEXATTRIBLPOINTERPROC)wglGetProcAddress("glVertexAttriblPointer");
		glIsBuffer = (PFNGLISBUFFERPROC)wglGetProcAddress("glIsBuffer");
		glMapBuffer = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer");
		glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
	}

	//GL_ARB_vertex_array_object
	GL_SUPPORTED(_GL_ARB_vertex_array_object) = isExtensionSupportedByDriver("GL_ARB_vertex_array_object");
	if( GL_SUPPORTED(_GL_ARB_vertex_array_object) != false) 
	{
		glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
		glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
		glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
		glIsVertexArray = (PFNGLISVERTEXARRAYPROC)wglGetProcAddress("glIsVertexArray");
	}

	GL_SUPPORTED(_GL_ARB_uniform_buffer_object) = isExtensionSupportedByDriver("GL_ARB_uniform_buffer_object");
	if(GL_SUPPORTED(_GL_ARB_uniform_buffer_object) != false)
	{


	}
	return true;
}

int OpenGLContext::isExtensionSupportedByDriver(const char *extension)
{
  const GLubyte *extensions = NULL;
  const GLubyte *start;
  GLubyte *where, *terminator;

  /* Extension names should not have spaces. */
  where = (GLubyte *) strchr(extension, ' ');

  if (where || *extension == '\0')
    return 0;

  extensions = glGetString(GL_EXTENSIONS);

  /* It takes a bit of care to be fool-proof about parsing the
     OpenGL extensions string. Don't be fooled by sub-strings,
     etc. */

  start = extensions;

  for (;;) {

    where = (GLubyte *) strstr((const char *) start, extension);
    if (!where)
      break;

    terminator = where + strlen(extension);

    if (where == start || *(where - 1) == ' ')
      if (*terminator == ' ' || *terminator == '\0')
        return 1;

    start = terminator;
  }

  return 0;
}

bool OpenGLContext::CreateGLContext(WindowContext* wndctx, BufferFormat* fmt, int major, int minor) //System specified
{
	PIXELFORMATDESCRIPTOR pfd = { 
		sizeof(PIXELFORMATDESCRIPTOR),    // size of this pfd  
		1,                                // version number  
		PFD_DRAW_TO_WINDOW |              // support window  
		PFD_SUPPORT_OPENGL,								// support OpenGL
		PFD_TYPE_RGBA,                    // RGBA type  
		fmt->iBitsPerPixel,               // 24-bit color depth  
		0, 0, 0, 0, 0, 0,                 // color bits ignored  
		1,                                // no alpha buffer  
		0,                                // shift bit ignored  
		0,                                // no accumulation buffer  
		0, 0, 0, 0,                       // accum bits ignored  
		fmt->iDepthBits,                  // 16-bit z-buffer      
		fmt->iStencilBits,                // no stencil buffer  
		0,                                // no auxiliary buffer  
		PFD_MAIN_PLANE,                   // main layer  
		0,                                // reserved  
		0, 0, 0                           // layer masks ignored  
	};

	// double buffered 
	if(fmt->bDoubleBuffer)
	{
		pfd.dwFlags |= PFD_DOUBLEBUFFER;
	}

	int  iPixelFormat; 
	iPixelFormat = ChoosePixelFormat(wndctx->hdc, &pfd);

	if(!iPixelFormat) {
		ASSERT(true, "Not choose pixel format");
		return false;
	}

	SetPixelFormat(wndctx->hdc, iPixelFormat, &pfd);

	HGLRC tempContext = wglCreateContext(wndctx->hdc);
	if(tempContext == NULL)
		return false;

	glctx = new GLContext();

	wglMakeCurrent(wndctx->hdc, tempContext);
	wndctx->glrc = tempContext;
	glctx->glrc = tempContext;

	//We now get OpenGL Context
	GetGLVer(&version);
	initExtensions();

	if(isExtensionSupported("WGL_ARB_pixel_format"))
	{
		const int attribList[] =
		{
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, fmt->iBitsPerPixel,
			WGL_DEPTH_BITS_ARB, fmt->iDepthBits,
			WGL_STENCIL_BITS_ARB, fmt->iStencilBits,
			0,        //End
		};

		UINT numFormats;

		wglChoosePixelFormatARB(wndctx->hdc, attribList, NULL, 1, &iPixelFormat, &numFormats);
		SetPixelFormat(wndctx->hdc, iPixelFormat, &pfd);
	}

	if(isExtensionSupported("WGL_ARB_create_context")) // Create context for OpenGL 3.0 and below
	{
		int attribs[] =
		{
			WGL_CONTEXT_MAJOR_VERSION_ARB, major,
			WGL_CONTEXT_MINOR_VERSION_ARB, minor,
			WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
			0
		};

		HGLRC glrc = wglCreateContextAttribsARB(wndctx->hdc, 0, attribs);
		if(!glrc) {

			printf("OpenGL %d.%d Context not supported!\n", major, minor);

			int correct_attribs[] =
			{
				WGL_CONTEXT_MAJOR_VERSION_ARB, version.major,
				WGL_CONTEXT_MINOR_VERSION_ARB, version.minor,
				WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
				0
			};
			glrc = wglCreateContextAttribsARB(wndctx->hdc, 0, correct_attribs);
		}
		
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(tempContext);

		wndctx->glrc = glrc;
		wglMakeCurrent(wndctx->hdc, wndctx->glrc);
	} else {
		wndctx->glrc = tempContext;
	}

	glctx->glrc = wndctx->glrc;
	GetGLVer(&version);
	printf("Created OpenGL %d.%d context\n", version.major, version.minor);

	return true;
}

void OpenGLContext::DestroyGLContext() //System specified
{
	wglMakeCurrent(NULL, NULL);
	wglDeleteContext(glctx->glrc);
	delete glctx;
}

void OpenGLContext::PrintOpenGLVersion()
{
	ASSERT(!glctx, "OpenGL Context not created!");

	GLVersion version;
	GetGLVer(&version);
	std::cout << "Vendor: " << version.glVendor << std::endl;
	std::cout << "OpenGL Version: " << version.major << "." << version.minor << std::endl;
	std::cout << "GLSL Version: " << version.glsl_major << "." << version.glsl_minor << std::endl;
	std::cout << "OpenGL VerInfo: " << version.glVer << std::endl;
	std::cout << "GLSL VerInfo: " << version.glslVer << std::endl;
}

void OpenGLContext::GetGLVer( GLVersion* ver )
{
	ASSERT(!glctx, "OpenGL Context not created!");

	// for all versions
	ver->glVendor = (char*)glGetString(GL_VENDOR);
	ver->glVer = (char*)glGetString(GL_VERSION); // ver = "3.2.0"
	ver->major = ver->glVer[0] - '0';
	if( ver->major >= 3)
	{
		// for GL 3.x
		glGetIntegerv(GL_MAJOR_VERSION, &ver->major); // major = 3
		glGetIntegerv(GL_MINOR_VERSION, &ver->minor); // minor = 2
	}
	else
	{
		ver->minor = ver->glVer[2] - '0';
	}
	if( ver->major >= 2) {// for GL 2.x and above
		// GLSL
		ver->glslVer = (char*)glGetString(GL_SHADING_LANGUAGE_VERSION); // ver = "1.50 NVIDIA via Cg compiler"
		ver->glsl_major = ver->glslVer[0] - '0';
		ver->glsl_minor = ver->glslVer[2] - '0';
	}
}

OpenGLContext::OpenGLContext(WindowContext* wctx, BufferFormat* fmt, int major, int minor) : m_wctx(wctx) //System specified
{
	memset(&version, 0, sizeof(GLVersion));
	for(int i=0; i<GL_Exts_Count; ++i)
		glExtsSupported[i] = false;

	for(int i=0; i<WGL_Exts_Count; ++i)
		wglExtsSupported[i] = false;

	CreateGLContext(wctx, fmt, major, minor);
}

OpenGLContext::~OpenGLContext()
{
	DestroyGLContext();
}

bool OpenGLContext::isExtensionSupported( const char* extension )
{
	ExtMap::iterator iter = m_glExtMap.find((char*)extension);
	if(iter == m_glExtMap.end())
		return false;

	bool bSysExt = false;
	if(extension[0] != 'G' && extension[1] != 'L')
		bSysExt = true;

	bool bResult;
	if(bSysExt) {
#ifdef _WIN32
	bResult = wglExtsSupported[iter->second];
#endif
	} else {
		bResult = glExtsSupported[iter->second];
	}
	return (bResult);
}

void OpenGLContext::PrintExtensions(bool sysExt)
{
	const char* extensions;
	if(sysExt) {
		if(wglGetExtensionsStringARB)
			extensions = wglGetExtensionsStringARB(m_wctx->hdc);

		std::cout << extensions;
	} else
	if(version.major >= 3 && glGetStringi != NULL) {
		GLint n, i;
		glGetIntegerv(GL_NUM_EXTENSIONS, &n);
		for (i = 0; i < n; i++) {
			std::cout << glGetStringi(GL_EXTENSIONS, i) << std::endl;
		}
	} else {
		extensions = (const char*)glGetString(GL_EXTENSIONS); //Flag GL_EXTENSIONS Deprecated in OpenGL 3.0
		std::cout << extensions;
	}
}
