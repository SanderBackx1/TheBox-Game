#include "stdafx.h"
#include "ExtraLifemanager.h"
#include "utils.h"

std::shared_ptr<Texture> ExtraLifemanager::m_pHealthTexture{ nullptr };
int ExtraLifemanager::m_InstanceCounter{ 0 };


ExtraLifemanager::ExtraLifemanager()
	:m_HealthSound{"Resources/Sound/HealthPickup.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pHealthTexture = std::make_shared<Texture>("Resources/Images/Health/health.png");
	}
	++m_InstanceCounter;
	Init();
}

void ExtraLifemanager::Draw() const
{
	for (std::shared_ptr<ExtraLife> el : m_pExtraLives)
	{
		el->Draw();
	}
}

void ExtraLifemanager::Update(Avatar& avatar)
{
	HandleCollision(avatar);
}

std::shared_ptr<Texture> ExtraLifemanager::GetTexture() const
{
	return m_pHealthTexture;
}

void ExtraLifemanager::Reset()
{
	m_pExtraLives.clear();
	Init();
}


void ExtraLifemanager::HandleCollision(Avatar & avatar)
{
	for (std::shared_ptr<ExtraLife> el : m_pExtraLives)
	{
		if (utils::IsOverlapping(avatar.GetShape(), el->GetShape()))
		{
			if(avatar.GetLives() < avatar.GetMaxLives())
			{
				avatar.SetLives(avatar.GetLives() + 1);
				m_HealthSound.Play(false);
				Remove(el);
			}
		}
	}
}

void ExtraLifemanager::Init()
{
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 1750.f, 950.f }, m_pHealthTexture }));
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 950.f, 220.f }, m_pHealthTexture }));
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 1750.f, 420.f }, m_pHealthTexture }));
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 860.f, 860.f }, m_pHealthTexture }));
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 70.f, 660.f }, m_pHealthTexture }));
	m_pExtraLives.push_back(std::make_shared<ExtraLife>( ExtraLife{ { 250.f, 120.f }, m_pHealthTexture }));

}

void ExtraLifemanager::Remove(std::shared_ptr<ExtraLife>& el)
{
	if (m_pExtraLives[m_pExtraLives.size() - 1] != el)
	{
		std::shared_ptr<ExtraLife> pTemp;
		for (size_t i{ 0 }; i < m_pExtraLives.size() - 1; ++i)
		{
			if (m_pExtraLives[i] == el)
			{
				pTemp = m_pExtraLives[m_pExtraLives.size() - 1];
				m_pExtraLives[m_pExtraLives.size() - 1] = m_pExtraLives[i];
				m_pExtraLives[i] = pTemp;
				pTemp = nullptr;
			}
		}
	};
	m_pExtraLives.pop_back();
}
