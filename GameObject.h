#pragma once
#include <memory>
#include "vector2f.h"
class Texture;
class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	virtual void Draw() const = 0;
	enum class Direction
	{
		left,
		right,
		up,
		down
	};

	Direction m_Direction;
};

