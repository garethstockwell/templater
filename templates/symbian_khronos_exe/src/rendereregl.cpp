//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// rendereregl.cpp
//

#include "rendereregl.h"
#include <e32debug.h>
#include <w32std.h>
#include <string.h>

const EGLint KAttribList[] =
		{
		EGL_RED_SIZE,			8,
		EGL_GREEN_SIZE,			8,
		EGL_BLUE_SIZE,			8,
        EGL_ALPHA_SIZE,         8,
		EGL_SURFACE_TYPE,		EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE,	EGL_OPENVG_BIT,
		EGL_NONE
		};

void CRendererEgl::EGLCheckError()
    {
    EGLint error = eglGetError();
    if(EGL_SUCCESS != error)
        {
        RDebug::Printf("[{{PROJECT}}] CEglRendering::EGLCheckError error %d", error);
        User::Panic(_L("EGL"), error);
        }
    }

void CRendererEgl::EGLCheckReturnError(EGLBoolean aBool)
    {
    if(!aBool)
        {
        RDebug::Printf("[{{PROJECT}}] CEglRendering::EGLCheckReturnError false");
        User::Panic(_L("EGL-RTN"), eglGetError());
        }
    }

void CRendererEgl::VGCheckError()
    {
    VGint error = vgGetError();
    if(VG_NO_ERROR != error)
        {
        RDebug::Printf("[{{PROJECT}}] CEglRendering::VGCheckError error %d", error);
        User::Panic(_L("VG"), error);
        }
    }

void CRendererEgl::GLCheckError()
    {
	GLenum error = glGetError();
    if(GL_NO_ERROR != error)
        {
        RDebug::Printf("[{{PROJECT}}] CEglRendering::GLCheckError error %d", error);
        User::Panic(_L("GL"), error);
        }
    }

CRendererEgl::CRendererEgl(RWindow& aWindow, EGLenum aApi)
	:	CRenderer(aWindow)
	,	iApi(aApi)
	{

	}

void CRendererEgl::ConstructL()
    {
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::ConstructL");
	CRenderer::ConstructL();
	EglSetupL();
	KhrSetup();
	KhrPaint();
	EglSwapBuffers();
    }

void CRendererEgl::DoDraw()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererEgl::DoDraw");
	KhrPaint();
	EglSwapBuffers();
	}

CRendererEgl::~CRendererEgl()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererEgl::~RendererEgl");

	if (EGL_NO_CONTEXT != iContext)
        {
        EGLCheckReturnError(eglDestroyContext(iDisplay, iContext));
        }

    if (EGL_NO_SURFACE != iSurface)
        {
        EGLCheckReturnError(eglDestroySurface(iDisplay,iSurface));
        }

    // Call eglMakeCurrent() to ensure the surfaces and contexts are truly destroyed.
    EGLCheckReturnError(eglMakeCurrent(iDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT));
    EGLCheckReturnError(eglTerminate(iDisplay));
    EGLCheckReturnError(eglReleaseThread());
	}

void CRendererEgl::EglSetupL()
    {
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglGetDisplay");
    iDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    EGLCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglInitialize");
    EGLCheckReturnError(eglInitialize(iDisplay, NULL, NULL));

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL vendor %s", eglQueryString(iDisplay, EGL_VENDOR));
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL version %s", eglQueryString(iDisplay, EGL_VERSION));
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL extensions %s", eglQueryString(iDisplay, EGL_EXTENSIONS));

    // Check that EGL provides the capabilities for this app.
    if(NULL == strstr(eglQueryString(iDisplay, EGL_CLIENT_APIS), "OpenVG"))
        {
        RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL OpenVG not listed in supported client APIs %s", eglQueryString(iDisplay, EGL_CLIENT_APIS));
        User::Leave(KErrNotSupported);
        }

    if(NULL == strstr(eglQueryString(iDisplay, EGL_EXTENSIONS), "EGL_SYMBIAN_COMPOSITION") )
        {
        RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL EGL_SYMBIAN_COMPOSITION not listed in extension string %s", eglQueryString(iDisplay, EGL_EXTENSIONS));
        User::Leave(KErrNotSupported);
        }

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglChooseConfig");
    EGLint numConfigs = 0;
    EGLConfig chosenConfig = 0;
    EGLCheckReturnError(eglChooseConfig(iDisplay, KAttribList, &chosenConfig, 1, &numConfigs));
    if (0 == numConfigs)
        {
        RDebug::Printf("[{{PROJECT}}] No matching configs found", eglQueryString(iDisplay, EGL_EXTENSIONS));
        User::Leave(KErrNotSupported);
        }

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglBindApi 0x%x", iApi);
    EGLCheckReturnError(eglBindAPI(iApi));

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglCreateWindowSurface");
    iSurface = eglCreateWindowSurface(iDisplay, chosenConfig, &Window(), NULL);
    EGLCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglGetConfigAttrib");
    TInt redSize, greenSize, blueSize, alphaSize;
    EGLCheckReturnError(eglGetConfigAttrib(iDisplay, chosenConfig, EGL_ALPHA_SIZE, &alphaSize));
    EGLCheckReturnError(eglGetConfigAttrib(iDisplay, chosenConfig, EGL_RED_SIZE, &redSize));
    EGLCheckReturnError(eglGetConfigAttrib(iDisplay, chosenConfig, EGL_GREEN_SIZE, &greenSize));
    EGLCheckReturnError(eglGetConfigAttrib(iDisplay, chosenConfig, EGL_BLUE_SIZE, &blueSize));
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL id:%d alpha:%d red:%d green:%d blue:%d",
                   chosenConfig, alphaSize, redSize, greenSize, blueSize);

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglCreateContext");
    iContext = eglCreateContext(iDisplay, chosenConfig, EGL_NO_CONTEXT, NULL);
    EGLCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSetupL eglMakeCurrent");
    CRendererEgl::EGLCheckReturnError(eglMakeCurrent(iDisplay, iSurface, iSurface, iContext));
    }

void CRendererEgl::EglSwapBuffers()
    {
    RDebug::Printf("[{{PROJECT}}] CRendererEgl::EglSwapBuffers");
    eglSwapBuffers(iDisplay, iSurface);
    EGLCheckError();
    }


