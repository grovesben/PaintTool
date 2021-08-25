#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CTriangle
{
public:
	CTriangle();
	~CTriangle();

	sf::CircleShape* NewShape();

private:
	sf::CircleShape* m_pTriangle;
};
