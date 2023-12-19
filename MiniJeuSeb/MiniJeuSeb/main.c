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

	int a = 0;

	actualState = MAINMENU;

	//boucle de jeu
	while (sfRenderWindow_isOpen(window))
	{
		//timer
		restartClock();
		
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}

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
			displayGame(window, player, boule); 
			displayMap(window, enemie, boule); 

			break;

		case PAUSE:

			break;


		default:
			break;
		}

		sfRenderWindow_display(window); 
	}
}