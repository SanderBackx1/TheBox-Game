#include "stdafx.h"
#include "Bulletmanager.h"
#include "Bullet.h"
#include "GameObject.h"
#include "utils.h"

std::shared_ptr<Texture> Bulletmanager::m_pBulletTexture{nullptr};
int Bulletmanager::m_InstanceCounter{ 0 };


Bulletmanager::Bulletmanager(int maxAmount, float maxTime, float cooldown)
	:m_MaxAmount{maxAmount}
	,m_MaxTime{maxTime}
	,m_Cooldown{cooldown}
	,m_MaxCooldown{cooldown}
	,m_Lazer{"Resources/Sound/Lazer.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pBulletTexture = std::make_unique<Texture>("Resources/Images/Bullets/spritesheet.png");
	}
	++m_InstanceCounter;
}

void Bulletmanager::Shoot(const Point2f& pos, const Vector2f velocity, GameObject::Direction dir)
{
	if (m_Cooldown <= 0.f)
	{

		m_pBullets.push_back(new Bullet{ {pos.x, pos.y}, velocity , dir ,m_pBulletTexture });
		m_Lazer.Play(false);
		ResetCooldown();
	}
}

bool Bulletmanager::BulletHit(const Rectf & shape)
{
	for (size_t i{}; i < m_pBullets.size(); ++i)
	{
		if (utils::IsOverlapping(shape, m_pBullets[i]->GetShape()))
		{
			Remove(*m_pBullets[i]);
			return true;
		}
	}
	return false;
}

void Bulletmanager::Draw() const
{
	for (size_t i{ 0 }; i<m_pBullets.size(); ++i)
	{
		if (m_pBullets[i])m_pBullets[i]->Draw();
	}
}

void Bulletmanager::Update(float elapsedSec, const Level& level)
{
	UpdateTime(elapsedSec);
	RemoveInactive();
	CheckCollision(level);
	for (size_t i{ 0 }; i<m_pBullets.size(); ++i)
	{
		m_pBullets[i]->Update(elapsedSec);
	}
}

void Bulletmanager::Remove(Bullet& bullet)
{
	if (m_pBullets[0] != &bullet)
	{
		Bullet* pTemp;
		for (size_t i{1}; i < m_pBullets.size(); ++i)
		{
			if (m_pBullets[i] == &bullet)
			{
				pTemp = m_pBullets[0];
				m_pBullets[0] = m_pBullets[i];
				m_pBullets[i] = pTemp;

				pTemp = nullptr;
			}
		}
	};
	m_pBullets.pop_front();
	delete &bullet;
}

void Bulletmanager::RemoveInactive()
{
	for (size_t i{ 0 }; i<m_pBullets.size(); ++i)
	{
		if(!m_pBullets[i]->IsActive())
		{
			Remove(*m_pBullets[i]);
		}
	}
}

void Bulletmanager::UpdateTime(float elapsedSec)
{
	if (m_Cooldown >= 0.f)
	{
		m_Cooldown -= elapsedSec;
	}
}

void Bulletmanager::ResetCooldown()
{
	m_Cooldown = m_MaxCooldown;
}

void Bulletmanager::CheckCollision(const Level & level)
{
	for (size_t i{ 0 }; i<m_pBullets.size(); ++i)
	{
		if (level.CheckCollision(m_pBullets[i]->GetShape(),m_pBullets[i]->GetVelocity()))
		{
			Remove(*m_pBullets[i]);
		}
	}
}




Bulletmanager::~Bulletmanager()
{
	for(size_t i{0}; i<m_pBullets.size(); ++i)
	{
		delete m_pBullets[i];
	}
}
	