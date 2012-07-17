//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// renderer.cpp
//

#include "renderer.h"
#include <e32debug.h>
#include <w32std.h>

CRenderer::CRenderer(RWindow& aWindow)
	:	iWindow(aWindow)
	{

	}

void CRenderer::ConstructL()
	{
	RDebug::Printf("[{{PROJECT}}] CRenderer::ConstructL");
	iRedrawTimer = CPeriodic::NewL(CActive::EPriorityIdle);
	}

CRenderer::~CRenderer()
	{
	RDebug::Printf("[{{PROJECT}}] CRenderer::~CRenderer");
	delete iRedrawTimer;
	}

void CRenderer::Draw()
	{
	RDebug::Printf("[{{PROJECT}}] CRenderer::Draw");
	DoDraw();
	}

void CRenderer::StartRedrawTimer(TInt aDelay)
	{
	RDebug::Printf("[{{PROJECT}}] CRenderer::StartRedrawTimer");
	if (iRedrawTimer->IsActive())
		{
		iRedrawTimer->Cancel();
		}
	iRedrawTimer->Start(0, aDelay, TCallBack(TimerCallBack, this));
	}

void CRenderer::StopRedrawTimer()
	{
	RDebug::Printf("[{{PROJECT}}] CRenderer::StopRedrawTimer");
	if(iRedrawTimer)
		{
		iRedrawTimer->Cancel();
		}
	}

TInt CRenderer::TimerCallBack(TAny* aRenderer)
    {
    static_cast<CRenderer*>(aRenderer)->Draw();
    return KErrNone;
    }

RWindow& CRenderer::Window() const
	{
	return iWindow;
	}

TRect CRenderer::WindowRect() const
	{
	return TRect(TPoint(), WindowSize());
	}

TSize CRenderer::WindowSize() const
	{
	return iWindow.Size();
	}

