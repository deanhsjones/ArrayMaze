
#include <iostream>
using namespace std;

constexpr char kTopRightBoarder = 187;
constexpr char kTopLeftBoarder = 201;
constexpr char kBottomRightBoarder = 188;
constexpr char kBottomLeftBoarder = 200;
constexpr char kHorizontalBoarder = 205;
constexpr char kVerticalBoarder = 186;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height);
int GetIndexFromXY(int x, int y, int width);

void DisplayTopBoarder(int width);
void DisplayBottomBoarder(int width);
void DisplayLeftBoarder();
void DisplayRightBoarder();



int main()
{
    int levelWidth;
    int levelHeight;

    GetLevelDimensions(levelWidth, levelHeight);

    char* pLevel = new char[levelWidth * levelHeight];

    for (int  i = 0; i < levelWidth * levelHeight; i++)
    {
        pLevel[i] = ' ';
    }

    DisplayLevel(pLevel, levelWidth, levelHeight);

    delete[] pLevel;
    pLevel = nullptr;


    return 0;

}

void GetLevelDimensions(int& width, int& height)
{
    cout << "Enter width of level: ";
    cin >> width;
    cout << "Enter height of level: ";
    cin >> height;
}

void DisplayLevel(char* pLevel, int width, int height)
{
    DisplayTopBoarder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBoarder();

        for (int x = 0; x < width; x++)
        {
            int i = GetIndexFromXY(x, y, width);
            cout << pLevel[i];

        }

        DisplayRightBoarder();
    }



    DisplayBottomBoarder(width);
}

int GetIndexFromXY(int x, int y, int width)
{
    return x + y * width;
}


void DisplayTopBoarder(int width)
{
    cout << kTopLeftBoarder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBoarder;
    }
    cout << kTopRightBoarder << endl;
}
void DisplayBottomBoarder(int width)
{
    cout << kBottomLeftBoarder;
    for (int i = 0; i < width; i++)
    {
        cout << kHorizontalBoarder;
    }
    cout << kBottomRightBoarder << endl;
}
void DisplayLeftBoarder()
{
    cout << kVerticalBoarder;
}
void DisplayRightBoarder()
{
    cout << kVerticalBoarder << endl;
}