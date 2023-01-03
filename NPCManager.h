#ifndef __NPCMANAGER_H
#define __NPCMANAGER_H

#include "NonPlayerCharacter.h"
#include <vector>
#include<cstdlib>

using namespace std;

class AbstractNPCFactory {
public:
	virtual ~AbstractNPCFactory() {}
	virtual NonPlayerCharacter* CreateCharacter(Player& player) = 0;
};

class SeekerFactory : public AbstractNPCFactory {
public:
	SeekerFactory();
	virtual ~SeekerFactory();
	virtual NonPlayerCharacter* CreateCharacter(Player& player);
};

class SproutFactory : public AbstractNPCFactory {
public:
	SproutFactory();
	virtual ~SproutFactory();
	virtual NonPlayerCharacter* CreateCharacter(Player& player);
};

class LighterFactory : public AbstractNPCFactory {
public:
	LighterFactory();
	virtual ~LighterFactory();
	virtual NonPlayerCharacter* CreateCharacter(Player& player);
};

class GuardianFactory : public AbstractNPCFactory {
public:
	GuardianFactory();
	virtual ~GuardianFactory();
	virtual NonPlayerCharacter* CreateCharacter(Player& player);
};

class NPCManager {
public:
	NPCManager(Player& plyr);
	~NPCManager();
	NonPlayerCharacter* GenerateRandomNPC();
	NonPlayerCharacter* GenerateSelectedNPC();
	void SetMaxVillain(int bound);
private:
	int factoryIndex;
	int factoryBound;
	vector<AbstractNPCFactory*> factories;
	Player& player;
};

#endif
