#include "menu.h"
#include "tools.h"
#include "music.h"

float timermusique = 0.f;

void initMenu()
{ 
	sfVector2f scale = { 0.3f, 0.3f };
	text = sfText_create();
	sfFont* font = sfFont_createFromFile("../assets/text/cakeroll.ttf");
	sfText_setString(text, "Click To Start");
	sfText_setFont(text, font);
	sfText_setCharacterSize(text, 50);
	sfText_setPosition(text, (sfVector2f) { 100, 500 });
	sfText_setColor(text, sfWhite);

	logo = sfSprite_create();
	sfTexture* texture = sfTexture_createFromFile("../assets/texture/foxai.png", NULL);
	sfSprite_setScale(logo, scale);
	sfSprite_setTexture(logo, texture, sfTrue);
	sfSprite_setPosition(logo, (sfVector2f) { 135, 100 });
	sfMusic_play(musiquemenu);
}

void updateMenu()
{
	if (actualState = MAINMENU)
	{
		if (timermusique > 0.15f)
		{
			sfSound_play(musiquemenu);
			timermusique = 0.f;
		}
	}
	else
	timermusique += GetDeltaTime();
	
	
	if (sfMouse_isButtonPressed(sfMouseLeft))
	{
		if (timermusique > 0.15f)
		{
			sfSound_play(musiquemenu);
			timermusique = 0.f;
		}
		actualState = INGAME;
	}
}

void displayMenu(sfRenderWindow* _window)
{
	sfRenderWindow_drawText(_window, text, NULL);
	sfRenderWindow_drawSprite(_window, logo, NULL);
}
