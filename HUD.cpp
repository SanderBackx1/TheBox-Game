#include "stdafx.h"
#include "HUD.h"
#include "utils.h"


HUD::HUD(const Point2f& bottomleft, float width, float height, int playerLives)
	:m_BottomLeftPos{bottomleft}
	,m_Width{width}
	,m_Height{height}
	,m_Shape{m_BottomLeftPos.x, m_BottomLeftPos.y, width, height}
	,m_PlayerLives{playerLives}
	,m_MaxLives{playerLives}
{
	SetLivesPos();
	
}

void HUD::Draw() const
{
	for (const Rectf& rect : m_Lives)
	{
	}
	for (int i{}; i < m_PlayerLives; ++i)
	{
		m_ExtraLifemanager.GetTexture()->Draw(m_Lives[i]);
	}
}

void HUD::Update(const Avatar& player)
{
	GetPlayerLives(player);
	
	
}


void HUD::GetPlayerLives(const Avatar& player)
{
	m_PlayerLives = player.GetLives();
}

void HUD::SetLivesPos()
{
	m_LiveShape.left = m_BottomLeftPos.x + 10.f;
	m_LiveShape.bottom = m_BottomLeftPos.y + 5.f;
	m_LiveShape.width = 20.f;
	m_LiveShape.height = 20.f;
	for (int i{}; i < m_PlayerLives; ++i)
	{
		m_Lives.push_back(m_LiveShape);
		m_LiveShape.left +=  m_LiveShape.width + 10.f;
	}
}
