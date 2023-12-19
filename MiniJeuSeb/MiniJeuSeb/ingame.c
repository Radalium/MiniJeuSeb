#include "ingame.h"
#include <stdlib.h>
#include <stdio.h>
#include "tools.h"
#include <math.h>
#include "music.h"

#define DEFAULT_POS_X 300.f
#define DEFAULT_POS_Y 500.f

typedef struct Perso Perso;
struct Perso {
	sfVector2f pos;
	sfVector2f taille;
}; 
struct Perso joueur = { 200.f,800.f,70.f,20.f };

typedef struct Deplacement Deplacement;
struct Deplacement {
	sfVector2f possBoule;
	sfVector2f circleVel;
	sfVector2f futurepos;
	float velocity;
    float angle;
	float timer ;
};
struct Deplacement deplace = { 300.f,500.f,0.0f, 1.f,0.f,0.f,500.f,0.f,0.f};

typedef struct Stats Stats;
struct Stats
{
	int score;
	int niveau; 
	char scoreStr[10];
	char niveauStr[10]; 
};
struct Stats stats = { 0,1 }; 

sfShader* shader; 
sfRenderStates renderState;

void initGame()
{
	shader = sfShader_createFromFile(NULL, NULL, "shader.frag");

	if (!shader) {
		printf("Erreur lors de la création du shader\n");
	}

	boule = sfCircleShape_create();
	player = sfRectangleShape_create();  
	lalignemagique= sfRectangleShape_create();

	sfRectangleShape_setSize(lalignemagique, (sfVector2f) { 600.f, 5.f });
	sfRectangleShape_setPosition(lalignemagique, (sfVector2f) { 0, 895.f });
	sfRectangleShape_setFillColor(lalignemagique, sfWhite);

	sfCircleShape_setRadius(boule, 20.f);
	sfCircleShape_setPosition(boule, deplace.possBoule);
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

	scoreText = sfText_create(); 
	sfFont* font = sfFont_createFromFile("../assets/text/Pixelary.ttf");
	sfText_setFont(scoreText, font);
	sfText_setPosition(scoreText, (sfVector2f) { 20.f, 800.f });
	sfText_setColor(scoreText, sfWhite);
	sfText_setCharacterSize(scoreText, 80);

	niveauText = sfText_create();
	sfText_setFont(niveauText, font); 
	sfText_setPosition(niveauText, (sfVector2f) { 325.f, 800.f }); 
	sfText_setColor(niveauText, sfWhite); 
	sfText_setCharacterSize(niveauText, 80); 
}

sfBool isPlaying = sfFalse;

void updateGame()
{
	deplace.futurepos.x = deplace.possBoule.x + deplace.circleVel.x * GetDeltaTime() * 800.f;
	deplace.futurepos.y = deplace.possBoule.y + deplace.circleVel.y * GetDeltaTime() * 800.f;
	deplace.timer += GetDeltaTime();

	if (isPlaying == sfFalse)
	{
		sfMusic_play(musiquejeu);
		isPlaying = sfTrue;
	}
	sfShader_setFloatUniform(shader, "iTime", deplace.timer);
	sfShader_setVec2Uniform(shader, "iResolution", vector2f(600.f, 900.f));

	deplace.possBoule.x += deplace.circleVel.x * GetDeltaTime() * 800.f;
	deplace.possBoule.y += deplace.circleVel.y * GetDeltaTime() * 800.f;
	sfCircleShape_setPosition(boule, deplace.possBoule);
	
	if (sfKeyboard_isKeyPressed(sfKeyD) && joueur.pos.x < 530)
	{
		joueur.pos.x += deplace.velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}
	else if (sfKeyboard_isKeyPressed(sfKeyQ) && joueur.pos.x > 70)
	{
		joueur.pos.x -= deplace.velocity * GetDeltaTime();
		sfRectangleShape_setPosition(player, joueur.pos);
	}

	if (deplace.futurepos.x >= 600 - sfCircleShape_getRadius(boule)){deplace.circleVel.x = -deplace.circleVel.x;}
	else if (deplace.futurepos.x <= 0.f + sfCircleShape_getRadius(boule) + 5.f){deplace.circleVel.x = -deplace.circleVel.x;}
	else if (deplace.futurepos.y < 0.f + sfCircleShape_getRadius(boule)){deplace.circleVel.y = -deplace.circleVel.y;}

	sfFloatRect bouleBox = sfCircleShape_getGlobalBounds(boule);
	sfFloatRect playerBox = sfRectangleShape_getGlobalBounds(player);
	sfFloatRect lalignemagiquerect = sfRectangleShape_getGlobalBounds(lalignemagique);

	if (sfFloatRect_intersects(&bouleBox, &playerBox, NULL))
	{
		float oujaitaper = 0.f;
		oujaitaper = (sfCircleShape_getPosition(boule).x  - sfRectangleShape_getPosition(player).x);
		oujaitaper /= 55.f;
		oujaitaper = (oujaitaper + 1.f)/ 2.f; 

		deplace.angle = lerp(15, 165, oujaitaper);
		deplace.circleVel = vector2f(- cos(deplace.angle * 3.14 / 180), - sin(deplace.angle * 3.14 / 180));
	}

	if (sfFloatRect_intersects(&bouleBox, &lalignemagiquerect, NULL))
	{
		deplace.possBoule.x = DEFAULT_POS_X;
		deplace.possBoule.y = DEFAULT_POS_Y;
		sfCircleShape_setPosition(boule, deplace.possBoule);

		deplace.circleVel.x = 0.f;
		deplace.circleVel.y = 1.f;
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

char map2[7][5] = {
		{1,2,3,2,1},
		{1,2,4,2,1},
		{1,2,3,2,1},
		{4,2,1,2,4},
		{3,2,3,2,3},
		{0,2,0,2,0},
		{0,0,0,0,0}
};

void displayMap(sfRenderWindow* _window, sfRectangleShape* _enemie, sfCircleShape* _boule)
{
	char* pointeur = map;
	sfFloatRect enemierect; 
	
	switch (stats.niveau)
	{
	case 1:
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				sfSprite_setPosition(_enemie, (sfVector2f) { 110 * x + 40, 80 * y + 20 });

				sfFloatRect bouleBox = sfCircleShape_getGlobalBounds(_boule);
				enemierect = sfRectangleShape_getGlobalBounds(_enemie);

				if (map[y][x] != 0 && sfFloatRect_intersects(&bouleBox, &enemierect, NULL))
				{
					deplace.circleVel.y = -deplace.circleVel.y;
					stats.score++;
					sfSound_play(bounce);
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
		if (stats.score == 25) stats.niveau = 2;
		break;

	case 2:
		for (int y = 0; y < 7; y++)
		{
			for (int x = 0; x < 5; x++)
			{
				sfSprite_setPosition(_enemie, (sfVector2f) { 110 * x + 40, 80 * y + 20 });

				sfFloatRect bouleBox = sfCircleShape_getGlobalBounds(_boule);
				enemierect = sfRectangleShape_getGlobalBounds(_enemie);

				if (map2[y][x] != 0 && sfFloatRect_intersects(&bouleBox, &enemierect, NULL))
				{
					deplace.circleVel.y = -deplace.circleVel.y;
					stats.score++;
					sfSound_play(bounce);
					map2[y][x] = 0;
				}

				if (map2[y][x] == 1)
				{
					sfRectangleShape_setFillColor(_enemie, sfWhite);
					sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
				}
				else if (map2[y][x] == 2)
				{
					sfRectangleShape_setFillColor(_enemie, sfRed);
					sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
				}
				else if (map2[y][x] == 3)
				{
					sfRectangleShape_setFillColor(_enemie, sfBlue);
					sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
				}
				else if (map2[y][x] == 4)
				{
					sfRectangleShape_setFillColor(_enemie, sfYellow);
					sfRenderWindow_drawRectangleShape(_window, _enemie, NULL);
				}
			}
		}
		break;
	}
	  sprintf(stats.scoreStr, "Score : %d", stats.score);
	  sprintf(stats.niveauStr, "Niveau : %d", stats.niveau);
	  sfText_setString(scoreText, stats.scoreStr);
	  sfText_setString(niveauText, stats.niveauStr);
	  sfRenderWindow_drawText(_window, scoreText, NULL);
	  sfRenderWindow_drawText(_window, niveauText, NULL); 
}

