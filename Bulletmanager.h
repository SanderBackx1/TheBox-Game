#pragma once
#include <deque>
#include "GameObject.h"
#include "Vector2f.h"
#include "Level.h"
#include "Doormanager.h"
#include "SoundEffect.h"
class Bullet;
class Bulletmanager
{
public:
	Bulletmanager(int maxAmount, float maxTime, float cooldown);
	~Bulletmanager();
	void Draw() const;
	void Update(float elapsedSec, const Level& level);
	void Shoot(const Point2f& pos, const Vector2f velocity, GameObject::Direction dir);
	bool BulletHit(const Rectf& shape);
	void Remove(Bullet& bullet);
	
	Bulletmanager(const Bulletmanager& gobj) = delete;
	Bulletmanager(Bulletmanager&& gobj) = delete;
	Bulletmanager& operator=(Bulletmanager&& other) = delete;
	Bulletmanager& operator=(const Bulletmanager& rhs) = delete;
private:

	std::deque<Bullet*>m_pBullets;
	SoundEffect m_Lazer;
	int m_MaxAmount;
	float m_MaxTime;
	float m_Cooldown;
	float m_MaxCooldown;

	void RemoveInactive();
	void UpdateTime(float elapsedSec);
	void ResetCooldown();
	void CheckCollision(const Level& level);
	
	//animation
	static std::shared_ptr<Texture> m_pBulletTexture;
	static int m_InstanceCounter;

};

