#pragma once
#include "SFML/Graphics.h"

sfRectangleShape* player;

sfCircleShape* boule;

sfRectangleShape* enemie;

void initGame();

void updateGame(); 


void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule);

void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie);

