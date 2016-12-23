#include "Main.h"



Game::Game()
{
	bg = al_load_bitmap("background.bmp");
	score =  0;
	numE = ECount = 10;
	wave = 1;
	lives = 5;
	ammo = 5;
	quit =DisplayReload = false;
}



void Game::Run()
{
	ALLEGRO_KEYBOARD_STATE key_state;
	ALLEGRO_MOUSE_STATE mouse_state;

	ALLEGRO_FONT *font;
	ALLEGRO_FONT* title;
	ALLEGRO_FONT* subtitle;

	font = al_load_ttf_font("BalooThambi-Regular.ttf", 20, 0);
	title = al_load_ttf_font("BalooThambi-Regular.ttf", 100, 0);
	subtitle = al_load_ttf_font("BalooThambi-Regular.ttf", 60, 0);


	Item background;
	background.bmp = al_load_bitmap("background.bmp");

	Item cross;
	cross.bmp = al_load_bitmap("Sniper.bmp");
	al_convert_mask_to_alpha(cross.bmp, al_map_rgb(255, 255, 255));
	cross.size = 3000;
	
	Item CrossReload;
	CrossReload.bmp = al_load_bitmap("Empty.bmp");
	al_convert_mask_to_alpha(CrossReload.bmp, al_map_rgb(255, 255, 255));
	CrossReload.size = 30;

	Item targets[100];
	for (int i = 0; i < numE; i++)
	{
		targets[i].bmp = al_load_bitmap("Enemy.bmp");
		targets[i].x = (i * -100) - 100;
		targets[i].y = rand() % 20 + 130;
		targets[i].visible = true;
		targets[i].phase = 1;
		targets[i].speed = rand() % 2 + wave;
		targets[i].size = 50;
	}

	Item reload;
	reload.bmp = al_load_bitmap("Reload.bmp");
	reload.size = 100;
	reload.x = rand() % 900;
	reload.y = rand() % 700;

	Item pew;
	pew.bmp = al_load_bitmap("pew.bmp");
	al_convert_mask_to_alpha(pew.bmp, al_map_rgb(255, 255, 255));
	pew.timer = 0;

										  
	while (quit == false)
	{
		al_get_keyboard_state(&key_state);

		if ((al_key_down(&key_state, ALLEGRO_KEY_ESCAPE)))
		{
			quit = true;
		}

		al_get_mouse_state(&mouse_state);
		cross.x = mouse_state.x - cross.size/2;
		cross.y = mouse_state.y - cross.size/2;

		CrossReload.x = mouse_state.x;
		CrossReload.y = mouse_state.y;

		if (mouse_state.buttons != 1)
		{
			trigger = true;

		}

		if ((trigger == true) && (mouse_state.buttons == 1) )
		{
			if (ammo >= 1)
			{
				pew.timer = 25;
				pew.x = rand() % 700 + 100;
				pew.y = rand() % 500 + 100;
				for (int i = 0; i < numE; i++)
				{
					if ((trigger == true) && (mouse_state.x >= targets[i].x && mouse_state.x <= targets[i].x + targets[i].size && mouse_state.y >= targets[i].y && mouse_state.y <= targets[i].y + targets[i].size) && (targets[i].visible == true))
					{
						targets[i].sx = 0;
						targets[i].sy = 0;
						targets[i].visible = false;
						score++;
						ECount--;
						targets[i].bmp = al_load_bitmap("RIP.bmp");
						al_convert_mask_to_alpha(targets[i].bmp, al_map_rgb(255, 255, 255));

					}
				}
			}

			ammo--;

			if (reload.visible && mouse_state.x >= reload.x && mouse_state.x <= reload.x + reload.size && mouse_state.y >= reload.y && mouse_state.y <= reload.y + reload.size)
			{
				ammo = 5;
			}
			trigger = false;
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
					ECount--;
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


		// WAVES //

		if ((ECount <= 0) && (lives != 0))
		{
			wave++;

			al_clear_to_color(al_map_rgb(0, 0, 0));
			al_draw_textf(title, al_map_rgb(255, 255, 255), 320, 20, 0, "WAVE %d", wave);
			al_flip_display();
			al_rest(3);
			ammo = 5;
			pew.timer = 0;



			if (numE <= 100)
			{
				numE = wave * 10;

				for (int i = 0; i < numE; i++)
				{
					targets[i].bmp = al_load_bitmap("Enemy.bmp");
					targets[i].x = (i * -100) - 100;
					targets[i].y = rand() % 20 + 130;
					targets[i].visible = true;
					targets[i].phase = 1;
					targets[i].size = 50;
					targets[i].speed = rand() % 2 + wave;
				}
			}
			else if (numE >= 101)
			{
				for (int i = 0; i < numE; i++)
				{
					targets[i].bmp = al_load_bitmap("Enemy.bmp");
					targets[i].x = (i * -100) - 100;
					targets[i].y = rand() % 20 + 130;
					targets[i].visible = true;
					targets[i].phase = 1;
					targets[i].size = 50;
					targets[i].speed = rand() % 2 + wave;
				}
			}

			ECount = numE;
		}

		if (ammo <= 0 && DisplayReload == false)
		{
			reload.visible = true;
			DisplayReload = true;
			reload.x = rand() % 900;
			reload.y = rand() % 700;
		}
		else if (ammo >= 1)
		{
			reload.visible = false;
			DisplayReload = false;
		}
		else
			ammo = 0;

		// Drawing //////////////////////////////////////////////////////////
		render.Draw(background.bmp, background.x, background.y);
		al_draw_rectangle(0, 0, 1000, 30, al_map_rgb(0, 0, 0), 35);
		

		for (int i = 0; i < numE; i++)
			if (!targets[i].visible)
				render.Draw(targets[i].bmp, targets[i].x, targets[i].y);

		for (int i = 0; i < numE; i++)
			if (targets[i].visible)
				render.Draw(targets[i].bmp, targets[i].x, targets[i].y);



		if (reload.visible)
			render.Draw(reload.bmp, reload.x, reload.y);

		if (ammo >= 1)
			render.Draw(cross.bmp, cross.x, cross.y);
		else
			render.Draw(CrossReload.bmp, CrossReload.x, CrossReload.y);

		if (pew.timer != 0)
		{
			render.Draw(pew.bmp, pew.x, pew.y);
			pew.timer--;
		}

		
			

		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 0, 0, "Score: %d", score);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, 0, "Wave: %d", wave);

		al_draw_textf(font, al_map_rgb(255, 255, 255), 859, 0, 0, "             Lives: %d", lives);
		al_draw_textf(font, al_map_rgb(255, 255, 255), 840, 20, 0, "Enemies Left: %d", ECount);

		al_draw_textf(font, al_map_rgb(255, 255, 255), mouse_state.x + 10, mouse_state.y + 10, 0, "%d", ammo);


		if (lives == 0)
		{
			for (int i = 0; i < numE; i++)
			{
				targets[i].speed = 0;

				al_clear_to_color(al_map_rgb(0, 0, 0));
				al_draw_textf(title, al_map_rgb(255, 255, 255), 230, 100, 0, "GAME OVER");
				al_draw_textf(subtitle, al_map_rgb(255, 255, 255), 140, 200, 0, "You finished with %d points",score);


				al_draw_textf(font, al_map_rgb(255, 255, 255), 380, 300, 0, "Press 'ENTER' to restart!");
				al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 10, 0, "ESC - Quit");



				// RESTART //
				if ((al_key_down(&key_state, ALLEGRO_KEY_ENTER)))
				{
					lives = 5;
					wave = 1;
					ammo = 5;
					score = 0;
					numE = 10;
					ECount = numE;
					for (int i = 0; i < numE; i++)
					{
						targets[i].bmp = al_load_bitmap("Enemy.bmp");
						targets[i].x = (i * -100) - 100;
						targets[i].y = rand() % 20 + 130;
						targets[i].visible = true;
						targets[i].phase = 1;
						targets[i].size = 50;
						targets[i].speed = rand() % 2 + wave;
					}
				}
			}
		}

		//////////////////////////////////////////////
				
		al_flip_display();
		al_rest(0.01); 
	}
}

void Game::End(ALLEGRO_DISPLAY* d)
{
	al_destroy_display(d);
}