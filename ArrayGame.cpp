#include <iostream>
#include "Game.h"
#include "Sound.h"
#include <windows.h>

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
        }
        else
        {
            cout << "You Won!" << endl;
        }

    }

    else
    {
        cout << "Game did not load, terminating now!" << endl;
    }
}


//
//void PlayDoorClosedSound()
//{
//    Beep(500, 75);
//    Beep(500, 75);
//}
//void PlayDoorOpenedSound()
//{
//    Beep(1397, 200);
//}
//void PlayKeyPickupSound()
//{
//    Beep(1568, 200);
//}
//void PlayWinSound()
//{
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1568, 200);
//    Beep(1245, 1000);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1397, 200);
//    Beep(1175, 1000);
//}