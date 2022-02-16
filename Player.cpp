#include <iostream>

#include "Player.h"
#include "Key.h"
#include "AudioManager.h"

using namespace std;

constexpr int kStartingNumberofLives = 3;

Player::Player()
	: PlaceableActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_money(0)
	, m_lives(kStartingNumberofLives)
	
{

}
//Player::~Player()
//{
//
//}


//void Player::SetPosition(int x, int y)
//{
//	m_position.x = x;
//	m_position.y = y;
//}

bool Player::HasKey()
{ 
	return m_pCurrentKey != nullptr;
}

bool Player::HasKey(ActorColor color)
{
	return HasKey() && m_pCurrentKey->GetColor() == color;
}

void Player::PickupKey(Key* key)
{
	m_pCurrentKey = key;
}

void Player::UseKey()
{ 
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey()
{	
	if (m_pCurrentKey)
	{
		AudioManager::GetInstance()->PlayKeyDropSound();
		m_pCurrentKey->Place(m_pPosition->x, m_pPosition->y);
		m_pCurrentKey = nullptr;
	}
}

void Player::Draw()
{
	cout << "@";
}