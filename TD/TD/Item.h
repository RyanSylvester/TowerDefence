

class Item
{
public:
	int x;
	int y;
	int size;
	ALLEGRO_BITMAP* bmp;

	int sx;
	int sy;
	int speed;

	int timer;

	int phase;
	bool visible;
	Item();
	void Move();
};