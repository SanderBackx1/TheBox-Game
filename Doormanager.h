#pragma once
#include "Door.h"
#include <memory>
#include <vector>
#include "SoundEffect.h" 
class Avatar;
class Doormanager
{
public:
	Doormanager();
	void Draw() const;
	void Update(float elapsedSec, bool areKeysCollected);
	void HandleCollision(Avatar& avatar );
	std::vector<Rectf> GetShapes() const;
	void Reset();

	Doormanager(const Doormanager& gobj) = delete;
	Doormanager(Doormanager&& gobj) = delete;
	Doormanager& operator=(Doormanager&& other) = delete;
	Doormanager& operator=(const Doormanager& rhs) = delete;
private:
	void Remove(std::shared_ptr<Door>& d);
	void Init();
	SoundEffect m_DoorOpeningSound;
	std::vector<std::shared_ptr<Door>> m_pDoors;


	static std::shared_ptr<Texture> m_pDoorTexture;
	static int m_InstanceCounter;
};

