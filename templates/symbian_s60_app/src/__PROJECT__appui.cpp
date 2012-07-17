//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}appui.cpp
//

#include "{{PROJECT}l}defs.h"
#include "{{PROJECT}l}appui.h"
#include "{{PROJECT}l}view.h"

#include <eikbtgpc.h>
#include <eikmenup.h>

const TInt KLskPosition = 0;

void C{{PROJECT}}AppUi::ConstructL()
	{
	BaseConstructL();

	// Calculate the size of the application window
	TRect rect = ClientRect();

	// Create the application view
	iAppView = C{{PROJECT}}AppView::NewL(rect);
	AddToStackL(iAppView);

	// Enable iIdleTimer to make the app return to foreground after a set delay
	iIdleTimer = CPeriodic::NewL(CActive::EPriorityStandard);

	iAppView->ActivateL();
	iAppView->DrawNow();

	Cba()->SetCommandL(KLskPosition, EAknSoftkeyOptions, _L("Options"));
	}


//-----------------------------------------------------------------------------
// CEikAppUi
//-----------------------------------------------------------------------------

C{{PROJECT}}AppUi::~C{{PROJECT}}AppUi()
	{
	if(iAppView)
		{
		RemoveFromStack(iAppView);
		delete iAppView;
		}
	delete iIdleTimer;
	}

void C{{PROJECT}}AppUi::HandleForegroundEventL(TBool aForeground)
	{
	if(!aForeground && iIdleTimer)
		{
		if(!iIdleTimer->IsActive())
			{
			iIdleTimer->Start(KIdleTimeOut, 0, TCallBack(BackgroundCallBack, this) );
			}
		}
	}

TInt C{{PROJECT}}AppUi::BackgroundCallBack(TAny* aSelf)
	{
	C{{PROJECT}}AppUi* self = static_cast<C{{PROJECT}}AppUi*>(aSelf);
	self->BringToForeground();
	return KErrNone;
	}

void C{{PROJECT}}AppUi::BringToForeground()
	{
	iIdleTimer->Cancel();
	const TInt err = iCoeEnv->WsSession().SetWindowGroupOrdinalPosition(iCoeEnv->RootWin().Identifier(), 0);
	}

void C{{PROJECT}}AppUi::DynInitMenuPaneL(
    TInt /*aResourceId*/, CEikMenuPane* aMenuPane)
    {
    TInt position;

    if(!aMenuPane->MenuItemExists(E{{PROJECT}}CmdA, position))
        {
        CEikMenuPaneItem::SData item;
        item.iText.Copy(_L("Option A"));
        item.iCommandId = E{{PROJECT}}CmdA;
        item.iFlags = 0;
        item.iCascadeId = 0;
        item.iExtraText = KNullDesC;
        aMenuPane->AddMenuItemL(item);
        }

	if(!aMenuPane->MenuItemExists(E{{PROJECT}}CmdB, position))
        {
        CEikMenuPaneItem::SData item;
        item.iText.Copy(_L("Option B"));
        item.iCommandId = E{{PROJECT}}CmdB;
        item.iFlags = 0;
        item.iCascadeId = 0;
        item.iExtraText = KNullDesC;
        aMenuPane->AddMenuItemL(item);
        }

    if(!aMenuPane->MenuItemExists(EAknCmdExit, position))
        {
        CEikMenuPaneItem::SData item;
        item.iText.Copy(_L("Exit"));
        item.iCommandId = EAknCmdExit;
        item.iFlags = 0;
        item.iCascadeId = 0;
        item.iExtraText=KNullDesC;
        aMenuPane->AddMenuItemL(item);
        }
    }

void C{{PROJECT}}AppUi::HandleCommandL(TInt aCommand)
	{
	switch (aCommand)
		{
		case E{{PROJECT}}CmdA:
			{
			User::InfoPrint(_L("Option A"));
			break;
			}

		case E{{PROJECT}}CmdB:
			{
			User::InfoPrint(_L("Option B"));
			break;
			}

		case EAknSoftkeyBack:
		case EEikCmdExit:
			{
			Exit();
			break;
			}
		}
	}

