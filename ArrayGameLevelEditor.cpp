
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <fstream>


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
constexpr int kBackspace = 8;



void GetLevelDimensions(int& width, int& height);
void DisplayLevel(char* pLevel, int width, int height, int cursorX, int cursorY);
int GetIndexFromXY(int x, int y, int width);

void DisplayTopBoarder(int width);
void DisplayBottomBoarder(int width);
void DisplayLeftBoarder();
void DisplayRightBoarder();
bool EditLevel(char* pLevel, int& cursorX, int& cursorY, int width, int height);
void SaveLevel(char* pLevel, int width, int height);
void DisplayLegend();
void RunEditor(char* pLevel, int width, int height);



int main()
{
    char* pLevel = nullptr;
    int levelWidth;
    int levelHeight;
    bool done = false;

    while (!done)
    {
        system("cls");
        cout << "Please select one of the following options: " << endl;
        cout << "1. Load level" << endl;
        cout << "2. New Level" << endl;
        cout << "3. Quit" << endl;

        int input;
        cin >> input;

        if (input == 1)
        {
            //load existing level
            cout << "Enter level name: " << endl;
            string levelName;
            cin >> levelName;

            levelName.insert(0, "../");

            ifstream levelFile;
            levelFile.open(levelName);

            if (!levelFile)
            {
                cout << "Opening file failed!" << endl;
            }
            else
            {
                constexpr int tempSize = 25;
                char temp[tempSize];

                levelFile.getline(temp, tempSize, '\n');
                levelWidth = atoi(temp);

                levelFile.getline(temp, tempSize, '\n');
                levelHeight = atoi(temp);

                pLevel = new char[levelWidth * levelHeight];
                levelFile.read(pLevel, levelWidth * levelHeight);
                levelFile.close();

                RunEditor(pLevel, levelWidth, levelHeight);

                delete[] pLevel;
                pLevel = nullptr;
            }

        }

        else if (input == 2)
        {
            //new level
            GetLevelDimensions(levelWidth, levelHeight);

            pLevel = new char[levelWidth * levelHeight];

            for (int i = 0; i < levelWidth * levelHeight; i++)
            {
                pLevel[i] = ' ';
            }

            RunEditor(pLevel, levelWidth, levelHeight);

            delete[] pLevel;
            pLevel = nullptr;
        }

        else
        {
            done = true;
        }
    }
}

   
void RunEditor(char* pLevel, int width, int height)
    {
        int cursorX = 0;
        int cursorY = 0;
        bool doneEditing = false;

        while (!doneEditing) 
        {

            system("cls");
            DisplayLevel(pLevel, width, height, cursorX, cursorY);
            DisplayLegend();
            doneEditing = EditLevel(pLevel, cursorX, cursorY, width, height);
        }

        system("cls");
        DisplayLevel(pLevel, width, height, -1, -1);
        DisplayLegend();

        SaveLevel(pLevel, width, height);

     

    }

void DisplayLegend()
{
    cout << "Arrows to move cursor" << endl;
    cout << "ESC to finish editing" << endl;
    cout << "+ | - for walls" << endl;
    cout << "@ for player start" << endl;
    cout << "r g b for key" << endl;
    cout << "R G B for door" << endl;
    cout << "$ for money" << endl;
    cout << "v for vertical moving enemy" << endl;
    cout << "h for horizontal moving enemy" << endl;
    cout << "e for non-moving enemy" << endl;
    cout << "X for end" << endl;
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
        else if(intInput == kBackspace)
        {
            //ignore
        }
        else
        {
            int index = GetIndexFromXY(newCursorX, newCursorY, width);
            pLevel[index] = (char)intInput;
        }
    }
    return false;
}


void SaveLevel(char* pLevel, int width, int height)
{
    cout << "Pick a name for your level file (eg Level1.txt): ";
    string levelName;
    cin >> levelName;

    levelName.insert(0, "../");

    ofstream levelFile;
    levelFile.open(levelName);
    if (!levelFile)
    {
        cout << "Opening file failed!" << endl;
    }
    else
    {
        levelFile << width << endl;
        levelFile << height << endl;
        levelFile.write(pLevel, width * height);
        if(!levelFile)
        {
            cout << "Write failed!" << endl;
        }
        levelFile.close();
    }
}