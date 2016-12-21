#pragma once
class Game
{
public:
	Game();
	Render render;
	ALLEGRO_BITMAP* bg;
	bool quit, trigger, DisplayReload;
	int numE, ECount, score, lives, ammo, wave;
	void Run();
	void End(ALLEGRO_DISPLAY* d);
	
};

