#include "stdafx.h"
#include "Enemy.h"
#include "utils.h"
#include "level.h"
#include "Avatar.h"

Enemy::Enemy(Rectf shape, float horSpeed, float jumpSpeed, int lives, float bulletcd, const std::shared_ptr<Texture>& pTexture)
	:m_Shape{ shape }
	,m_Height{shape.height}
	, m_HorSpeed{ horSpeed }
	, m_JumpSpeed{ jumpSpeed }
	, m_GravPull{ 0.f, -981.f }
	, m_Velocity{ 0.f,0.f }
	, m_Bullets{ 3,4.f, bulletcd }
	, m_Lives{lives}
	,m_pEnemyTexture{pTexture}
	,m_State{Actions::idle}
	,m_AnimFrame{0}
	,m_AnimTime{0.f}
	,m_FrameWidth{40.f}
	,m_FrameHeight{40.f}
	,m_NrFramesPerSec{10}
{
}
void Enemy::Draw() const
{

	m_Bullets.Draw();
	DrawAnimation();
}

void Enemy::Update(float elapsedSec, Level& level, Avatar& player)
{
	level.HandleCollision(m_Shape, m_Velocity, *this);
	ApplyVelocity(elapsedSec);
	ApplyGravity(elapsedSec);
	ChangeSize();
	ChangeAnimation();
	DoAnimation(elapsedSec);
	Clamp(level.GetBoundaries());
	if (IsPlayerNearby(player))
	{
		m_State = Actions::shooting;
		Point2f playerPos{ player.GetShape().left, player.GetShape().bottom };
		Point2f enemyPos{ m_Shape.left, m_Shape.bottom };
		if (playerPos.x - enemyPos.x < 0.f) m_Direction = GameObject::Direction::left;
		if (playerPos.x - enemyPos.x > 0.f) m_Direction = GameObject::Direction::right;
		Shoot(m_Bullets);
	}
	else
	{
		m_State = Actions::idle;
	}
	m_Bullets.Update(elapsedSec, level);
	if (m_Bullets.BulletHit(player.GetShape()))
	{
		if (player.GetLives() > 0)
		{
			player.SetLives(player.GetLives() - 1);
			player.PlayDamageSound();
		}

	};
}

void Enemy::SetPos(Point2f & pos)
{
	m_Shape.left = pos.x;
	m_Shape.bottom = pos.y;
}

int Enemy::GetLives() const
{
	return m_Lives;
}

void Enemy::SetLives(int newLives)
{
	m_Lives = newLives;
}

Rectf Enemy::GetShape() const
{
	return m_Shape;
}

Vector2f Enemy::GetVelocity() const
{
	return m_Velocity;
}

void Enemy::Shoot(Bulletmanager & bulletmanager)
{
	Vector2f velocity{ 250.f,0.f };
	int random = rand() % (m_Lives);
	bulletmanager.Shoot({ m_Shape.left, m_Shape.bottom + (m_Height * random) }, velocity, m_Direction);
}

bool Enemy::IsPlayerNearby(const Avatar & player)
{
	Point2f playerPos{ player.GetShape().left, player.GetShape().bottom };
	Point2f enemyPos{ m_Shape.left, m_Shape.bottom };

	if (playerPos.x - enemyPos.x > -300.f && playerPos.x - enemyPos.x < 300.f && playerPos.y - enemyPos.y > -80.f && playerPos.y - enemyPos.y < 80.f)
	{
		return true;
	}
	return false;
}

void Enemy::ChangeSize()
{

	m_Shape.height = m_Height * m_Lives;
}

void Enemy::DoAnimation(float elapsedSec)
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

void Enemy::DrawAnimation() const
{
	Rectf sourceRect;
	Rectf destRect{ m_Shape };
	sourceRect.left = m_FrameWidth * m_AnimFrame;
	sourceRect.bottom = m_FrameHeight * (int(m_State)+1);
	sourceRect.width = m_FrameWidth;
	sourceRect.height = m_FrameHeight;
	glPushMatrix();
	if (m_Direction == GameObject::Direction::left)
	{
		glTranslatef(m_Shape.left + m_Shape.width / 2, m_Shape.bottom, 0.f);
		glScalef(-1.f, 1.f, 1.f);
		glTranslatef(-m_Shape.left - m_Shape.width / 2, -m_Shape.bottom, 0.f);
	}
	m_pEnemyTexture->Draw(destRect, sourceRect);
	glPopMatrix();

}

void Enemy::ChangeAnimation()
{
	switch (m_State)
	{
	case Enemy::Actions::idle:
		m_AnimState = Enemy::Animation::idle;
		break;
	case Enemy::Actions::shooting:
		m_AnimState = Enemy::Animation::shooting;
		break;
	case Enemy::Actions::dead:
		m_AnimState = Enemy::Animation::dead;
		break;
	default:
		break;
	}
	switch (m_AnimState)
	{
	case Enemy::Animation::idle:
		m_NrOfFrames = 9;
		if (m_AnimFrame > 9) m_AnimFrame = 0;
		break;
	case Enemy::Animation::shooting:
		m_NrOfFrames = 4;
		if (m_AnimFrame > 4) m_AnimFrame = 0;
		break;
	case Enemy::Animation::dead:
		m_NrOfFrames = 10;
		if (m_AnimFrame > 10) m_AnimFrame = 0;
		break;
	default:
		break;
	}
}

void Enemy::ApplyGravity(float elapsedSec)
{
	m_Velocity.x += m_GravPull.x*elapsedSec;
	m_Velocity.y += m_GravPull.y*elapsedSec;
}

void Enemy::ApplyVelocity(float elapsedSec)
{
	m_Shape.left += m_Velocity.x * elapsedSec;
	m_Shape.bottom += m_Velocity.y*elapsedSec;
}
void Enemy::Clamp(Rectf& boundaries)
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