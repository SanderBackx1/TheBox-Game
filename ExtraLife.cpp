#include "stdafx.h"
#include "ExtraLife.h"
#include "utils.h"
#include "Texture.h"

ExtraLife::ExtraLife(const Point2f& pos,const std::shared_ptr<Texture>& pTexture)
	:m_Shape {pos.x, pos.y, 20.f, 20.f}
	,m_pHealthTexture{pTexture}
{
}

void ExtraLife::Draw() const
{
	m_pHealthTexture->Draw(m_Shape);
}

Rectf ExtraLife::GetShape() const
{
	return m_Shape;
}
