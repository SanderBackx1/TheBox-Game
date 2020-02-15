#include "stdafx.h"
#include "Bullet.h"
#include "utils.h"
#include "Texture.h"

Bullet::Bullet(const Point2f& pos, const Vector2f& velocity, GameObject::Direction dir, const std::shared_ptr<Texture>& pTexture)
	:m_Shape{ pos.x, pos.y, 10,10 }
	, m_Velocity{ velocity }
	, m_AccumTime{ 0.f }
	, m_MaxTime{ 1.f }
	, m_Active{ true }
	, m_NrOfFrames{5}
	, m_NrFramesPerSec{10}
	, m_AnimTime{0.f}
	, m_FrameHeight{40.f}
	, m_FrameWidth{40.f}
	, m_AnimFrame{0}
	, m_pBulletTexture{ pTexture }

{
	m_Direction = dir;
}
void Bullet::Draw() const
{
	
	DrawAnimation();
}
void Bullet::Update(float elapsedSec)
{
	if (m_Active)
	{
		ChangeState();
		UpdateTime(elapsedSec);
		if (m_Direction == GameObject::Direction::left)
		{

			m_Shape.left -= m_Velocity.x*elapsedSec;
		}
		else if (m_Direction == GameObject::Direction::right)
		{
			m_Shape.left += m_Velocity.x*elapsedSec;
		}
	}
	DoAnimation(elapsedSec);
}

void Bullet::UpdateTime(float elapsedSec)
{
	m_AccumTime += elapsedSec;
}

void Bullet::ChangeState()
{
	if (m_AccumTime >= m_MaxTime)
	{
		m_Active = false;
	}
	else
	{
		m_Active = true;
	}
}


void Bullet::DoAnimation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime > 1.0f)
	{
		++m_AnimFrame;
		m_AnimFrame %= m_NrOfFrames;

		m_AnimTime -= 1.0f / m_NrFramesPerSec;
	}
}

void Bullet::DrawAnimation() const
{
	Rectf sourceRect;
	Rectf destRect{ m_Shape };
	sourceRect.left = m_FrameWidth * m_AnimFrame;
	sourceRect.bottom = m_FrameHeight;
	sourceRect.width = m_FrameWidth;
	sourceRect.height = m_FrameHeight;
	glPushMatrix();
	if (m_Direction == GameObject::Direction::left)
	{
		glTranslatef(m_Shape.left + m_Shape.width / 2, m_Shape.bottom, 0.f);
		glScalef(-1.f, 1.f, 1.f);
		glTranslatef(-m_Shape.left - m_Shape.width / 2, -m_Shape.bottom, 0.f);
	}
	m_pBulletTexture->Draw(destRect, sourceRect);
	glPopMatrix();
}


bool Bullet::IsActive() const
{
	return m_Active;
}


Rectf Bullet::GetShape() const
{
	return m_Shape;
}

Vector2f Bullet::GetVelocity() const
{
	return m_Velocity;
}




