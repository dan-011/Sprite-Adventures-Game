#ifndef __ITEM_H
#define __ITEM_H

#include "Player.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class Item {
public:
	Item(Player& plyr, int x, int y, double frmRte);
	virtual ~Item();
	virtual ALLEGRO_BITMAP* GetFrame(const double& time);
	int GetXPos() const;
	void SetXPos(int x);
	int GetYPos() const;
	void SetYPos(int y);
	bool GetVisibility();
	void SetVisibility(bool visibility);

protected:
	int RandXPos() {
		srand(time(NULL));
		int val = (rand() % 600) + 60;
		return val;
	}
	void AddFrame(ALLEGRO_BITMAP* frame);
	virtual void AffectPlayer() = 0;
	Player& GetPlayer();
	void IncrementFrameIndex();
	virtual void Movement(double time) = 0;
private:
	Player& player;
	int xpos;
	int ypos;
	bool isVisible;
	double framerate;
	double holdTime;
	vector<ALLEGRO_BITMAP*> frames;
	int frameIndex;
};


class Sword : public Item {
public:
	Sword(Player& plyr);
	virtual ~Sword();
	virtual void AffectPlayer() override;
	virtual void Movement(double time) override;

private:
	double moveRate;
	int moveDist;
	double moveTime;
	bool goingDown;
};
#endif