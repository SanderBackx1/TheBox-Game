#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "Bulletmanager.h"
#include "SoundEffect.h"
#include "Texture.h"
class Level;
class Enemymanager;
class Avatar : public GameObject
{
public:
	Avatar(Rectf shape, float horSpeed, float jumpSpeed, int lives);
	virtual ~Avatar() = default;
	virtual void Draw() const;
	void Update(float elapsedSec, Level& level);
	Avatar(const Avatar& gobj) = delete;
	Avatar(Avatar&& gobj) = delete;
	Avatar& operator=(Avatar&& other) = delete;
	Avatar& operator=(const Avatar& rhs) = delete;

	void SetPos(Point2f& pos);
	Rectf GetShape() const;
	Vector2f GetVelocity() const;
	void HandleBulletCollision(Enemymanager& enemymanager);
	int GetLives() const;
	int GetMaxLives() const;
	void SetLives(int newLives);
	void PlayDamageSound();
	bool IsGameOver() const;
	
	void Reset(const Rectf& shape, int lives);

private:
	enum class ActorState {
		waiting,
		moving,
		jumping, 
		falling,
		dead
	};
	enum class Animation
	{
		idle = 1,
		run = 2,
		shoot = 3,
		runshoot = 4,
		jump = 5,
		jumpshoot = 6,
		dead = 7
	};
	bool IsDead() const;
	void HandleDeath(float elapsedSec);
	void HandleMoveKeys(Level& level);
	void HandleShootKey();
	void ApplyGravity(float elapsedSec);
	void ApplyVelocity(float elapsedSec);
	void Clamp(Rectf& boundaries);
	void Shoot(Bulletmanager& bulletmanager);
	void ChangeAirState();
	Rectf m_Shape;
	float m_HorSpeed;
	float m_JumpSpeed;
	int m_Lives;
	int m_MaxLives;
	bool m_IsShooting;

	Vector2f m_GravPull;
	Vector2f m_Velocity;
	ActorState m_State;
	Bulletmanager m_Avatarbullets;
	
	//sound
	SoundEffect m_DamageTakenSound;

	//animation
	Texture m_Texture;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	float m_FrameHeight;
	float m_FrameWidth;
	int m_AnimFrame;
	Animation m_AnimState;
	bool m_GameOver;
	float m_GameOverTimer;

	void InitAnimation();
	void DoAnimation(float elapsedSec);
	void DrawAnimation() const;
	void ChangeAnimation();
	void ChangeAnimationParams();
};

