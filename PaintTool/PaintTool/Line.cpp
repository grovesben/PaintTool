#include "Line.h"

CLine::CLine()
{
	m_pLine = nullptr;
}

CLine::~CLine()
{
	m_pLine = nullptr;
}

sf::RectangleShape* CLine::NewShape()
{
	sf::RectangleShape* line = new sf::RectangleShape;
	return line;
}
