//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}view.cpp
//

#include "{{PROJECT}l}appui.h"
#include "{{PROJECT}l}defs.h"
#include "{{PROJECT}l}view.h"
#include <eikenv.h>

C{{PROJECT}}AppView* C{{PROJECT}}AppView::NewL(const TRect& aRect)
	{
	C{{PROJECT}}AppView* self = new(ELeave) C{{PROJECT}}AppView();
	CleanupStack::PushL(self);
	self->ConstructL(aRect);
	CleanupStack::Pop();
	return self;
	}

C{{PROJECT}}AppView::~C{{PROJECT}}AppView()
	{

	}

C{{PROJECT}}AppView::C{{PROJECT}}AppView()
	{

	}

void C{{PROJECT}}AppView::ConstructL(const TRect& aRect)
	{
	CreateWindowL();
	EnableDragEvents();
	Window().SetPointerGrab(ETrue);
	InitComponentArrayL();
	SetRect(aRect);
	}

void C{{PROJECT}}AppView::SizeChanged()
	{

	}

void C{{PROJECT}}AppView::HandlePointerEventL(const TPointerEvent& /*aPointerEvent*/)
	{

	}

TKeyResponse C{{PROJECT}}AppView::OfferKeyEventL(const TKeyEvent& /*aKeyEvent*/, TEventCode /*aType*/)
	{
	return EKeyWasNotConsumed;
	}

void C{{PROJECT}}AppView::Draw(const TRect& aRect) const
	{
	CWindowGc& gc = SystemGc();
	gc.SetBrushColor(TRgb(255, 255, 255));
	gc.SetBrushStyle(CGraphicsContext::ESolidBrush);
	gc.Clear(aRect);
	}

void C{{PROJECT}}AppView::HandleControlEventL(CCoeControl* /*aControl*/, TCoeEvent /*aEventType*/)
	{

	}

