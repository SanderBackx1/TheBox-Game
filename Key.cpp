#include "stdafx.h"
#include "Key.h"
#include "utils.h"
#include "Texture.h"

Key::Key(const Point2f& pos, const std::shared_ptr<Texture>& pTexture)
	:m_Shape{pos.x, pos.y, 20.f,20.f}
	,m_pKeyTexture{pTexture}
{

}

void Key::Draw() const
{
	m_pKeyTexture->Draw(m_Shape);
}

Rectf Key::GetShape() const
{
	return m_Shape;
}


