#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CBox
{
public:
	CBox();
	~CBox();

	sf::RectangleShape* NewShape();

private:
	sf::RectangleShape* m_pRectangle;
};
