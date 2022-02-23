#pragma once
#include "GameStateMachine.h"

class Game;
class GameStates;


class StateMachineExampleGame : public GameStateMachine
{
public:
    enum class SceneName //the different states we will be in
    {
        None,
        MainMenu,
        Gameplay, 
        Settings,
        HighScore, 
        Lose, 
        Win


    };

private:
    Game* m_pOwner; //for each concrete SM we'll have an owner, that will be the Game, so they can interact
    
    GameState* m_pCurrentState; 
    GameState* m_pNewState;

public:
    StateMachineExampleGame(Game* pOwner);

    virtual bool Init() override;
    virtual bool UpdateCurrentState(bool processInput = true) override;
    virtual void DrawCurrentState() override;
    virtual void ChangeState(GameState* pNewState) override;
    virtual void Cleanup();
    void LoadScene(SceneName scene);

};

