#include "Main.h"


void Render::Draw(ALLEGRO_BITMAP* bmp, int x, int y)
{
	al_draw_bitmap(bmp, x, y, 0);
}