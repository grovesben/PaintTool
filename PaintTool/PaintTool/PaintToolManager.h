#pragma once
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <wingdi.h>

class PaintToolManager
{
private:


public:
	PaintToolManager();
	~PaintToolManager();

	CHOOSECOLOR cc;                 // common dialog box structure 
	COLORREF acrCustClr[16]; // array of custom colors 
	HWND hwnd;                      // owner window
	//HBRUSH hbrush;                  // brush handle
	DWORD rgbCurrent;        // initial color selection
	COLORREF cr;
	bool isPaintDialogOpen = false; // true while dialog is open

	void OpenPaintDialog(sf::Window* _windowRef, sf::Color* _ColourRef);
};