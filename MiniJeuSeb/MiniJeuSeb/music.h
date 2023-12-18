#pragma once
#include "SFML/Audio.h"
#include "SFML/Graphics.h"

void initMusique();

void updateMusique();

void displayMusique(sfRenderWindow* _window);


sfMusic* musiquemenu;
sfMusic* musiquejeu;

sfSound* bounce;
sfSound* bounce2;
