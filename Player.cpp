#include "Player.h"
#include <iostream>

void Player::Movements(double& time, ALLEGRO_KEYBOARD_STATE*& keyState, int background_width) {
	if (ypos == 305) {
		int i = 10;
	}
	MovementBoundsCheck(background_width);
	if (GetIsUnsheathingSword()) {
		UnsheathSword(time);
		return;
	}
	if (takingDamage) {
		Damage(time);
		return;
	}
	if (isJumping) {
		Move(time, isFacingRight ? JumpRight : JumpLeft);
		lastKeyPressed = ALLEGRO_KEY_SPACE;
		return;
	}
	if (isAttacking) {
		Punch(time);
		return;

	}
	if (!isOnPlatform) {
		Move(time, isFacingRight ? FallRight : FallLeft);
		lastKeyPressed = ALLEGRO_KEY_SPACE;
		return;
	}
	if (al_key_down(keyState, ALLEGRO_KEY_ENTER)) {
		Punch(time);
		return;
	}
	else if (al_key_down(keyState, ALLEGRO_KEY_D)) { // press D
		//MoveRight(time);
		Move(time, RunRight);
		lastKeyPressed = ALLEGRO_KEY_D;

	}
	else if (al_key_down(keyState, ALLEGRO_KEY_A)) {
		//MoveLeft(time);
		Move(time, RunLeft);
		lastKeyPressed = ALLEGRO_KEY_A;
	}
	if (al_key_down(keyState, ALLEGRO_KEY_SPACE) || al_key_down(keyState, ALLEGRO_KEY_W)) { // jumping
		if (lastKeyPressed == ALLEGRO_KEY_SPACE && ypos == 310) {
			playerSprite = GetIdle(0);
			lastKeyPressed = 0;
			return;
		}
		if (lastKeyPressed != ALLEGRO_KEY_SPACE) {
			isJumping = true; // set to false at the peak of the parabola
			fallIndex = 0;
			Move(time, isFacingRight ? JumpRight : JumpLeft); // changes y value
			lastKeyPressed = ALLEGRO_KEY_SPACE;
		}
	}
	else if (!isOnPlatform && !isJumping) {
		Move(time, isFacingRight ? FallRight : FallLeft);
		lastKeyPressed = ALLEGRO_KEY_SPACE;
	}
	else if(!al_key_down(keyState, ALLEGRO_KEY_A) && !al_key_down(keyState, ALLEGRO_KEY_D)&& !al_key_down(keyState, ALLEGRO_KEY_W)&& !al_key_down(keyState, ALLEGRO_KEY_SPACE)) {
		//Idle(time);
		SetIdle();
		lastKeyPressed = 0;
		Move(time, isFacingRight ? IdleRight : IdleLeft);
	}
}

void Player::SetRunRight() {
	isFacingRight = true;
	isRunningLeft = false;
	isRunningRight = true;
}

void Player::SetRunLeft() {
	isFacingRight = false;
	isRunningLeft = true;
	isRunningRight = false;
}

void Player::SetIdle() {
	isRunningLeft = false;
	isRunningRight = false;
}

void Player::Move(double& time, Movement movement) {
	int x;
	int y;
	switch (movement) {
		case RunRight:
			playerSprite = GetRunRight();
			SetRunRight();
			TimeMovement(time, runRightIndex, jumpIndex, run_time, true, false, xpos + run_distance);
			break;
		case RunLeft:
			// negative offset
			playerSprite = GetRunLeft();
			SetRunLeft();
			TimeMovement(time, runLeftIndex, jumpIndex, run_time, true, false, xpos - run_distance);
			break;
		case JumpRight:
			playerSprite = GetJumpRight();
			x = xpos + jump_x_distance;
			y = ypos - jump_heights[jumpIndex];
			
			TimeMovement(time, runRightIndex, jumpIndex, jump_time, isRunningRight, true, x, y);

			if (jumpIndex > 7) {
				jumpIndex = 0;
				isJumping = false;
			}
			break;
		case JumpLeft:
			playerSprite = GetJumpLeft();
			x = xpos - jump_x_distance;
			y = ypos - jump_heights[jumpIndex];

			TimeMovement(time, runRightIndex, jumpIndex, jump_time, isRunningLeft, true, x, y);

			if (jumpIndex > 7) {
				jumpIndex = 0;
				isJumping = false;
			}
			break;
		case FallRight:
			playerSprite = GetFallRight();
			x = xpos + jump_x_distance;
			y = ypos + fall_heights[fallIndex];

			TimeMovement(time, runRightIndex, fallIndex, fall_time, isRunningRight, true, x, y);

			if (fallIndex > 7) {
				isOnPlatform = true;
			}
			break;
		case FallLeft:
			playerSprite = GetFallLeft();
			x = xpos - jump_x_distance;
			y = ypos + fall_heights[fallIndex];

			TimeMovement(time, runRightIndex, fallIndex, fall_time, isRunningLeft, true, x, y);

			if (fallIndex > 7) {
				isOnPlatform = true;
			}
			break;
		case SmrsltRight:
			playerSprite = smrsltRightArray[smrsltIndex];
			break;
		case SmrsltLeft:
			playerSprite = smrsltLeftArray[smrsltIndex];
			break;
		case IdleRight:
			playerSprite = GetIdleRight();
			TimeMovement(time, idleIndex, idleIndex, idle_time, false, false);
			break;
		case IdleLeft:
			playerSprite = GetIdleLeft();
			TimeMovement(time, idleIndex, idleIndex, idle_time, false, false);
			break;
	}
}

void Player::TimeMovement(double& time, int& xIndex, int& yIndex, double timeWindow, bool movingX, bool movingY, int xOffset, int yOffset) {
	if (movingX || movingY) {
		idleIndex = 0;
	}
	if (al_get_time() - time > timeWindow) {
		if (movingX) {
			xpos = xOffset;
			xIndex++;
		}
		if (movingY) {
			int prevY = ypos;
			ypos = yOffset;
			if (prevY > ypos) {
				jumpIndex++;
			}
			else {
				fallIndex++;
			}
		}
		if (!movingX && !movingY) { // we are idle
			idleIndex++;
		}
		time = al_get_time();
	}
}

void Player::Punch(double& time) {
	isAttacking = true;
	runRightIndex = 0;
	runLeftIndex = 0;
	playerSprite = GetAttack();
	if (al_get_time() - time > punchTime) {
		punchIndex++;
		if (punchIndex >= GetAttackLeftArray()[punchType].size()) {
			isAttacking = false;
			punchIndex = 0;
			punchType++;
			if (punchType >= 3) {
				punchType = 0;
			}
		}
		time = al_get_time();
	}
}

void Player::Damage(double& time) {
	takingDamage = true;
	runRightIndex = 0;
	runLeftIndex = 0;
	playerSprite = GetDamage();
	if (al_get_time() - time > damageTime) {
		damageIndex++;
		if (damageIndex >= damageRight.size()) {
			takingDamage = false;
			damageIndex = 0;
		}
		time = al_get_time();
	}
	if (damageIndex == 7 && lives <= 0) canExit = true;
}

void Player::Idle(double& time) {
	runRightIndex = 0; // when we're idle reset run
	runLeftIndex = 0;
	playerSprite = GetIdle();
	if (al_get_time() - time > idle_time) {
		idleIndex++;
		time = al_get_time();
	}
}

void Player::MovementBoundsCheck(int background_width) {
	if (runRightIndex >= GetRunRightArray().size()) {
		runRightIndex = 0;
	}
	if (idleIndex >= GetIdleRightArray().size()) {
		idleIndex = 0;
	}
	if (runLeftIndex >= GetRunRightArray().size()) {
		runLeftIndex = 0;
	}
	if (xpos >= background_width) {
		xpos = 0;
	}
	else if (xpos <= 0) {
		xpos = background_width;
	}
	if (ypos != ground) {
		isOnPlatform = false;
	}
	else {
		isOnPlatform = true;
	}
}

ALLEGRO_BITMAP* Player::GetSprite() {
	return playerSprite;
}

int Player::GetXPos() {
	return xpos;
}

int Player::GetYPos() {
	return ypos;
}

bool Player::GetIsOnPlat() {
	return GetYPos() == ground;
}

bool Player::GetIsAttacking() const {
	return isAttacking;
}

int Player::GetLives() const {
	return lives;
}
void Player::TakeDamage(int amount) {
	lives -= amount;
	takingDamage = true;
	if (lives < 0) {
		lives = 0;
	}
}

bool Player::GetIsTakingDamage() const {
	return takingDamage;
}

int Player::GetScore() const {
	return score;
}

void Player::AddToScore(int amount) {
	score += amount;
}
int Player::GetWeaponIndex() const {
	return weaponIndex;
}
int Player::GetAttackDamage() const {
	if (!holdingSword) return 5;
	else return 20;
}

bool Player::GetIsFacingRight() const {
	return isFacingRight;
}

bool Player::CanExit() const {
	return canExit;
}

bool Player::GetIsJumping() const {
	return isJumping;
}
ALLEGRO_BITMAP* Player::GetRunRight() const {
	if (!holdingSword) {
		return runRightArray[runRightIndex];
	}
	else {
		return runRightSwordArray[runRightIndex];
	}
}
ALLEGRO_BITMAP* Player::GetRunLeft() const {
	if (!holdingSword) {
		return runLeftArray[runLeftIndex];
	}
	else {
		return runLeftSwordArray[runLeftIndex];
	}
}
ALLEGRO_BITMAP* Player::GetJumpRight() const {
	if (!holdingSword) {
		return jumpRightArray[jumpIndex];
	}
	else {
		return jumpRightSwordArray[runRightIndex];
	}
}
ALLEGRO_BITMAP* Player::GetJumpLeft() const {
	if (!holdingSword) {
		return jumpLeftArray[jumpIndex];
	}
	else {
		return jumpLeftSwordArray[jumpIndex];
	}
}ALLEGRO_BITMAP* Player::GetFallRight() const {
	return fallRightArray[fallIndex];
}
ALLEGRO_BITMAP* Player::GetFallLeft() const {
	return fallLeftArray[fallIndex];
}
ALLEGRO_BITMAP* Player::GetIdleRight() const {
	if (!holdingSword) {
		return idleRightArray[idleIndex];
	}
	else {
		return idleRightSwordArray[idleIndex];
	}
}
ALLEGRO_BITMAP* Player::GetIdleLeft() const {
	if (!holdingSword) {
		return idleLeftArray[idleIndex];
	}
	else {
		return idleLeftSwordArray[idleIndex];
	}
}
ALLEGRO_BITMAP* Player::GetDamageRight() const {
	return damageRight[damageIndex];
}
ALLEGRO_BITMAP* Player::GetDamageLeft() const {
	return damageLeft[damageIndex];
}
ALLEGRO_BITMAP* Player::GetAttackRight() const {
	if (!holdingSword) {
		return punchRight[punchType][punchIndex];
	}
	else {
		return attackRightSwordArray[punchType][punchIndex];
	}
}
ALLEGRO_BITMAP* Player::GetAttackLeft() const {
	if (!holdingSword) {
		return punchLeft[punchType][punchIndex];
	}
	else {
		return attackLeftSwordArray[punchType][punchIndex];
	}
}
ALLEGRO_BITMAP* Player::GetRun() const {
	return isFacingRight ? GetRunRight() : GetRunLeft();
}
ALLEGRO_BITMAP* Player::GetJump() const {
	return isFacingRight ? GetRunRight() : GetRunLeft();
}
ALLEGRO_BITMAP* Player::GetFall() const {
	return isFacingRight ? GetFallRight() : GetFallLeft();
}
ALLEGRO_BITMAP* Player::GetIdle() const {
	return isFacingRight ? GetIdleRight() : GetIdleLeft();
}
ALLEGRO_BITMAP* Player::GetIdle(int index) const {
	if (!holdingSword) {
		return isFacingRight ? idleRightArray[index] : idleLeftArray[index];
	}
	else {
		return isFacingRight ? idleRightArray[index] : idleLeftArray[index]; // idle with sword
	}
}
ALLEGRO_BITMAP* Player::GetDamage() const {
	return isFacingRight ? GetDamageRight() : GetDamageLeft();
}
ALLEGRO_BITMAP* Player::GetAttack() const {
	return isFacingRight ? GetAttackRight() : GetAttackLeft();
}

vector<ALLEGRO_BITMAP*>& Player::GetRunRightArray() {
	return holdingSword ? runRightSwordArray : runRightArray;
}
vector<ALLEGRO_BITMAP*>& Player::GetRunLeftArray() {
	return holdingSword ? runLeftSwordArray : runLeftArray;
}

vector<ALLEGRO_BITMAP*>& Player::GetIdleRightArray() {
	return holdingSword ? idleRightSwordArray : idleRightArray;
}
vector<ALLEGRO_BITMAP*>& Player::GetIdleLeftArray() {
	return holdingSword ? idleLeftSwordArray : idleLeftArray;
}

vector<vector<ALLEGRO_BITMAP*>>& Player::GetAttackRightArray() {
	return holdingSword ? attackRightSwordArray : punchRight;
}
vector<vector<ALLEGRO_BITMAP*>>& Player::GetAttackLeftArray() {
	return holdingSword ? attackLeftSwordArray : punchLeft;
}

vector<ALLEGRO_BITMAP*>& Player::GetDamageRightArray() {
	return damageRight;
}
vector<ALLEGRO_BITMAP*>& Player::GetDamageLeftArray() {
	return damageLeft;
}

vector<ALLEGRO_BITMAP*>& Player::GetJumpRightArray() {
	return holdingSword ? jumpRightSwordArray : jumpRightArray;
}
vector<ALLEGRO_BITMAP*>& Player::GetJumpLeftArray() {
	return holdingSword ? jumpLeftSwordArray : jumpLeftArray;
}

vector<ALLEGRO_BITMAP*>& Player::GetFallRightArray() {
	return fallRightArray;

}
vector<ALLEGRO_BITMAP*>& Player::GallLeftArray() {
	return fallLeftArray;
}

bool Player::GetHasSword() const {
	return holdingSword;
}
bool Player::GetIsUnsheathingSword() const {
	return unsheathingSword;
}
void Player::ReceiveSword() {
	holdingSword = true;
	unsheathingSword = true;
}

void Player::UnsheathSword(double& time) {
	playerSprite = GetUnsheathArray()[unsheathSwordIndex];
	if (al_get_time() - time > unsheathSwordRate) {
		
		unsheathSwordIndex++;
		if (unsheathSwordIndex >= GetUnsheathArray().size()) {
			unsheathingSword = false;
		}
		time = al_get_time();
	}
}
vector<ALLEGRO_BITMAP*>& Player::GetUnsheathArray() {
	return isFacingRight ? unsheathSwordRightArray : unsheathSwordLeftArray;
}
