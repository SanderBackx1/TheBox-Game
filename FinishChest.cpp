#include "stdafx.h"
#include "FinishChest.h"
#include "Texture.h"
#include "utils.h"

FinishChest::FinishChest(const Rectf& shape)
	:m_Shape{shape}
	,m_GameWon{false}
	, m_pChestTexture{ std::make_unique<Texture>("Resources/Images/Chest/chest.png") }
{
}

void FinishChest::Draw() const
{
	m_pChestTexture->Draw(m_Shape);
}

void FinishChest::Reset()
{
	m_GameWon = false;
}

void FinishChest::HandleCollision(Avatar & avatar)
{
	if (IsHit(avatar.GetShape()))
	{
		m_GameWon = true;
	}
}

bool FinishChest::IsGameWon() const
{
	return m_GameWon;
}

bool FinishChest::IsHit(const Rectf& actorshape)
{
	return utils::IsOverlapping(m_Shape, actorshape);;
}
