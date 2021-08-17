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

// vector
std::vector< sf::Shape*> PaintWindow::m_vpShapes;

// colour
PaintToolManager* PaintWindow::m_pMainManager = new PaintToolManager();
sf::Color* PaintWindow::m_pCurrentPenColour = new sf::Color(sf::Color::Red);

// tool
int PaintWindow::m_iTool = 0;

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
sf::Vector2f drawingButtonDimensions(40.0f, 40.0f);
sf::RectangleShape PaintWindow::m_DrawingButton(drawingButtonDimensions);
sf::Vector2f drawingSelectedDimensions1(20.0f, 2.5f), drawingSelectedDimensions2(20.0f, 5.0f), drawingSelectedDimensions3(20.0f, 10.0f);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected1(drawingSelectedDimensions1);

sf::RectangleShape PaintWindow::m_DrawingButtonSelected2(drawingSelectedDimensions2);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected3(drawingSelectedDimensions3);

// colour button
sf::Vector2f colourDimension(13.33f, 40.0f);
sf::RectangleShape PaintWindow::m_ColourButton1(colourDimension);
sf::RectangleShape PaintWindow::m_ColourButton2(colourDimension);
sf::RectangleShape PaintWindow::m_ColourButton3(colourDimension);

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
	m_ToolBar.setFillColor(sf::Color::Black);

	sf::Vector2f rectanglePosition(5.0f, 5.0f);
	m_RectangleButton.setPosition(rectanglePosition);
	m_RectangleButton.setFillColor(sf::Color::White);
	m_RectangleButtonSelected.setPosition(rectanglePosition.x + 10.0f, rectanglePosition.y + 10.0f);
	m_RectangleButtonSelected.setFillColor(sf::Color::White);


	m_CircleButton.setFillColor(sf::Color::White);
	m_CircleButton.setPosition(50.0f, 5.0f);
	m_CircleButtonSelected.setFillColor(sf::Color::White);
	m_CircleButtonSelected.setPosition(60.0f, 15.0f);

	sf::Vector2f drawingPosition(100.0f, 5.0f);
	m_DrawingButton.setPosition(drawingPosition);
	m_DrawingButton.setFillColor(sf::Color::White);
	m_DrawingButtonSelected1.setPosition(drawingPosition.x + 10.0f, drawingPosition.y + 7.5f);
	m_DrawingButtonSelected2.setPosition(drawingPosition.x + 10.0f, drawingPosition.y + 16.5f);
	m_DrawingButtonSelected3.setPosition(drawingPosition.x + 10.0f, drawingPosition.y + 27.5f);
	m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
	m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
	m_DrawingButtonSelected3.setFillColor(sf::Color::Black);

	sf::Vector2f colourPosition(150.0f, 5.0f);
	m_ColourButton1.setPosition(colourPosition);
	m_ColourButton1.setFillColor(sf::Color::Red);
	m_ColourButton2.setPosition(colourPosition.x + 13.33f, colourPosition.y);
	m_ColourButton2.setFillColor(sf::Color::Green);
	m_ColourButton3.setPosition(colourPosition.x + 26.66f, colourPosition.y);
	m_ColourButton3.setFillColor(sf::Color::Blue);

	PaintWindow::NewCanvas();
	PaintWindow::Update();
}

void PaintWindow::Update()
{


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

		if (event.type == sf::Event::Resized)
		{
			sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
			m_RenderWindow->setView(sf::View(visibleArea));
		}

		m_iMousePosition = sf::Mouse::getPosition(*m_RenderWindow);
		// check if button pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 50.0f && m_iMousePosition.x > 5.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_RectangleButtonSelected.setFillColor(*m_pCurrentPenColour);
			m_CircleButtonSelected.setFillColor(sf::Color::White);
			m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
			m_iTool = 1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 100.0f && m_iMousePosition.x > 50.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_CircleButtonSelected.setFillColor(*m_pCurrentPenColour);
			m_RectangleButtonSelected.setFillColor(sf::Color::White);
			m_DrawingButtonSelected1.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected2.setFillColor(sf::Color::Black);
			m_DrawingButtonSelected3.setFillColor(sf::Color::Black);
			m_iTool = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 150.0f && m_iMousePosition.x > 100.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
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
			m_iTool = 2;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 200.0f && m_iMousePosition.x > 150.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_pMainManager->OpenPaintDialog(&window, m_pCurrentPenColour);
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MousePressed == true)
		{
			// line stuff
			float opposite, adjacent, angle, hypo;
			sf::Vector2f lineSize;

			switch (m_iTool)
			{
			case 0:
				//scale m_CircleShape
				m_pCircleShape->setScale(m_fMousePosition - m_Offset);
				m_pCircleShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 1:
				m_pRectangleShape->setScale(m_fMousePosition - m_Offset);
				m_pRectangleShape->setFillColor(*m_pCurrentPenColour);
				break;
			case 2:
				if (m_iMousePosition.y > m_iBrushSize && m_iMousePosition.y < m_iWindowYSize - m_iBrushSize)
				{
					Drawing(m_pCanvas, m_iMousePosition);
					m_pCanvasTexture->loadFromImage(*m_pCanvas);
				}
				break;
			case 3:
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
				
			default:
				break;
			}

			// update/setup mouse position
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_RenderWindow);
			m_iMousePosition = mousePos;
			m_fMousePosition.x = ((float)mousePos.x);
			m_fMousePosition.y = ((float)mousePos.y);
		

		}
		else if (event.type == sf::Event::MouseButtonReleased)
		{
			SetMousePressed(false);

		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_MousePressed == false)
		{
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
				break;
			case 3:
				m_pLine = m_oLine.NewShape();
				m_vpShapes.push_back(m_pLine);
				break;
			default:
				break;
			}



			// setup mouse position
			sf::Vector2i mousePos = sf::Mouse::getPosition(*m_RenderWindow);
			m_iMousePosition = mousePos;
			m_fMousePosition.x = ((float)mousePos.x);
			m_fMousePosition.y = ((float)mousePos.y);


			// set offset
			m_Offset = m_fMousePosition;

			// set position of shapes / draw
			switch (m_iTool)
			{
			case 0:
				m_pCircleShape->setPosition(m_fMousePosition);
				break;
			case 1:
				m_pRectangleShape->setPosition(m_fMousePosition);
				break;
			case 2:
				break;
			case 3:
				m_pLine->setPosition(m_fMousePosition);
			default:
				break;
			}


			SetMousePressed(true);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
		{
			m_pMainManager->OpenPaintDialog(&window, m_pCurrentPenColour);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		{
			m_iTool = 0;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		{
			m_iTool = 1;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
		{
			m_iTool = 2;
		}		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
		{
			m_iTool = 3;
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
			// set fill colour for line button
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
	m_RenderWindow->draw(*m_pCanvasSprite);
	for (int i = 0; i < m_vpShapes.size(); i++)
	{
		window.draw(*m_vpShapes[i]);
	}
	m_RenderWindow->draw(m_ToolBar);
	m_RenderWindow->draw(m_RectangleButton);
	m_RenderWindow->draw(m_CircleButton);
	m_RenderWindow->draw(m_DrawingButton);
	m_RenderWindow->draw(m_RectangleButtonSelected);
	m_RenderWindow->draw(m_CircleButtonSelected);
	m_RenderWindow->draw(m_DrawingButtonSelected1);
	m_RenderWindow->draw(m_DrawingButtonSelected2);
	m_RenderWindow->draw(m_DrawingButtonSelected3);
	m_RenderWindow->draw(m_ColourButton1);
	m_RenderWindow->draw(m_ColourButton2);
	m_RenderWindow->draw(m_ColourButton3);


	// create static function/variable for transparent canvas
	//sf::Image* canvas = new sf::Image;
	//canvas->create(m_iWindowXSize, m_iWindowYSize, sf::Color::Transparent);

	//sf::Texture* canvasTexture = new sf::Texture;
	//canvasTexture->loadFromImage(*canvas);

	//sf::Sprite* canvasSprite = new sf::Sprite;
	//canvasSprite->setTexture(*canvasTexture);
	//canvasSprite->setOrigin((*canvasSprite).getGlobalBounds().width / 2, (*canvasSprite).getGlobalBounds().height / 2);
	//canvasSprite->setPosition(m_iWindowXSize / 2, m_iWindowYSize / 2);

	//m_RenderWindow->draw(*canvasSprite);
	m_RenderWindow->draw(*m_pLine);

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
