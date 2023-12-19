#pragma once
#include "SFML/Graphics.h"

sfRectangleShape* player;

sfCircleShape* boule;

sfRectangleShape* enemie;

sfTexture* texture;

void initGame();

void updateGame(); 


void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule, sfRenderStates* _renderState); 

void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie, sfCircleShape* _boule); 


