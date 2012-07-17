//
// {{COPYRIGHT}}
//
// {{PROJECT}}
// {{PROJECT}l}view.h
//

#ifndef {{PROJECT}u}VIEW_H
#define {{PROJECT}u}VIEW_H

#include <coecntrl.h>
#include <coecobs.h>


class C{{PROJECT}}AppView
:	public CCoeControl,
	public MCoeControlObserver
	{
public:
	static C{{PROJECT}}AppView* NewL(const TRect& aRect);
	~C{{PROJECT}}AppView();
	RWindow& TheWindow();
	const RWindow& TheWindow() const { return const_cast<C{{PROJECT}}AppView*>(this)->TheWindow(); }

private:
	C{{PROJECT}}AppView();
	void ConstructL(const TRect& aRect);

private:
	// MCoeControlObserver
	void HandleControlEventL(CCoeControl *aControl, TCoeEvent aEventType);

private:
	// CCoeControl
	void HandlePointerEventL(const TPointerEvent& aPointerEvent);
	TKeyResponse OfferKeyEventL(const TKeyEvent& aKeyEvent,TEventCode aType);
	void SizeChanged();
	void Draw(const TRect& aRect) const;
	};

#endif //{{PROJECT}u}VIEW_H

