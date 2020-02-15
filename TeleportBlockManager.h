#pragma once
#include <memory>
#include <vector>
#include <utility>
#include "Avatar.h"
#include "SoundEffect.h"
class TeleportBlock;
class TeleportBlockManager
{
public:
	TeleportBlockManager();
	void Update(Avatar& avatar, float elapsedSec);
	void Draw() const;
	void Reset();


	TeleportBlockManager(const TeleportBlockManager& gobj) = delete;
	TeleportBlockManager(TeleportBlockManager&& gobj) = delete;
	TeleportBlockManager& operator=(TeleportBlockManager&& other) = delete;
	TeleportBlockManager& operator=(const TeleportBlockManager& rhs) = delete;

private:
	void Init();
	void SwapActivePair(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock>>& pair);
	SoundEffect m_TeleportSound;
	std::vector<std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock>>> m_BlockPairs;

	static std::shared_ptr<Texture> m_pTPBlockTexture;
	static int m_InstanceCounter;
};

