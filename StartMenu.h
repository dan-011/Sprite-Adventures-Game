
#ifndef __STARTMENU_H
#define __STARTMENU_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>


using namespace std;

class StartMenu {
private:
	vector<ALLEGRO_BITMAP*> startMenuFrames;
	int width;
	int height;
	size_t framesLength;
	int framesIndex;
	const double frames_time = 0.1;

	vector<ALLEGRO_BITMAP*> enterGameFrames;
	int enter_index;
	size_t enterLength;
	const double enter_time = 0.11;

	bool reverse;

	ALLEGRO_SAMPLE* title_song;
	ALLEGRO_SAMPLE* enter_song;
	ALLEGRO_SAMPLE_INSTANCE* song_instance;
	ALLEGRO_FONT* title_font1;
	ALLEGRO_FONT* title_font2;
	ALLEGRO_FONT* enter_font;
	const int title1_xpos = 300;
	const int title1_ypos = 50;
	const int title2_xpos = 450;
	const int title2_ypos = 100;
	const int enter_xpos = 150;
	const int enter_ypos = 370;

public:
	StartMenu() : framesIndex(0), enter_index(0), reverse(false) {
		al_reserve_samples(10);

		title_song = al_load_sample("Assets/Music/Adventure/title.wav");
		enter_song = al_load_sample("Assets/Music/Animation-Audios/game_start.mp3");
		song_instance = al_create_sample_instance(title_song);
		al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
		al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

		title_font1 = al_load_ttf_font("Assets/Fonts/alagard.ttf", 40, 0);
		title_font2 = al_load_ttf_font("Assets/Fonts/alagard.ttf", 70, 0);
		enter_font = al_load_ttf_font("Assets/Fonts/PressStart2P.ttf", 20, 0);
		
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl0.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl1.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl2.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl3.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl4.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl5.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl6.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl7.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl8.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl9.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl10.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl11.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl12.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl13.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl14.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl15.png"));
		enterGameFrames.push_back(al_load_bitmap("Assets/Animations/Enter/expl16.png"));

		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame0.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame1.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame2.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame3.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame4.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame5.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame6.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame7.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame8.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame9.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame10.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame11.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame12.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame13.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame14.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame15.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame16.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame17.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame18.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame19.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame20.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame21.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame22.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame23.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame24.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame25.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame26.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame27.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame28.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame29.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame30.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame31.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame32.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame33.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame34.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame35.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame36.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame37.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame38.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame39.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame40.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame41.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame42.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame43.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame44.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame45.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame46.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame47.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame48.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame49.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame50.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame51.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame52.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame53.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame54.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame55.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame56.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame57.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame58.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame59.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame60.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame61.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame62.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame63.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame64.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame65.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame66.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame67.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame68.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame69.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame70.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame71.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame72.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame73.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame74.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame75.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame76.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame77.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame78.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame79.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame80.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame81.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame82.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame83.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame84.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame85.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame86.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame87.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame88.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame89.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame90.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame91.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame92.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame93.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame94.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame95.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame96.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame97.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame98.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame99.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame100.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame101.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame102.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame103.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame104.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame105.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame106.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame107.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame108.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame109.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame110.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame111.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame112.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame113.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame114.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame115.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame116.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame117.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame118.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame119.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame120.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame121.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame122.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame123.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame124.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame125.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame126.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame127.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame128.png"));
		startMenuFrames.push_back(al_load_bitmap("Assets/Start-Menus/Start-Menu-1/frame129.png"));

		enterLength = enterGameFrames.size();

		framesLength = startMenuFrames.size();
		width = al_get_bitmap_width(startMenuFrames[0]);
		height = al_get_bitmap_height(startMenuFrames[0]);
	}
	~StartMenu() {
		for (unsigned int i = 0; i < framesLength; i++) {
			al_destroy_bitmap(startMenuFrames[i]);
		}
		for (unsigned int i = 0; i < enterLength; i++) {
			al_destroy_bitmap(enterGameFrames[i]);
		}
		al_destroy_sample(title_song);
		al_destroy_sample(enter_song);
		al_destroy_sample_instance(song_instance);
		al_destroy_font(title_font1);
		al_destroy_font(enter_font);
	}

	void RunLoadingScreen(double& time, ALLEGRO_KEYBOARD_STATE*& keyState);
	void ChangeFrame(double& time);
};

#endif
