//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}.cpp
//

#include "{{PROJECT}l}app.h"
#include <eikstart.h>

static CApaApplication* NewApplication()
	{
	return new C{{PROJECT}}Application;
	}

TInt E32Main()
	{
	return EikStart::RunApplication(NewApplication);
	}

