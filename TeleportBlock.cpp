#include "stdafx.h"
#include "TeleportBlock.h"
#include "Avatar.h"
#include "utils.h"

TeleportBlock::TeleportBlock(const Rectf& shape, bool active, const std::shared_ptr<Texture>& pTexture)
	:m_Shape{shape}
	,m_Active{active}
	, m_NrOfFrames{ 10 }
	, m_NrFramesPerSec{ 20 }
	, m_AnimTime{ 0.f }
	, m_FrameHeight{ 40.f }
	, m_FrameWidth{ 40.f }
	, m_AnimFrame{ 0 }
	, m_pTPBlockTexture{ pTexture }
	, m_AnimColor{AnimColor::red}
{
}

void TeleportBlock::TeleportActor(Avatar & avatar)
{
	avatar.SetPos(Point2f{ m_Shape.left, m_Shape.bottom });
}

bool TeleportBlock::IsHit(Avatar & avatar) const
{
	return utils::IsOverlapping(m_Shape, avatar.GetShape());
}

void TeleportBlock::Draw() const
{
		DrawAnimation();
}

void TeleportBlock::SwapActive()
{
	m_Active = !m_Active;
}

void TeleportBlock::StartCooldown()
{
	m_Cooldown = 3.0f;
}

bool TeleportBlock::CheckCooldown() const
{
	if (m_Cooldown <= 0.f)
	{
		return true;
	}
	return false;
}

void TeleportBlock::ChangeCooldown(float chg)
{
	if (m_Cooldown > 0.f)
	{
		m_Cooldown -= chg;
	}
}

void TeleportBlock::Update(float elapsedSec)
{
	if (m_Cooldown > 0.f) m_Active = false;
	if (m_Cooldown <= 0.f) m_Active = true;
	ChangeAnimation();
	DoAnimation(elapsedSec);
}

void TeleportBlock::DoAnimation(float elapsedSec)
{
	m_AnimTime += elapsedSec;
	if (m_AnimTime > 1.0f)
	{
		++m_AnimFrame;
		m_AnimFrame %= m_NrOfFrames;

		m_AnimTime -= 1.0f / m_NrFramesPerSec;
	}
}

void TeleportBlock::DrawAnimation() const
{
	Rectf sourceRect;
	Rectf destRect{ m_Shape };
	sourceRect.left = m_FrameWidth * m_AnimFrame;
	sourceRect.bottom = m_FrameHeight * int(m_AnimColor);
	sourceRect.width = m_FrameWidth;
	sourceRect.height = m_FrameHeight;
	glPushMatrix();
	if (m_Direction == GameObject::Direction::left)
	{
		glTranslatef(m_Shape.left + m_Shape.width / 2, m_Shape.bottom, 0.f);
		glScalef(-1.f, 1.f, 1.f);
		glTranslatef(-m_Shape.left - m_Shape.width / 2, -m_Shape.bottom, 0.f);
	}
	m_pTPBlockTexture->Draw(destRect, sourceRect);
	glPopMatrix();
}

void TeleportBlock::ChangeAnimation()
{
	if (m_Active) m_AnimColor = AnimColor::purple;
	if (!m_Active) m_AnimColor = AnimColor::red;
}
