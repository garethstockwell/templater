//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// application.cpp
//

#include "application.h"
// Replace with real renderer
#include "renderergc.h"
#include <bacline.h>
#include <e32debug.h>
#include <w32std.h>

const TInt KDefaultScreenNo = 0;

class CWsCanvas: public CBase
{
public:
	static CWsCanvas* NewL(TInt, const TPoint&);
	~CWsCanvas();

	CWindowGc& Gc() const { return *iGc; }
	RWsSession& Session() { return iWs; }
	RWindow& Window() { return iWin; }
    const TSize& ScreenSize() const { return iSz; }

private:
	CWsCanvas(TInt, const TPoint&);
	void ConstructL();

private:
    const TInt iScrId;
	const TPoint iPos;
	TSize iSz;
	RWsSession iWs;
	RWindowGroup iGrp;
	RWindow iWin;
	CWsScreenDevice* iScr;
	CWindowGc* iGc;
};

CWsCanvas* CWsCanvas::NewL(TInt aScrId, const TPoint& aPos)
	{
	CWsCanvas* self = new (ELeave) CWsCanvas(aScrId, aPos);
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

CWsCanvas::CWsCanvas(TInt aScrId, const TPoint& aPos)
    :   iScrId(aScrId)
    ,   iPos(aPos)
	{

	}

CWsCanvas::~CWsCanvas()
	{
	delete iGc;
	delete iScr;
	iGrp.Close();
	iWin.Close();
	iWs.Close();
	}

void CWsCanvas::ConstructL()
	{
	TInt err = iWs.Connect();
	User::LeaveIfError(err);

	iScr = new (ELeave) CWsScreenDevice(iWs);
	err = iScr->Construct(iScrId);
	User::LeaveIfError(err);

	err = iScr->CreateContext(iGc);
	User::LeaveIfError(err);

	iGrp = RWindowGroup(iWs);
	err = iGrp.Construct(0xbadf00d, ETrue, iScr);
	User::LeaveIfError(err);

	iWin = RWindow(iWs);
	err = iWin.Construct(iGrp, (TUint32)this);
	User::LeaveIfError(err);

	iSz = iScr->SizeInPixels();
	iWin.SetExtent(iPos, iSz);
	iWin.SetBackgroundColor();
	iWin.Activate();
	iWin.SetVisible(ETrue);

	iWs.Flush();

	iWs.SetFocusScreen(iScrId);
	}

class CWsEventHandler : public CActive
    {
public:
    CWsEventHandler(RWsSession& aSession, RWindow& aWindow, MWsEventObserver& aObserver);
    ~CWsEventHandler();
private:
    void ConstructL();
    void RequestEvent();
    void RunL();
    void DoCancel();
private:
    RWsSession& iSession;
    RWindow& iWindow;
    MWsEventObserver& iObserver;
    };

CWsEventHandler::CWsEventHandler(RWsSession& aSession, RWindow& aWindow, MWsEventObserver& aObserver)
    :   CActive(CActive::EPriorityStandard)
    ,   iSession(aSession)
    ,   iWindow(aWindow)
    ,   iObserver(aObserver)
    {
    RDebug::Printf("[{{PROJECT}}] CWsEventHandler::CWsEventHandler");
    CActiveScheduler::Add(this);
    RequestEvent();
    }

CWsEventHandler::~CWsEventHandler()
    {
    RDebug::Printf("[{{PROJECT}}] CWsEventHandler::~CWsEventHandler");
    Cancel();
    }

void CWsEventHandler::ConstructL()
    {
    CActiveScheduler::Add(this);
    RequestEvent();
    }

void CWsEventHandler::RequestEvent()
    {
    iStatus = KRequestPending;
    iSession.EventReady(&iStatus);
    SetActive();
    }

void CWsEventHandler::RunL()
    {
    if (KErrNone == iStatus.Int())
        {
        TWsEvent event;
        iSession.GetEvent(event);
        RequestEvent();
        switch (event.Type())
            {
            case EEventPointer:
                iObserver.PointerEvent();
                break;
            }
        }
    }

void CWsEventHandler::DoCancel()
    {
    iSession.EventReadyCancel();
    }

CWsApp::CWsApp()
	{

	}

CWsApp* CWsApp::NewL()
	{
	RDebug::Printf("[{{PROJECT}}] CWsApp::NewL");
	CWsApp* self = new (ELeave) CWsApp;
	CleanupStack::PushL(self);
	self->ConstructL();
	CleanupStack::Pop(self);
	return self;
	}

void CWsApp::ConstructL()
    {
	RDebug::Printf("[{{PROJECT}}] CWsApp::ConstructL");

	iScrId = KDefaultScreenNo;
	CCommandLineArguments* args = CCommandLineArguments::NewLC();
	for (TInt i=1; i<args->Count(); ++i)
		{
		const TPtrC arg = args->Arg(i);
		// Put command-line parsing code here if required
		RDebug::Print(_L("[{{PROJECT}}] CWsApp::ConstructL ignoring argument %S"), &arg);
		}
	CleanupStack::PopAndDestroy(args);

	iAppView = CWsCanvas::NewL(iScrId, iPos);
    iSz = iAppView->ScreenSize();
	iEventHandler = new (ELeave) CWsEventHandler(iAppView->Session(), iAppView->Window(), *this);
	iRenderer = CRendererGc::NewL(iAppView->Gc(), iAppView->Window());
	iRenderer->Draw();
	//iRenderer->StartRedrawTimer();
	}

void CWsApp::Start()
	{
	RDebug::Printf("[{{PROJECT}}] CWsApp::Start");
	CActiveScheduler::Start();
	}

void CWsApp::Stop()
	{
    RDebug::Printf("[{{PROJECT}}] CWsApp::Stop");
    CActiveScheduler::Stop();
	}

void CWsApp::PointerEvent()
    {
    RDebug::Printf("[{{PROJECT}}] CWsApp::PointerEvent");
    Stop();
    }

CWsApp::~CWsApp()
	{
	delete iRenderer;
	delete iEventHandler;
	delete iAppView;
	}

