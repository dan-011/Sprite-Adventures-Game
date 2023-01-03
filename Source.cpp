#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <ctime>
#include "Player.h"
#include "StartMenu.h"
#include "NonPlayerCharacter.h"
#include "NPCManager.h"
#include "GameOverScreen.h"
#include "Items.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

#define PURPLE al_map_rgb(128, 0, 128)
#define MAYA_BLUE al_map_rgb(115, 194, 251)
#define BLACK al_map_rgb(0,0,0)

using namespace std;

int CountAliveNPCs(const vector<NonPlayerCharacter*>& vec) {
	int count = 0;
	for (auto c : vec) {
		if (c->GetIsAlive()) count++;
	}
	return count;
}

int main() {
	al_init(); // sets up allegro
	al_init_font_addon(); // sets up the font addon
	al_init_ttf_addon(); // these inits could fail
	al_install_keyboard(); // install keyboard
	al_init_image_addon();
	al_install_audio();
	al_init_acodec_addon();

	ALLEGRO_KEYBOARD_STATE* keyState = new ALLEGRO_KEYBOARD_STATE;
	
	al_init_image_addon();
	ALLEGRO_BITMAP* background;
	background = al_load_bitmap("Assets/Backgrounds/forest.png");//al_load_bitmap("Backgrounds/forest3.png");
	int background_width = al_get_bitmap_width(background);
	int background_height = al_get_bitmap_height(background);

	ALLEGRO_DISPLAY* display = al_create_display(background_width, background_height); // create a display that is that size
	ALLEGRO_BITMAP* icon = al_load_bitmap("Assets/Icons/dragon.png");
	al_set_display_icon(display, icon);
	al_set_window_title(display, "The Adventures of SPRITE");
	
	double time = al_get_time();
	double npcTime = al_get_time();

	StartMenu sm;
	sm.RunLoadingScreen(time, keyState);

	ALLEGRO_SAMPLE* forest_song;
	ALLEGRO_SAMPLE_INSTANCE* forest_song_instance;
	//al_reserve_samples(10);
	//forest_song = al_load_sample("Assets/Music/Adventure/TheForest.wav");
	//forest_song = al_load_sample("Assets/Music/Adventure/AdventureTheme.mp3");
	forest_song = al_load_sample("Assets/Music/Adventure/RetroForest.mp3");


	ALLEGRO_BITMAP* filledHeart = al_load_bitmap("Assets/Hearts/PNG/basic/heart.png");
	ALLEGRO_BITMAP* emptyHeart = al_load_bitmap("Assets/Hearts/PNG/basic/background.png");

	forest_song_instance = al_create_sample_instance(forest_song);
	al_set_sample_instance_playmode(forest_song_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(forest_song_instance, al_get_default_mixer());

	Player player;
	// we move the image to move the character
	bool end_loop = false;
	vector<int> yvals;
	al_play_sample_instance(forest_song_instance);
	int i = 0;
	ALLEGRO_SAMPLE* death_song = al_load_sample("Assets/Music/Death.mp3");
	ALLEGRO_SAMPLE_INSTANCE* death_song_instance = al_create_sample_instance(death_song);
	al_set_sample_instance_playmode(death_song_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(death_song_instance, al_get_default_mixer());

	ALLEGRO_SAMPLE* power_up = al_load_sample("Assets/Music/PowerUp.mp3");
	ALLEGRO_SAMPLE_INSTANCE* power_up_instance = al_create_sample_instance(power_up);
	al_set_sample_instance_playmode(power_up_instance, ALLEGRO_PLAYMODE_ONCE);
	al_attach_sample_instance_to_mixer(power_up_instance, al_get_default_mixer());

	// PUT SOMEWHERE ELSE
	ALLEGRO_COLOR white = al_map_rgb(255, 255, 255);
	ALLEGRO_FONT* scoreFont = al_load_ttf_font("Assets/Fonts/alagard.ttf", 40, 0);
	char score[128];
	
	NPCManager npcManager(player);
	vector<NonPlayerCharacter*> nonPlayerCharacters;
	double addPlayersTimer = al_get_time();
	int addNPCWait = 1;
	bool firstDeath = true;
	Sword sword(player);
	bool noPowerUp = true;
	srand(al_get_time());
	while (!end_loop) {
		i++;
		al_get_keyboard_state(keyState);
		
		if (al_key_down(keyState, ALLEGRO_KEY_ESCAPE)) {
			end_loop = true;
			break;
		}
		if (player.GetScore() >= 15) npcManager.SetMaxVillain(2);
		if (player.GetScore() >= 30) npcManager.SetMaxVillain(3);
		if (player.GetScore() >= 45) npcManager.SetMaxVillain(4);
		player.Movements(time, keyState, background_width);
		if (al_get_time() - addPlayersTimer > addNPCWait) {
			
			nonPlayerCharacters.push_back(npcManager.GenerateRandomNPC());
			addPlayersTimer = al_get_time();
			addNPCWait = rand() % 5 + 1;
			
		}

		al_clear_to_color(BLACK);
		al_draw_bitmap(background, 0, 0, 0);
		if (player.GetScore() >= 50 && !player.GetHasSword())
			sword.SetVisibility(true);
		if (sword.GetVisibility()) {
			al_draw_bitmap(sword.GetFrame(time), sword.GetXPos(), sword.GetYPos(), 0);
		}
		if (player.GetIsUnsheathingSword() && noPowerUp) {
			al_play_sample_instance(power_up_instance);
			noPowerUp = false;
		}
		al_draw_bitmap(player.GetSprite(), player.GetXPos(), player.GetYPos() , 0);
		int aliveNPCs = CountAliveNPCs(nonPlayerCharacters);
		for (auto npc : nonPlayerCharacters) {
			if (!npc->GetIsAlive()) continue;
			npc->Activity(npcTime, keyState);
			al_draw_bitmap_region(npc->GetBitMap(), npc->GetWidthPos(), npc->GetHeightPos(), npc->GetFrameWidth(), npc->GetFrameHeight(), npc->GetXPos(), npc->GetYPos(), 0);
		}
		int startX = 15;
		int ypos = 20;
		int heartOffset = 30;
		for (int i = 0; i < (int)player.GetLives()/5; i++) {
			al_draw_bitmap(filledHeart, startX, ypos, 0);
			startX += heartOffset;
		}
		for (int i = (int)player.GetLives()/5; i < 5; i++) {
			al_draw_bitmap(emptyHeart, startX, ypos, 0);
			startX += heartOffset;
		}
		std::snprintf(score, 128, "%d", player.GetScore());
		al_draw_text(scoreFont, white, 640, 20, 0, score);
		al_flip_display(); // draw offscreen and display on screen
		player.MovementBoundsCheck(background_width);
		if (player.GetLives() == 0 && firstDeath) {
			al_stop_sample_instance(forest_song_instance);
			al_play_sample_instance(death_song_instance);
			firstDeath = false;
		}
		if (player.CanExit()) break;
	}
	if (player.GetLives() == 0) {
		double deathTime = al_get_time();
		while (al_get_time() - deathTime < 2) {
			// wait
		}
		al_destroy_sample(death_song);
		al_destroy_sample_instance(death_song_instance);

		GameOver gameOver;
		deathTime = al_get_time();
		gameOver.RunGameOverScreen(deathTime, keyState, player.GetScore());
	}

	for (auto character : nonPlayerCharacters) {
		if (character != NULL) delete character;
	}
	al_stop_sample_instance(forest_song_instance);
	al_destroy_sample(power_up);
	al_destroy_sample_instance(power_up_instance);

	al_destroy_bitmap(icon);
	al_destroy_sample(forest_song);
	al_destroy_sample_instance(forest_song_instance);
	// for every create function there is a destroy  function
	al_destroy_bitmap(background);
	al_destroy_display(display); // destroy allocated memory
	al_uninstall_keyboard();
	al_destroy_bitmap(filledHeart);
	al_destroy_bitmap(emptyHeart);
	al_destroy_font(scoreFont);
	delete keyState;
	return 0;
}