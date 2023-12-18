#pragma once
#include "SFML/Graphics.h"

sfRectangleShape* player;
sfCircleShape* boule;

void initGame();

void updateGame(); 

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule);
