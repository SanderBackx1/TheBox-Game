#include "stdafx.h"
#include "Door.h"
#include "utils.h"
#include "Texture.h"

Door::Door(const Point2f& pos, const Color4f color, bool IsClosed, float height, const std::shared_ptr<Texture> & pTexture)
	:m_Position{pos}
	,m_Shape{pos.x, pos.y, 20,height}
	,m_Color{color}
	,m_IsClosed{IsClosed}
	,m_pDoorTexture(pTexture)
{
}

void Door::Draw() const
{
	m_pDoorTexture->Draw(m_Shape);
}
void Door::SwapOpenClose()
{
	m_IsClosed = !m_IsClosed;
}

bool Door::IsHit(const Rectf& shape)
{
	return utils::IsOverlapping(m_Shape, shape);
}

bool Door::IsOpen() const
{
	return !m_IsClosed;
}

Rectf Door::GetShape() const
{
	return m_Shape;
}

