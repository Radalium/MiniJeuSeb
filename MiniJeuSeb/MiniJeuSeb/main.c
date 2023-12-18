#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SFML/Graphics.h"
#include "menu.h"
#include "tools.h"




 

int main() {

	sfVideoMode mode = { 600, 900, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, NULL);

	sfEvent event;
	initMenu();
	actualState = MAINMENU;



	//boucle de jeu
	while (sfRenderWindow_isOpen(window))
	{
		//timer
		/*restartClock();*/


		//update
		while (sfRenderWindow_pollEvent(window, &event))
		{
			if (event.type == sfEvtClosed)
			{
				sfRenderWindow_close(window);
			}
		}
		sfRenderWindow_clear(window, sfBlack);
		
		if (actualState == MAINMENU) {
			updateMenu();
			displayMenu(window);
		}
		else if (actualState == INGAME)  {

		}
		else if (actualState == PAUSE) {

		}
		else if (actualState == QUIT) {

		}

		



	
		sfRenderWindow_display(window);
	}
}