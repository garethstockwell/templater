//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// renderer.cpp
//

#include "renderergc.h"
#include <e32debug.h>
#include <w32std.h>

CRendererGc* CRendererGc::NewL(CWindowGc& aGc, RWindow& aWindow)
	{
	RDebug::Printf("[{{PROJECT}}] CRendererGc::NewL");
	CRendererGc* self = new (ELeave) CRendererGc(aGc, aWindow);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop();
	return self;
	}

CRendererGc::CRendererGc(CWindowGc& aGc, RWindow& aWindow)
	:	CRenderer(aWindow)
	,	iGc(aGc)
	{

	}

void CRendererGc::ConstructL()
    {
    RDebug::Printf("[{{PROJECT}}] CRendererGc::ConstructL");
	CRenderer::ConstructL();
    }

CRendererGc::~CRendererGc()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererGc::~RendererGc");
	}

void CRendererGc::DoDraw()
	{
	RDebug::Printf("[{{PROJECT}}] CRendererGc::DoDraw");
	iGc.Activate(Window());
	Window().BeginRedraw(WindowRect());

	// Replace with real drawing
	iGc.SetBrushColor(TRgb(255, 0, 0));
	iGc.Clear(WindowRect());

	Window().EndRedraw();
	iGc.Deactivate();
	}

