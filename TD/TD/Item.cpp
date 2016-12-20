#include "Main.h"



Item::Item()
{
	x = y = size = sx = sy = speed = phase = 0;
	visible = true;
}


void Item::Move()
{
	x += sx;
	y += sy;
}