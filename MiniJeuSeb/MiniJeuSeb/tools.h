#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void initTools();
void restartClock();
float GetDeltaTime();


typedef enum states {

	MAINMENU,
	INGAME,
	PAUSE,
	QUIT
}states;

states actualState;