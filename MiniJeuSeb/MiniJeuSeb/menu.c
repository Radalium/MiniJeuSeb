#include "menu.h"


void initMenu()
{

	text = sfText_create();
	sfFont* font = sfFont_createFromFile("arial.ttf");
	sfText_setString(text, "Click To Start");
	sfText_setFont(text, font);
	sfText_setCharacterSize(text, 50);
	sfText_setPosition(text, (sfVector2f) { 100, 100 });
	sfText_setColor(text, sfWhite);
}

void updateMenu()
{
	
}

void displayMenu(sfRenderWindow* _window)
{
	sfRenderWindow_drawText(_window, text, NULL);
}
