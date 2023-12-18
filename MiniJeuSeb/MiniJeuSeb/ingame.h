#pragma once
#include "SFML/Graphics.h"

sfRectangleShape* player;
sfRectangleShape* enemie;

void initGame();

void updateGame(); 

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player);
void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie);
