#include "MainMenuState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using namespace std;

constexpr int kEscapeKey = 27;

constexpr chat kPlay = '1'
constexpr chat kQuit = '2'

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool MainMenuState::Update(bool processInput)
{
	bool shouldQuit = false;
	if (processInput)
	{
		int input = _getch();
		if (input == kEscapeKey || (char)input = kQuit)
		{
			shouldQuit = true;
		}
		elseif((char)input == kPlay)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SeceneName::Gameplay);
		}
	}
	return shouldQuit;
}

void MainMenuState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "      ---- MAIN MENU ----      " << endl << endl;
	cout << "    " << kPlay << ". Play" << endl;
	cout << "    " << kQuit << ". Quit" << endl;
}