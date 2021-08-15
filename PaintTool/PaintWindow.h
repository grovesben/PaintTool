#pragma once
#include <iostream>
#include "Ellipse.h"
#include "Box.h"
#include "PaintToolManager.h"


class PaintWindow
{
public:
	PaintWindow();
	~PaintWindow();

	static void Start();
	static void Update();
	static void Render();

	static bool GetMousePressed();
	static void SetMousePressed(bool _pressed);

	static void NewCanvas();

	static void Drawing(sf::Image* _canvasRef, sf::Vector2i _mousePosition);

	// window
	static sf::RenderWindow* m_RenderWindow;
	static int m_iWindowXSize;
	static int m_iWindowYSize;

	// mouse 
	static sf::Vector2f m_Offset;
	static sf::Vector2f m_fMousePosition;
	static sf::Vector2i m_iMousePosition;
	static bool m_MousePressed;

	// canvas
	static sf::Image* m_pCanvas;
	static sf::Texture* m_pCanvasTexture;
	static sf::Sprite* m_pCanvasSprite;

	// drawing
	static int m_iBrushSize;

	// ellipse
	static sf::CircleShape* m_pCircleShape;
	static CEllipse m_oEllipse;

	// rectangle
	static sf::RectangleShape* m_pRectangleShape;
	static CBox m_oBox;

	// vector
	static std::vector < sf::Shape*> m_vpShapes;

	// colour
	static PaintToolManager* m_pMainManager;
	static sf::Color* m_pCurrentPenColour;

	// tool
	static int m_iTool;

	// toolbar
	static sf::RectangleShape m_ToolBar;
	static sf::RectangleShape m_RectangleButton;
	static sf::RectangleShape m_RectangleButtonSelected;
	static sf::CircleShape m_CircleButton;
	static sf::CircleShape m_CircleButtonSelected;
	static sf::RectangleShape m_DrawingButton;
	static sf::RectangleShape m_DrawingButtonSelected;
	static sf::RectangleShape m_ColourButton1;
	static sf::RectangleShape m_ColourButton2;
	static sf::RectangleShape m_ColourButton3;
};

