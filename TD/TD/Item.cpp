#include "Main.h"



Item::Item()
{
	x = y = sx = sy = 0;
}




void Item::Draw()
{
	al_draw_bitmap(bmp, x, y, 0);
}

void Item::Move()
{
	x += sx;
	y += sy;
}