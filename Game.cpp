#include "stdafx.h"
#include "Game.h"
#include <iostream>
Game::Game( const Window& window ) 
	:m_Window{ window }
	,m_Avatar{{70,170,40,40},150,520,5}
	,m_Camera{500.f,500.f}
	,m_Light{1000.f,1000.f}
	, m_HUD{ {20,450},100,40,5 }
	,m_Keymanager{5}
	,m_FinishChest{{980,540,40,40}}
	, m_TeleportBlockManager{}
	, m_Enemymanager{}
	, m_ExtraLifemanager{}
	, m_Doormanager{}
	,m_MainSong{"Resources/Sound/main.mp3"}
	,m_GameWon{"Resources/Images/Game/GameWon.png"}
	,m_GameLost{"Resources/Images/Game/GameLost.png"}
	
{
	m_MainSong.Play(true);
	
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_Camera.SetBoundaries(m_Level.GetBoundaries());
	m_MainSong.Resume();
}

void Game::Cleanup( )
{
}

void Game::Update( float elapsedSec )
{
	// Check keyboard state
	//const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	//if ( pStates[SDL_SCANCODE_RIGHT] )
	//{
	//	std::cout << "Right arrow key is down\n";
	//}
	//if ( pStates[SDL_SCANCODE_LEFT] && pStates[SDL_SCANCODE_UP])
	//{
	//	std::cout << "Left and up arrow keys are down\n";
	//}
	if (!m_FinishChest.IsGameWon() && !m_Avatar.IsGameOver())
	{
		m_Enemymanager.Update(elapsedSec, m_Level, m_Avatar);
		m_TeleportBlockManager.Update(m_Avatar, elapsedSec);
		m_Doormanager.Update(elapsedSec, m_Keymanager.AreAllCollected());
		m_Doormanager.HandleCollision(m_Avatar);
		m_FinishChest.HandleCollision(m_Avatar);
		m_Avatar.HandleBulletCollision(m_Enemymanager);
		m_Keymanager.Update(m_Avatar.GetShape());
		m_ExtraLifemanager.Update(m_Avatar);
		m_HUD.Update(m_Avatar);
		m_Avatar.Update(elapsedSec, m_Level);
	}
	else
	{
		HandleKeydown();
	}

}

void Game::Draw( ) const
{
	
	ClearBackground( );
	if (!m_FinishChest.IsGameWon() && !m_Avatar.IsGameOver())
	{
		glPushMatrix();
		glTranslatef(-m_Camera.GetPosition(m_Avatar.GetShape()).x, -m_Camera.GetPosition(m_Avatar.GetShape()).y, 0.f);
		m_Level.DrawBackground();
		m_Enemymanager.Draw();
		m_Doormanager.Draw();
		m_TeleportBlockManager.Draw();
		m_Keymanager.Draw();
		m_ExtraLifemanager.Draw();
		m_FinishChest.Draw();
		m_Avatar.Draw();
		m_Light.Draw(m_Avatar.GetShape());
		glTranslatef(m_Camera.GetPosition(m_Avatar.GetShape()).x, m_Camera.GetPosition(m_Avatar.GetShape()).y, 0.f);
		glPopMatrix();
		m_HUD.Draw();
	}
	else if (m_Avatar.IsGameOver())
	{
		m_GameLost.Draw({ 0.f,0.f,m_Window.width, m_Window.height });
	}
	else
	{
		m_GameWon.Draw({ 0.f,0.f,m_Window.width, m_Window.height });
	}
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	//std::cout << "KEYUP event: " << e.keysym.sym << std::endl;
	//switch ( e.keysym.sym )
	//{
	//case SDLK_LEFT:
	//	//std::cout << "Left arrow key released\n";
	//	break;
	//case SDLK_RIGHT:
	//	//std::cout << "`Right arrow key released\n";
	//	break;
	//case SDLK_1:
	//case SDLK_KP_1:
	//	//std::cout << "Key 1 released\n";
	//	break;
	//}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.4f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::HandleKeydown()
{
	const Uint8 *pStates = SDL_GetKeyboardState( nullptr );
	if ( pStates[SDL_SCANCODE_R] )
	{
		Reset();
	}
}

void Game::Reset()
{
	m_TeleportBlockManager.Reset();
	m_Enemymanager.Reset();
	m_Doormanager.Reset();
	m_Keymanager.Reset();
	m_ExtraLifemanager.Reset();
	m_FinishChest.Reset();
	m_Avatar.Reset({ 70,170,40,40 }, 3);
}
