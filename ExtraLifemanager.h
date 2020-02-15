#pragma once
#include <vector>
#include "ExtraLife.h"
#include "Avatar.h"
#include "SoundEffect.h"

class ExtraLifemanager
{
public:
	ExtraLifemanager();
	void Draw()const;
	void Update(Avatar& avatar);
	std::shared_ptr<Texture> GetTexture() const;
	void Reset();

	ExtraLifemanager(const ExtraLifemanager& gobj) = delete;
	ExtraLifemanager(ExtraLifemanager&& gobj) = delete;
	ExtraLifemanager& operator=(ExtraLifemanager&& other) = delete;
	ExtraLifemanager& operator=(const ExtraLifemanager& rhs) = delete;
private:
	void HandleCollision(Avatar& avatar);
	void Init();
	void Remove(std::shared_ptr<ExtraLife>& el);
	std::vector<std::shared_ptr<ExtraLife>> m_pExtraLives;
	SoundEffect m_HealthSound;

	//texture
	static std::shared_ptr<Texture> m_pHealthTexture;
	static int m_InstanceCounter;
};

