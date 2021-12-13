// ArrayGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>

using namespace std;
const char kPlayerSymbol = '@';

int GetIndexFromCoordinates(int X, int y, int width);
void DrawLevel(char level[], int width, int height, int playerX, int playerY);
void UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey);

int main()
{
    constexpr int kWidth = 25;
    constexpr int kHeight = 15;

    char levelArray[]{ '+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '+',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', '*', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+', '-', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '|',
                       '|', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'D', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'X', '|',
                       '+', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '+' };

    int playerX = 1;
    int playerY = 1;
    bool playerHasKey = false;

    while (true)
    {
        system("cls");
        DrawLevel(levelArray, kWidth, kHeight, playerX, playerY);
        UpdatePlayerPosition(levelArray, playerX, playerY, kWidth, playerHasKey);
    }


     DrawLevel(levelArray, kWidth, kHeight, playerX, playerY);
}

int GetIndexFromCoordinates(int x, int y, int width)
{
    return x + y * width;
}

void DrawLevel(char level[], int width, int height, int playerX, int playerY)
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
            int index = GetIndexFromCoordinates(x, y, width);
            cout << level[index];

            }
        }
        cout << endl;
    }
}

void UpdatePlayerPosition(char level[], int& playerX, int& playerY, int width, bool& playerHasKey)
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
    else if (level[index] == '*')
    {
        playerHasKey = true;
        level[index] = ' ';
        playerX = newPlayerX;
        playerY = newPlayerY;
    }
    else if (level[index] == 'D' && playerHasKey)
    {
        level[index] = ' ';
        playerHasKey = false;
        playerX = newPlayerX;
        playerY = newPlayerY;
    };
    
}