

class Item
{
public:
	int x;
	int y;
	ALLEGRO_BITMAP* bmp;

	int sx;
	int sy;
	Item();
	void Draw();
	void Move();
};