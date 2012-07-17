//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// vgline.cpp
//

#include "vgline.h"
#include <e32debug.h>

_LIT(KVGLineName, "vgline");

CRendererEgl* CRendererVGLine::NewL(RWindow& aWindow)
    {
    CRendererVGLine* self = new (ELeave) CRendererVGLine(aWindow);
    CleanupStack::PushL(self);
    self->ConstructL();
    CleanupStack::Pop(self);
    return self;
    }

const TDesC& CRendererVGLine::Name()
	{
	return KVGLineName;
	}

CRendererVGLine::CRendererVGLine(RWindow& aWindow)
    :   CRendererEgl(aWindow, EGL_OPENVG_API)
	{

    }

void CRendererVGLine::KhrSetup()
    {
    static VGubyte const Segments[] =
        {
        VG_MOVE_TO_ABS,
        VG_LINE_TO_REL,
        VG_CLOSE_PATH
        };

    static VGfloat const Coords[] =
        {
        110, 35,
        50, 160,
        };

    VGfloat strokeColor[4]  = {1.f, 0.f, 0.f, 1.f};

    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrSetup vgCreatePaint");
    iVGPaint = vgCreatePaint();
    VGCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrSetup vgSetParameterX");
    vgSetParameteri(iVGPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
    VGCheckError();
    vgSetParameterfv(iVGPaint, VG_PAINT_COLOR, 4, strokeColor);
    VGCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrSetup vgCreatePath");
    iVGPath = vgCreatePath(VG_PATH_FORMAT_STANDARD,
                           VG_PATH_DATATYPE_F,
                           1.0f, // scale
                           0.0f, // bias
                           3,    // segmentCapacityHint
                           4,    // coordCapacityHint
                           VG_PATH_CAPABILITY_ALL);
    VGCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrSetup vgAppendPathData");
    vgAppendPathData(iVGPath, sizeof(Segments), Segments, Coords);
    VGCheckError();
    }

void CRendererVGLine::KhrPaint()
    {
    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrPaint vgSetPaint");
    vgSetPaint(iVGPaint, VG_STROKE_PATH);
    VGCheckError();

    RDebug::Printf("[{{PROJECT}}] CRendererVGLine::KhrPaint vgDrawPath");
    vgDrawPath(iVGPath, VG_STROKE_PATH);
    VGCheckError();
    }

