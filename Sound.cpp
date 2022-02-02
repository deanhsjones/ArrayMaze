#include "Sound.h"
#include <windows.h>
#include <conio.h>


Sound::Sound()
{

}
Sound::~Sound()
{

}


void Sound::PlayDoorClosedSound()
{
	Beep(1397, 200);
}
void Sound::PlayDoorOpenedSound()
{
	Beep(1397, 200);
}
void Sound::PlayKeyPickupSound() 
{
	Beep(1568, 200);
}
void Sound::PlayWinSound()
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
