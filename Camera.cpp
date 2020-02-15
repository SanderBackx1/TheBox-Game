#include "stdafx.h"
#include "Camera.h"
#include "utils.h"

Camera::Camera(float width, float height)
	:m_Width(width)
	, m_Height(height)


{
}

void Camera::SetBoundaries(const Rectf & boundaries)
{
	m_Boundaries = boundaries;
}

void Camera::Draw(const Rectf & toTrack) const
{
	Rectf cameraRect;
	Point2f trackedObj{ Track(toTrack) };
	cameraRect.left = trackedObj.x - m_Width / 2;
	cameraRect.bottom = trackedObj.y - m_Height / 2;
	cameraRect.width = m_Width;
	cameraRect.height = m_Height;

	
}

Point2f Camera::Track(const Rectf & toTrack) const
{
	Point2f trackObj{ toTrack.left + toTrack.width, toTrack.bottom + toTrack.height / 2 };
	Clamp(trackObj);
	return { trackObj };
}

void Camera::Clamp(Point2f & bottomLeftPos) const
{
	if (bottomLeftPos.x + m_Width / 2 > m_Boundaries.left + m_Boundaries.width)
	{
		float overLap{ (bottomLeftPos.x + m_Width / 2) - (m_Boundaries.left + m_Boundaries.width) };
		bottomLeftPos.x -= overLap;
	}
	else if (bottomLeftPos.x - m_Width / 2 < m_Boundaries.left)
	{
		float overLap{ -m_Boundaries.left + (bottomLeftPos.x - m_Width / 2) };
		bottomLeftPos.x += -overLap;
	}

	if (bottomLeftPos.y + m_Height / 2 > m_Boundaries.bottom + m_Boundaries.height)
	{
		float overLap{ (bottomLeftPos.y + m_Height / 2) - (m_Boundaries.bottom + m_Boundaries.height) };
		bottomLeftPos.y -= overLap;
	}
	else if (bottomLeftPos.y - m_Height / 2 < m_Boundaries.bottom)
	{
		float overLap{ -m_Boundaries.bottom + (bottomLeftPos.y - m_Height / 2) };
		bottomLeftPos.y -= overLap;
	}
}

Point2f Camera::GetPosition(const Rectf& toTrack) const
{
	Point2f trackObj{ Track(toTrack).x, Track(toTrack).y };
	trackObj.x -= m_Width / 2;
	trackObj.y -= m_Height / 2;
	return trackObj;
}

void Camera::Update(float elapsedSec)
{

}
