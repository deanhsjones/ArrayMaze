#include "Game.h"



Game::Game()
	:m_isGameOver(false){ }

Game::~Game(){ }


void Game::Run()
{
	Draw();

	m_isGameOver = Update();
	if(m_isGameOver)
	{
		Draw();
	}
}







    
  /*  if (m_level.IsSpace(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsKey(newPlayerX, newPlayerY))
    {
        
        m_level.PickupKey(newPlayerX, newPlayerY);
        m_player.PickupKey();
        m_player.SetPosition(newPlayerX, newPlayerY);
    }   
    else if (m_level.IsDoor(newPlayerX, newPlayerY) && m_player.HasKey())
    {
        m_level.OpenDoor(newPlayerX, newPlayerY);
        m_player.UseKey();
        m_player.SetPosition(newPlayerX, newPlayerY);
        
    }
    else if(m_level.IsDoor(newPlayerX, newPlayerY) && !m_player.HasKey())
    {
       
    }
    else if(m_level.IsGoal(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
        return true;
    }
    return false;
}*/





