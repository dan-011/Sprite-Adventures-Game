#include "Items.h"
#include <iostream>
#include <cmath>
Item::Item(Player& plyr, int x, int y, double frmRte) : player(plyr), xpos(x), ypos(y), isVisible(false), framerate(frmRte), holdTime(-1), frameIndex(0) {}
Item::~Item() {
	for (auto frame : frames) {
		al_destroy_bitmap(frame);
	}
}
ALLEGRO_BITMAP* Item::GetFrame(const double& time) {
	if (!isVisible) return NULL;
	if (holdTime < 0) holdTime = time;
	AffectPlayer();
	ALLEGRO_BITMAP* ret = frames.at(frameIndex);
	if (al_get_time() - holdTime > framerate) {
		IncrementFrameIndex();
		holdTime = al_get_time();
	}
	Movement(al_get_time());
	return ret;
}
int Item::GetXPos() const {
	return xpos;
}
void Item::SetXPos(int x) {
	xpos = x;
}
int Item::GetYPos() const {
	return ypos;
}
void Item::SetYPos(int y) {
	ypos = y;
}
bool Item::GetVisibility() {
	return isVisible;
}
void Item::SetVisibility(bool visibility) {
	isVisible = visibility;
}
void Item::AddFrame(ALLEGRO_BITMAP* frame) {
	frames.push_back(frame);
}
Player& Item::GetPlayer() {
	return player;
}
void Item::IncrementFrameIndex() {
	frameIndex++;
	if (frameIndex >= frames.size()) frameIndex = 0;
}

Sword::Sword(Player& plyr) : Item(plyr, RandXPos(), 275, .2), moveRate(.1), moveDist(2), moveTime(-1), goingDown(true) {
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword0.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword1.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword2.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword3.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword4.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword5.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword6.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword7.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword8.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword9.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword10.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword11.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword12.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword13.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword14.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword15.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword16.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword17.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword18.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword19.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword20.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword21.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword22.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword23.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword24.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword25.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword26.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword27.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword28.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword29.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword30.png"));
	AddFrame(al_load_bitmap("Assets/Animations/FlamingSword/flamingSword31.png"));
}
Sword::~Sword() {}
void Sword::AffectPlayer() {
	if (abs(GetPlayer().GetXPos() - GetXPos()) < 10) {
		GetPlayer().ReceiveSword();
		SetVisibility(false);
	}
}
void Sword::Movement(double time) {
	if (moveTime < 0) moveTime = time;
	if (al_get_time() - moveTime > moveRate) {
		if (goingDown) {
			SetYPos(GetYPos() - moveDist);
		}
		else {
			SetYPos(GetYPos() + moveDist);
		}
		if (GetYPos() > 290) goingDown = !goingDown;
		else if (GetYPos() < 275) goingDown = !goingDown;
		moveTime = al_get_time();
	}
}