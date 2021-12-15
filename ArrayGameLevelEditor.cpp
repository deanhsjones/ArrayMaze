
#include <iostream>
#include <conio.h>
#include <windows.h>


using namespace std;


constexpr char kCursor = '_';

constexpr char kTopRightBoarder = 187;
constexpr char kTopLeftBoarder = 201;
constexpr char kBottomRightBoarder = 188;
constexpr char kBottomLeftBoarder = 200;
constexpr char kHorizontalBoarder = 205;
constexpr char kVerticalBoarder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;

void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);

void DisplayTopBoarder(int width);
void DisplayBottomBoarder(int width);
void DisplayLeftBoarder();
void DisplayRightBoarder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);



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

    int cursorX = 0;
    int cursorY = 0;
    bool doneEditing = false;

    while (!doneEditing) {

        system("cls");
        DisplayLevel(pLevel, levelWidth, levelHeight, cursorX, cursorY);
        doneEditing = EditLevel(pLevel, cursorX, cursorY, levelWidth, levelHeight);
    }

    system("cls");
    DisplayLevel(pLevel, levelWidth, levelHeight, -1, -1);

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

void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY)
{
    DisplayTopBoarder(width);

    for (int y = 0; y < height; y++)
    {
        DisplayLeftBoarder();

        for (int x = 0; x < width; x++)
        {
            if (cursorX == x && cursorY == y)
            {
                cout << kCursor;
            }
            else
            {
            int index = GetIndexFromXY(x, y, width);
            cout << pLevel[index];

            }

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

bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height)
{
    int newCursorX = cursorX;
    int newCursorY = cursorY;

    int intInput = _getch();

    if (intInput == kArrowInput)
    {
        int arrowInput = _getch();

        switch (arrowInput)
        {
        case kLeftArrow:
        newCursorX--;
        break;


        case kRightArrow:
        newCursorX++;
        break;

        case kUpArrow:
        newCursorY--;
        break;

        case kDownArrow:
        newCursorY++;
        break;

        default: break;
        }

        if (newCursorX < 0)
            newCursorX = 0;
        
        else if(newCursorX == width)
            newCursorX = width - 1;

        if (newCursorY < 0)
            newCursorY = 0;

        else if (newCursorY == height)
            newCursorY = height - 1;

        cursorX = newCursorX;
        cursorY = newCursorY;
    }
    else
    {
        if (intInput == kEscape)
        {
            return true;
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}