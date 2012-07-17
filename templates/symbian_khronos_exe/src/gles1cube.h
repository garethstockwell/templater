//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// gles1cube.h
//

#ifndef GLES1CUBE_H
#define GLES1CUBE_H

#include "rendereregl.h"

class CRendererGLES1Cube : public CRendererEgl
    {
public:
    static CRendererEgl* NewL(RWindow& aWindow);
    ~CRendererGLES1Cube();
    static const TDesC& Name();

private:
    CRendererGLES1Cube(RWindow& aWindow);
    void KhrSetup();
    void KhrPaint();

private:
    TReal iAngle;
    GLuint iCoordinateColorBuffer;
    GLuint iIndexBuffer;
    };

#endif // GLES1CUBE_H

