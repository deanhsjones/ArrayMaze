#include "StateMachineExampleGame.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "Game.h"


StateMachineExampleGame::StateMachineExampleGame(Game* pOwner)
	: m_pOwner(pOwner)
	, m_pCurrentState(nullptr)
	, m_pNewState(nullptr)
{

}

bool StateMachineExampleGame::Init()
{
	LoadScene(SceneName::MainMenu);
	return true;
}
 bool StateMachineExampleGame::UpdateCurrentState(bool processInput)
 {
	 bool done = false;
	 if (m_pNewState != nullptr) // do we have a new state?
	 {
		 ChangeState(m_pNewState); //if not, change it to the new state
		 m_pNewState = nullptr; //now we're in the state so it's good
	 }
	 if (m_pCurrentState != nullptr)	//we have a state that we want to update
	 {
		 done = m_pCurrentState->Update(processInput);
	 }
	 return done;
 }
 void StateMachineExampleGame::DrawCurrentState()
{
	 if (m_pCurrentState)
	 {
		 m_pCurrentState->Draw();	//if we have a current state, draw it
	 }
}
 void StateMachineExampleGame::ChangeState(GameState* pNewState)
{
	 if (m_pCurrentState)
	 {
		 m_pCurrentState->Exit();	//if we have a current state, exit it
	 }

	 delete m_pCurrentState;	//delete the current state
	 m_pCurrentState = pNewState; //set thew new state
	 pNewState->Enter();	//and enter it
}
 bool StateMachineExampleGame::Cleanup()
{
	 if (m_pCurrentState)
	 {
		 m_pCurrentState->Exit();	//if we have a current state, exit and delete it
		 delete m_pCurrentState;
	 }

	 return true;
}
void StateMachineExampleGame::LoadScene(SceneName scene)
{
	switch (scene)
	{
	case SceneName::MainMenu:
		m_pNewState = new MainMenuState(this);
		break;
	case SceneName::Gameplay:
		m_pNewState = new GameplayState(this)
			break;

		default: break;
	}
}
