#pragma once
#include "GameObject.h"
class Key :
	public GameObject
{
public:
	Key(const Point2f& pos, const std::shared_ptr<Texture> & pTexture);
	virtual ~Key() = default;
	virtual void Draw() const;
	Rectf GetShape()const;

private:
	Rectf m_Shape;
	std::shared_ptr<Texture> m_pKeyTexture;
};

