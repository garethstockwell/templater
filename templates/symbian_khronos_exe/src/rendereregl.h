//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// rendereregl.h
//

#ifndef RENDEREREGL_H
#define RENDEREREGL_H

#include "renderer.h"
#include <egl/egl.h>
#include <vg/openvg.h>
#include <gles/gl.h>

class CRendererEgl : public CRenderer
	{
public:
	~CRendererEgl();

protected:
	CRendererEgl(RWindow& aWindow, EGLenum aApi);
	void ConstructL();

	static void EGLCheckError();
    static void EGLCheckReturnError(EGLBoolean aBool);
    static void VGCheckError();
    static void GLCheckError();

private:
	void DoDraw();
	void EglSetupL();
	virtual void KhrSetup() = 0;
	virtual void KhrPaint() = 0;
	void EglSwapBuffers();

private:
	const EGLenum iApi;
	EGLDisplay iDisplay;
	EGLSurface iSurface;
	EGLContext iContext;
	};

#endif // RENDEREREGL_H

