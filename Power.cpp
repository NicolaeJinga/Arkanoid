#include "Power.h"

void Power::Init()
{

}

void Power::Update(float dt)
{
	m_position += m_velocity * dt;
}

void Power::Draw(sf::RenderTarget& renderTarget)
{
	m_sprite.setPosition(m_position);
	renderTarget.draw(m_sprite);	
}