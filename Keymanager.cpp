#include "stdafx.h"
#include "Keymanager.h"
#include "utils.h"
#include "Texture.h"

std::shared_ptr<Texture> Keymanager::m_pKeyTexture{ nullptr };
int Keymanager::m_InstanceCounter{ 0 };


Keymanager::Keymanager(int totalKeys)
	:m_TotalCollected{0}
	,m_TotalKeys{totalKeys}
	,m_KeySound{"Resources/Sound/Key.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pKeyTexture = std::make_shared<Texture>("Resources/Images/Key/key.png");
	}
	Init();
}

void Keymanager::Draw() const
{
	for (std::shared_ptr<Key> k : m_pKeys)
	{
		k->Draw();
	}
}

void Keymanager::Update(const Rectf & avatarShape)
{
	HandleCollision(avatarShape);
}

bool Keymanager::AreAllCollected() const
{
	return m_TotalCollected == m_TotalKeys;
}

void Keymanager::Reset()
{
	m_pKeys.clear();
	m_TotalCollected = 0;
	m_TotalKeys = 5;
	Init();
}

void Keymanager::HandleCollision(const Rectf & avatarShape)
{
	for (std::shared_ptr<Key> k: m_pKeys)
	{
		if (utils::IsOverlapping(avatarShape, k->GetShape()))
		{
			Remove(k);
			m_TotalCollected++;
			m_KeySound.Play(false);
		}
	}
}

void Keymanager::Remove(std::shared_ptr<Key>& k)
{
	if (m_pKeys[m_pKeys.size()-1] != k)
	{
		std::shared_ptr<Key> pTemp;
		for (size_t i{ 0 }; i < m_pKeys.size()-1; ++i)
		{
			if (m_pKeys[i] == k)
			{
				pTemp = m_pKeys[m_pKeys.size() - 1];
				m_pKeys[m_pKeys.size() - 1] = m_pKeys[i];
				m_pKeys[i] = pTemp;
				pTemp = nullptr;
			}
		}
	};
	m_pKeys.pop_back();
}




void Keymanager::Init()
{
	m_pKeys.push_back(std::make_shared<Key>(Key{ { 455.f,220.f}, m_pKeyTexture }));
	m_pKeys.push_back(std::make_shared<Key>(Key{ { 1620.f,400.f }, m_pKeyTexture }));
	m_pKeys.push_back(std::make_shared<Key>(Key{ { 1520.f,960.f }, m_pKeyTexture }));
	m_pKeys.push_back(std::make_shared<Key>(Key{ { 340.f,800.f }, m_pKeyTexture }));
	m_pKeys.push_back(std::make_shared<Key>(Key{ { 60.f, 950.f }, m_pKeyTexture }));
}



