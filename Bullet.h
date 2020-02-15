#pragma once
#include "GameObject.h"
#include "Vector2f.h"
class Level;
class Bullet : public GameObject
{
public:
	Bullet(const Point2f& pos, const Vector2f& velocity, GameObject::Direction dir, const std::shared_ptr<Texture>& pTexture);
	virtual ~Bullet() = default;
	void Draw() const;
	void Update(float elapsedSec);
	bool IsActive()const;
	Rectf GetShape() const;
	Vector2f GetVelocity() const;

	Bullet(const Bullet& gobj) = delete;
	Bullet(Bullet&& gobj) = delete;
	Bullet& operator=(Bullet&& other) = delete;
	Bullet& operator=(const Bullet& rhs) = delete;


private:
	Rectf m_Shape;
	void UpdateTime(float elapsedSec);
	void ChangeState();
	Vector2f m_Velocity;
	bool m_Active;
	float m_AccumTime;
	float m_MaxTime;

	std::shared_ptr<Texture> m_pBulletTexture;
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	float m_FrameHeight;
	float m_FrameWidth;
	int m_AnimFrame;


	void DoAnimation(float elapsedSec);
	void DrawAnimation() const;

};


