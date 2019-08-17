#include "Pallet.h"

Pallet::Pallet()
{
	m_position = sf::Vector2f(0.0f,0.0f);
	m_velocity = sf::Vector2f(0.0f,0.0f);
	m_normal = sf::Vector2f(0.0f,0.0f);
	m_length = 150.0f;
	m_height = 20.0f;
	m_angle = 80.0f;
}

void Pallet::Init(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f normal)
{
	m_position = position;
	m_velocity = velocity;
	m_normal = normal;
	m_height = 20.0f;
	m_length = 150.0f - m_height;
	m_angle = 70.0f;
	m_circlePositions[0] = position + sf::Vector2f(m_normal.y,-m_normal.x)*m_length/2.0f;
	m_circlePositions[1] = position + sf::Vector2f(-m_normal.y,m_normal.x)*m_length/2.0f;
	m_texture.loadFromFile("Pallet.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(m_sprite.getLocalBounds().width/2.0f,m_sprite.getLocalBounds().height/2.0f);
}

void Pallet::Update(float dt)
{
	
	m_position += m_velocity *dt;
	m_circlePositions[0] = m_position + sf::Vector2f(m_normal.y,-m_normal.x)*m_length/2.0f;
	m_circlePositions[1] = m_position + sf::Vector2f(-m_normal.y,m_normal.x)*m_length/2.0f;
}

void Pallet::Draw(sf::RenderTarget& renderTarget)
{
	m_sprite.setPosition(m_position);
	renderTarget.draw(m_sprite);
}