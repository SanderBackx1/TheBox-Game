#pragma once
#include "GameObject.h"
#include "Avatar.h"

class FinishChest :
	public GameObject
{
public:
	FinishChest(const Rectf& shape);
	virtual ~FinishChest() = default;
	virtual void Draw() const;
	void  Reset();
	void HandleCollision(Avatar& avatar);
	bool IsGameWon() const;


	FinishChest(const FinishChest& gobj) = delete;
	FinishChest(FinishChest&& gobj) = delete;
	FinishChest& operator=(FinishChest&& other) = delete;
	FinishChest& operator=(const FinishChest& rhs) = delete;
private:

	bool IsHit(const Rectf& actorshape);
	bool m_GameWon;
	Rectf m_Shape;
	std::unique_ptr<Texture> m_pChestTexture;
	
};

