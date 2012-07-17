//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// renderer.h
//

#ifndef RENDERER_H
#define RENDERER_H

#include <e32base.h>

class CPeriodic;
class RWindow;

class CRenderer : public CBase
	{
public:
	~CRenderer();

	void Draw();

	void StartRedrawTimer(TInt aDelay = 0);
    void StopRedrawTimer();

	static TInt TimerCallBack(TAny* aRenderer);

protected:
	CRenderer(RWindow& aWindow);
	void ConstructL();
	virtual void DoDraw() = 0;
	RWindow& Window() const;
	TRect WindowRect() const;
	TSize WindowSize() const;

private:
	RWindow& iWindow;
	CPeriodic* iRedrawTimer;
	};

#endif // RENDERER_H

