#include "ingame.h"

void initGame()
{
	player = sfRectangleShape_create(); 
	sfVector2f pos = { 300,500 };
	sfRectangleShape_setPosition(player, pos);
	sfRectangleShape_setFillColor(player, sfWhite);
}

void updateGame()
{

}


void displayGame(sfRenderWindow* _window, sfRectangleShape* _player)
{
	sfRenderWindow_drawRectangleShape(_window, _player, NULL);
}
