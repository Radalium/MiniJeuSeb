#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "SFML/Graphics.h"

typedef enum states {

	MAINMENU,
	INGAME,
	PAUSE,
	QUIT
}states;

states actualState = MAINMENU;

int main() {

	sfVideoMode mode = { 600, 900, 32 };
	sfRenderWindow* window;
	window = sfRenderWindow_create(mode, "Window", sfDefaultStyle, NULL);

	sfEvent event;

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
		
		if (actualState == MAINMENU) {

		}
		else if (actualState == INGAME) {

		}
		else if (actualState == PAUSE) {

		}
		else if (actualState == QUIT) {

		}

		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_display(window);
	}
}