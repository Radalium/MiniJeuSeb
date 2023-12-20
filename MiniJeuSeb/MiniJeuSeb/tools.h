#pragma once
#include "SFML/Graphics.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void initTools();
void restartClock();
float GetDeltaTime();
float lerp(float _a, float _b, float _t);

sfVector2f vector2f(float _a, float _b);

typedef enum states {

	MAINMENU,
	INGAME,
	PAUSE,
	QUIT,
	GAGNER
}states;

states actualState;