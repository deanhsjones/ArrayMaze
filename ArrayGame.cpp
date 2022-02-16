#include "vld.h"
#include <iostream>
#include "Game.h"
#include "AudioManager.h"



using namespace std;

int main()
{
    Game myGame;
    
    if (myGame.Load())
    {
        while(!myGame.IsGameOver())
        {
            myGame.Run();
        }

        if (myGame.DidUserQuit())
        {
            cout << "Thanks for playing!";
        }

        else if (myGame.GetPlayerLives() < 0)
        {
            cout << "You lose!" << endl;
            AudioManager::GetInstance()->PlayLoseSound();
        }
        else
        {
            cout << "You Won!" << endl;
            AudioManager::GetInstance()->PlayWinSound();
        }


    }

    else
    {
        cout << "Game did not load, terminating now!" << endl;
    }

AudioManager::DestroyInstance();
return 0;

}