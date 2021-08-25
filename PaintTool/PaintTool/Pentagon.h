#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class CPentagon
{
public:
	CPentagon();
	~CPentagon();

	sf::CircleShape* NewShape();

private:
	sf::CircleShape* m_pPentagon;
};
