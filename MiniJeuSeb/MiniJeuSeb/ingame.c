#include "ingame.h"
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <math.h>

#define DEFAULT_POS_X 300.f
#define DEFAULT_POS_Y 500.f

 

typedef struct Perso Perso;
struct Perso
{
	sfVector2f pos;
	sfVector2f taille;
}; 
struct Perso joueur = { 200.f,800.f,70.f,20.f };
float velocity = 500.0f;
float angle = 0.f;

sfVector2f possBoule = { 300.f,500.f };
sfVector2f circleVel = { 0.0f, 1.f };
sfVector2f futurepos = { 0.f,0.f };


float timer = 0.f;
sfShader* shader; 
sfRenderStates renderState;

void initGame()
{
	shader = sfShader_createFromFile(NULL, NULL, "shader.frag");

	if (!shader) {
		printf("Erreur lors de la cr�ation du shader\n");
	}
	

	boule = sfCircleShape_create();
	player = sfRectangleShape_create();  
	lalignemagique= sfRectangleShape_create();

	sfRectangleShape_setSize(lalignemagique, (sfVector2f) { 600.f, 5.f });
	sfRectangleShape_setPosition(lalignemagique, (sfVector2f) { 0, 895.f });
	sfRectangleShape_setFillColor(lalignemagique, sfWhite);



	sfCircleShape_setRadius(boule, 20.f);
	sfCircleShape_setPosition(boule, possBoule);
	sfCircleShape_setFillColor(boule, sfWhite);
	sfCircleShape_setOrigin(boule, (sfVector2f) { 20.f, 20.f});
	sfCircleShape_setTexture(boule, NULL, sfTrue);

	sfRectangleShape_setSize(player, (sfVector2f) { 70.f, 20.f });
	sfRectangleShape_setPosition(player,joueur.pos);  
	sfRectangleShape_setFillColor(player, sfWhite); 
	sfRectangleShape_setOrigin(player, (sfVector2f) { 35.f, 10.f });


	sfVector2f tailleEnemie = { 85.f,20.f };
    enemie = sfRectangleShape_create(); 
	sfRectangleShape_setSize(enemie, tailleEnemie);  
}

void updateGame()
{
	futurepos.x = possBoule.x + circleVel.x * GetDeltaTime() * 800.f;
	futurepos.y = possBoule.y + circleVel.y * GetDeltaTime() * 800.f;

	timer += GetDeltaTime();

	sfShader_setFloatUniform(shader, "iTime", timer);

	sfShader_setVec2Uniform(shader, "iResolution", vector2f(600.f, 900.f));

	possBoule.x += circleVel.x * GetDeltaTime() * 800.f;
	possBoule.y += circleVel.y * GetDeltaTime() * 800.f;

	sfCircleShape_setPosition(boule, possBoule);
	

	if (sfKeyboard_isKeyPressed(sfKeyD) && joueur.pos.x < 530)
	{
		joueur.pos.x += velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}
	else if (sfKeyboard_isKeyPressed(sfKeyQ) && joueur.pos.x > 70)
	{
		joueur.pos.x -= velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}


	if (futurepos.x >= 600 - sfCircleShape_getRadius(boule))
	{
		circleVel.x = -circleVel.x;
	}
	else if (futurepos.x <= 0.f + sfCircleShape_getRadius(boule) + 5.f)
	{
		circleVel.x = -circleVel.x;
	}
	
	/*else if (sfCircleShape_getPosition(boule).y >= 900 - 2 * sfCircleShape_getRadius(boule))
	{
		circleVel.y = -circleVel.y * GetDeltaTime();
	}*/
	else if (futurepos.y < 0.f + sfCircleShape_getRadius(boule))
	{
		circleVel.y = -circleVel.y;
	}

	sfFloatRect bouleBox = sfCircleShape_getGlobalBounds(boule);
	sfFloatRect playerBox = sfRectangleShape_getGlobalBounds(player);
	sfFloatRect lalignemagiquerect = sfRectangleShape_getGlobalBounds(lalignemagique);


	if (sfFloatRect_intersects(&bouleBox, &playerBox, NULL))
	{
		
		float oujaitaper = 0.f;

		oujaitaper = (sfCircleShape_getPosition(boule).x  - sfRectangleShape_getPosition(player).x);

		oujaitaper /= 55.f;

		oujaitaper = (oujaitaper + 1.f)/ 2.f; 
		
		angle = lerp(15, 165, oujaitaper);

		circleVel = vector2f(- cos(angle * 3.14 / 180), - sin(angle * 3.14 / 180));

	}

	

	if (sfFloatRect_intersects(&bouleBox, &lalignemagiquerect, NULL))
	{
		possBoule.x = DEFAULT_POS_X;
		possBoule.y = DEFAULT_POS_Y;
		sfCircleShape_setPosition(boule, possBoule);
		
			circleVel.x = 0.f;
			circleVel.y = 1.f;
		

	}

	


}

void displayGame(sfRenderWindow* _window, sfRectangleShape* _player, sfCircleShape* _boule)
{

	

	renderState.shader = shader;
	renderState.blendMode = sfBlendAlpha;
	renderState.transform = sfTransform_Identity;
	renderState.texture = NULL;

	sfRenderWindow_drawRectangleShape(_window, _player, NULL);
	sfRenderWindow_drawCircleShape(_window, _boule, &renderState);
	
	sfRenderWindow_drawRectangleShape(_window, lalignemagique, NULL);
}


char map[7][5] = {
		{1,1,1,1,1},
		{1,1,4,1,1},
		{1,4,1,4,1},
		{4,1,1,1,4},
		{3,3,3,3,3},
		{0,2,0,2,0},
		{0,0,0,0,0}
	};


void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie, sfCircleShape* _boule, int* _score1)
{
	char* pointeur = map;
	sfFloatRect enemierect; 

	  for (int y = 0; y < 7; y++)
	  {
	  	for (int x = 0; x < 5; x++)
	  	{
	  		sfSprite_setPosition(_enemie, (sfVector2f) { 110 * x + 40, 80 * y + 20 }); 
	  		
	  		sfFloatRect bouleBox = sfCircleShape_getGlobalBounds(_boule);
	  		enemierect = sfRectangleShape_getGlobalBounds(_enemie);
	  
	  		if (map[y][x] != 0 && sfFloatRect_intersects(&bouleBox, &enemierect, NULL)) 
	  		{
				circleVel.y = -circleVel.y;
				_score1 += 1;                      
	  			map[y][x] = 0;
	  		}
	  		
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

