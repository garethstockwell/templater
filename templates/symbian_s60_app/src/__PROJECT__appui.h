//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}appui.h
//

#ifndef {{PROJECT}u}APPUI_H
#define {{PROJECT}u}APPUI_H

#include <aknappui.h>
#include <{{PROJECT}l}.rsg>

class C{{PROJECT}}AppView;

class C{{PROJECT}}AppUi
:	public CAknAppUi
	{
public:
	void ConstructL();
	~C{{PROJECT}}AppUi();

private:
	// CEikAppUi
	void DynInitMenuPaneL(TInt aResourceId, CEikMenuPane* aMenuPane);
	void HandleCommandL(TInt aCommand);
	void HandleForegroundEventL(TBool aForeground);
	static TInt BackgroundCallBack(TAny* aSelf);
	void BringToForeground();

private:
	C{{PROJECT}}AppView* iAppView;
	CPeriodic* iIdleTimer;
	};

#endif // {{PROJECT}u}APPUI_H

