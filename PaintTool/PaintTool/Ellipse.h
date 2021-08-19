#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CEllipse
{
public:
	CEllipse();
	~CEllipse();

	sf::CircleShape* NewShape();

private:
	sf::CircleShape* m_pCircle;
};


