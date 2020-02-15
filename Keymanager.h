#pragma 
#include "Key.h"
#include <memory>
#include <vector>
#include "SoundEffect.h"
class Keymanager
{
public:
	Keymanager(int totalKeys);
	void Draw()const;
	void Update(const Rectf& avatarShape);
	bool AreAllCollected() const;
	void Reset();


	Keymanager(const Keymanager& gobj) = delete;
	Keymanager(Keymanager&& gobj) = delete;
	Keymanager& operator=(Keymanager&& other) = delete;
	Keymanager& operator=(const Keymanager& rhs) = delete;
private:
	void HandleCollision(const Rectf& avatarShape);
	void Remove(std::shared_ptr<Key>& k);
	void Init();	
	SoundEffect m_KeySound;
	int m_TotalKeys;
	std::vector<std::shared_ptr<Key>> m_pKeys;
	int m_TotalCollected;

	//Texture
	static std::shared_ptr<Texture> m_pKeyTexture;
	static int m_InstanceCounter;
};

