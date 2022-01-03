#include "Player.h"
#include <iostream>
using namespace std;

Player::Player()
	: M_hasKey(false)
{

}
Player::~Player()
{

}


void Player::SetPosition(int X, int y)
{
	m_position.x = x;
	m_position.y = y;
}

bool Player::HasKey()
{ 
	return m_hasKey;
}

void Player::PickupKey()
{
	m_hasKey = true;
}

void Player::UseKey()
{ 
	m_hasKey = false;
}

void Player::Draw()
{
	cout << kPlayerSymbol;
}