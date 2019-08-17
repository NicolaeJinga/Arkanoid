#ifndef __BALL_H__
#define __BALL_H__

#include "SFML/Graphics.hpp"

class Ball
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_radius;

	bool m_hasBeenServed;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	Ball();

	void Init(sf::Vector2f position, sf::Vector2f velocity);
	void Update(float dt);
	void Draw(sf::RenderTarget& renderTarget);
};


#endif // __BALL_H__