#include "Ellipse.h"

CEllipse::CEllipse()
{
	m_pCircle = nullptr;
}

CEllipse::~CEllipse()
{
	m_pCircle = nullptr;
}


sf::CircleShape* CEllipse::NewShape()
{
	sf::CircleShape* circle = new sf::CircleShape(0.5f);
	m_pCircle = circle;

	return m_pCircle;
}



