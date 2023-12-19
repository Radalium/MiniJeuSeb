#include "music.h"

void initMusique()
{
	musiquejeu = sfMusic_createFromFile("..//assets/sounds/ingame.ogg");
	musiquemenu = sfMusic_createFromFile("..//assets/sounds/menu.ogg");

	bounce = sfSound_create();
	bounce2 = sfSound_create();

	sfSoundBuffer* bounceBuf = sfSoundBuffer_createFromFile("..//assets/sounds/bounce.wav");
	sfSoundBuffer* bounceBuf2 = sfSoundBuffer_createFromFile("..//assets/sounds/bounce2.wav");
	sfSound_setBuffer(bounce, bounceBuf);
	sfSound_setBuffer(bounce2, bounceBuf2);

	sfMusic_setLoop(musiquejeu, sfTrue);
	sfMusic_setLoop(musiquemenu, sfTrue);

	sfMusic_setVolume(musiquejeu, 50);
	sfMusic_setVolume(musiquemenu, 50);

	sfSound_setVolume(bounce, 50);
	sfSound_setVolume(bounce2, 50);
}

void updateMusique()
{
}

void displayMusique(sfRenderWindow* _window)
{
}
