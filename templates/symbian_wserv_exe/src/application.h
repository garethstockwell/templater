//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// application.h
//

#include <e32base.h>

class CRenderer;
class CWsCanvas;
class CWsEventHandler;

class MWsEventObserver
    {
public:
    virtual void PointerEvent() = 0;
    };

class CWsApp : public CBase
             , public MWsEventObserver
    {
public:
    static CWsApp* NewL();
    ~CWsApp();
    void Start();
    void Stop();

    // MWsEventObserver
    void PointerEvent();

private:
    CWsApp();
    void ConstructL();

private:
    CWsCanvas* iAppView;
    CWsEventHandler* iEventHandler;
	CRenderer* iRenderer;
    TPoint iPos;
    TSize iSz;
    TInt iScrId;
    };

