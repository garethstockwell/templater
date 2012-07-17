//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}document.cpp
//

#include "{{PROJECT}l}document.h"
#include "{{PROJECT}l}appui.h"

C{{PROJECT}}Document::C{{PROJECT}}Document(CEikApplication& aApp)
	: CAknDocument(aApp)
	{

	}

CEikAppUi* C{{PROJECT}}Document::CreateAppUiL()
	{
	return new(ELeave) C{{PROJECT}}AppUi;
	}

