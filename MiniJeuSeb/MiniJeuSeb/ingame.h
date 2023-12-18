#pragma once
#include "SFML/Graphics.h"

sfRectangleShape* player;

void initGame();

void updateGame(); 

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player);
