#include "PaintToolManager.h"

PaintToolManager::PaintToolManager()
{
	// Initialize CHOOSECOLOR
	ZeroMemory(&cc, sizeof(cc));
	cc.lStructSize = sizeof(cc);
	cc.hwndOwner = hwnd;
	cc.lpCustColors = (LPDWORD)acrCustClr;
	cc.rgbResult = rgbCurrent;
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
}

PaintToolManager::~PaintToolManager()
{
}

void PaintToolManager::OpenPaintDialog(sf::Window* _windowRef, sf::Color* _ColourRef)
{
	hwnd = _windowRef->getSystemHandle();

	if (ChooseColor(&cc) == TRUE)
	{
		cr = cc.rgbResult;

		_ColourRef->r = GetRValue(cr);
		_ColourRef->g = GetGValue(cr);
		_ColourRef->b = GetBValue(cr);
	}
}
