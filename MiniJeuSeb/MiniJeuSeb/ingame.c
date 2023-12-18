#include "ingame.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_POS_X 300.f
#define DEFAULT_POS_Y 500.f


typedef struct Perso Perso;
struct Perso
{
	sfVector2f pos;
	sfVector2f taille;
}; 
struct Perso joueur = { 200.f,800.f,70.f,20.f };
float velocity = 0.1f;
float velocityboulle = 0.1f;
float angle = 0.f;

sfVector2f possBoule = { 300.f,500.f };

void initGame()
{
	boule = sfCircleShape_create();
	player = sfRectangleShape_create();  
	
	sfCircleShape_setRadius(boule, 20.f);
	sfCircleShape_setPosition(boule, possBoule);
	sfCircleShape_setFillColor(boule, sfWhite);
	sfRectangleShape_setSize(player, (sfVector2f) { 70.f, 20.f });
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


	if (sfKeyboard_isKeyPressed(sfKeySpace))
	{
		if (possBoule.y > 0.f)
		{
			possBoule.y -= velocityboulle * GetDeltaTime();
		}
		else if (possBoule.y < 0.f)
		{
			possBoule.y -= -velocityboulle * GetDeltaTime();
		}
		sfCircleShape_setPosition(boule, possBoule);
	}

	

}

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule)
{
	sfRenderWindow_drawRectangleShape(_window, _player, NULL);
	sfRenderWindow_drawCircleShape(_window, _boule, NULL);
}
