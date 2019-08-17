#ifndef __BORDER_H__
#define __BORDER_H__

#include "SFML/Graphics.hpp"

class Border
{
public:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_normal;

	float m_length;
	float m_height;

	sf::Texture m_texture;
	sf::Sprite m_sprite;

	Border();

	void Init(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f normal, float length, float height);


	// B---------------A
	// |       ^       |
	// |       |       |
	// C---------------D

	sf::Vector2f A();
	sf::Vector2f B();
	sf::Vector2f C();
	sf::Vector2f D();
	void Update(float dt);
	void Draw(sf::RenderTarget& renderTarget);
};


#endif // __BORDER_H__