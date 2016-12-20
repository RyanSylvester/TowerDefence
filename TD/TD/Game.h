#pragma once
class Game
{
public:
	Game();
	Render render;
	ALLEGRO_BITMAP* bg;
	bool quit;
	int numE;
	int score;
	int lives;
	void Run();
	void End(ALLEGRO_DISPLAY* d);
	
};

