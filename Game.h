#ifndef __GAME_H__
#define __GAME_H__

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Ball.h"
#include "Pallet.h"
#include "Block.h"
#include "Border.h"

class Game
{
public:

	sf::RenderWindow m_window;
	int m_currentState;

	sf::Texture m_bgTexture;
	sf::Sprite	m_bgSprite;

	sf::SoundBuffer	m_ballHitBuffer;
	sf::SoundBuffer	m_loseBuffer;
	sf::SoundBuffer	m_winBuffer;
	sf::Sound		m_ballhitSound;
	sf::Sound		m_loseSound;
	sf::Sound		m_winSound;

	sf::Font m_font;
	sf::Text m_text;
	
	bool m_gameLost;

	bool m_mouse;
	bool m_toggleMouse;

	int m_nrBorders;
	int m_nrBalls;
	int m_nrBlocks;
	int m_nrCurrentBlocks;
	int m_nrBlocksPerRow;
	int m_nrBlocksPerColumn;
	float m_delayBetweenBlocks;

	sf::Vector2f m_blockPlacementOffset;
	sf::Vector2f* m_blocksA;
	sf::Vector2f* m_blocksB;
	sf::Vector2f* m_blocksC;
	sf::Vector2f* m_blocksD;

	Ball m_ball;
	Pallet m_pallet;
	Border m_borders[4];
	Block* m_blocks;

	

	enum m_States
	{
		SPLASHSCREEN=0,
		MENU,
		GAME,
		SCORESCREEN,
		COUNT,
		INVALID
	};

	void Init();
	void Reset();
	void InitBlocks();
	void BallInitOnPallet();
	sf::Vector2f BallRepositionUponCollision(sf::Vector2f A, sf::Vector2f B, sf::Vector2f normal, Ball& ball);
	void Update(float dt);
	void Draw();
};

#endif // __GAME_H__