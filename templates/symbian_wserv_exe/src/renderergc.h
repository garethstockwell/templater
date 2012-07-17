//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// renderergc.h
//

#include "renderer.h"

class CWindowGc;

class CRendererGc : public CRenderer
	{
public:
	static CRendererGc* NewL(CWindowGc& aGc, RWindow& aWindow);
	~CRendererGc();

protected:
	void DoDraw();

private:
	CRendererGc(CWindowGc& aGc, RWindow& aWindow);
	void ConstructL();

private:
	CWindowGc& iGc;
	};

