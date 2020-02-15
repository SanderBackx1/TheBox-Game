#pragma once
#include "GameObject.h"
class Door :
	public GameObject
{
public:
	Door(const Point2f& pos, const Color4f color, bool IsClosed, float height, const std::shared_ptr<Texture> & pTexture);
	virtual void Draw() const;
	virtual ~Door()=default;
	void SwapOpenClose();
	bool IsHit(const Rectf& shape);
	bool IsOpen()const;
	Rectf GetShape() const;


private:

	Rectf m_Shape;
	Point2f m_Position;
	bool m_IsClosed;
	Color4f m_Color;

	std::shared_ptr<Texture> m_pDoorTexture;
};

