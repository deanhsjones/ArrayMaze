#include <conio.h>
#include <iostream>
#include "Game.h"
#include "AudioManager.h"
#include <windows.h>
#include <assert.h>

#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Money.h"
#include "Goal.h"

using namespace std;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;


Game::Game()
	:m_isGameOver(false){ }

Game::~Game(){ }

bool Game::Load()
{
	return m_level.Load("Level1.txt", m_player.GetXPositionPointer(), m_player.GetYPositionPointer() );
}
void Game::Run()
{
	Draw();

	m_isGameOver = Update();
	if(m_isGameOver)
	{
		Draw();
	}
}


bool Game::IsGameOver()
{ 
	return m_isGameOver;
}


bool Game::Update()
{
    int input = _getch();
    int arrowInput = 0;
    int newPlayerX = m_player.GetXPosition();
    int newPlayerY = m_player.GetYPosition();

    //arrow keys pressed

    if (input == kArrowInput)
    {
        arrowInput = _getch();
    }

    if ((input == kArrowInput && arrowInput == kLeftArrow) || (char)input == 'A' || (char)input == 'a')
    {
        newPlayerX--;
    }
    if ((input == kArrowInput && arrowInput == kRightArrow) || (char)input == 'D' || (char)input == 'd')
    {
        newPlayerX++;
    }
    if ((input == kArrowInput && arrowInput == kUpArrow) || (char)input == 'W' || (char)input == 'w')
    {
        newPlayerY--;
    }
    if ((input == kArrowInput && arrowInput == kDownArrow) || (char)input == 'S' || (char)input == 's')
    {
        newPlayerY++;
    }
    if (input == kEscape)
    {
        m_UserQuit = true;
        return true;
    }
    else if ((char)input == 'Z' || (char)input == 'z')
    {
        m_player.DropKey();
    }


     if (newPlayerX == m_player.GetXPosition() && newPlayerY == m_player.GetYPosition())
    {
        return false;
    }
    else
    {
        return HandleCollision(newPlayerX, newPlayerY);
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
void Game::Draw()
{   
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("cls");

    m_level.Draw();
    
    COORD actorCursorPosition;
    actorCursorPosition.X = m_player.GetXPosition();
    actorCursorPosition.Y = m_player.GetYPosition();
    SetConsoleCursorPosition(console, actorCursorPosition);
    m_player.Draw();

    COORD currentCursorPosition;
    currentCursorPosition.X = 0;
    currentCursorPosition.Y = 0;
    SetConsoleCursorPosition(console, currentCursorPosition);
}

bool Game::HandleCollision(int newPlayerX, int newPlayerY)
{   
    bool isGameDone = false;
    PlaceableActor* collidedActor = m_level.UpdateActors(newPlayerX, newPlayerY);
    if (collidedActor != nullptr && collidedActor->IsActive())
    {
        switch (collidedActor->GetType())
        {
        case ActorType::Enemy:
        {
            Enemy* collidedEnemy = dynamic_cast<Enemy*>(collidedActor);
            assert(collidedEnemy);
            AudioManager::GetInstance()->PlayLoseLivesSound();

            collidedEnemy->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);

            m_player.DecrementLives();
            if (m_player.GetLives() < 0)
            {
                isGameDone = true;
            }

            break;

        }

        case ActorType::Money:
        {
            Money* collidedMoney = dynamic_cast<Money*>(collidedActor);
            assert(collidedMoney);

            collidedMoney->Remove();
            m_player.AddMoney(collidedMoney->GetWorth());
            m_player.SetPosition(newPlayerX, newPlayerY);
            AudioManager::GetInstance()->PlayMoneySound();
            break;
        }

        case ActorType::Key:
        {
            Key* collidedKey = dynamic_cast<Key*>(collidedActor);
            assert(collidedKey);

            m_player.PickupKey(collidedKey);
            collidedKey->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);
            AudioManager::GetInstance()->PlayKeyPickupSound();

            break;
        }

        case ActorType::Door:
        {
            Door* collidedDoor = dynamic_cast<Door*>(collidedActor);
            assert(collidedDoor);

            if (!collidedDoor->IsOpen())
            {
                if (m_player.HasKey(collidedDoor->GetColor()))
                {
                    collidedDoor->Open();
                    collidedDoor->Remove();
                    m_player.UseKey();
                    m_player.SetPosition(newPlayerX, newPlayerY);
                    AudioManager::GetInstance()->PlayDoorOpenSound();
                }
                else
                {
                    AudioManager::GetInstance()->PlayDoorClosedSound();
                }

            }
            else
            {
                m_player.SetPosition(newPlayerX, newPlayerY);

            }
            break;
        }

        case ActorType::Goal:
        {
            Goal* collidedGoal = dynamic_cast<Goal*>(collidedActor);
            assert(collidedGoal);

            collidedGoal->Remove();
            m_player.SetPosition(newPlayerX, newPlayerY);
            isGameDone = true;

            break;
        }

        default:
            break;
        }

    }
    else if (m_level.IsSpace(newPlayerX, newPlayerY))
    {
        m_player.SetPosition(newPlayerX, newPlayerY);
    }
    else if (m_level.IsWall(newPlayerX, newPlayerY))
    {
        //do nothing
    }

    return isGameDone;
}


