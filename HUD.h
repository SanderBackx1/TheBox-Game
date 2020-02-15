#pragma once
#include "Avatar.h"
#include <vector>
#include "ExtraLifemanager.h"
class HUD
{
public:
	HUD(const Point2f& bottomleft, float width, float height, int playerLives);
	void Draw()const;
	void Update(const Avatar& player);
	HUD(const HUD& gobj) = delete;
	HUD(HUD&& gobj) = delete;
	HUD& operator=(HUD&& other) = delete;
	HUD& operator=(const HUD& rhs) = delete;
	
private:
	void GetPlayerLives(const Avatar& player);
	void SetLivesPos();
	Point2f m_BottomLeftPos;
	float m_Width;
	float m_Height;
	Rectf m_Shape;
	int m_PlayerLives;
	Rectf m_LiveShape;
	int m_MaxLives;
	std::vector<Rectf>m_Lives;

	ExtraLifemanager m_ExtraLifemanager;
	std::shared_ptr<Texture> m_pHealthTexture;
};

