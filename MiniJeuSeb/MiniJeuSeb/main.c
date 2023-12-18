#include <stdio.h>
#include <stdlib.h>
#include "SFML/Graphics.h"

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

		sfRenderWindow_clear(window, sfBlack);
		sfRenderWindow_display(window);
	}
}