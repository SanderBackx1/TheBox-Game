#pragma once
#include <memory>

class Camera
{
public:
	Camera(float width, float height);
	void SetBoundaries(const Rectf& boundaries);
	void Draw(const Rectf& toTrack) const;
	Point2f GetPosition(const Rectf& toTrack) const;
	void Update(float elapsedSec);
private:
	float m_Width;
	float m_Height;
	Rectf m_Boundaries;
	float m_Shake;
;
	Point2f Track(const Rectf& toTrack) const;
	void Clamp(Point2f& bottomLeftPos) const;

};

