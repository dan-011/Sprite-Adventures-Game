#include "GameOverScreen.h"
#include <string>

GameOver::GameOver(): framesIndex(0) {
    al_reserve_samples(10);

    gameover_song = al_load_sample("Assets/Music/GameOver.mp3");
    song_instance = al_create_sample_instance(gameover_song);
    al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());

    gameover_font1 = al_load_ttf_font("Assets/Fonts/alagard.ttf", 70, 0);
    score_font = al_load_ttf_font("Assets/Fonts/alagard.ttf", 20, 0);
    esc_font = al_load_ttf_font("Assets/Fonts/PressStart2P.ttf", 20, 0);

    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame0.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame1.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame2.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame3.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame4.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame5.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame6.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame7.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame8.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame9.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame10.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame11.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame12.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame13.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame14.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame15.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame16.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame17.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame18.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame19.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame20.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame21.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame22.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame23.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame24.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame25.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame26.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame27.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame28.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame29.png"));
    gameOverFrames.push_back(al_load_bitmap("Assets/GameOver/frame30.png"));

    width = al_get_bitmap_width(gameOverFrames[0]);
    height = al_get_bitmap_height(gameOverFrames[0]);

}
GameOver::~GameOver() {
    for (auto frame : gameOverFrames) {
        al_destroy_bitmap(frame);
    }
	al_destroy_sample(gameover_song);
	al_destroy_sample_instance(song_instance);
	al_destroy_font(gameover_font1);
}

void GameOver::RunGameOverScreen(double& time, ALLEGRO_KEYBOARD_STATE*& keyState, int score) {
	ALLEGRO_BITMAP* gameOverFrame;
	al_play_sample_instance(song_instance);
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
    vector<int> scores = { score };
    GetScores(scores);
    char scr1[128];
    char scr2[128];
    char scr3[128];
    int firstScore = scores.size() - 1;
    int secondScore = scores.size() - 2;
    int thirdScore = scores.size() - 3;
    snprintf(scr1, 128, "1. %d", scores[firstScore]);
    snprintf(scr2, 128, "2. %d", scores[secondScore]);
    snprintf(scr3, 128, "3. %d", scores[thirdScore]);

    if (scores[firstScore] == 0) {
        scr1[3] = '~';
    }
    if (scores[secondScore] == 0) {
        scr2[3] = '~';
    }
    if (scores[thirdScore] == 0) {
        scr3[3] = '~';
    }
	//ALLEGRO_COLOR grey = al_map_rgb(128, 128, 128);
	bool clicked_esc = false;
	do {
		gameOverFrame = gameOverFrames[framesIndex];
		ChangeFrame(time);
		al_draw_bitmap(gameOverFrame, 0, 0, 0);
		al_draw_text(gameover_font1, white, 175, 50, 0, "GAME OVER");
        al_draw_text(score_font, white, 210, 120, 0, "HIGH SCORES:");
        al_draw_text(score_font, white, 230, 145, 0, scr1);
        al_draw_text(score_font, white, 230, 170, 0, scr2);
        al_draw_text(score_font, white, 230, 195, 0, scr3);
        if ((int)time % 2 == 0) {
            al_draw_text(esc_font, white, 200, 370, 0, "PRESS ESC TO EXIT");
        }
		al_flip_display();
		al_get_keyboard_state(keyState);

		clicked_esc = al_key_down(keyState, ALLEGRO_KEY_ESCAPE);
	} while (!clicked_esc);
	al_stop_sample_instance(song_instance);
}
void GameOver::ChangeFrame(double& time) {
    if (al_get_time() - time > frames_time) {
        framesIndex++;
        if (framesIndex >= gameOverFrames.size()) framesIndex = 0;
        time = al_get_time();
    }
}
void GameOver::GetScores(vector<int>& scores) {
    ifstream scoresFile;
    scoresFile.open("Scores.txt");
    string line;
    while (!scoresFile.eof()) {
        getline(scoresFile, line);
        if (line.size() == 0) continue;
        scores.push_back(stoi(line));
    }
    while (scores.size() < 3) scores.push_back(0);
    sort(scores.begin(), scores.end());
    scoresFile.close();
    ofstream outputFile;
    outputFile.open("Scores.txt", std::ios::trunc);
    for (auto score : scores) {
        outputFile << to_string(score) << endl;
    }
    outputFile.close();
}