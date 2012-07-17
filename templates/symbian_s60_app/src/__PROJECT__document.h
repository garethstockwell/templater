//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}document.h
//

#ifndef {{PROJECT}u}DOCUMENT_H
#define {{PROJECT}u}DOCUMENT_H

#include <akndoc.h>

class C{{PROJECT}}Document
:	public CAknDocument
	{
public:
	C{{PROJECT}}Document(CEikApplication& aApp);

private:
	CEikAppUi* CreateAppUiL();
	};

#endif //{{PROJECT}u}DOCUMENT_H

