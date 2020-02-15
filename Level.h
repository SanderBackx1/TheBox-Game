#pragma once
#include <vector>
#include "Texture.h"
#include "GameObject.h"
#include "Vector2f.h"

class Level
{
public:
	Level();
	void DrawBackground() const;
	Rectf GetBoundaries()const;
	void HandleCollision(Rectf& actorShape, Vector2f& actorVelocity, GameObject& actor);
	bool IsOnGround(const Rectf& actorShape) const;
	bool CheckCollision(const Rectf& actorShape,const Vector2f& actorVelocity) const;

	Level(const Level& gobj) = delete;
	Level(Level&& gobj) = delete;
	Level& operator=(Level&& other) = delete;
	Level& operator=(const Level& rhs) = delete;

private:
	std::vector<std::vector<Point2f>> m_Vertices;
	Texture m_BackgroundTexture;
	Rectf m_Boundaries;
	Rectf m_Temp;
};

