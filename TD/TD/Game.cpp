#include "Main.h"



Game::Game()
{
}



void Game::Run()
{
	//int numE;

	ALLEGRO_MOUSE_STATE mouse_state;


	Item cross;
	cross.bmp = al_load_bitmap("Crosshairs.bmp");
	al_convert_mask_to_alpha(cross.bmp, al_map_rgb(255, 255, 255));
	cross.x = 100;
	cross.y = 100;
	

	Item targets[10];
	for (int i = 0; i < 10; i++)
	{
		targets[i].bmp = al_load_bitmap("Enemy.bmp");
		targets[i].x = rand() % 760;
		targets[i].y = rand() % 560;
	}



	ALLEGRO_KEYBOARD_STATE key_state; //ALLEGRO_KEYBOARD_STATE is a "user define type" in Allegro


									  
	bool quit = false;
	while (quit == false)
	{

		al_get_keyboard_state(&key_state);

		//end program
		if (al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)) //al_key_down checks the status of a key in the key_state structure
		{
			quit = true;
		}

		al_get_mouse_state(&mouse_state);
		cross.x = mouse_state.x-20;
		cross.y = mouse_state.y-20;



		al_clear_to_color(al_map_rgb(255, 255, 255));
		
		for (int i = 0; i < 10; i++)
		{
			render.Draw(targets[i].bmp, targets[i].x, targets[i].y);
		}
		render.Draw(cross.bmp, cross.x, cross.y);





		al_flip_display();
		al_rest(0.01); 
	}



}

void Game::End(ALLEGRO_DISPLAY* d)
{
	al_destroy_display(d);
}