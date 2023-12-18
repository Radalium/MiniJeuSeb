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
float angle = 0.f;

sfVector2f possBoule = { 300.f,500.f };
sfVector2f circleVel = { 0.1f, 0.1f };

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

	sfVector2f tailleEnemie = { 85.f,20.f };
    enemie = sfRectangleShape_create(); 
	sfRectangleShape_setSize(enemie, tailleEnemie);  
}

void updateGame()
{
	if (sfKeyboard_isKeyPressed(sfKeyD) && joueur.pos.x < 520)
	{
		joueur.pos.x += velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}
	else if (sfKeyboard_isKeyPressed(sfKeyQ) && joueur.pos.x > 10)
	{
		joueur.pos.x -= velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}

	//possBoule.x += circleVel.x;
	possBoule.y += circleVel.y;

		if (possBoule.y >= 900 * sfCircleShape_getRadius(boule))
		{
			circleVel.y = -circleVel.y * GetDeltaTime(); 
		}
		else if (possBoule.y <= 0.f)
		{
			circleVel.y = -circleVel.y * GetDeltaTime();
		}
		sfCircleShape_setPosition(boule, possBoule);

		printf("%f\n", possBoule);
	
}

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule)
{
	sfRenderWindow_drawRectangleShape(_window, _player, NULL);
	sfRenderWindow_drawCircleShape(_window, _boule, NULL);
}

void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie)
{
	char map[7][5] = {
		{1,1,1,1,1},
		{1,1,4,1,1},
		{1,4,1,4,1},
		{4,1,1,1,4},
		{3,3,3,3,3},
		{0,2,0,2,0},
		{0,0,0,0,0}
	};

	for (int y = 0; y < 7; y++)
	{
		for (int x = 0; x < 5; x++)
		{
			sfSprite_setPosition(_enemie, (sfVector2f) { 110 * x + 40, 80 * y + 20 }); 
			if (map[y][x] == 1)
			{
				sfRectangleShape_setFillColor(_enemie, sfWhite);
		        sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
			}
			else if (map[y][x] == 2) 
			{
				sfRectangleShape_setFillColor(_enemie, sfRed);
				sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
			}
			else if (map[y][x] == 3)
			{
				sfRectangleShape_setFillColor(_enemie, sfBlue); 
				sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
			}
			else if (map[y][x] == 4)
			{
				sfRectangleShape_setFillColor(_enemie, sfYellow);
				sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
			}
		}
	}
}
