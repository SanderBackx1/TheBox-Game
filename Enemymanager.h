#pragma once
#include <vector>
#include "level.h"
#include "Avatar.h"
#include "SoundEffect.h"

class Enemy;

class Enemymanager
{
public:
	Enemymanager();

	void Draw() const;
	void Update(float elapsedSec, Level& level, Avatar& player);
	std::vector<Enemy*> GetEnemies()const;
	void DeleteEnemy(Enemy* enemy);
	void OnHit(Enemy* hitEnemy);
	void PlaySound();
	void Reset();
	~Enemymanager();



	Enemymanager(const Enemymanager& gobj) = delete;
	Enemymanager(Enemymanager&& gobj) = delete;
	Enemymanager& operator=(Enemymanager&& other) = delete;
	Enemymanager& operator=(const Enemymanager& rhs) = delete;
private:
	Level * m_pLevel;
	void InitEnemies();
	SoundEffect m_EnemyDeathSound;
	std::vector<Enemy*> m_pEnemies;

	static std::shared_ptr<Texture> m_pEnemyTexture;
	static int m_InstanceCounter;
};

