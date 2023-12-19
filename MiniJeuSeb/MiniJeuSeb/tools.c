#include "tools.h"

sfTime sftime;
sfClock* sfclock;

void initTools()
{
	sfclock = sfClock_create();
	srand(time(NULL));
}
void restartClock(){sftime = sfClock_restart(sfclock);}
float GetDeltaTime(){return sfTime_asSeconds(sftime);}

float lerp(float _a, float _b, float _t){return (1 - _t)* _a + _t * _b;}

sfVector2f vector2f(float _a, float _b)
{
	sfVector2f vector;
	vector.x = _a;
	vector.y = _b;
	return vector;
}