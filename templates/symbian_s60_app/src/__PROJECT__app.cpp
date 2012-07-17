//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}app.cpp
//

#include "{{PROJECT}l}app.h"
#include "{{PROJECT}l}document.h"

const TUid KUid{{PROJECT}} = { {{UID}} };

TUid C{{PROJECT}}Application::AppDllUid() const
	{
	return KUid{{PROJECT}};
	}

CApaDocument* C{{PROJECT}}Application::CreateDocumentL()
	{
	return new (ELeave) C{{PROJECT}}Document(*this);
	}

