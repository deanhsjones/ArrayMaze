#include "HighScoreState.h"

#include <iostream>
#include <conio.h>
#include "Utility.h"

#include "StateMachineExampleGame.h"

using namespace std;

HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_HighScores = Utility::WriteHighScore(0); //call the Write function passing in 0 so that the lowest score (0) is erased- remember to set this as public in Utility.h!
	
}

bool HighScoreState::Update(bool processInput)
{

	if (processInput)
	{
		int input = _getch(); //press any key to exit the scoreboard
		
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		
	}
	return false;
}

void HighScoreState::Draw()
{
	system("cls");
	cout << endl << endl << endl;
	cout << "      ---- HIGH SCORES ----      " << endl << endl;
	
	for (auto i  = m_HighScores.rbegin(); i != m_HighScores.rend(); i++) //reverse begin = back of the set; rend = reverse end
	{
		cout << "          " << *i << endl;  //display the score currently entered at i by deferencing the iterator to show the value of the element
		cout << endl << endl;

	}
		cout << endl << "    Press any key to go back to Main Menu" << endl << endl;
}