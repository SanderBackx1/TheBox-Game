#include "stdafx.h"
#include "TeleportBlockManager.h"
#include "TeleportBlock.h"
#include <iostream>

std::shared_ptr<Texture> TeleportBlockManager::m_pTPBlockTexture{ nullptr };
int TeleportBlockManager::m_InstanceCounter{ 0 };

TeleportBlockManager::TeleportBlockManager()
	:m_TeleportSound{"Resources/Sound/Teleport.ogg"}
{
	if (m_InstanceCounter == 0)
	{
		m_pTPBlockTexture = std::make_unique<Texture>("Resources/Images/Teleport/spritesheet.png");
	}
	++m_InstanceCounter;
	Init();
}

void TeleportBlockManager::Update(Avatar& avatar, float elapsedSec)
{
	for (std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>& pair : m_BlockPairs)
	{
		if (pair.first.get()->IsHit(avatar) && pair.first.get()->CheckCooldown())
		{
			pair.second.get()->TeleportActor(avatar);
			m_TeleportSound.Play(false);
			SwapActivePair(pair);
			pair.first.get()->StartCooldown();
			pair.second.get()->StartCooldown();


		}
		else if (pair.second.get()->IsHit(avatar) && pair.second.get()->CheckCooldown())
		{

			pair.first.get()->TeleportActor(avatar);
		

			m_TeleportSound.Play(false);
			pair.first.get()->StartCooldown();
			pair.second.get()->StartCooldown();
		}
		if(!pair.first.get()->CheckCooldown()) pair.first.get()->ChangeCooldown(elapsedSec);
		if (!pair.second.get()->CheckCooldown()) pair.second.get()->ChangeCooldown(elapsedSec);
		pair.first.get()->Update(elapsedSec);
		
		pair.second.get()->Update(elapsedSec);
	}
}

void TeleportBlockManager::Draw() const
{
	for (const std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>& pair : m_BlockPairs)
	{
		pair.first.get()->Draw();
		pair.second.get()->Draw();
	}
}

void TeleportBlockManager::Reset()
{
	m_BlockPairs.clear();
	Init();
	
}

void TeleportBlockManager::Init()
{
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ {1150,400,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 1340,120,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 1630,250,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 1630,650,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 1820,410,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 1350,861,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 985,700,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 670,440,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 200,900,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 720,900,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 1820,947,40,40 } ,true, m_pTPBlockTexture }, new TeleportBlock{ { 470,800,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 360,820,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 90,862,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 420,980,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 55,345,40,40 },true, m_pTPBlockTexture }));
	m_BlockPairs.push_back(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock >>(new TeleportBlock{ { 560,345,40,40 },true, m_pTPBlockTexture }, new TeleportBlock{ { 610, 540,40,40 },true, m_pTPBlockTexture }));
	 
}

void TeleportBlockManager::SwapActivePair(std::pair<std::shared_ptr<TeleportBlock>, std::shared_ptr<TeleportBlock>>& pair)
{
		pair.first.get()->SwapActive();
		pair.second.get()->SwapActive();
}
