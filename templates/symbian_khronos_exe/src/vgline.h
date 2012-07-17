//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// vgline.h
//

#ifndef VGLINE_H
#define VGLINE_H

#include "rendereregl.h"

class CRendererVGLine : public CRendererEgl
    {
public:
    static CRendererEgl* NewL(RWindow& aWindow);
    static const TDesC& Name();

private:
    CRendererVGLine(RWindow& aWindow);
    void KhrSetup();
    void KhrPaint();

private:
    VGPaint iVGPaint;
    VGPath iVGPath;
    };

#endif

