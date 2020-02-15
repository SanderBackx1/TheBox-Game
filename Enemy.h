#pragma once
#include "GameObject.h"
#include "Bulletmanager.h"

class Level;
class Enemy :
	public GameObject
{
public:
	Enemy(Rectf shape, float horSpeed, float jumpSpeed, int lives, float bulletcd, const std::shared_ptr<Texture>& pTexture);
	virtual ~Enemy() = default;
	virtual void Draw() const;
	void Update(float elapsedSec, Level& level, Avatar& player);
	Enemy(const Enemy& gobj) = delete;
	Enemy(Enemy&& gobj) = delete;
	Enemy& operator=(Enemy&& other) = delete;
	Enemy& operator=(const Enemy& rhs) = delete;

	void SetPos(Point2f& pos);
	int GetLives() const;
	void SetLives(int newLives);
	Rectf GetShape() const;
	Vector2f GetVelocity() const;
private:
	enum class Actions
	{
		idle,
		shooting,
		dead,
	};

	void ApplyGravity(float elapsedSec);
	void ApplyVelocity(float elapsedSec);
	void Clamp(Rectf& boundaries);
	void Shoot(Bulletmanager& bulletmanager);
	bool IsPlayerNearby(const Avatar& player);
	void ChangeSize();
	Rectf m_Shape;
	int m_Lives;
	float m_HorSpeed;
	float m_JumpSpeed;
	Vector2f m_GravPull;
	Vector2f m_Velocity;
	Bulletmanager m_Bullets;
	Actions m_State;

	//Animation
	enum class Animation
	{
		idle = 1,
		shooting=2,
		dead =3
	};
	Animation m_AnimState;
	std::shared_ptr<Texture> m_pEnemyTexture;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	float m_FrameHeight;
	float m_FrameWidth;
	int m_AnimFrame;
	float m_Height;
	void DoAnimation(float elapsedSec);
	void DrawAnimation() const;
	void ChangeAnimation();

};

