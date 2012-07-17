//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}app.h
//

#ifndef {{PROJECT}u}APP_H
#define {{PROJECT}u}APP_H

#include <aknapp.h>

class C{{PROJECT}}Application
:	public CAknApplication
	{
private:
	CApaDocument* CreateDocumentL();
	TUid AppDllUid() const;
	};

#endif // {{PROJECT}u}APP_H

