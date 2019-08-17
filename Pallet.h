#ifndef __PALLET_H__
#define __PALLET_H__

#include "SFML/Graphics.hpp"

class Pallet
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_normal;
	
	float m_length;
	float m_height;
	float m_angle;

	sf::Vector2f m_circlePositions[2];

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	Pallet();

	void Init(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f normal);
	void Update(float dt);
	void Draw(sf::RenderTarget& renderTarget);
};


#endif // __PALLET_H__