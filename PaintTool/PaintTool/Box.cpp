#include "Box.h"

CBox::CBox()
{
	m_pRectangle = nullptr;
}

CBox::~CBox()
{
	m_pRectangle = nullptr;
}

sf::RectangleShape* CBox::NewShape()
{
	sf::Vector2f dimensions(1.0f, 1.0f);
	sf::RectangleShape* rectangle = new sf::RectangleShape(dimensions);
	m_pRectangle = rectangle;
	return m_pRectangle;
}
