#include "music.h"

void initMusique()
{
	musiquejeu = sfMusic_createFromFile("..//assets/sounds/ingame.ogg");
	musiquemenu = sfMusic_createFromFile("..//assets/sounds/menu.ogg");
	bounce = sfSound_create();

	sfSoundBuffer* bounceBuf = sfSoundBuffer_createFromFile("..//assets/sounds/bounce.ogg");
	sfSound_setBuffer(bounce, bounceBuf);


	sfMusic_setLoop(musiquejeu, sfTrue);
	sfMusic_setLoop(musiquemenu, sfTrue);

	sfMusic_setVolume(musiquejeu, 20);
	sfMusic_setVolume(musiquemenu, 50);

	sfSound_setVolume(bounce, 50);
}