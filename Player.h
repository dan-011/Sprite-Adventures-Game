#ifndef __PLAYER_H
#define __PLAYER_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <vector>

using namespace std;
enum Movement {
	RunRight = 0,
	RunLeft = 1,
	JumpRight = 2,
	JumpLeft = 3,
	FallRight = 4,
	FallLeft = 5,
	SmrsltRight = 6,
	SmrsltLeft = 7,
	IdleRight = 8,
	IdleLeft = 9
};

class Player {
private:
#pragma region Position
	int lives = 25;
	int score = 0;
	int xpos;
	int ypos;
	int weaponIndex = 0;
	bool canExit = false;

	int ground = 310;

	const int player_width = 100;
	const int player_height = 74;
#pragma endregion

#pragma region Movement
	int runLeftIndex;
	int runRightIndex;
	int idleIndex;
	int jumpIndex;
	int fallIndex;
	int smrsltIndex;
	int attackPwr = 5;

	bool isFacingRight;
	bool isRunningRight;
	bool isRunningLeft;

	const int runArraySize = 6;
	const int idleArraySize = 4;
	const int jumpArraySize = 4;
	const int smrsltArraySize = 4;
	const int fallArraySize = 2;

	const int run_distance = 12;
	const int jump_x_distance = 5;
	const double run_time = 0.07;
	const double idle_time = 0.15;
	const double jump_time = 0.03;// 0.125;
	const double fall_time = 0.025;

	const vector<int> jump_heights = {8, 8, 8, 8, 1, 1, 1, 1};//{ 20, 10, 5, 1 };
	const vector<int> fall_heights = {4, 4, 4, 4, 5, 5, 5, 5 };//{ 9, 9, 9, 5, 4, 3}; // 36

	bool isJumping;
	bool isOnPlatform; // this will be true when the character is in contact with a platform

	int lastKeyPressed;

	vector<ALLEGRO_BITMAP*> runRightArray;
	vector<ALLEGRO_BITMAP*> runLeftArray;

	vector<ALLEGRO_BITMAP*> idleRightArray;
	vector<ALLEGRO_BITMAP*> idleLeftArray;

	vector<ALLEGRO_BITMAP*> jumpRightArray;
	vector<ALLEGRO_BITMAP*> jumpLeftArray;

	vector<ALLEGRO_BITMAP*> smrsltRightArray;
	vector<ALLEGRO_BITMAP*> smrsltLeftArray;

	vector<ALLEGRO_BITMAP*> fallRightArray;
	vector<ALLEGRO_BITMAP*> fallLeftArray;

	bool isAttacking = false;

	int punchType = 0;
	int punchIndex = 0;
	const double punchTime = .1;

	vector<ALLEGRO_BITMAP*> punchRight1;
	vector<ALLEGRO_BITMAP*> punchRight2;
	vector<ALLEGRO_BITMAP*> punchRight3;

	vector<vector<ALLEGRO_BITMAP*>> punchRight;

	vector<ALLEGRO_BITMAP*> punchLeft1;
	vector<ALLEGRO_BITMAP*> punchLeft2;
	vector<ALLEGRO_BITMAP*> punchLeft3;

	vector<vector<ALLEGRO_BITMAP*>> punchLeft;

	bool takingDamage = false;

	int damageIndex = 0;
	const double damageTime = .1;

	vector<ALLEGRO_BITMAP*> damageRight;
	vector<ALLEGRO_BITMAP*> damageLeft;

	bool holdingSword = false;
	bool unsheathingSword = false;

	ALLEGRO_BITMAP* playerSprite;
#pragma endregion
	void Move(double& time, Movement movement);
	void Idle(double& time);
	void Punch(double& time);
	void Damage(double& time);
	void UnsheathSword(double& time);

	void SetRunRight();
	void SetRunLeft();
	void SetIdle();

	ALLEGRO_BITMAP* GetRunRight() const;
	ALLEGRO_BITMAP* GetRunLeft() const;
	ALLEGRO_BITMAP* GetJumpRight() const;
	ALLEGRO_BITMAP* GetJumpLeft() const;
	ALLEGRO_BITMAP* GetFallRight() const;
	ALLEGRO_BITMAP* GetFallLeft() const;
	ALLEGRO_BITMAP* GetIdleRight() const;
	ALLEGRO_BITMAP* GetIdleLeft() const;
	ALLEGRO_BITMAP* GetDamageRight() const;
	ALLEGRO_BITMAP* GetDamageLeft() const;
	ALLEGRO_BITMAP* GetAttackRight() const;
	ALLEGRO_BITMAP* GetAttackLeft() const;

	ALLEGRO_BITMAP* GetRun() const;
	ALLEGRO_BITMAP* GetJump() const;
	ALLEGRO_BITMAP* GetFall() const;
	ALLEGRO_BITMAP* GetIdle() const;
	ALLEGRO_BITMAP* GetIdle(int index) const;
	ALLEGRO_BITMAP* GetDamage() const;
	ALLEGRO_BITMAP* GetAttack() const;

	vector<ALLEGRO_BITMAP*>& GetRunRightArray();
	vector<ALLEGRO_BITMAP*>& GetRunLeftArray();

	vector<ALLEGRO_BITMAP*>& GetIdleRightArray();
	vector<ALLEGRO_BITMAP*>& GetIdleLeftArray();

	vector<vector<ALLEGRO_BITMAP*>>& GetAttackRightArray();
	vector<vector<ALLEGRO_BITMAP*>>& GetAttackLeftArray();

	vector<ALLEGRO_BITMAP*>& GetDamageRightArray();
	vector<ALLEGRO_BITMAP*>& GetDamageLeftArray();

	vector<ALLEGRO_BITMAP*>& GetJumpRightArray();
	vector<ALLEGRO_BITMAP*>& GetJumpLeftArray();

	vector<ALLEGRO_BITMAP*>& GetFallRightArray();
	vector<ALLEGRO_BITMAP*>& GallLeftArray();
	
	vector<ALLEGRO_BITMAP*>& GetUnsheathArray();

	//void MovementBoundsCheck(int background_width);

	vector<ALLEGRO_BITMAP*> runRightSwordArray;
	vector<ALLEGRO_BITMAP*> runLeftSwordArray;

	vector<ALLEGRO_BITMAP*> idleRightSwordArray;
	vector<ALLEGRO_BITMAP*> idleLeftSwordArray;

	vector<vector<ALLEGRO_BITMAP*>> attackRightSwordArray;
	vector<vector<ALLEGRO_BITMAP*>> attackLeftSwordArray;

	// vector<ALLEGRO_BITMAP*> damageRightSwordArray;
	// vector<ALLEGRO_BITMAP*> damageLeftSwordArray;

	vector<ALLEGRO_BITMAP*> jumpRightSwordArray;
	vector<ALLEGRO_BITMAP*> jumpLeftSwordArray;

	// vector<ALLEGRO_BITMAP*> fallRightSwordArray;
	// vector<ALLEGRO_BITMAP*> fallLeftSwordArray;

	int unsheathSwordIndex = 0;
	double unsheathSwordRate = .1;

	vector<ALLEGRO_BITMAP*> unsheathSwordRightArray;
	vector<ALLEGRO_BITMAP*> unsheathSwordLeftArray;

	void TimeMovement(double& time, int& xIndex, int& yIndex, double timeWindow, bool movingX, bool movingY, int xOffset = 0, int yOffset = 0);

public:
#pragma region Construction and Destruction
	Player() :xpos(10), ypos(310), lastKeyPressed(0), runLeftIndex(0), runRightIndex(0), idleIndex(0), isFacingRight(true), isRunningRight(false), isRunningLeft(false), isJumping(false), isOnPlatform(true), jumpIndex(0), fallIndex(0), smrsltIndex(0) {
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight0.png"));
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight1.png"));
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight2.png"));
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight3.png"));
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight4.png"));
		runRightArray.push_back(al_load_bitmap("Assets/Animations/Run/runRight5.png"));

		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft0.png"));
		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft1.png"));
		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft2.png"));
		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft3.png"));
		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft4.png"));
		runLeftArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeft5.png"));

		idleRightArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRight0.png"));
		idleRightArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRight1.png"));
		idleRightArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRight2.png"));
		idleRightArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRight3.png"));

		idleLeftArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeft0.png"));
		idleLeftArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeft1.png"));
		idleLeftArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeft2.png"));
		idleLeftArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeft3.png"));

		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight0.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight0.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight1.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight1.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight2.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight2.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight3.png"));
		jumpRightArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpRight3.png"));


		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft0.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft0.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft1.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft1.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft2.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft2.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft3.png"));
		jumpLeftArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpLeft3.png"));


		smrsltRightArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltRight0.png"));
		smrsltRightArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltRight1.png"));
		smrsltRightArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltRight2.png"));
		smrsltRightArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltRight3.png"));


		smrsltLeftArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltLeft0.png"));
		smrsltLeftArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltLeft1.png"));
		smrsltLeftArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltLeft2.png"));
		smrsltLeftArray.push_back(al_load_bitmap("Assets/Animations/Smrslt/smrsltLeft3.png"));

		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight0.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight0.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight0.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight0.png")); // DELETE OR FIND SOMETHING ELSE TO DO WITH THIS
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight1.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight1.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight1.png"));
		fallRightArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallRight1.png"));


		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft0.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft0.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft0.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft0.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft1.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft1.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft1.png"));
		fallLeftArray.push_back(al_load_bitmap("Assets/Animations/Fall/fallLeft1.png"));

		punchRight1.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight11.png"));
		punchRight1.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight12.png"));
		punchRight1.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight13.png"));
		punchRight1.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight14.png"));

		punchRight2.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight21.png"));
		punchRight2.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight22.png"));
		punchRight2.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight23.png"));
		punchRight2.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight24.png"));

		punchRight3.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight31.png"));
		punchRight3.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight32.png"));
		punchRight3.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight33.png"));
		punchRight3.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight34.png"));
		punchRight3.push_back(al_load_bitmap("Assets/Animations/Punch/punchRight35.png"));

		punchRight = { punchRight1, punchRight2, punchRight3 };

		punchLeft1.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft11.png"));
		punchLeft1.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft12.png"));
		punchLeft1.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft13.png"));
		punchLeft1.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft14.png"));

		punchLeft2.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft21.png"));
		punchLeft2.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft22.png"));
		punchLeft2.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft23.png"));
		punchLeft2.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft24.png"));

		punchLeft3.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft31.png"));
		punchLeft3.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft32.png"));
		punchLeft3.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft33.png"));
		punchLeft3.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft34.png"));
		punchLeft3.push_back(al_load_bitmap("Assets/Animations/Punch/punchLeft35.png"));

		punchLeft = { punchLeft1, punchLeft2, punchLeft3 };

		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight0.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight1.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight2.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight3.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight4.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight5.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight6.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight7.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight8.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight9.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight10.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight11.png"));
		damageRight.push_back(al_load_bitmap("Assets/Animations/Damage/damageRight12.png"));

		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft0.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft1.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft2.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft3.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft4.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft5.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft6.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft7.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft8.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft9.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft10.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft11.png"));
		damageLeft.push_back(al_load_bitmap("Assets/Animations/Damage/damageLeft12.png"));

		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword0.png"));
		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword1.png"));
		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword2.png"));
		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword3.png"));
		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword4.png"));
		runRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runRightSword5.png"));

		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword0.png"));
		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword1.png"));
		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword2.png"));
		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword3.png"));
		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword4.png"));
		runLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Run/runLeftSword5.png"));

		idleRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRightSword0.png"));
		idleRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRightSword1.png"));
		idleRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRightSword2.png"));
		idleRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleRightSword3.png"));

		idleLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeftSword0.png"));
		idleLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeftSword1.png"));
		idleLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeftSword2.png"));
		idleLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Idle/idleLeftSword3.png"));

		vector<ALLEGRO_BITMAP*> attackRightSwordArray1;
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight10.png"));
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight11.png"));
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight12.png"));
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight13.png"));
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight14.png"));
		attackRightSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight15.png"));

		vector<ALLEGRO_BITMAP*> attackRightSwordArray2;
		attackRightSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight20.png"));
		attackRightSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight21.png"));
		attackRightSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight22.png"));
		attackRightSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight23.png"));

		vector<ALLEGRO_BITMAP*> attackRightSwordArray3;
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight30.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight31.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight32.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight33.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight34.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight35.png"));
		attackRightSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackRight36.png"));

		attackRightSwordArray = { attackRightSwordArray1, attackRightSwordArray2, attackRightSwordArray3 };

		vector<ALLEGRO_BITMAP*> attackLeftSwordArray1;
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft10.png"));
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft11.png"));
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft12.png"));
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft13.png"));
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft14.png"));
		attackLeftSwordArray1.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft15.png"));

		vector<ALLEGRO_BITMAP*> attackLeftSwordArray2;
		attackLeftSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft20.png"));
		attackLeftSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft21.png"));
		attackLeftSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft22.png"));
		attackLeftSwordArray2.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft23.png"));

		vector<ALLEGRO_BITMAP*> attackLeftSwordArray3;
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft30.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft31.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft32.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft33.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft34.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft35.png"));
		attackLeftSwordArray3.push_back(al_load_bitmap("Assets/Animations/Punch/attackLeft36.png"));

		attackLeftSwordArray = { attackLeftSwordArray1, attackLeftSwordArray2, attackLeftSwordArray3 };

		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight0.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight0.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight1.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight1.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight2.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight2.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight3.png"));
		jumpRightSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordRight3.png"));

		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft0.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft0.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft1.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft1.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft2.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft2.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft3.png"));
		jumpLeftSwordArray.push_back(al_load_bitmap("Assets/Animations/Jump/jumpSwordLeft3.png"));

		unsheathSwordRightArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordRight0.png"));
		unsheathSwordRightArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordRight1.png"));
		unsheathSwordRightArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordRight2.png"));
		unsheathSwordRightArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordRight3.png"));

		unsheathSwordLeftArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordLeft0.png"));
		unsheathSwordLeftArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordLeft1.png"));
		unsheathSwordLeftArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordLeft2.png"));
		unsheathSwordLeftArray.push_back(al_load_bitmap("Assets/Animations/Unsheath/unsheathSwordLeft3.png"));

		playerSprite = idleRightArray[0];
	};

	~Player() {
		for (int i = 0; i < runArraySize; i++) {
			al_destroy_bitmap(runRightArray[i]); // destroy the bitmap to prevent memory leaks
			al_destroy_bitmap(runLeftArray[i]);
			al_destroy_bitmap(runRightSwordArray[i]);
			al_destroy_bitmap(runLeftSwordArray[i]);
		}
		for (int i = 0; i < idleArraySize; i++) {
			al_destroy_bitmap(idleRightArray[i]);
			al_destroy_bitmap(idleLeftArray[i]);
			al_destroy_bitmap(idleRightSwordArray[i]);
			al_destroy_bitmap(idleLeftSwordArray[i]);
		}
		for (int i = 0; i < jumpArraySize; i++) {
			al_destroy_bitmap(jumpRightArray[i]);
			al_destroy_bitmap(jumpLeftArray[i]);
			al_destroy_bitmap(jumpRightSwordArray[i]);
			al_destroy_bitmap(jumpLeftSwordArray[i]);
		}
		for (int i = 0; i < smrsltArraySize; i++) {
			al_destroy_bitmap(smrsltRightArray[i]);
			al_destroy_bitmap(smrsltLeftArray[i]);
		}
		for (int i = 0; i < fallArraySize; i++) {
			al_destroy_bitmap(fallRightArray[i]);
			al_destroy_bitmap(fallLeftArray[i]);
		}
		for (int i = 0; i < 3; i++) {
			
			for (int j = 0; j < punchRight[i].size(); j++) {
				al_destroy_bitmap(punchRight[i][j]);
				al_destroy_bitmap(punchLeft[i][j]);
			}
			for (int j = 0; j < attackRightSwordArray[i].size(); j++) {
				al_destroy_bitmap(attackRightSwordArray[i][j]);
				al_destroy_bitmap(attackLeftSwordArray[i][j]);
			}
		}
		for (int i = 0; i < damageRight.size(); i++) {
			al_destroy_bitmap(damageRight[i]);
			al_destroy_bitmap(damageLeft[i]);
		}
		for (int i = 0; i < unsheathSwordRightArray.size(); i++) {
			al_destroy_bitmap(unsheathSwordLeftArray[i]);
			al_destroy_bitmap(unsheathSwordRightArray[i]);
		}
	}
#pragma endregion

#pragma region Accessors
	ALLEGRO_BITMAP* GetSprite();
	int GetLives() const;
	int GetXPos();
	int GetYPos();
	bool GetIsTakingDamage() const;
	void TakeDamage(int amount);
	int GetScore() const;
	void AddToScore(int amount);
	int GetWeaponIndex() const;
	int GetAttackDamage() const;
	bool GetIsOnPlat(); // delete later
	void MovementBoundsCheck(int background_width); // verify that it is ok to move back to private
	bool GetIsFacingRight() const;
	bool CanExit() const;
	bool GetIsJumping() const;
	bool GetHasSword() const;
	bool GetIsUnsheathingSword() const;
	void ReceiveSword();
#pragma endregion

#pragma region Move
	void Movements(double& time, ALLEGRO_KEYBOARD_STATE* &keyState, int background_width);
	bool GetIsAttacking() const;
#pragma endregion
	
};
#endif
