#include<iostream>
#include "Game.h"
#include "Utilities.h"


void Game::Init()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	srand((unsigned int)time(NULL));
	m_window.create(sf::VideoMode(1920,900), "Arkanoid", sf::Style::Default, settings);
	m_window.setMouseCursorVisible(false);
	m_bgTexture.loadFromFile("bg.png");
	m_bgSprite.setTexture(m_bgTexture);
	m_bgSprite.setScale((float)m_window.getSize().x/m_bgTexture.getSize().x,(float)m_window.getSize().y/m_bgTexture.getSize().y);
	m_bgSprite.setPosition(0.0f,0.0f);

	m_ballHitBuffer.loadFromFile("pong.wav");
	m_ballhitSound.setBuffer(m_ballHitBuffer);
	m_loseBuffer.loadFromFile("lose.wav");
	m_loseSound.setBuffer(m_loseBuffer);
	m_winBuffer.loadFromFile("win.wav");
	m_winSound.setBuffer(m_winBuffer);

	m_font.loadFromFile("arial.ttf");
	m_text.setFont(m_font);
	m_text.setCharacterSize(50);
	m_text.setString("YOU LOSE!");
	m_text.setOrigin(m_text.getLocalBounds().width/2.0f,m_text.getLocalBounds().height/2.0f);
	m_text.setPosition(m_window.getSize().x/2.0f,m_window.getSize().y/2.0f);
	
	m_gameLost = false;
	m_mouse = true;
	m_toggleMouse = false;
	m_nrBorders = 4;
	m_nrBalls	= 1;
	m_nrBlocksPerRow = 16;
	m_nrBlocksPerColumn = 8;
	m_nrBlocks = m_nrBlocksPerRow*m_nrBlocksPerColumn;
	m_nrCurrentBlocks = m_nrBlocks;
	m_delayBetweenBlocks = 0.05f;

	m_blocks = new Block[m_nrBlocks];
	m_blockPlacementOffset = sf::Vector2f(15.0f+m_blocks[0].m_length,10.0f+m_blocks[0].m_height);
	InitBlocks();
	//Init Borders
	m_borders[0].Init(sf::Vector2f((float)m_window.getSize().x/2.0f, 5.0f)								,sf::Vector2f(0.0f,0.0f),sf::Vector2f(0.0f,1.0f) ,(float)m_window.getSize().x,10.0f);
	m_borders[1].Init(sf::Vector2f(5.0f,(float)m_window.getSize().y/2.0f)								,sf::Vector2f(0.0f,0.0f),sf::Vector2f(1.0f,0.0f) ,(float)m_window.getSize().x,10.0f);
	m_borders[2].Init(sf::Vector2f((float)m_window.getSize().x -5.0f, (float)m_window.getSize().y/2.0f) ,sf::Vector2f(0.0f,0.0f),sf::Vector2f(-1.0f,0.0f),(float)m_window.getSize().x,10.0f);
	m_borders[3].Init(sf::Vector2f((float)m_window.getSize().x/2.0f, (float)m_window.getSize().y -5.0f)	,sf::Vector2f(0.0f,0.0f),sf::Vector2f(0.0f,-1.0f),(float)m_window.getSize().x,10.0f);
	for(int i = 0 ; i < m_nrBorders ; ++ i )
	{
		m_borders[i].m_sprite.setScale(m_borders[i].m_length,1.0f);
		m_borders[i].m_sprite.setOrigin(m_borders[i].m_sprite.getTexture()->getSize().x/2.0f,m_borders[i].m_sprite.getTexture()->getSize().y/2.0f);
		m_borders[i].m_sprite.setPosition(m_borders[i].m_position);
		m_borders[i].m_sprite.setRotation(90);
	}   
	m_borders[0].m_sprite.setRotation(0);
	m_borders[3].m_sprite.setRotation(0);
	
	m_pallet.Init(sf::Vector2f(m_window.getSize().x/2.0f - m_pallet.m_length/2.0f,19.0f*m_window.getSize().y/20.0f),sf::Vector2f(0.0f,0.0f),sf::Vector2f(0.0f,-1.0f));
	BallInitOnPallet();
	
	m_blocksA = new sf::Vector2f[m_nrBlocks];
	m_blocksB = new sf::Vector2f[m_nrBlocks];
	m_blocksC = new sf::Vector2f[m_nrBlocks];
	m_blocksD = new sf::Vector2f[m_nrBlocks];

	m_currentState = m_States::GAME;
}

void Game::Reset()
{
	delete[] m_blocksA;
	delete[] m_blocksB;
	delete[] m_blocksC;
	delete[] m_blocksD;
	m_gameLost = false;
	m_nrCurrentBlocks = m_nrBlocks;
	for(int i = 0 ; i < m_nrBlocks ; ++ i)
		m_blocks[i].m_isAlive = true;
	InitBlocks();
	m_pallet.Init(sf::Vector2f(m_window.getSize().x/2.0f - m_pallet.m_length/2.0f,19.0f*m_window.getSize().y/20.0f),sf::Vector2f(0.0f,0.0f),sf::Vector2f(0.0f,-1.0f));
	BallInitOnPallet();
	m_ball.m_hasBeenServed = false;
	m_blocksA = new sf::Vector2f[m_nrBlocks];
	m_blocksB = new sf::Vector2f[m_nrBlocks];
	m_blocksC = new sf::Vector2f[m_nrBlocks];
	m_blocksD = new sf::Vector2f[m_nrBlocks];
}

void Game::InitBlocks()
{
	for(int i = 0, row = 0, column = 0 ; i < m_nrBlocks ; ++i, ++column)
	{
		if(column == m_nrBlocksPerRow)
		{
			row++;
			column=0;
		}
		m_blocks[i].Init(
			sf::Vector2f((float)m_window.getSize().x/19.0f + column*m_blockPlacementOffset.x,
			(float)m_window.getSize().y/19.0f + row*m_blockPlacementOffset.y), 
			sf::Vector2f(0.0f,0.0f),
			100.0f,
			50.0f,
			sf::Color(sf::Color(rand()%200+50,rand()%200+50,rand()%200+50)),
			(m_nrCurrentBlocks - i) * m_delayBetweenBlocks);

	}
}

void Game::BallInitOnPallet()
{
	m_ball.Init(sf::Vector2f(m_pallet.m_position.x - 2.0f * m_ball.m_radius, m_pallet.m_position.y - 2.0f*m_ball.m_radius - 1.0f),sf::Vector2f(0.0f,0.0f));
}

sf::Vector2f Game::BallRepositionUponCollision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f normal, Ball& ball)
{
	sf::Vector2f m = ball.m_position - A;
	sf::Vector2f NormBA = Utilities::Normalized(B-A);
	sf::Vector2f z = Utilities::Dot(m,NormBA)*Utilities::Normalized(NormBA);
	sf::Vector2f d = z-m;
	sf::Vector2f r = Utilities::Normalized(d)*m_ball.m_radius;
	if(Utilities::Dot(m,normal) < 0)
		return m_ball.m_position + d + r;
	else	
		return m_ball.m_position + d - r;
}

void Game::Update(float dt)
{
	switch(m_currentState)
	{
	case SPLASHSCREEN:
		{
		
		}
	case MENU:
		{

		}
	case GAME:
		{
			if((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) && m_gameLost)
				Reset();
			if(!m_gameLost)
			{
				//Update Pallet
				m_pallet.Update(dt);
				m_pallet.m_velocity = sf::Vector2f(0.0f,0.0f);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
					m_pallet.m_velocity = sf::Vector2f(-1200.0f,0.0f);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
					m_pallet.m_velocity = sf::Vector2f(1200.0f,0.0f);
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && !m_toggleMouse)
				{
					m_toggleMouse = true;
					m_mouse = !m_mouse;
				}
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1) && m_toggleMouse)
				{
					m_toggleMouse = false;
				}
				if(m_mouse)
					m_pallet.m_position.x = (float)sf::Mouse::getPosition(m_window).x;
			
				//Collision Pallet with Borders
				if(m_pallet.m_position.x - m_pallet.m_length/2.0f - m_pallet.m_height/2.0f < m_borders[1].m_position.x + m_borders[1].m_height/2.0f)
					m_pallet.m_position.x = m_borders[1].m_position.x + m_borders[1].m_height/2.0f + m_pallet.m_length/2.0f + m_pallet.m_height/2.0f;
				if(m_pallet.m_position.x + m_pallet.m_length/2.0f + m_pallet.m_height/2.0f > m_borders[2].m_position.x - m_borders[2].m_height/2.0f)
					m_pallet.m_position.x = m_borders[2].m_position.x - m_borders[2].m_height/2.0f - m_pallet.m_length/2.0f - m_pallet.m_height/2.0f;

				//Update Ball
				m_ball.Update(dt);

				if(!m_ball.m_hasBeenServed)
				{
					BallInitOnPallet();
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						m_ball.m_hasBeenServed = true;
						m_ball.m_velocity = sf::Vector2f(300.0f,-600.0f);
					}
				}
			}
			//Collision Ball with Borders
			for(int i = 0 ; i < m_nrBorders-1 ; ++ i)
			{
				if(Utilities::CollisionCircleWithLine(m_ball.m_position, m_ball.m_radius, m_borders[i].A(), m_borders[i].B()))
				{
					m_ball.m_position = BallRepositionUponCollision(m_borders[i].A(), m_borders[i].B(), m_borders[i].m_normal, m_ball);
					m_ball.m_velocity = Utilities::Reflect(m_borders[i].m_normal, -m_ball.m_velocity);
					m_ballhitSound.play();
				}
			}
			if(m_nrCurrentBlocks!=0)
				if(Utilities::CollisionCircleWithLine(m_ball.m_position, m_ball.m_radius, m_borders[3].A(), m_borders[3].B()))
				{
					m_ball.m_position = BallRepositionUponCollision(m_borders[3].A(), m_borders[3].B(), m_borders[3].m_normal, m_ball);
					m_ball.m_velocity = Utilities::Reflect(m_borders[3].m_normal, -m_ball.m_velocity);
					m_loseSound.play();
					m_gameLost = true;
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
						Reset();
				}
		
			//Collision Ball with Pallet
			sf::Vector2f palletA = Utilities::PointA(m_pallet.m_position,m_pallet.m_normal,m_pallet.m_length,m_pallet.m_height);
			sf::Vector2f palletB = Utilities::PointB(m_pallet.m_position,m_pallet.m_normal,m_pallet.m_length,m_pallet.m_height);
			sf::Vector2f palletC = Utilities::PointC(m_pallet.m_position,m_pallet.m_normal,m_pallet.m_length,m_pallet.m_height);
			sf::Vector2f palletD = Utilities::PointD(m_pallet.m_position,m_pallet.m_normal,m_pallet.m_length,m_pallet.m_height);
			if(Utilities::CollisionCircleWithSegment(m_ball.m_position, m_ball.m_radius, palletA, palletB))
			{
				m_ball.m_position = BallRepositionUponCollision(palletA, palletB, m_pallet.m_normal, m_ball);
				float ballHitOnPallet = Utilities::Dot(m_ball.m_position-m_pallet.m_position,sf::Vector2f(-m_pallet.m_normal.y,m_pallet.m_normal.x));
				float angle = (ballHitOnPallet-(-m_pallet.m_length/2.0f))/m_pallet.m_length * 2 * m_pallet.m_angle + (-m_pallet.m_angle);
				sf::Vector2f unitDirection = Utilities::CreateUnitVectorFromAngle(angle + Utilities::GetAngle(m_pallet.m_normal));
				m_ball.m_velocity = unitDirection * Utilities::Magnitude(m_ball.m_velocity);
				m_ballhitSound.play();
			}
			if(Utilities::CollisionCircleWithSegment(m_ball.m_position, m_ball.m_radius, palletC, palletD))
			{
				m_ball.m_position = BallRepositionUponCollision(palletC, palletD, sf::Vector2f(-m_pallet.m_normal.x,-m_pallet.m_normal.y), m_ball);
				m_ball.m_velocity = Utilities::Reflect(sf::Vector2f(-m_pallet.m_normal.x,-m_pallet.m_normal.y), -m_ball.m_velocity);
				m_ballhitSound.play();
			}
			for(int i = 0 ; i < 2; ++ i)
			{
				sf::Vector2f normal = Utilities::Normalized(m_ball.m_position - m_pallet.m_circlePositions[i]);
				if(Utilities::CollisionCircleWithCircle(m_ball.m_position,m_ball.m_radius,m_pallet.m_circlePositions[i],m_pallet.m_height/2.0f))
				{
					m_ball.m_position = m_pallet.m_circlePositions[i] + normal*(m_ball.m_radius + m_pallet.m_height/2.0f);
					m_ball.m_velocity = Utilities::Reflect(normal,-m_ball.m_velocity);
					m_ballhitSound.play();
				}
			}

			//Update Blocks + Collision Ball with Blocks
			for(int i = 0 ; i < m_nrBlocks ; ++ i)
			{
				if(m_blocks[i].m_isAlive)
				{
					m_blocks[i].Update(dt);
				
					m_blocksA[i] = Utilities::PointA(m_blocks[i].m_position,m_blocks[i].m_normals[0],m_blocks[i].m_length,m_blocks[i].m_height);
					m_blocksB[i] = Utilities::PointB(m_blocks[i].m_position,m_blocks[i].m_normals[0],m_blocks[i].m_length,m_blocks[i].m_height);
					m_blocksC[i] = Utilities::PointC(m_blocks[i].m_position,m_blocks[i].m_normals[0],m_blocks[i].m_length,m_blocks[i].m_height);
					m_blocksD[i] = Utilities::PointD(m_blocks[i].m_position,m_blocks[i].m_normals[0],m_blocks[i].m_length,m_blocks[i].m_height);
					if(Utilities::CollisionCircleWithSegment(m_ball.m_position,m_ball.m_radius,m_blocksA[i],m_blocksB[i]))
					{
						m_ball.m_position = BallRepositionUponCollision(m_blocksA[i],m_blocksB[i], m_blocks[i].m_normals[0],m_ball);
						m_ball.m_velocity = Utilities::Reflect(m_blocks[i].m_normals[0], -m_ball.m_velocity);
						m_ballhitSound.play();
						m_blocks[i].m_isAlive = false;
						m_nrCurrentBlocks--;
					}
					else
					if(Utilities::CollisionCircleWithSegment(m_ball.m_position,m_ball.m_radius,m_blocksB[i],m_blocksC[i]))
					{
						m_ball.m_position = BallRepositionUponCollision(m_blocksB[i],m_blocksC[i], m_blocks[i].m_normals[1],m_ball);
						m_ball.m_velocity = Utilities::Reflect(m_blocks[i].m_normals[1], -m_ball.m_velocity);
						m_ballhitSound.play();
						m_blocks[i].m_isAlive = false;
						m_nrCurrentBlocks--;
					}
					else
					if(Utilities::CollisionCircleWithSegment(m_ball.m_position,m_ball.m_radius,m_blocksC[i],m_blocksD[i]))
					{
						m_ball.m_position = BallRepositionUponCollision(m_blocksC[i],m_blocksD[i], m_blocks[i].m_normals[2],m_ball);
						m_ball.m_velocity = Utilities::Reflect(m_blocks[i].m_normals[2], -m_ball.m_velocity);
						m_ballhitSound.play();
						m_blocks[i].m_isAlive = false;
						m_nrCurrentBlocks--;
					}
					else
					if(Utilities::CollisionCircleWithSegment(m_ball.m_position,m_ball.m_radius,m_blocksD[i],m_blocksA[i]))
					{
						m_ball.m_position = BallRepositionUponCollision(m_blocksD[i],m_blocksA[i], m_blocks[i].m_normals[3],m_ball);
						m_ball.m_velocity = Utilities::Reflect(m_blocks[i].m_normals[3], -m_ball.m_velocity);
						m_ballhitSound.play();
						m_blocks[i].m_isAlive = false;
						m_nrCurrentBlocks--;
					}
					
				}
			}

			if(m_nrCurrentBlocks == 0)
			{
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					Reset();
			}

		}
	case SCORESCREEN:
		{

		}
	}
}

void Game::Draw()
{
	m_window.clear();
	switch(m_currentState)
	{
	case SPLASHSCREEN:
		{

		}
	case MENU:
		{

		}
	case GAME:
		{
			m_window.draw(m_bgSprite);
			for(int i = 0 ; i < m_nrBorders ; ++ i)
				m_borders[m_nrBorders-1-i].Draw(m_window);
			m_ball.Draw(m_window);
			m_pallet.Draw(m_window);
			for(int i = 0 ; i < m_nrBlocks ; ++ i)
				if(m_blocks[i].m_isAlive)
					m_blocks[i].Draw(m_window);
			if(m_nrCurrentBlocks==0)
			{
				if(m_winSound.getStatus() == sf::Sound::Status::Stopped)
					m_winSound.play();
				m_text.setString("Congratulations!");
				m_text.setOrigin(m_text.getLocalBounds().width/2.0f,m_text.getLocalBounds().height/2.0f);
				m_text.setPosition(m_window.getSize().x/2.0f,m_window.getSize().y/2.0f);
				m_window.draw(m_text);
			}
			if(m_gameLost)
			{
				m_text.setString("YOU LOSE!");
				m_text.setOrigin(m_text.getLocalBounds().width/2.0f,m_text.getLocalBounds().height/2.0f);
				m_text.setPosition(m_window.getSize().x/2.0f,m_window.getSize().y/2.0f);
				m_window.draw(m_text);
			}
		}
	case SCORESCREEN:
		{

		}
	}
}