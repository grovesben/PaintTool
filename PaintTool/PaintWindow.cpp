#include "PaintWindow.h"

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

sf::Vector2f rectangleButtonDimensions(40.0f, 40.0f);
sf::RectangleShape PaintWindow::m_RectangleButton(rectangleButtonDimensions);
sf::Vector2f buttonSelectedDimensions(20.0f, 20.0f);
sf::RectangleShape PaintWindow::m_RectangleButtonSelected(buttonSelectedDimensions);

sf::CircleShape PaintWindow::m_CircleButton(20.0f);
sf::CircleShape PaintWindow::m_CircleButtonSelected(10.0f);

sf::Vector2f drawingButtonDimensions(40.0f, 40.0f);
sf::RectangleShape PaintWindow::m_DrawingButton(drawingButtonDimensions);
sf::Vector2f drawingSelectedDimensions(20.0f, 5.0f);
sf::RectangleShape PaintWindow::m_DrawingButtonSelected(drawingSelectedDimensions);

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
	m_DrawingButtonSelected.setPosition(drawingPosition.x + 10.0f, drawingPosition.y + 17.5f);
	m_DrawingButtonSelected.setFillColor(sf::Color::Black);

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
		m_iMousePosition = sf::Mouse::getPosition(*m_RenderWindow);
		// check if button pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 50.0f && m_iMousePosition.x > 5.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_RectangleButtonSelected.setFillColor(*m_pCurrentPenColour);
			m_CircleButtonSelected.setFillColor(sf::Color::White);
			m_DrawingButtonSelected.setFillColor(sf::Color::Black);
			m_iTool = 1;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 100.0f && m_iMousePosition.x > 50.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_CircleButtonSelected.setFillColor(*m_pCurrentPenColour);
			m_RectangleButtonSelected.setFillColor(sf::Color::White);
			m_DrawingButtonSelected.setFillColor(sf::Color::Black);
			m_iTool = 0;
		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_iMousePosition.x < 150.0f && m_iMousePosition.x > 100.0f && m_iMousePosition.y < 50.0f && m_iMousePosition.y > 5.0f)
		{
			m_DrawingButtonSelected.setFillColor(*m_pCurrentPenColour);
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
			m_DrawingButtonSelected.setFillColor(*m_pCurrentPenColour);
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
	m_RenderWindow->draw(m_DrawingButtonSelected);
	m_RenderWindow->draw(m_ColourButton1);
	m_RenderWindow->draw(m_ColourButton2);
	m_RenderWindow->draw(m_ColourButton3);


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

	for (int i = 0; i < m_iBrushSize; i++)
	{
		_canvasRef->setPixel(_mousePosition.x, _mousePosition.y, *m_pCurrentPenColour);

		_canvasRef->setPixel(_mousePosition.x + i, _mousePosition.y, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x - i, _mousePosition.y, *m_pCurrentPenColour);

		_canvasRef->setPixel(_mousePosition.x, _mousePosition.y + i, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x, _mousePosition.y - i, *m_pCurrentPenColour);

		_canvasRef->setPixel(_mousePosition.x + i, _mousePosition.y + i, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x - i, _mousePosition.y + i, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x + i, _mousePosition.y - i, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x + i, _mousePosition.y + i, *m_pCurrentPenColour);
		_canvasRef->setPixel(_mousePosition.x - i, _mousePosition.y - i, *m_pCurrentPenColour);
	}
	
}

