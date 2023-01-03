
#include "NonPlayerCharacter.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

//xpos(RandXPos()), ypos(275), curframe(0), frameWidth(120), frameHeight(120), bitmapIndex(0), isFacingRight(false), player(plyr), lives(25)
NonPlayerCharacter::NonPlayerCharacter(int x, int y, int width, int height, Player& plyr, int lvs) : xpos(x), ypos(y), frameWidth(width), frameHeight(height), player(plyr), lives(lvs) {}
NonPlayerCharacter::~NonPlayerCharacter() {
	for (auto btmp : rightBitmaps) {
		al_destroy_bitmap(btmp);
	}
	for (auto btmp : leftBitmaps) {
		al_destroy_bitmap(btmp);
	}
}
void NonPlayerCharacter::Activity(double& time, ALLEGRO_KEYBOARD_STATE* keyState) {
	if (!isAlive) return;
	if (movementTime < 0 || animationTime < 0) {
		movementTime = time;
		animationTime = time;
		attackTime = time;
	}
	if (al_get_time() - attackTime > 1) { // waiting time between each attack
		canAttack = true;
		attackTime = al_get_time();
	}
	else {
		canAttack = false;
	}
	/*
	Lock the bitmap type for the current activity
	when it is not locked, it will walk towards the player
	Receive the keystroke to know if the player is attacking
	*/
	int xdiff = player.GetXPos() - GetXPos();
	if (abs(xdiff) < GetDistFromPlyr() && bitmapIndex != 0) {
		if (!together) {
			isIdle = true;
		}
		together = true;
		if (firstAttack) {
			canAttack = al_get_time() - attackTime > 1;
			firstAttack = false;
			attackTime = al_get_time();
		}
		if (!isTakingDamage) {
			lockedAnimation = true;
			if (!player.GetIsUnsheathingSword() && player.GetIsOnPlat() && !player.GetIsTakingDamage() && canAttack && ((xdiff < 0 && !GetIsFacingRight()) || (xdiff >= 0 && GetIsFacingRight()))) {
				isIdle = false;
				curframe = 0;
				bitmapIndex = GetAttackIndex();
				player.TakeDamage(GetAttackDamage());
				isAttacking = true;
			}
			else if (player.GetIsOnPlat() &&  !player.GetIsTakingDamage() && al_key_down(keyState, ALLEGRO_KEY_ENTER) && ((xdiff < 0 && player.GetIsFacingRight()) || (xdiff > 0 && !player.GetIsFacingRight()))) {
				TakeDamage(player.GetAttackDamage());
			}
		}
		else {
			isIdle = true;
		}
	}
	else {
		together = false;
		lockedAnimation = false;
		isIdle = false;
		firstAttack = true;
	}
	if (first) lockedAnimation = true;
	if (al_get_time() - animationTime > framerate) {
		if (curframe >= bitmapBounds.at(bitmapIndex) - 1) {
			if (bitmapIndex == 5) {
				isAlive = false;
				player.AddToScore(GetMonsterValue());
				return;
			}
			if (isTakingDamage) {
				lockedAnimation = false;
				isTakingDamage = false;
			}
			else {
				if (first) {
					first = false;
					lockedAnimation = false;
				}
				if (isAttacking) {
					isAttacking = false;
					lockedAnimation = false;
				}
				curframe = -1;
			}
		}
		if (isIdle && !isTakingDamage) lockedAnimation = false;
		if (!lockedAnimation) {
			if (together) {
				bitmapIndex = GetIdleIndex();
			}
			else {
				bitmapIndex = GetWalkIndex();
				// move towards the character
			}
		}
		curframe++;
		animationTime = al_get_time();
	}
	if (!lockedAnimation && !isTakingDamage && !isAttacking && !isIdle) { // those last two might mess with things
		if (al_get_time() - movementTime > movementRate) {
			if (xdiff < 0) { // they are to the left
				SetIsFacingRight(false);
				xpos -= walkDist;
			}
			else {
				SetIsFacingRight(true);
				xpos += walkDist;
			}
			movementTime = al_get_time();
		}
	}
	if (bitmapIndex >= bitmapBounds.size()) {
		bitmapIndex = GetIdleIndex();
	}
}
ALLEGRO_BITMAP* NonPlayerCharacter::GetBitMap() const {
	return GetIsFacingRight() ? rightBitmaps[bitmapIndex] : leftBitmaps[bitmapIndex];
}
int NonPlayerCharacter::GetWidthPos() {
	return 0;
}
int NonPlayerCharacter::GetHeightPos() {
	return curframe * frameHeight;
}
int NonPlayerCharacter::GetFrameWidth() {
	return frameWidth;
}
int NonPlayerCharacter::GetFrameHeight() {
	return frameHeight;
}
int NonPlayerCharacter::GetXPos() const {
	return xpos;
}
int NonPlayerCharacter::GetYPos() const {
	return ypos;
}
int NonPlayerCharacter::GetCurrFrame() const {
	return curframe;
}
bool NonPlayerCharacter::GetIsFacingRight() const {
	return isFacingRight;
}
void NonPlayerCharacter::SetIsFacingRight(bool dir) {
	isFacingRight = dir;
}
int NonPlayerCharacter::GetLives() const {
	return lives;
}
void NonPlayerCharacter::SetLives(int lvs) {
	lives = lvs;
}
void NonPlayerCharacter::TakeDamage(int amount) {
	SetLives(GetLives() - amount);
	lockedAnimation = true;
	isTakingDamage = true;
	if (GetLives() <= 0) {
		bitmapIndex = GetDeathIndex();
	}
	else {
		bitmapIndex = GetDamageIndex();
	}
	curframe = 0;
}
bool NonPlayerCharacter::GetIsAlive() const {
	return isAlive;
}

SeekerNPC::SeekerNPC(Player& plyr) : NonPlayerCharacter(RandXPos(), 275, 120, 120, plyr, 50) {
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/spawnRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/walkRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/attackRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/damageRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/deathRight.png"));

	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/spawnLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/walkLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/attackLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/damageLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Seeker/deathLeft.png"));

	bitmapBounds.push_back(11);
	bitmapBounds.push_back(6);
	bitmapBounds.push_back(6);
	bitmapBounds.push_back(10);
	bitmapBounds.push_back(4);
	bitmapBounds.push_back(5);
}
SeekerNPC::~SeekerNPC() {
}

int SeekerNPC::GetMonsterValue() const {
	return 20;
}
int SeekerNPC::GetSpawnIndex() const {
	return 0;
}
int SeekerNPC::GetIdleIndex() const {
	return 1;
}
int SeekerNPC::GetWalkIndex() const {
	return 2;
}
int SeekerNPC::GetAttackIndex() const {
	return 3;
}
int SeekerNPC::GetDamageIndex() const {
	return 4;
}
int SeekerNPC::GetDeathIndex() const {
	return 5;
}
int SeekerNPC::GetAttackDamage() const {
	return 15;
}
int SeekerNPC::GetDistFromPlyr() const {
	return 60;
}

SproutNPC::SproutNPC(Player& plyr) : NonPlayerCharacter((RandXPos() % 2 == 0 ? -100 : 800), 305, 96, 96, plyr, 10) {
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/moveRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/attackRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/damageRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/deathRight.png"));

	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/moveLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/attackLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/damageLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Sprout/deathLeft.png"));

	bitmapBounds.push_back(4);
	bitmapBounds.push_back(4);
	bitmapBounds.push_back(5);
	bitmapBounds.push_back(6);
	bitmapBounds.push_back(5);
	bitmapBounds.push_back(8);

}
SproutNPC::~SproutNPC() {

}
int SproutNPC::GetAttackDamage() const {
	return 5;
}
int SproutNPC::GetMonsterValue() const {
	return 5;
}
int SproutNPC::GetSpawnIndex() const {
	return 0;
}
int SproutNPC::GetIdleIndex() const {
	return 1;
}
int SproutNPC::GetWalkIndex() const {
	return 2;
}
int SproutNPC::GetAttackIndex() const {
	return 3;
}
int SproutNPC::GetDamageIndex() const {
	return 4;
}
int SproutNPC::GetDeathIndex() const {
	return 5;
}
int SproutNPC::GetDistFromPlyr() const {
	return 60;
}

LighterNPC::LighterNPC(Player& plyr) : NonPlayerCharacter((RandXPos() % 2 == 0 ? -100 : 800), 240, 196, 196, plyr, 60) {
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/walkRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/attackRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/damageRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/deathRight.png"));

	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/walkLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/attackLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/damageLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Lighter/deathLeft.png"));

	bitmapBounds.push_back(4);
	bitmapBounds.push_back(4);
	bitmapBounds.push_back(8);
	bitmapBounds.push_back(10);
	bitmapBounds.push_back(4);
	bitmapBounds.push_back(8);
}
LighterNPC::~LighterNPC() {}
int LighterNPC::GetAttackDamage() const {
	return 35;
}
int LighterNPC::GetMonsterValue() const {
	return 40;
}
int LighterNPC::GetSpawnIndex() const {
	return 0;
}
int LighterNPC::GetIdleIndex() const {
	return 1;
}
int LighterNPC::GetWalkIndex() const {
	return 2;
}
int LighterNPC::GetAttackIndex() const {
	return 3;
}
int LighterNPC::GetDamageIndex() const {
	return 4;
}
int LighterNPC::GetDeathIndex() const {
	return 5;
}
int LighterNPC::GetDistFromPlyr() const {
	return 100;
}

GuardianNPC::GuardianNPC(Player& plyr) : NonPlayerCharacter((RandXPos() % 2 == 0 ? -100 : 800), 290, 120, 120, plyr, 10) {
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/idleRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/walkRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/attackRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/damageRight.png"));
	rightBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/deathRight.png"));

	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/idleLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/walkLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/attackLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/damageLeft.png"));
	leftBitmaps.push_back(al_load_bitmap("Assets/NPCs/Guardian/deathLeft.png"));

	bitmapBounds.push_back(6);
	bitmapBounds.push_back(6);
	bitmapBounds.push_back(8);
	bitmapBounds.push_back(8);
	bitmapBounds.push_back(4);
	bitmapBounds.push_back(10);
}
GuardianNPC::~GuardianNPC() {}
int GuardianNPC::GetAttackDamage() const {
	return 15;
}
int GuardianNPC::GetMonsterValue() const {
	return 30;
}
int GuardianNPC::GetSpawnIndex() const {
	return 0;
}
int GuardianNPC::GetIdleIndex() const {
	return 1;
}
int GuardianNPC::GetWalkIndex() const {
	return 2;
}
int GuardianNPC::GetAttackIndex() const {
	return 3;
}
int GuardianNPC::GetDamageIndex() const {
	return 4;
}
int GuardianNPC::GetDeathIndex() const {
	return 5;
}
int GuardianNPC::GetDistFromPlyr() const {
	return 60;
}