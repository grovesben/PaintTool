#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CLine
{
public:
	CLine();
	~CLine();

	sf::RectangleShape* NewShape();

private:
	sf::RectangleShape* m_pLine;
};



