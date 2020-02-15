#include "stdafx.h"
#include "Level.h"
#include "SVGParser.h"
#include "utils.h"

Level::Level()
	: m_BackgroundTexture{ "Resources/Images/Level/level.png" }
{
	SVGParser::GetVerticesFromSvgFile("Resources/Images/Level/level.svg", m_Vertices);
	m_Boundaries = { 0,0, m_BackgroundTexture.GetWidth(), m_BackgroundTexture.GetHeight() };
}

void Level::DrawBackground() const
{
	m_BackgroundTexture.Draw();
	utils::SetColor( {1.f, 1.f,0.f,1.f} );
//	utils::DrawPolygon(m_Vertices[0], true, 2.f);
	
}
Rectf Level::GetBoundaries() const
{
	return m_Boundaries;
}

void Level::HandleCollision(Rectf & actorShape, Vector2f & actorVelocity, GameObject & actor)
{
	m_Temp = actorShape;
	utils::HitInfo hitInfo;


	Point2f tempP1{ actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height };
	Point2f tempP2{ actorShape.left + actorShape.width / 2, actorShape.bottom - 1.f };


	
	if (utils::Raycast(m_Vertices[0], tempP1, tempP2, hitInfo))
	{

		if (actorVelocity.y > 0.f)
		{
				actorShape.bottom = hitInfo.intersectPoint.y - actorShape.height-2.f;
			actorVelocity.y = 0.f;
		}
		else
		{
			actorShape.bottom = hitInfo.intersectPoint.y;
			actorVelocity.y = 0.f;
		}
	}

	Point2f tempP3{ actorShape.left , actorShape.bottom + actorShape.height / 2.f };
	Point2f tempP4{ actorShape.left + actorShape.width, actorShape.bottom + actorShape.height / 2.f };


	if (utils::Raycast(m_Vertices[0], tempP3, tempP4, hitInfo))
	{
		/*left*/if (actor.m_Direction == GameObject::Direction::left)actorShape.left = hitInfo.intersectPoint.x;
		if (actor.m_Direction == GameObject::Direction::right)actorShape.left = hitInfo.intersectPoint.x - actorShape.width;
	}

}

bool Level::IsOnGround(const Rectf & actorShape) const
{
	utils::HitInfo hitInfo;
	return utils::Raycast(m_Vertices[0], { actorShape.left + actorShape.width / 2, actorShape.bottom + actorShape.height }, { actorShape.left + actorShape.width / 2, actorShape.bottom - 1.f}, hitInfo);
}

bool Level::CheckCollision(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	utils::HitInfo hitInfo;

	Point2f tempP3{ actorShape.left , actorShape.bottom + actorShape.height / 2.f };
	Point2f tempP4{ actorShape.left + actorShape.width , actorShape.bottom + actorShape.height / 2.f };


	if (utils::Raycast(m_Vertices[0], tempP3, tempP4, hitInfo))
	{
		return true;

	}
	return false;
}
