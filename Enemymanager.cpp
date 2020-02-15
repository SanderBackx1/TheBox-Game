#include "stdafx.h"
#include "Enemymanager.h"
#include "Enemy.h"
#include "Level.h"
#include "utils.h"

std::shared_ptr<Texture> Enemymanager::m_pEnemyTexture{ nullptr };
int Enemymanager::m_InstanceCounter{ 0 };

Enemymanager::Enemymanager()
	:m_EnemyDeathSound{"Resources/Sound/EnemyDeath.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pEnemyTexture = std::make_shared<Texture>( "Resources/Images/Enemy/spritesheet.png" );
	}
	InitEnemies();
}

void Enemymanager::Draw() const
{
	for (size_t i{}; i < m_pEnemies.size(); ++i)
	{
		m_pEnemies[i]->Draw();
	}
}

void Enemymanager::Update(float elapsedSec, Level& level,Avatar& player)
{
	for (size_t i{}; i < m_pEnemies.size(); ++i)
	{
		m_pEnemies[i]->Update(elapsedSec, level, player);
	}
}

std::vector<Enemy*> Enemymanager::GetEnemies() const
{
	return m_pEnemies;
}

void Enemymanager::DeleteEnemy(Enemy * enemy)
{
	if (enemy == m_pEnemies[m_pEnemies.size() - 1])
	{
		delete m_pEnemies[m_pEnemies.size() - 1];
		m_pEnemies.pop_back();
	}
	else
	{
		size_t it{ 0 };
		while (enemy != m_pEnemies[it])
		{
			++it;
		}
		Enemy* pTemp;
		pTemp = m_pEnemies[it];
		m_pEnemies[it] = m_pEnemies[m_pEnemies.size() - 1];
		delete pTemp;
		m_pEnemies.pop_back();
	}
}

void Enemymanager::OnHit(Enemy * hitEnemy)
{
	if (hitEnemy->GetLives() > 1) hitEnemy->SetLives(hitEnemy->GetLives() - 1);
	else DeleteEnemy(hitEnemy);
}

//bool Enemymanager::IsHit(const Rectf & shape)
//{
//	for (size_t i{}; i < m_pEnemies.size(); ++i)
//	{
//		if (utils::IsOverlapping(shape, m_pEnemies.at(i)->GetShape())) return true;
//	}
//
//	return false;
//}

void Enemymanager::PlaySound() 
{
	m_EnemyDeathSound.Play(false);
}

void Enemymanager::Reset()
{
	for (size_t i{}; i < m_pEnemies.size(); ++i)
	{
		delete m_pEnemies[i];
		m_pEnemies[i] = nullptr;
	}
	while (m_pEnemies.size() != 0)
	{
		m_pEnemies.pop_back();
	}
	InitEnemies();
}


Enemymanager::~Enemymanager()
{
	for (size_t i{}; i < m_pEnemies.size(); ++i)
	{
		delete m_pEnemies[i];
		m_pEnemies[i] = nullptr;
	}
}

void Enemymanager::InitEnemies()
{
	m_pEnemies.push_back(new Enemy{ Rectf{ 400,210,40,40 }, 100.f, 40.f,1,1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 1480,320,40,40 }, 100.f, 40.f,1,1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 1820,300,40,40 }, 100.f, 40.f,1,1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 1100,965,40,40 }, 100.f, 40.f,1,1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 1666,947,40,40 }, 100.f, 40.f,1,1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 780,120,40,40 }, 100.f, 40.f,3, 1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 600,710,40,40 }, 100.f, 40.f,1, 1.f, m_pEnemyTexture });
	m_pEnemies.push_back(new Enemy{ Rectf{ 260,350,40,40 }, 100.f, 40.f,3, 1.f, m_pEnemyTexture });
}
