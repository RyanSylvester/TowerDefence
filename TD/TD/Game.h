#pragma once
class Game
{
public:
	Game();
	Render render;
	void Run();
	void End(ALLEGRO_DISPLAY* d);
	
};

