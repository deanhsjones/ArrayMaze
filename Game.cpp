#include "Game.h"



Game::Game()
    :m_pStateMachine(nullptr);
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
    if (pStateMachine)
    {
        pStateMachine->Init();
        m_pStateMachine = pStateMachine;
    }
}
void Game::RunGameLoop()
{
    bool isGameOver = false;
    while (!isGameOver)
    {
        Update(false);
        Draw();
        isGameOver = Update();
    }
    Draw();
}
void Game::Deinitialize()
{
    if (m_pStateMachine)
    {
        m_pStateMachine->Cleanup();
    }
}


bool Game::Update(bool processInput)
{
    return m_pStateMachine->UpdateCurrentState(processInput);
}
void Game::Draw()
{
    m_pStateMachine->DrawCurrentState();
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





