
#ifndef __NONPLAYERCHARACTER_H
#define __NONPLAYERCHARACTER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>
#include "Player.h"

using namespace std;

class NonPlayerCharacter {
public:
	NonPlayerCharacter(int x, int y, int width, int height, Player& plyr, int lvs);
	virtual ~NonPlayerCharacter();
	virtual void Activity(double& time, ALLEGRO_KEYBOARD_STATE* keyState);
	virtual ALLEGRO_BITMAP* GetBitMap() const;
	virtual int GetWidthPos(); // 0 for vertical bitmaps
	virtual int GetHeightPos(); // 0 for horizontal bitmaps
	virtual int GetFrameWidth();
	virtual int GetFrameHeight();
	virtual int GetXPos() const;
	virtual int GetYPos() const;
	virtual int GetCurrFrame() const;
	virtual bool GetIsFacingRight() const;
	virtual void SetIsFacingRight(bool dir);
	virtual int GetLives() const;
	virtual void SetLives(int lives);
	virtual void TakeDamage(int amount);
	virtual bool GetIsAlive() const;

	virtual int GetAttackDamage() const = 0;
	virtual int GetMonsterValue() const = 0;
	virtual int GetSpawnIndex() const = 0;
	virtual int GetIdleIndex() const = 0;
	virtual int GetWalkIndex() const = 0;
	virtual int GetAttackIndex() const = 0;
	virtual int GetDamageIndex() const = 0;
	virtual int GetDeathIndex() const = 0;
	virtual int GetDistFromPlyr() const = 0;
protected:
	int RandXPos() {
		srand(time(NULL));
		int val = (rand() % 600) + 60;
		return val;
	}

	int xpos;
	int ypos;
	int curframe = 0;
	int frameWidth;
	int frameHeight;
	int bitmapIndex = 0;
	vector<int> bitmapBounds;
	vector<ALLEGRO_BITMAP*> rightBitmaps; // 0 is spawn, 1 is walk, ...
	vector<ALLEGRO_BITMAP*> leftBitmaps;
	double framerate = .1;
	bool isFacingRight = false;
	Player& player;
	int lives;
	bool lockedAnimation = true;
	bool first = true;
	bool isAlive = true;
	bool isTakingDamage = false;
	bool isAttacking = false;
	bool canAttack = false;
	bool isIdle = false;
	int walkDist = 5;
	double movementTime = -1;
	double animationTime = -1;
	double movementRate = .05;
	bool lockedMovement = false;
	bool firstAttack = true;
	double attackTime = -1;
	bool together = false;
	int numHits = 0;
};

class SeekerNPC : public NonPlayerCharacter {
public:
	SeekerNPC(Player& plyr);
	virtual ~SeekerNPC();
	virtual int GetAttackDamage() const override;
	virtual int GetMonsterValue() const override;
	virtual int GetSpawnIndex() const override;
	virtual int GetIdleIndex() const override;
	virtual int GetWalkIndex() const override;
	virtual int GetAttackIndex() const override;
	virtual int GetDamageIndex() const override;
	virtual int GetDeathIndex() const override;
	virtual int GetDistFromPlyr() const override;

};

class SproutNPC : public NonPlayerCharacter {
public:
	SproutNPC(Player& plyr);
	virtual ~SproutNPC();
	virtual int GetAttackDamage() const override;
	virtual int GetMonsterValue() const override;
	virtual int GetSpawnIndex() const override;
	virtual int GetIdleIndex() const override;
	virtual int GetWalkIndex() const override;
	virtual int GetAttackIndex() const override;
	virtual int GetDamageIndex() const override;
	virtual int GetDeathIndex() const override;
	virtual int GetDistFromPlyr() const override;

};

class LighterNPC : public NonPlayerCharacter {
public:
	LighterNPC(Player& plyr);
	virtual ~LighterNPC();
	virtual int GetAttackDamage() const override;
	virtual int GetMonsterValue() const override;
	virtual int GetSpawnIndex() const override;
	virtual int GetIdleIndex() const override;
	virtual int GetWalkIndex() const override;
	virtual int GetAttackIndex() const override;
	virtual int GetDamageIndex() const override;
	virtual int GetDeathIndex() const override;
	virtual int GetDistFromPlyr() const override;

};

class GuardianNPC : public NonPlayerCharacter {
public:
	GuardianNPC(Player& plyr);
	virtual ~GuardianNPC();
	virtual int GetAttackDamage() const override;
	virtual int GetMonsterValue() const override;
	virtual int GetSpawnIndex() const override;
	virtual int GetIdleIndex() const override;
	virtual int GetWalkIndex() const override;
	virtual int GetAttackIndex() const override;
	virtual int GetDamageIndex() const override;
	virtual int GetDeathIndex() const override;
	virtual int GetDistFromPlyr() const override;
	

};
#endif
