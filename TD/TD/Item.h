

class Item
{
public:
	ALLEGRO_BITMAP* bmp;
	int x, y, size, sx, sy, speed, timer, phase;
	bool visible;

	Item();
	void Move();
};