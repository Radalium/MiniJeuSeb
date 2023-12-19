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
		
			//update
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
			displayGame(window, player, boule, &renderState); 
			displayMap(window, enemie, boule); 
			break;

		case PAUSE:
			break;
		}
		sfVector2f vec = { 10.f, 10.f };
		
		sfShader_setTextureUniform(shader, "blur_radius", texture);
		sfShader_setTextureUniform(shader, "texture", texture);
		sfRenderWindow_drawRectangleShape(window, player, &renderState);
		sfRenderWindow_display(window); 
	}
}