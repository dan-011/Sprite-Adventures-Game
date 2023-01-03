#ifndef __GAMEOVERSCREEN_H
#define __GAMEOVERSCREEN_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class GameOver {
public:
	GameOver();
	~GameOver();
	void RunGameOverScreen(double& time, ALLEGRO_KEYBOARD_STATE*& keyState, int score);
	void ChangeFrame(double& time);
	void GetScores(vector<int>& scores);
private:
	vector<ALLEGRO_BITMAP*> gameOverFrames;
	int width;
	int height;
	int framesIndex;
	const double frames_time = 0.1;

	ALLEGRO_SAMPLE* gameover_song;
	ALLEGRO_SAMPLE_INSTANCE* song_instance;
	ALLEGRO_FONT* gameover_font1;
	ALLEGRO_FONT* score_font;
	ALLEGRO_FONT* esc_font;
	const int gameOver_Xpos = 100;
	const int gameOver_Ypos = 100;


};

#endif