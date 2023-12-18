#include "ingame.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Perso Perso;
struct Perso
{
	sfVector2f pos;
	sfVector2f taille;
}; 
struct Perso joueur = { 200.f,800.f,70.f,20.f };
float velocity = 0.1f;

void initGame()
{
	player = sfRectangleShape_create();  
	sfRectangleShape_setPosition(player,joueur.pos); 
	sfRectangleShape_setFillColor(player, sfWhite); 
	sfRectangleShape_setSize(player,joueur.taille);  
}

void updateGame()
{
	if (sfKeyboard_isKeyPressed(sfKeyD))
	{
		joueur.pos.x += velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}
	if (sfKeyboard_isKeyPressed(sfKeyQ))
	{
		joueur.pos.x -= velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}
	printf("X: %f  Y: %f\n", joueur.pos.x, joueur.pos.y);  
}

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player)
{
	sfRenderWindow_drawRectangleShape(_window, _player, NULL);
}
