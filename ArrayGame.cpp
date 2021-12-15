// ArrayGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;
const char kPlayerSymbol = '@';
constexpr char WAL = 219;
constexpr char KEY = 232;
constexpr char DOR = 179;
constexpr char GOL = 36;
constexpr int kOpenDoorColor = 10;
constexpr int kClosedDoorColor = 12;
constexpr int kRegularColor = 7;



int GetIndexFromCoordinates(int X, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey);
bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);
void PlayDoorClosedSound();
void PlayDoorOpenedSound();
void PlayKeyPickupSound();
void PlayWinSound();

int main()
{
    constexpr int kWidth = 25;
    constexpr int kHeight = 15;

    char levelArray[]{ WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', KEY, WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, WAL, ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', WAL,
                       WAL, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', DOR, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', GOL, WAL,
                       WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL, WAL };

    int playerX = 1;
    int playerY = 1;
    bool playerHasKey = false;
    bool gameOver = false;


    while (!gameOver)
    {
        system("cls");
        DrawLevel(levelArray, kWidth, kHeight, playerX, playerY, playerHasKey);
        gameOver = UpdatePlayerPosition(levelArray, playerX, playerY, kWidth, playerHasKey);

    }
     system("cls");
     DrawLevel(levelArray, kWidth, kHeight, playerX, playerY, playerHasKey);
     cout << "You Won!" << endl;
     PlayWinSound();
}

int GetIndexFromCoordinates(int x, int y, int width)
{
    return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY, bool playerHasKey)
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (playerX == x && playerY == y)
            {
                cout << kPlayerSymbol;
            }
            else
            {
            int indexToPrint = GetIndexFromCoordinates(x, y, width);
            HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
            if (level[indexToPrint] == DOR)
            {
                if (playerHasKey)
                {
                    SetConsoleTextAttribute(console, kOpenDoorColor);
                }
                else
                {
                    SetConsoleTextAttribute(console, kClosedDoorColor);
                }
            }
            else
            {
                SetConsoleTextAttribute(console, kRegularColor);
            }
            cout << level[indexToPrint];

            }
        }
        cout << endl;
    }
}

bool UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey)
{
    char input = _getch();

    int newPlayerX = playerX;
    int newPlayerY = playerY;


    switch (input)
    {
    case 'w':
    case 'W':
    {
        newPlayerY--;
        break;
    }
    case 's':
    case 'S':
    {
        newPlayerY++;
        break;
    }
    case 'a':
    case 'A':
    {
        newPlayerX--;
        break;
    }
    case 'd':
    case 'D':
    {
        newPlayerX++;
        break;
    }
    default:
        break;

    }

    int index = GetIndexFromCoordinates(newPlayerX, newPlayerY, width);
    if (level[index] == ' ')
    {
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
    else if (level[index] == KEY)
    {
        playerHasKey = true;
        level[index] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
        PlayKeyPickupSound();
    }
    else if (level[index] == DOR && playerHasKey)
    {
        level[index] = ' ';
        playerHasKey = false;
        playerX = newPlayerX;
        playerY = newPlayerY;
        PlayDoorOpenedSound();
    }
    else if (level[index] == DOR && !playerHasKey)
    {
        PlayDoorClosedSound();
    }
    else if (level[index] == GOL)
    {
        level[index] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
        return true;
    }
    return false;
    
}

void PlayDoorClosedSound()
{
    Beep(500, 75);
    Beep(500, 75);
}
void PlayDoorOpenedSound()
{
    Beep(1397, 200);
}
void PlayKeyPickupSound()
{
    Beep(1568, 200);
}
void PlayWinSound()
{
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1568, 200);
    Beep(1245, 1000);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1397, 200);
    Beep(1175, 1000);
}