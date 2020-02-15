#include "stdafx.h"
#include "Avatar.h"
#include "utils.h"
#include "level.h"
#include "Enemy.h"
#include "Enemymanager.h"
#include <iostream>

Avatar::Avatar(Rectf shape, float horSpeed, float jumpSpeed, int lives)
	:m_Shape{shape}
	,m_HorSpeed{horSpeed}
	,m_JumpSpeed{jumpSpeed}
	,m_GravPull{ 0.f, -981.f }
	,m_Velocity{0.f,0.f}
	,m_Avatarbullets{ 5,0.5f,0.2f }
	,m_Lives{ lives }
	,m_MaxLives{lives }
	,m_IsShooting{false}
	,m_GameOver{false}
	,m_DamageTakenSound{"Resources/Sound/PlayerDamage.ogg"}
	,m_Texture{"Resources/Images/Avatar/spritesheet.png"}
	,m_GameOverTimer{ 2.f }
{
	InitAnimation();
	m_Direction = GameObject::Direction::right;
}

void Avatar::Draw() const
{
	utils::SetColor({ 1.f,1.f, 1.f, 1.f });
	DrawAnimation();
	m_Avatarbullets.Draw();
}

void Avatar::Update(float elapsedSec, Level& level)
{
	if (!IsDead())
	{
		HandleMoveKeys(level);
		HandleShootKey();
	}
	ApplyVelocity(elapsedSec);
	ApplyGravity(elapsedSec);
	HandleDeath(elapsedSec);
	ChangeAnimation();
	DoAnimation(elapsedSec);
	level.HandleCollision(m_Shape, m_Velocity, *this);
	Clamp(level.GetBoundaries());
	m_Avatarbullets.Update(elapsedSec, level);
}

void Avatar::SetPos(Point2f & pos)
{
	m_Shape.left = pos.x;
	m_Shape.bottom = pos.y;
}

Rectf Avatar::GetShape() const
{
	return m_Shape;
}

Vector2f Avatar::GetVelocity() const
{
	return m_Velocity;
}


bool Avatar::IsDead() const
{
	if (m_Lives == 0) return true;
	else return false;
}

void Avatar::HandleDeath(float elapsedSec)
{
	if (IsDead())
	{
		m_State = ActorState::dead;
		m_Velocity.x = 0.f;
		if (m_GameOverTimer <= 0.f)
		{
			m_GameOver = true;
		}
		m_GameOverTimer -= elapsedSec;
	}
}

void Avatar::HandleMoveKeys(Level & level)
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);
		if ((!pStates[SDL_SCANCODE_RIGHT] || !pStates[SDL_SCANCODE_LEFT]) && m_Velocity.y ==0)
	{
		m_Velocity.x = 0;
		m_State = ActorState::waiting;
	//	m_Direction = Direction::down;
	}

	if (pStates[SDL_SCANCODE_RIGHT] || pStates[SDL_SCANCODE_D])
	{
		m_Velocity.x = m_HorSpeed;
		m_State = ActorState::moving;
		m_Direction = Direction::right;
	}
	else if (pStates[SDL_SCANCODE_LEFT] || pStates[SDL_SCANCODE_A])
	{
		m_Velocity.x = -m_HorSpeed;
		m_State = ActorState::moving;
		m_Direction = Direction::left;
	}
	if ((pStates[SDL_SCANCODE_UP] || pStates[SDL_SCANCODE_W] )&&  level.IsOnGround(m_Shape) )
	{
		m_Velocity.y = m_JumpSpeed;
		m_State = ActorState::jumping;
	//	m_Direction = Direction::up;
	}

	if (!level.IsOnGround(m_Shape))
	{
		ChangeAirState();
	}


	if (pStates[SDL_SCANCODE_H] || pStates[SDL_SCANCODE_I])
	{
		std::cout << "---HOW TO PLAY---\n";
		std::cout << "A or left arrow -\t MOVE LEFT\n";
		std::cout << "D or right arrow -\t MOVE RIGHT\n";
		std::cout << "W or up arrow -\t\t JUMP \n";
		std::cout << "SPACE -\t\t\t Shoot\n";
		std::cout << "\n\n";
		std::cout << "Collect all the keys in order to be able to leave the compound full of enemies!\n";
		std::cout << "Use the teleportation voids to your advantage!\n";
		std::cout << "Don't get shot down !\n";
		std::cout << "------------------------";

	}
}

void Avatar::HandleShootKey()
{
	const Uint8 *pStates = SDL_GetKeyboardState(nullptr);
	if (pStates[SDL_SCANCODE_SPACE])
	{
  		Shoot(m_Avatarbullets);
		m_IsShooting = true;
	}
	else
	{
		m_IsShooting = false;
	}
}


void Avatar::Shoot(Bulletmanager & bulletmanager)
{
	Vector2f velocity{ 250.f,0.f };
	bulletmanager.Shoot({ m_Shape.left + m_Shape.width/2, m_Shape.bottom+ m_Shape.height/3 }, velocity, m_Direction);
}

void Avatar::ChangeAirState()
{
	if (m_Velocity.y < 0)
	{
		m_State = ActorState::falling;
	}
	else if (m_Velocity.y > 0)
	{
		m_State = ActorState::jumping;
	}

}


void Avatar::ApplyGravity(float elapsedSec)
{

		m_Velocity.x += m_GravPull.x*elapsedSec;
		if (m_Velocity.y > -m_JumpSpeed) m_Velocity.y += m_GravPull.y*elapsedSec;
}

void Avatar::ApplyVelocity(float elapsedSec)
{
	m_Shape.left += m_Velocity.x * elapsedSec;
	 m_Shape.bottom += m_Velocity.y*elapsedSec;
}


void Avatar::Clamp(Rectf& boundaries)
{
	if (m_Shape.left + m_Shape.width >= boundaries.left + boundaries.width)
	{
		m_Shape.left = (boundaries.left + boundaries.width) - m_Shape.width;
	}
	else if (m_Shape.left < boundaries.left)
	{
		m_Shape.left = boundaries.left;
	}

	if (m_Shape.bottom < boundaries.bottom)
	{
		m_Shape.bottom = boundaries.bottom;
	}

	if (m_Shape.bottom + m_Shape.height > boundaries.bottom + boundaries.height)
	{
		m_Shape.bottom = (boundaries.bottom + boundaries.height) - m_Shape.height;
	}
}
void Avatar::HandleBulletCollision(Enemymanager& enemymanager)
{
	for (size_t i{ 0 }; i < enemymanager.GetEnemies().size(); ++i)
	{
		if (m_Avatarbullets.BulletHit(enemymanager.GetEnemies().at(i)->GetShape()))
		{
			enemymanager.OnHit(enemymanager.GetEnemies().at(i));
			enemymanager.PlaySound();
		}
	}
}

int Avatar::GetLives() const
{
	return m_Lives;
}

int Avatar::GetMaxLives() const
{
	return m_MaxLives;
}

void Avatar::SetLives(int newLives)
{
	m_Lives = newLives;
}

void Avatar::PlayDamageSound()
{
	m_DamageTakenSound.Play(false);
}

bool Avatar::IsGameOver() const
{
	return m_GameOver;
}

void Avatar::Reset(const Rectf& shape, int lives)
{
	m_Shape = shape;
	m_Velocity = { 0.f,0.f };
	m_Lives = lives;
	m_MaxLives = lives;
	m_GameOver = false;
	m_GameOverTimer = 2.f;
	m_State = ActorState::waiting;
	m_AnimState = Animation::idle;

}

 
void Avatar::InitAnimation()
{
	m_NrOfFrames = 9;
	m_NrFramesPerSec = 10;
	m_FrameHeight = 40.f;
	m_FrameWidth = 40.f;
	m_AnimFrame = 0;
	m_AnimTime = 0.f;
	m_AnimState = Animation::idle;
}

void Avatar::DoAnimation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime > 1.0f)
	{
		++m_AnimFrame;
		if (m_AnimState == Animation::dead) if (m_AnimFrame == 9) m_AnimFrame = 8;
		m_AnimFrame %= m_NrOfFrames;

		m_AnimTime -= 1.0f / m_NrFramesPerSec;
	}
}

void Avatar::DrawAnimation() const
{
	Rectf sourceRect;
	Rectf destRect{ m_Shape };
	sourceRect.left = m_FrameWidth * m_AnimFrame;
	sourceRect.bottom = m_FrameHeight * int(m_AnimState);
	sourceRect.width = m_FrameWidth;
	sourceRect.height = m_FrameHeight;
	glPushMatrix();
	if (m_Direction == GameObject::Direction::left)
	{
		glTranslatef(m_Shape.left + m_Shape.width / 2, m_Shape.bottom, 0.f);
		glScalef(-1.f, 1.f, 1.f);
		glTranslatef(-m_Shape.left - m_Shape.width / 2, -m_Shape.bottom, 0.f);
	}
	m_Texture.Draw(destRect, sourceRect);
	glPopMatrix();
}

void Avatar::ChangeAnimation()
{
	if (m_AnimState != Avatar::Animation::dead)
	{
		switch (m_State)
		{
		case Avatar::ActorState::moving:
			if (m_Velocity.y <= 0)
			{
				m_AnimState = Animation::run;
			}
			else if(m_Velocity.y > 0 || m_Velocity.y < -16.f)
			{
				m_AnimState = Animation::jump;
			}
			if (m_IsShooting)
			{
				m_AnimState = Animation::runshoot;
			}
			break;
		case Avatar::ActorState::jumping:
		case Avatar::ActorState::falling:
			m_AnimState = Animation::jump;
			if (m_IsShooting)
			{ 
				m_AnimState = Animation::jumpshoot;
			}
			break;
		case Avatar::ActorState::waiting:
			m_AnimState = Animation::idle;
			if (m_IsShooting)
			{
				m_AnimState = Animation::shoot;
			}
			break;
		case Avatar::ActorState::dead:
				m_AnimState = Animation::dead;
			break;
		default:
			break;
	}
	ChangeAnimationParams();
	}
}

void Avatar::ChangeAnimationParams()
{
	
		switch (m_AnimState)
		{
		case Avatar::Animation::jump:
		case Avatar::Animation::dead:
			m_NrOfFrames = 10;
			if (m_AnimFrame > 10) m_AnimFrame = 0;
			break;
		case Avatar::Animation::runshoot:
		case Avatar::Animation::idle:
			m_NrOfFrames = 9;
			if (m_AnimFrame > 9) m_AnimFrame = 0;
			break;
		case Avatar::Animation::run:
			m_NrOfFrames = 8;
			if (m_AnimFrame > 8) m_AnimFrame = 0;
			break;
		case Avatar::Animation::jumpshoot:
			m_NrOfFrames = 5;
			if (m_AnimFrame > 5) m_AnimFrame = 0;
			break;
		case Avatar::Animation::shoot:
			m_NrOfFrames = 4;
			if (m_AnimFrame > 4) m_AnimFrame = 0;
			break;
		default:
			break;
		}
	}

