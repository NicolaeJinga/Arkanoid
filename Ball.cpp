#include "Ball.h"

Ball::Ball()
{
	m_position = sf::Vector2f(0.0f,0.0f);
	m_velocity = sf::Vector2f(0.0f,0.0f);
	m_radius = 10.0f;
	m_hasBeenServed = false;
}

void Ball::Init(sf::Vector2f position, sf::Vector2f velocity)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = 10.0f;
	m_hasBeenServed = false;
	m_texture.loadFromFile("Ball.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width/2.0f,m_sprite.getLocalBounds().height/2.0f);
}

void Ball::Update(float dt)
{
	m_position += m_velocity * dt;
}

void Ball::Draw(sf::RenderTarget& renderTarget)
{
	m_sprite.setColor(sf::Color::Red);
	m_sprite.setPosition(m_position);
	renderTarget.draw(m_sprite);
}