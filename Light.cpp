#include "stdafx.h"
#include "Light.h"


Light::Light(float width, float height)
	:m_Width(width)
	, m_Height(height)
	,m_Texture{ "Resources/Images/Camera/shade.png" }
{
}


void Light::Draw(const Rectf & toTrack) const
{
	Rectf cameraRect;
	Point2f trackedObj{ Track(toTrack) };
	cameraRect.left = trackedObj.x - m_Width / 2;
	cameraRect.bottom = trackedObj.y - m_Height / 2;
	cameraRect.width = m_Width;
	cameraRect.height = m_Height;
	m_Texture.Draw(cameraRect);
}
Point2f Light::Track(const Rectf & toTrack) const
{
	Point2f trackObj{ toTrack.left + toTrack.width, toTrack.bottom + toTrack.height / 2 };
	return { trackObj };
}

