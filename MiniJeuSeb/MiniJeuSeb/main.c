#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SFML/Graphics.h"
#include "menu.h"
#include "ingame.h"
#include "tools.h"
#include "music.h"

int main() 
{
    sfEvent event;
	sfVideoMode mode = { 600, 900, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Foxo Invader - Made By Radalium & Renard100suel", sfDefaultStyle, NULL);
	sfRenderTexture* renderTexture = sfRenderTexture_create(600, 900, sfFalse); 

	initMusique();
	initMenu();
	initTools();
	initGame();
	
	float timermusique = 0.f;
	
	sfShader* shader = NULL; 
	sfRenderStates renderState; 
	if (!sfShader_isAvailable())
	{
		printf("Shader impossible...\n");
		return EXIT_FAILURE;
	}
	else{
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
			
			sfTexture* texture1 = sfRenderTexture_getTexture(renderTexture); 
			sfSprite* sprite1 = sfSprite_create(); 
			sfSprite_setTexture(sprite1, texture1, sfFalse); 
			sfRenderWindow_drawSprite(window, sprite1, NULL); 
			sfMusic_stop(musiquemenu); 
			updateGame();  
			displayGame(window, player, boule); 
			displayMap(window, enemie, boule, renderTexture); 
			
			
			break;

		case PAUSE:
			break;
		
		case QUIT:
			sfRenderWindow_close(window);
		break;
		}
		sfRenderWindow_display(window); 
	}
	
}