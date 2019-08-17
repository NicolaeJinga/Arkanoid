#ifndef __POWER_H__
#define __POWER_H__

#include "SFML/Graphics.hpp"

class Power
{
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	enum Types
	{
		INCREASE_PALLET_WIDTH = 0,
		DECREASE_PALLET_WIDTH,
		INCREASE_BALL_SPEED,
		DECREASE_BALL_SPEED,
		MULTIPLY_BALL,
		PIERCE_BALL,
		SAFE_NET,
		MAGNET,
		
		COUNT,
		INVALID
	};

	void Init();
	void Update(float dt);
	void Draw(sf::RenderTarget& renderTarget);
};



#endif // __POWER_H__