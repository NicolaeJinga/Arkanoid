#include "Block.h"

Block::Block()
{
	m_position = sf::Vector2f(0.0f,0.0f);
	m_velocity = sf::Vector2f(0.0f,0.0f);
	m_length = 100.0f;
	m_height = 50.0f;
	m_isAlive = true;
	m_movingForward = false;
	m_timesToMoveForward = 5;
	m_timeToWaitUntilNextMove = 0.0f;
	m_firstTimeMoving = true;
}

void Block::Init(sf::Vector2f position, sf::Vector2f velocity, float length, float height, sf::Color color, float delay)
{
	m_position = position;
	m_velocity = velocity;
	m_normals[0] = sf::Vector2f(  0.0f, -1.0f );
	m_normals[1] = sf::Vector2f( -1.0f,  0.0f );
	m_normals[2] = sf::Vector2f(  0.0f,  1.0f );
	m_normals[3] = sf::Vector2f(  1.0f,  0.0f );
	m_length = length;
	m_height = height;
	m_isAlive = true;
	m_time.restart().asSeconds();
	m_movingForward = false;
	m_timesToMoveForward = 5;
	m_timeToMoveForward = 1.0f;
	m_timeToWaitUntilNextMove = 10.0f;
	m_firstTimeMoving = true;
	m_timeToWaitUntilFirstMove = delay;
	m_color = color;
	m_texture.loadFromFile("Block.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setScale(m_length/m_texture.getSize().x,m_height/m_texture.getSize().y);
	m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.0f,m_sprite.getTexture()->getSize().y/2.0f);
	m_sprite.setColor(m_color);
}

void Block::Update(float dt)
{   //   if it moves   && moved how much it had to
	if(m_movingForward && m_time.getElapsedTime().asSeconds() > m_timeToMoveForward)
	{
		m_velocity = sf::Vector2f(0.0f,0.0f);
		m_time.restart().asSeconds();
		m_movingForward = false;
		m_timesToMoveForward --;
		m_firstTimeMoving = false;
	}
	else //if it doesnt move && still has to move
		if(!m_movingForward && m_timesToMoveForward > 0)
		{
			if(m_firstTimeMoving)
			{
				if(m_time.getElapsedTime().asSeconds() > m_timeToWaitUntilFirstMove)
				{
					m_time.restart().asSeconds();
					m_movingForward = true;
					m_velocity = sf::Vector2f(0.0f,30.0f);
				}
			}
			else
			{
				if(m_time.getElapsedTime().asSeconds() > m_timeToWaitUntilNextMove)
				{
					m_time.restart().asSeconds();
					m_movingForward = true;
					m_velocity = sf::Vector2f(0.0f,30.0f);
				}
			}
		}
	m_position += m_velocity * dt;
}

void Block::Draw(sf::RenderTarget& renderTarget)
{
	m_sprite.setPosition(m_position);
	renderTarget.draw(m_sprite);
}