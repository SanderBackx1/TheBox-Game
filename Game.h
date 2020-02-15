#pragma once
#include "Level.h"
#include "Avatar.h"
#include "TeleportBlockManager.h"
#include "Camera.h"
#include "Light.h"
#include "Enemy.h"
#include "Enemymanager.h"
#include "Doormanager.h"
#include "Keymanager.h"
#include "HUD.h"
#include "SoundStream.h"
#include "ExtraLifemanager.h"
#include "FinishChest.h"

class Game
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	~Game();

	void Update( float elapsedSec );
	void Draw( ) const;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	const Window m_Window;
	Level m_Level;
	Avatar m_Avatar;
	Camera m_Camera;
	Light m_Light; 
	TeleportBlockManager m_TeleportBlockManager;
	Enemymanager m_Enemymanager;
	Doormanager m_Doormanager;
	Keymanager m_Keymanager;
	ExtraLifemanager m_ExtraLifemanager;
	FinishChest m_FinishChest;
	SoundStream m_MainSong;
	Texture m_GameWon;
	Texture m_GameLost;
	HUD m_HUD;
	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( ) const;

	void HandleKeydown();
	
	void Reset();
};