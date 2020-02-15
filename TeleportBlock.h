#pragma once
#include "GameObject.h"
class Avatar;
class TeleportBlock :	public GameObject
{
public:
	TeleportBlock(const Rectf& shape, bool active,const std::shared_ptr<Texture>& pTexture);

	void TeleportActor(Avatar& avatar);
	bool IsHit(Avatar& avatar) const;
	virtual void Draw() const;
	void SwapActive();
	void StartCooldown();
	bool CheckCooldown() const;
	void ChangeCooldown(float chg);
	void Update(float elapsedSec);

	TeleportBlock(const TeleportBlock& gobj) = delete;
	TeleportBlock(TeleportBlock&& gobj) = delete;
	TeleportBlock& operator=(TeleportBlock&& other) = delete;
	TeleportBlock& operator=(const TeleportBlock& rhs) = delete;
private:
	Rectf m_Shape;
	bool m_Active;
	float m_Cooldown;
	

	std::shared_ptr<Texture> m_pTPBlockTexture;
	enum class AnimColor
	{
		purple = 1,
		red = 2
	};
	int m_NrOfFrames;
	int m_NrFramesPerSec;
	float m_AnimTime;
	float m_FrameHeight;
	float m_FrameWidth;
	int m_AnimFrame;
	AnimColor m_AnimColor;

	void DoAnimation(float elapsedSec);
	void DrawAnimation() const;
	void ChangeAnimation();
};

