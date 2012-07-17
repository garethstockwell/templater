//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// application.h
//

#ifndef APPLICATION_H
#define APPLICATION_H

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

#endif // APPLICATION_H

