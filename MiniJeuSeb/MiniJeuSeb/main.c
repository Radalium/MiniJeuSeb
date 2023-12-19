#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SFML/Graphics.h"
#include "menu.h"
#include "ingame.h"
#include "tools.h"

int main() {

	sfVideoMode mode = { 600, 900, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Foxo Invader - Made By Radalium & Renard100suel", sfDefaultStyle, NULL);

	sfEvent event;
	initMenu();
	initTools();
	initGame();

	sfShader* shader = NULL;
	sfRenderStates renderState;

	sfText* score;
	score = sfText_create();
	sfFont* font;
	font = sfFont_createFromFile("../assets/text/cakeroll.ttf");
	sfText_setFont(score, font);
	sfText_setPosition(score, (sfVector2f) { 100.f, 500.f });
	sfText_setColor(score, sfWhite);
	sfText_setCharacterSize(score, 24);  

	int score1 = 0;
	char scoreStr[20];

	

	if (!sfShader_isAvailable())
	{
		printf("Shader impossible...\n");
		return EXIT_FAILURE;
	}
	else
	{
		shader = sfShader_createFromFile(/*"hello vert"*/NULL, NULL, "shader.frag");
		if (shader == NULL) 
			return EXIT_FAILURE;
		renderState.shader = shader;
		renderState.blendMode = sfBlendAlpha;
		renderState.transform = sfTransform_Identity;
		renderState.texture = NULL;
	}
    actualState = MAINMENU;

	//boucle de jeu
	while (sfRenderWindow_isOpen(window))
	{
		//timer
		restartClock();
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed){sfRenderWindow_close(window);}
		
		} 
		sfRenderWindow_clear(window, sfBlack);

		switch (actualState)
		{
		case MAINMENU:
			
			updateMenu();
			displayMenu(window);
			break;

		case INGAME:
 
			updateGame(); 
			displayGame(window, player, boule); 
			score1++;
			displayMap(window, enemie, boule,score1);  

			sprintf(scoreStr, "Score: %d", score1); 
			sfText_setString(score, scoreStr);
			sfRenderWindow_drawText(window, score, NULL); 
			break;

		case PAUSE:
			break;
		}
		sfVector2f vec = { 10.f, 10.f };
		
		
		sfRenderWindow_display(window); 
	}
}