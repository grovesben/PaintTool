#include "PaintWindow.h"

//___ setting up all the static variables ___//

// render window
int PaintWindow::m_iWindowXSize = 1024;
int PaintWindow::m_iWindowYSize = 720;
sf::RenderWindow window(sf::VideoMode(PaintWindow::m_iWindowXSize, PaintWindow::m_iWindowYSize), "Paint");
sf::RenderWindow* PaintWindow::m_RenderWindow = &window;

// mouse
sf::Vector2f PaintWindow::m_Offset;
sf::Vector2f PaintWindow::m_fMousePosition;
sf::Vector2i PaintWindow::m_iMousePosition;
bool PaintWindow::m_MousePressed;

// canvas
sf::Image* PaintWindow::m_pCanvas;
sf::Texture* PaintWindow::m_pCanvasTexture;
sf::Sprite* PaintWindow::m_pCanvasSprite;

// drawing
int PaintWindow::m_iBrushSize = 5;
sf::Image* PaintWindow::m_pDrawingCanvas;
sf::Texture* PaintWindow::m_pDrawingCanvasTexture;
sf::Sprite* PaintWindow::m_pDrawingCanvasSprite;

// line
sf::RectangleShape lineShape(sf::Vector2f(1, 1));
sf::RectangleShape* PaintWindow::m_pLine = &lineShape;
 CLine PaintWindow::m_oLine;

// ellipse
sf::CircleShape circleShape(0.0f);
sf::CircleShape* PaintWindow::m_pCircleShape = &circleShape;
CEllipse circle;
CEllipse PaintWindow::m_oEllipse = circle;

// rectangle
sf::Vector2f dimensions(1.0f, 1.0f);
sf::RectangleShape rectangleShape(dimensions);
sf::RectangleShape* PaintWindow::m_pRectangleShape = &rectangleShape;
CBox box;
CBox PaintWindow::m_oBox = box;

// triangle
sf::CircleShape triangleShape(0.0f);
sf::CircleShape* PaintWindow::m_pTriangleShape = &triangleShape;
CTriangle triangle;
CTriangle PaintWindow::m_oTriangle = triangle;

// pentagon
sf::CircleShape pentagonShape(0.0f);
sf::CircleShape* PaintWindow::m_pPentagonShape = &pentagonShape;
CPentagon pentagon;
CPentagon PaintWindow::m_oPentagon = pentagon;

// bitmap
sf::Texture* PaintWindow::m_pBitmapTexture;
sf::Sprite* PaintWindow::m_pBitmapSprite;

// vector
std::vector< sf::Shape*> PaintWindow::m_vpShapes;
std::vector <sf::Sprite*> PaintWindow::m_vpSprites;
std::vector <sf::Sprite*> PaintWindow::m_vpDrawing;
std::vector <sf::Image*> PaintWindow::m_vpDrawingImage;
std::vector <sf::Texture*> PaintWindow::m_vpDrawingTexture;

// colour
PaintToolManager* PaintWindow::m_pMainManager = new PaintToolManager();
sf::Color* PaintWindow::m_pCurrentPenColour = new sf::Color(sf::Color::Red);

// aykroyd
std::string PaintWindow::m_sAykroyd = "image/Aykroyd_0.bmp";
int PaintWindow::m_iAykroydCounter = 0;

// tool
int PaintWindow::m_iTool = 1;

// toolbar
sf::Vector2f toolbarDimensions(((float)PaintWindow::m_iWindowXSize),50.0f);
sf::RectangleShape PaintWindow::m_ToolBar(toolbarDimensions);

// buttons
// rectangle button
sf::Vector2f rectangleButtonDimensions(40.0f, 40.0f);
sf::RectangleShape PaintWindow::m_RectangleButton(rectangleButtonDimensions);
sf::Vector2f buttonSelectedDimensions(20.0f, 20.0f);
sf::RectangleShape PaintWindow::m_RectangleButtonSelected(buttonSelectedDimensions);

// circle button
sf::CircleShape PaintWindow::m_CircleButton(20.0f);
sf::CircleShape PaintWindow::m_CircleButtonSelected(10.0f);

// drawing button
sf::Vector2f drawingButtonDimensions(20.0f, 40.0f);
sf::RectangleShape PaintWindow::m_DrawingButton(drawingButtonDimensions);
sf::Vector2f drawingSelectedDimensions1(3.0f, 3.0f), drawingSelectedDimensions2(5.5f, 5.5f), drawingSelectedDimensions3(10.0f, 10.0f);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected1(drawingSelectedDimensions1);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected2(drawingSelectedDimensions2);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected3(drawingSelectedDimensions3);

// colour button
sf::Vector2f colourDimension(13.33f, 40.0f);
sf::RectangleShape PaintWindow::m_ColourButton1(colourDimension);
sf::RectangleShape PaintWindow::m_ColourButton2(colourDimension);
sf::RectangleShape PaintWindow::m_ColourButton3(colourDimension);

// line button
sf::Vector2f lineButtonDimensions(40.0f, 40.0f);
sf::RectangleShape PaintWindow::m_LineButton(lineButtonDimensions);
sf::Vector2f lineButtonSelectedDimensions1(20.0f, 2.5f), lineButtonSelectedDimensions2(20.0f, 5.0f), lineButtonSelectedDimensions3(20.0f, 10.0f);
sf::RectangleShape PaintWindow::m_LineButtonSelected1(lineButtonSelectedDimensions1);
sf::RectangleShape PaintWindow::m_LineButtonSelected2(lineButtonSelectedDimensions2);
sf::RectangleShape PaintWindow::m_LineButtonSelected3(lineButtonSelectedDimensions3);

// triangle button
sf::CircleShape PaintWindow::m_TriangleButton(26.0f);
sf::CircleShape PaintWindow::m_TriangleButtonSelected(16.0f);

// pentagon button
sf::CircleShape PaintWindow::m_PentagonButton(21.0f);
sf::CircleShape PaintWindow::m_PentagonButtonSelected(11.0f);

// akroyd button
sf::Texture PaintWindow::m_tAykroydButton;
sf::Sprite PaintWindow::m_sAykroydButton;
sf::Texture PaintWindow::m_tAykroydButtonSelected;
sf::Sprite PaintWindow::m_sAykroydButtonSelected;

PaintWindow::PaintWindow()
{
	m_MousePressed = false;
}

PaintWindow::~PaintWindow()
{
	m_RenderWindow = nullptr;
	m_pCircleShape = nullptr;
	m_pRectangleShape = nullptr;
	m_pMainManager = nullptr;

}

void PaintWindow::Start()
{
	//m_RenderWindow->setVerticalSyncEnabled(true);
	// set bit map stamp
	NewBitmapStamp();
	
	// toolbar
	m_ToolBar.setFillColor(sf::Color::Black);

	// rectangle button
	sf::Vector2f rectanglePosition(5.0f, 5.0f);
	m_RectangleButton.setPosition(rectanglePosition);
	m_RectangleButton.setFillColor(sf::Color::White);
	m_RectangleButtonSelected.setPosition(rectanglePosition.x + 10.0f, rectanglePosition.y + 10.0f);
	m_RectangleButtonSelected.setFillColor(sf::Color::White);

	// circle button
	m_CircleButton.setFillColor(sf::Color::White);
	m_CircleButton.setPosition(50.0f, 5.0f);
	m_CircleButtonSelected.setFillColor(sf::Color::White);
	m_CircleButtonSelected.setPosition(60.0f, 15.0f);

	// line button
	sf::Vector2f linePosition(95.0f, 5.0f);
	m_LineButton.setFillColor(sf::Color::White);
	m_LineButton.setPosition(linePosition);
	m_LineButtonSelected1.setPosition(linePosition.x + 10.0f, linePosition.y + 7.5f);
	m_LineButtonSelected2.setPosition(linePosition.x + 10.0f, linePosition.y + 16.5f);
	m_LineButtonSelected3.setPosition(linePosition.x + 10.0f, linePosition.y + 27.5f);
	m_LineButtonSelected1.setFillColor(sf::Color::Black);
	m_LineButtonSelected2.setFillColor(sf::Color::Black);
	m_LineButtonSelected3.setFillColor(sf::Color::Black);

	// drawing button
	sf::Vector2f drawingPosition(140.0f, 5.0f);
	float drawingButtonPosition = m_DrawingButton.getSize().x / 2;
	m_DrawingButton.setPosition(drawingPosition);
	m_DrawingButton.setFillColor(sf::Color::White);
	m_DrawingButtonSelected1.setPosition(drawingPosition.x + drawingButtonPosition - 1.5f, drawingPosition.y + 7.5f);
	m_DrawingButtonSelected2.setPosition(drawingPosition.x + drawingButtonPosition - 2.5f, drawingPosition.y + 16.5f);
	m_DrawingButtonSelected3.setPosition(drawingPosition.x + drawingButtonPosition - 5.0f, drawingPosition.y + 27.5f);
	m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
	m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
	m_DrawingButtonSelected3.setFillColor(sf::Color::Black);

	// triangle 
	m_TriangleButton.setFillColor(sf::Color::White);
	m_TriangleButton.setPosition(165.0f, 5.0f);
	m_TriangleButton.setPointCount(3);
	m_TriangleButtonSelected.setFillColor(sf::Color::White);
	m_TriangleButtonSelected.setPosition(175.0f, 15.0f);
	m_TriangleButtonSelected.setPointCount(3);

	// pentagon
	m_PentagonButton.setFillColor(sf::Color::White);
	m_PentagonButton.setPosition(215.0f, 5.0f);
	m_PentagonButton.setPointCount(5);
	m_PentagonButtonSelected.setFillColor(sf::Color::White);
	m_PentagonButtonSelected.setPosition(225.0f, 15.0f);
	m_PentagonButtonSelected.setPointCount(5);

	// colour button
	sf::Vector2f colourPosition(window.getSize().x - 45.0f, 5.0f);
	m_ColourButton1.setPosition(colourPosition);
	m_ColourButton1.setFillColor(sf::Color::Red);
	m_ColourButton2.setPosition(colourPosition.x + 13.33f, colourPosition.y);
	m_ColourButton2.setFillColor(sf::Color::Green);
	m_ColourButton3.setPosition(colourPosition.x + 26.66f, colourPosition.y);
	m_ColourButton3.setFillColor(sf::Color::Blue);

	// aykroyd button
	m_tAykroydButton.loadFromFile("image/skull_2.bmp");
	m_sAykroydButton.setTexture(m_tAykroydButton);
	m_sAykroydButton.setPosition(265.0f, 0.0f);
	m_tAykroydButtonSelected.loadFromFile("image/skull_0.bmp");
	m_sAykroydButtonSelected.setTexture(m_tAykroydButtonSelected);
	m_sAykroydButtonSelected.setPosition(265.0f, 0.0f);
	m_sAykroydButtonSelected.setScale(0, 0);

	PaintWindow::NewCanvas();
	PaintWindow::Update();
}

void PaintWindow::Update()
{

	bool canDelete = true;
	while (m_RenderWindow->isOpen())
	{
		sf::Event event;
		while (m_RenderWindow->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_RenderWindow->close();
			}
		}

		if (event.type == sf::Event::MouseButtonReleased)
		{
			SetMousePressed(false);
			//m_vpDrawing.push_back(m_pDrawingCanvasSprite);
		}

		// undo attempt
	/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			if (canDelete == true && m_vpShapes.size() != 0)
			{
				m_vpShapes.pop_back();
					canDelete = false;
			}
		}*/
		// save function
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (canDelete == true)
			{
				sf::Texture texture;
				texture.create(window.getSize().x, window.getSize().y);
				texture.update(window);
				*m_pCanvas = texture.copyToImage();
				m_pCanvasTexture->loadFromImage(*m_pCanvas);
				m_pCanvasSprite->setTexture(*m_pCanvasTexture);

				WipeVectors();
				canDelete = false;
			}
		}
		// load function
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::L))
		{
			if (canDelete == true)
			{
				WipeVectors();
				canDelete = false;
			}
		}
		// new canvas function
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::N))
		{
			if (canDelete == true)
			{
				delete m_pCanvas;
				m_pCanvas = nullptr;
				delete m_pCanvasSprite;
				m_pCanvasSprite = nullptr;
				delete m_pCanvasTexture;
				m_pCanvasTexture = nullptr;

				NewCanvas();
				WipeVectors();
				canDelete = false;
			}
		}

		if (event.type == sf::Event::EventType::KeyReleased)
		{
			canDelete = true;
		}
			

		// Resize window without changing anything
		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_RenderWindow->setView(sf::View(visibleArea));
		}

		// get mouse position so straight lines work properly 
		m_iMousePosition = sf::Mouse::getPosition(*m_RenderWindow);

		// when mouse if first clicked, it enters here
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MousePressed == false)
		{
			// check if button on tool bar is clicked
			if (m_iMousePosition.y < 50.0f)
			{
				ButtonPressCheck();
			}

			// add shapes to vector
			switch (m_iTool)
			{
			case 0:
				m_pCircleShape = m_oEllipse.NewShape();
				m_vpShapes.push_back(m_pCircleShape);
				break;
			case 1:
				m_pRectangleShape = m_oBox.NewShape();
				m_vpShapes.push_back(m_pRectangleShape);
				break;
			case 2:
				NewDrawingCanvas();
				break;
			case 3:
				m_pLine = m_oLine.NewShape();
				m_vpShapes.push_back(m_pLine);
				break;
			case 4:
				m_pTriangleShape = m_oTriangle.NewShape();
				m_vpShapes.push_back(m_pTriangleShape);
				break;
			case 5:
				m_pPentagonShape = m_oPentagon.NewShape();
				m_vpShapes.push_back(m_pPentagonShape);
				break;
			case 6:
				if (m_iMousePosition.y > 50.0f)
				{
					NewBitmapStamp();
					m_vpSprites.push_back(m_pBitmapSprite);
				}
				break;
			default:
				break;
			}
		
			// setup mouse position for setting offset
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_RenderWindow);
			m_iMousePosition = mousePos;
			m_fMousePosition.x = ((float)mousePos.x);
			m_fMousePosition.y = ((float)mousePos.y);

			// set offset for scaling shapes
			m_Offset = m_fMousePosition;

			// set position of shapes
			switch (m_iTool)
			{
			case 0:
				m_pCircleShape->setPosition(m_fMousePosition);
				break;
			case 1:
				m_pRectangleShape->setPosition(m_fMousePosition);
				break;
			case 2:
				// drawing doesn't need this 
				break;
			case 3:
				m_pLine->setPosition(m_fMousePosition);
				break;
			case 4:
				m_pTriangleShape->setPosition(m_fMousePosition);
				break;
			case 5:
				m_pPentagonShape->setPosition(m_fMousePosition);
				break;
			case 6:
				m_pBitmapSprite->setPosition(m_fMousePosition);
				break;

			default:
				break;
			}
		
			SetMousePressed(true);
		}

		// enters here while mouse button down
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MousePressed == true)
		{
			// line stuff
			float opposite, adjacent, angle, hypo;
			sf::Vector2f lineSize;


			switch (m_iTool)
			{
			case 0:
				//scale circle set colour
				m_pCircleShape->setScale(m_fMousePosition - m_Offset);
				m_pCircleShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 1:
				// scale circle set colour
				m_pRectangleShape->setScale(m_fMousePosition - m_Offset);
				m_pRectangleShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 2:
				// drawing pixels on canvas
				if (m_iMousePosition.y > m_iBrushSize && m_iMousePosition.y < m_iWindowYSize - m_iBrushSize)
				{
					//Drawing(m_pCanvas, m_iMousePosition);
					//m_pCanvasTexture->loadFromImage(*m_pCanvas);
					Drawing(m_pDrawingCanvas, m_iMousePosition);
					m_pDrawingCanvasTexture->loadFromImage(*m_pDrawingCanvas);
				}
				break;
			case 3:
				// use pythagoras to set line(rectangle) angle and length
				opposite = m_fMousePosition.y - m_pLine->getPosition().y;
				adjacent = m_fMousePosition.x - m_pLine->getPosition().x;
				angle = atan2(opposite, adjacent);
				angle *= 180 / 3.14;
				hypo = sqrt(opposite * opposite + adjacent * adjacent);
				lineSize.x = hypo;
				lineSize.y = m_iBrushSize;
				m_pLine->setRotation(angle);
				m_pLine->setSize(sf::Vector2f(lineSize));
				m_pLine->setFillColor(*m_pCurrentPenColour);

				break;
			case 4:
				m_pTriangleShape->setScale(m_fMousePosition - m_Offset);
				m_pTriangleShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 5:
				m_pPentagonShape->setScale(m_fMousePosition - m_Offset);
				m_pPentagonShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 6:
				// Aykroyd needs no telling where to be.
				break;
			default:
				break;
			}


			// update/setup mouse position
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_RenderWindow);
			m_iMousePosition = mousePos;
			m_fMousePosition.x = ((float)mousePos.x);
			m_fMousePosition.y = ((float)mousePos.y);
		}

		// buttons for debug
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			m_pMainManager->OpenPaintDialog(&window, m_pCurrentPenColour);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) // circle
		{
			m_iTool = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) // rectangle
		{
			m_iTool = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) // drawing
		{
			m_iTool = 2;
		}		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) // line
		{
			m_iTool = 3;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5)) // triangle
		{
			m_iTool = 4;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6)) // pentagon
		{
			m_iTool = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7)) // aykroyd
		{
			m_iTool = 6;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			m_iBrushSize = 2;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_iBrushSize = 5;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		{
			m_iBrushSize = 10;
		}

		// sets currently selected tool (selected icon) to colour selected
		switch (m_iTool)
		{
		case 0:
			m_CircleButtonSelected.setFillColor(*m_pCurrentPenColour);
			break;
		case 1:
			m_RectangleButtonSelected.setFillColor(*m_pCurrentPenColour);
			break;
		case 2:
			if (m_iBrushSize == 2)
			{
				m_DrawingButtonSelected1.setFillColor(*m_pCurrentPenColour);
			}
			else if(m_iBrushSize == 5)
			{
				m_DrawingButtonSelected2.setFillColor(*m_pCurrentPenColour);
			}
			else if (m_iBrushSize == 10)
			{
				m_DrawingButtonSelected3.setFillColor(*m_pCurrentPenColour);
			}
			break;
		case 3:
			if (m_iBrushSize == 2)
			{
				m_LineButtonSelected1.setFillColor(*m_pCurrentPenColour);
			}
			else if (m_iBrushSize == 5)
			{
				m_LineButtonSelected2.setFillColor(*m_pCurrentPenColour);
			}
			else if (m_iBrushSize == 10)
			{
				m_LineButtonSelected3.setFillColor(*m_pCurrentPenColour);
			}
			break;
		case 4:
			m_TriangleButtonSelected.setFillColor(*m_pCurrentPenColour);
			break;
		case 5:
			m_PentagonButtonSelected.setFillColor(*m_pCurrentPenColour);
			break;
		case 6:
			m_sAykroydButtonSelected.setScale(1, 1);
			break;
		default:
			break;
		}

		PaintWindow::Render();

	}
}

void PaintWindow::Render()
{

	m_RenderWindow->clear(sf::Color::Black);

	// canvas for drawing
	m_RenderWindow->draw(*m_pCanvasSprite);

	// drawing
	if (m_vpDrawing.size() != 0)
	{
		for (int i = 0; i < m_vpDrawing.size(); i++)
		{
			window.draw(*m_vpDrawing[i]);
		}
	}

	// all shapes
	for (int i = 0; i < m_vpShapes.size(); i++)
	{
		if (m_vpShapes[i]->getPosition().x > 1)
		{
			window.draw(*m_vpShapes[i]);
		}
	}

	// bitmap stamps
	for (int i = 0; i < m_vpSprites.size(); i++)
	{
		window.draw(*m_vpSprites[i]);
	}
	
	// all buttons/selected icons
	m_RenderWindow->draw(m_ToolBar);
	m_RenderWindow->draw(m_RectangleButton);
	m_RenderWindow->draw(m_CircleButton);
	m_RenderWindow->draw(m_LineButton);
	m_RenderWindow->draw(m_DrawingButton);
	m_RenderWindow->draw(m_RectangleButtonSelected);
	m_RenderWindow->draw(m_CircleButtonSelected);
	m_RenderWindow->draw(m_LineButtonSelected1);
	m_RenderWindow->draw(m_LineButtonSelected2);
	m_RenderWindow->draw(m_LineButtonSelected3);
	m_RenderWindow->draw(m_DrawingButtonSelected1);
	m_RenderWindow->draw(m_DrawingButtonSelected2);
	m_RenderWindow->draw(m_DrawingButtonSelected3);
	m_RenderWindow->draw(m_ColourButton1);
	m_RenderWindow->draw(m_ColourButton2);
	m_RenderWindow->draw(m_ColourButton3);
	m_RenderWindow->draw(m_TriangleButton);
	m_RenderWindow->draw(m_TriangleButtonSelected);
	m_RenderWindow->draw(m_PentagonButton);
	m_RenderWindow->draw(m_PentagonButtonSelected);
	m_RenderWindow->draw(m_sAykroydButton);
	m_RenderWindow->draw(m_sAykroydButtonSelected);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{

	}

	m_RenderWindow->display();
}

bool PaintWindow::GetMousePressed()
{
	return m_MousePressed;
}

void PaintWindow::SetMousePressed(bool _pressed)
{
	m_MousePressed = _pressed;
}

// Canvas to be drawn on using pixel change
void PaintWindow::NewCanvas()
{
	sf::Image* canvas = new sf::Image;
	canvas->create(m_iWindowXSize, m_iWindowYSize, sf::Color::White);
	m_pCanvas = canvas;
	
	sf::Texture* canvasTexture = new sf::Texture;
	canvasTexture->loadFromImage(*canvas);
	m_pCanvasTexture = canvasTexture;

	sf::Sprite* canvasSprite = new sf::Sprite;
	canvasSprite->setTexture(*m_pCanvasTexture);
	canvasSprite->setOrigin((*canvasSprite).getGlobalBounds().width / 2, (*canvasSprite).getGlobalBounds().height / 2);
	canvasSprite->setPosition(m_iWindowXSize / 2, m_iWindowYSize / 2);
	m_pCanvasSprite = canvasSprite;
	
}

// Creates all the things needed to create a summoning portal to the lair of Aykroyd
void PaintWindow::NewBitmapStamp()
{
	sf::Texture* imageTex;
	imageTex = new sf::Texture();
	imageTex->loadFromFile(m_sAykroyd);
	if (m_iAykroydCounter == 20)
	{
		m_iAykroydCounter = 0;
	}
	SetAykroyd(m_iAykroydCounter);
	if (!(imageTex->loadFromFile(m_sAykroyd)))
	{
		std::cout << "Aykroyd not found" << std::endl;
	}
	m_pBitmapTexture = imageTex;

	sf::Sprite* imageSprite;
	imageSprite = new sf::Sprite();
	imageSprite->setTexture(*imageTex);
	m_pBitmapSprite = imageSprite;
	m_pBitmapSprite->setOrigin(m_pBitmapSprite->getLocalBounds().width / 2, m_pBitmapSprite->getLocalBounds().height / 2);

	m_iAykroydCounter++;
}

void PaintWindow::NewDrawingCanvas()
{

	sf::Image* canvas = new sf::Image;
	canvas->create(m_iWindowXSize, m_iWindowYSize, sf::Color::White);
	m_pDrawingCanvas = canvas;
	m_vpDrawingImage.push_back(m_pDrawingCanvas);

	sf::Texture* canvasTexture = new sf::Texture;
	canvasTexture->loadFromImage(*canvas);
	m_pDrawingCanvasTexture = canvasTexture;
	m_vpDrawingTexture.push_back(m_pDrawingCanvasTexture);

	sf::Sprite* canvasSprite = new sf::Sprite;
	canvasSprite->setTexture(*m_pDrawingCanvasTexture);
	canvasSprite->setOrigin((*canvasSprite).getGlobalBounds().width / 2, (*canvasSprite).getGlobalBounds().height / 2);
	canvasSprite->setPosition(m_iWindowXSize / 2, m_iWindowYSize / 2);
	m_pDrawingCanvasSprite = canvasSprite;

	
	m_pDrawingCanvasTexture->update(window);
	*m_pDrawingCanvas = m_pDrawingCanvasTexture->copyToImage();
	m_pDrawingCanvasTexture->loadFromImage(*m_pDrawingCanvas);
	sf::Sprite* m_pDrawingCanvasSprite = new sf::Sprite;
	m_pDrawingCanvasSprite->setTexture(*m_pDrawingCanvasTexture);
	m_vpDrawing.push_back(m_pDrawingCanvasSprite);
}

// draws the pixels
void PaintWindow::Drawing(sf::Image* _canvasRef, sf::Vector2i _mousePosition)
{

	for (int i = -m_iBrushSize; i < m_iBrushSize; i++)
	{
		for (int j = -m_iBrushSize; j < m_iBrushSize; j++)
		{
			_canvasRef->setPixel(_mousePosition.x + i, _mousePosition.y + j, *m_pCurrentPenColour);
		}
	}
	
}

void PaintWindow::WipeVectors()
{
	while (m_vpShapes.size() != 0)
	{
		m_vpShapes.pop_back();
	}
	while (m_vpSprites.size() != 0)
	{
		m_vpSprites.pop_back();
	}
	while (m_vpDrawing.size() != 0)
	{
		m_vpDrawing.pop_back();
	}
	while (m_vpDrawingImage.size() != 0)
	{
		m_vpDrawingImage.pop_back();
	}
	while (m_vpDrawingTexture.size() != 0)
	{
		m_vpDrawingTexture.pop_back();
	}
}


// checks if a button was pressed
void PaintWindow::ButtonPressCheck()
{
	// square
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 45.0f && m_iMousePosition.x > 5.0f && m_iMousePosition.y > 5.0f)
	{
		m_RectangleButtonSelected.setFillColor(*m_pCurrentPenColour);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(0, 0);
		m_iTool = 1;
	}
	// circle
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 90.0f && m_iMousePosition.x > 50.0f && m_iMousePosition.y > 5.0f)
	{
		m_CircleButtonSelected.setFillColor(*m_pCurrentPenColour);
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(0, 0);
		m_iTool = 0;
	}
	// line 
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 135.0f && m_iMousePosition.x > 95.0f && m_iMousePosition.y > 5.0f)
	{
		if (m_iMousePosition.y < 15.0f)
		{
			m_LineButtonSelected1.setFillColor(*m_pCurrentPenColour);
			m_LineButtonSelected2.setFillColor(sf::Color::Black);
			m_LineButtonSelected3.setFillColor(sf::Color::Black);
			m_iBrushSize = 2;
		}
		else if (m_iMousePosition.y < 29.0f && m_iMousePosition.y > 15.5f)
		{
			m_LineButtonSelected1.setFillColor(sf::Color::Black);
			m_LineButtonSelected2.setFillColor(*m_pCurrentPenColour);
			m_LineButtonSelected3.setFillColor(sf::Color::Black);
			m_iBrushSize = 5;
		}
		else if (m_iMousePosition.y > 30.5f)
		{
			m_LineButtonSelected1.setFillColor(sf::Color::Black);
			m_LineButtonSelected2.setFillColor(sf::Color::Black);
			m_LineButtonSelected3.setFillColor(*m_pCurrentPenColour);
			m_iBrushSize = 10;
		}
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(0, 0);

		m_iTool = 3;
	}
	// drawing
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 160.0f && m_iMousePosition.x > 140.0f && m_iMousePosition.y > 5.0f) // drawing conditional
	{
		if (m_iMousePosition.y < 15.0f)
		{
			m_DrawingButtonSelected1.setFillColor(*m_pCurrentPenColour);
			m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
			m_iBrushSize = 2;
		}
		else if (m_iMousePosition.y < 29.0f && m_iMousePosition.y > 15.5f)
		{
			m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected2.setFillColor(*m_pCurrentPenColour);
			m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
			m_iBrushSize = 5;
		}
		else if (m_iMousePosition.y > 30.5f)
		{
			m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected3.setFillColor(*m_pCurrentPenColour);
			m_iBrushSize = 10;
		}
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(0, 0);

		m_iTool = 2;
	}
	// aykroyd
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 210.0f && m_iMousePosition.x > 169.0f && m_iMousePosition.y > 5.0f)
	{
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(*m_pCurrentPenColour);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(0, 0);
		m_iTool = 4;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 254.0f && m_iMousePosition.x > 218.0f && m_iMousePosition.y > 5.0f)
	{
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(*m_pCurrentPenColour);
		m_sAykroydButtonSelected.setScale(0, 0);
		m_iTool = 5;
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 300.0f && m_iMousePosition.x > 269.0f && m_iMousePosition.y > 5.0f)
	{
		m_RectangleButtonSelected.setFillColor(sf::Color::White);
		m_CircleButtonSelected.setFillColor(sf::Color::White);
		m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
		m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
		m_LineButtonSelected1.setFillColor(sf::Color::Black);
		m_LineButtonSelected2.setFillColor(sf::Color::Black);
		m_LineButtonSelected3.setFillColor(sf::Color::Black);
		m_TriangleButtonSelected.setFillColor(sf::Color::White);
		m_PentagonButtonSelected.setFillColor(sf::Color::White);
		m_sAykroydButtonSelected.setScale(1, 1);
		m_iTool = 6;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 1020.0f && m_iMousePosition.x > 975.0f && m_iMousePosition.y > 5.0f)
	{
		m_pMainManager->OpenPaintDialog(&window, m_pCurrentPenColour);

	}
}

// welcome to Aykroyd's lair, here is where his form shifts
void PaintWindow::SetAykroyd(int _aykroyd)
{
	m_sAykroyd = "image/Aykroyd_" + std::to_string(_aykroyd) +".bmp";
}

