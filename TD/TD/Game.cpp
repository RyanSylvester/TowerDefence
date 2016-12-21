#include "Main.h"



Game::Game()
{
	bg = al_load_bitmap("background.bmp");
	numE = score = lives = 0;
	quit = false;
}



void Game::Run()
{
	numE = 50;
	lives = 5;
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_MOUSE_STATE mouse_state;
	ALLEGRO_FONT *font;
	font = al_load_ttf_font("Ubuntu.ttf", 20, 0);

	Item background;
	background.bmp = al_load_bitmap("background.bmp");

	Item cross;
	cross.bmp = al_load_bitmap("Crosshairs.bmp");
	al_convert_mask_to_alpha(cross.bmp, al_map_rgb(255, 255, 255));
	cross.size = 20;
	
	Item targets[100];
	for (int i = 0; i < numE; i++)
	{
		targets[i].bmp = al_load_bitmap("Enemy.bmp");
		targets[i].x = (i * -100);
		targets[i].y = rand() % 20 + 130;
		targets[i].visible = true;
		targets[i].phase = 1;
		targets[i].speed = 4;
		targets[i].size = 50;
	}
									  
	while (quit == false)
	{
		al_get_keyboard_state(&key_state);

		if ((al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)) || (lives <= 0))
		{
			quit = true;
		}

		al_get_mouse_state(&mouse_state);
		cross.x = mouse_state.x - cross.size;
		cross.y = mouse_state.y - cross.size;

		if (mouse_state.buttons & 1) 
		{
			for (int i = 0; i < numE; i++)
			{
				if ((mouse_state.x >= targets[i].x && mouse_state.x <= targets[i].x + targets[i].size && mouse_state.y >= targets[i].y && mouse_state.y <= targets[i].y + targets[i].size) && (targets[i].visible == true))
				{
					targets[i].x = -1000;
					targets[i].y = -1000;
					targets[i].visible = false;
					score++;
				}
			}
		}

		for (int i = 0; i < numE; i++) // Enemies follow path
		{
			if (targets[i].visible == true)
			{
				if ((targets[i].x >= 820 - (targets[i].size / 2)) && (targets[i].phase == 1))
					targets[i].phase = 2;
				if ((targets[i].y >= 350) && (targets[i].phase == 2))
					targets[i].phase = 3;
				if ((targets[i].x <= 190) && (targets[i].phase == 3))
					targets[i].phase = 4;
				if ((targets[i].y >= 600) && (targets[i].phase == 4))
					targets[i].phase = 5;
				if ((targets[i].x >= 1000) && (targets[i].phase == 5))
				{
					targets[i].phase = 6;
					lives--;
				}

				targets[i].sx = 0;
				targets[i].sy = 0;

				if (targets[i].phase == 1)
					targets[i].sx = targets[i].speed;
				else if (targets[i].phase == 2)
					targets[i].sy = targets[i].speed;
				else if (targets[i].phase == 3)
					targets[i].sx = targets[i].speed * -1;
				else if (targets[i].phase == 4)
					targets[i].sy = targets[i].speed;
				else if (targets[i].phase == 5)
					targets[i].sx = targets[i].speed;

				targets[i].Move();
			}
		}

		
		// Drawing
		render.Draw(background.bmp, background.x, background.y);
		for (int i = 0; i < numE; i++)
			render.Draw(targets[i].bmp, targets[i].x, targets[i].y);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 75, 0, 0, "%d", score);
		render.Draw(cross.bmp, cross.x, cross.y);
		

				
		al_flip_display();
		al_rest(0.01); 
	}
}

void Game::End(ALLEGRO_DISPLAY* d)
{
	al_destroy_display(d);
}