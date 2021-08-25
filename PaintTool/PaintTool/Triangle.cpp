#include "Triangle.h"

CTriangle::CTriangle()
{
	m_pTriangle = nullptr;
}

CTriangle::~CTriangle()
{
	m_pTriangle = nullptr;
}

sf::CircleShape* CTriangle::NewShape()
{
	sf::CircleShape* triangle = new sf::CircleShape(0.5f, 3);
	return triangle;
}
