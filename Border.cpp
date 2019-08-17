#include "Border.h"

Border::Border()
{
	m_position = sf::Vector2f(0.0f,0.0f);
	m_velocity = sf::Vector2f(0.0f,0.0f);
	m_normal   = sf::Vector2f(0.0f,0.0f);
	m_length = 0.0f;
	m_height = 0.0f;
}

void Border::Init(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f normal, float length, float height)
{
	m_position = position;
	m_velocity = velocity;
	m_normal = normal;
	m_length = length;
	m_height = height;
	m_texture.loadFromFile("Border.png");
	m_sprite.setTexture(m_texture);
}

sf::Vector2f Border::A()
{
	sf::Vector2f n0 = sf::Vector2f(-m_normal.y,m_normal.x);
	return m_position+(n0*m_length/2.0f)+(m_normal*m_height/2.0f);
}
sf::Vector2f Border::B()
{
	sf::Vector2f n0 = sf::Vector2f(-m_normal.y,m_normal.x);
	return m_position+(n0*-m_length/2.0f)+(m_normal*m_height/2.0f);
}
sf::Vector2f Border::C()
{
	sf::Vector2f n0 = sf::Vector2f(-m_normal.y,m_normal.x);
	return m_position+(n0*-m_length/2.0f)+(m_normal*-m_height/2.0f);
}
sf::Vector2f Border::D()
{
	sf::Vector2f n0 = sf::Vector2f(-m_normal.y,m_normal.x);
	return m_position+(n0*m_length/2.0f)+(m_normal*-m_height/2.0f);
}

void Border::Update(float dt)
{
	m_position += m_velocity * dt;
}

void Border::Draw(sf::RenderTarget& renderTarget)
{
	m_sprite.setPosition(m_position);
	renderTarget.draw(m_sprite);
}

