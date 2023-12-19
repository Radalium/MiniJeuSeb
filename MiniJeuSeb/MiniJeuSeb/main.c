#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SFML/Graphics.h"
#include "menu.h"
#include "ingame.h"
#include "tools.h"
#include "music.h"

int main() {

	sfVideoMode mode = { 600, 900, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Foxo Invader - Made By Radalium & Renard100suel", sfDefaultStyle, NULL);

	sfEvent event;
	initMenu();
	initMusique();
	initTools();
	initGame();
	float tiemrmusique = 0.f;
	

	sfShader* shader = NULL;
	sfRenderStates renderState;

	sfText* scoreText;
	scoreText = sfText_create();
	sfFont* font;
	font = sfFont_createFromFile("../assets/text/cakeroll.ttf");
	sfText_setFont(scoreText, font);
	sfText_setPosition(scoreText, (sfVector2f) { 100.f, 500.f });
	sfText_setColor(scoreText, sfWhite);
	sfText_setCharacterSize(scoreText, 24);

	int score;
	score = 0;
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
			displayMap(window, enemie, boule,score);  
			printf("%d\n", score);
			sprintf(scoreStr, "Score: %d", score); 
			sfText_setString(scoreText, scoreStr);
			sfRenderWindow_drawText(window, scoreText, NULL); 
			break;

		case PAUSE:
			break;
		}
		sfVector2f vec = { 10.f, 10.f };
		
		
		sfRenderWindow_display(window); 
	}
}