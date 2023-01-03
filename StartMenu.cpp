#include "StartMenu.h"

void StartMenu::RunLoadingScreen(double& time, ALLEGRO_KEYBOARD_STATE*& keyState) {
	ALLEGRO_BITMAP* startMenuFrame;
	al_play_sample_instance(song_instance);
	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	//ALLEGRO_COLOR grey = al_map_rgb(128, 128, 128);
	bool clicked_enter = false;
	do {
		if (framesIndex == framesLength - 1) {
			reverse = true;
		}
		if (framesIndex == 0) {
			reverse = false;
		}
		startMenuFrame = startMenuFrames[framesIndex];
		ChangeFrame(time);
		al_draw_bitmap(startMenuFrame, 0, 0, 0);
		al_draw_text(title_font1, black, title1_xpos, title1_ypos, 0, "The Adventures of");
		al_draw_text(title_font2, black, title2_xpos, title2_ypos, 0, "Sprite");
		if ((int)time % 2 == 0) {
			al_draw_text(enter_font, white, enter_xpos, enter_ypos, 0, "press ENTER to start");
		}
		al_flip_display();
		al_get_keyboard_state(keyState);

		clicked_enter = al_key_down(keyState, ALLEGRO_KEY_ENTER) || al_key_down(keyState, ALLEGRO_KEY_ESCAPE);
	} while (!clicked_enter);
	time = al_get_time();
	al_stop_sample_instance(song_instance);
	al_play_sample(enter_song, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
	time = al_get_time();
	double frame_time = time;
	while (al_get_time() - time < 2) {
		if (al_get_time() - frame_time > enter_time) {
			enter_index++;
			frame_time = al_get_time();
		}
		if (enter_index >= enterLength) {
			break;
		}
		float sw = al_get_bitmap_width(enterGameFrames[enter_index]);
		float sh = al_get_bitmap_height(enterGameFrames[enter_index]);
		al_draw_bitmap(enterGameFrames[enter_index], 0, 0, 0);
		al_flip_display();
	}
	al_clear_to_color(black);
	al_flip_display();
	time = al_get_time();
	while (al_get_time() - time < 0.5) {
		// wait
	}

}

void StartMenu::ChangeFrame(double& time) {
	if (al_get_time() - time > frames_time) {
		reverse ? framesIndex-- : framesIndex++;
		time = al_get_time();
	}
}