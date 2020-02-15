#include "stdafx.h"
#include "Doormanager.h"
#include "Avatar.h"

std::shared_ptr<Texture> Doormanager::m_pDoorTexture{ nullptr };
int Doormanager::m_InstanceCounter{ 0 };


Doormanager::Doormanager()
	:m_DoorOpeningSound{"Resources/Sound/DoorOpening.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pDoorTexture = std::make_shared<Texture>("Resources/Images/Door/door.png");
	}
	Init();
}

void Doormanager::Draw() const
{
	for (const std::shared_ptr<Door>& door : m_pDoors)
	{
		door->Draw();
	}

}

void Doormanager::Update(float elapsedSec, bool areKeysCollected)
{
	for (std::shared_ptr<Door>& door : m_pDoors)
	{
		if (areKeysCollected && !door->IsOpen())
		{
			door->SwapOpenClose();
			m_DoorOpeningSound.Play(false);
		}
		
		if (door->IsOpen()) Remove(door);
	}
	
}



void Doormanager::HandleCollision(Avatar& avatar)
{
	for (const std::shared_ptr<Door>& door : m_pDoors)
	{
		if (door->IsHit(avatar.GetShape()))
		{
			Point2f newPos{ door->GetShape().left - avatar.GetShape().width, avatar.GetShape().bottom };
			avatar.SetPos(newPos);
		}
	}
}

std::vector<Rectf> Doormanager::GetShapes() const
{
	std::vector<Rectf> shapes;
	for (const std::shared_ptr<Door>& door : m_pDoors)
	{
		shapes.push_back(door->GetShape());
		
	}
	return shapes;
}

void Doormanager::Reset()
{
	m_pDoors.clear();
	Init();
}

void Doormanager::Remove(std::shared_ptr<Door>& d)
{
	if (m_pDoors[m_pDoors.size() - 1] != d)
	{
		std::shared_ptr<Door> pTemp;
		for (size_t i{ 0 }; i < m_pDoors.size()-1; ++i)
		{
			if (m_pDoors[i] == d)
			{
				pTemp = m_pDoors[m_pDoors.size() - 1];
				m_pDoors[m_pDoors.size() - 1] = m_pDoors[i];
				m_pDoors[i] = pTemp;
				pTemp = nullptr;
			}
		}
	};
	m_pDoors.pop_back();
}

void Doormanager::Init()
{
	m_pDoors.push_back(std::make_shared<Door>( Door{ { 700,540 }, {1.f,0.f,0.f,1.f}, true, 100.f,m_pDoorTexture }));
}

