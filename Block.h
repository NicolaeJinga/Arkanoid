#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "SFML/Graphics.hpp"

class Block
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_normals[4];

	float m_length;
	float m_height;
	
	bool m_isAlive;
//	bool m_hasPower;
	
	sf::Clock m_time;
	bool m_movingForward;
	int m_timesToMoveForward;
	float m_timeToMoveForward;
	float m_timeToWaitUntilNextMove;
	bool m_firstTimeMoving;
	float m_timeToWaitUntilFirstMove;
	
	

	sf::Color m_color;
	sf::Texture m_texture;
	sf::Sprite m_sprite;

	Block();

	void Init(sf::Vector2f position, sf::Vector2f velocity, float length, float height, sf::Color color, float delay);
	void Update(float dt);
	void Draw(sf::RenderTarget& renderTarget);
};


#endif // __BLOCK_H__