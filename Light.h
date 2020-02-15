#pragma once
#include "Texture.h"
class Light
{
public:
	Light(float width, float height);
	void Draw(const Rectf& toTrack) const;
//	Point2f GetPosition(const Rectf& toTrack) const;


private:
	float m_Width;
	float m_Height;
	Rectf m_Boundaries;
	Texture m_Texture;

	Point2f Track(const Rectf& toTrack) const;

};

