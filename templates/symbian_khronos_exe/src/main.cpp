//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// main.cpp
//

#include "application.h"
#include <e32debug.h>

void MainL()
	{
	RDebug::Printf("[{{PROJECT}}] ::MainL");
	CWsApp* app = CWsApp::NewL();
	CleanupStack::PushL(app);
    app->Start();
	CleanupStack::PopAndDestroy(1, app);
	}

GLDEF_C TInt E32Main()
    {
	RDebug::Printf("[{{PROJECT}}] ::E32Main");

	CTrapCleanup* tc = CTrapCleanup::New();
	if (!tc)
		{
		return KErrNoMemory;
		}

	CActiveScheduler* as = new CActiveScheduler;
	if (!as)
		{
		delete tc;
		return KErrNoMemory;
		}

	CActiveScheduler::Install(as);
	TRAPD(err, MainL());

	delete as;
	delete tc;
	return err;
    }

