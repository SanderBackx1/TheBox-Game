#pragma once
#include "GameObject.h"
class ExtraLife :
	public GameObject
{
public:
	ExtraLife(const Point2f& pos,const std::shared_ptr<Texture>& pTexture);
	virtual ~ExtraLife() = default;
	virtual void Draw() const;
	Rectf GetShape()const;


private:
	Rectf m_Shape;
	std::shared_ptr<Texture> m_pHealthTexture;
	
};

