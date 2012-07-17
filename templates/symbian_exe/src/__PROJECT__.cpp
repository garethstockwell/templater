//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}.cpp
//

#include <e32base.h>
#include <e32cons.h>

//-----------------------------------------------------------------------------
// C{{PROJECT}}App
//-----------------------------------------------------------------------------

class C{{PROJECT}}App
:	public CActive
	{
public:
	static C{{PROJECT}}App* NewLC();
	~C{{PROJECT}}App();
	void StartL();
	
private:
	C{{PROJECT}}App();
	void ConstructL();
	void RunL();
	void DoCancel();
	
private:
	CActiveScheduler*	iScheduler;
	CConsoleBase*		iConsole;
	};
	
	
C{{PROJECT}}App* C{{PROJECT}}App::NewLC()
	{
	C{{PROJECT}}App* self = new (ELeave) C{{PROJECT}}App();
	CleanupStack::PushL(self);
	self->ConstructL();
	return self;
	}


C{{PROJECT}}App::C{{PROJECT}}App()
:	CActive(CActive::EPriorityHigh)
	{
	
	}


void C{{PROJECT}}App::ConstructL()
	{
	iScheduler = new (ELeave) CActiveScheduler;
	CActiveScheduler::Install(iScheduler);
	
	iConsole = Console::NewL(KNullDesC, TSize(KConsFullScreen, KConsFullScreen) );
	
	CActiveScheduler::Add(this);
	}


C{{PROJECT}}App::~C{{PROJECT}}App()
	{
	Cancel();
	delete iConsole;
	delete iScheduler;
	}


void C{{PROJECT}}App::StartL()
	{
	iConsole->Printf(_L("Press any key ...\n"));

	iStatus = KRequestPending;
	iConsole->Read(iStatus);
	SetActive();
	
	CActiveScheduler::Start();
	}


void C{{PROJECT}}App::RunL()	
	{
	iConsole->Printf(_L("Exiting ...\n"));
	User::After(500000);
	CActiveScheduler::Stop();
	}


void C{{PROJECT}}App::DoCancel()
	{
	
	}


//-----------------------------------------------------------------------------
// Main
//-----------------------------------------------------------------------------

void MainL()
	{
	C{{PROJECT}}App* app = C{{PROJECT}}App::NewLC();
	app->StartL();
	CleanupStack::PopAndDestroy(app);
	}


TInt E32Main()
	{
	__UHEAP_MARK;
		
	// Setup TRAP harness
	CTrapCleanup* cleanup = CTrapCleanup::New();
	TInt r = KErrNoMemory;
	if (cleanup)
		{
		TRAP(r, MainL());
		delete cleanup;
		}
	
	// Check we didn't leak any memory
	__UHEAP_MARKEND;
	return r;
	}




