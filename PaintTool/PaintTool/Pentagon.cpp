#include "Pentagon.h"

CPentagon::CPentagon()
{
	m_pPentagon = nullptr;
}

CPentagon::~CPentagon()
{
	m_pPentagon = nullptr;
}

sf::CircleShape* CPentagon::NewShape()
{
	sf::CircleShape* pentagon = new sf::CircleShape(0.5f, 5);
	return pentagon;
}
