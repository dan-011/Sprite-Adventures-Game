#include "NPCManager.h"
SeekerFactory::SeekerFactory() {}
SeekerFactory::~SeekerFactory() {}
NonPlayerCharacter* SeekerFactory::CreateCharacter(Player& player) {
	return new SeekerNPC(player);
}

SproutFactory::SproutFactory() {}
SproutFactory::~SproutFactory() {}
NonPlayerCharacter* SproutFactory::CreateCharacter(Player& player) {
	return new SproutNPC(player);
}

LighterFactory::LighterFactory() {}
LighterFactory::~LighterFactory() {}
NonPlayerCharacter* LighterFactory::CreateCharacter(Player& player) {
	return new LighterNPC(player);
}

GuardianFactory::GuardianFactory() {}
GuardianFactory::~GuardianFactory() {}
NonPlayerCharacter* GuardianFactory::CreateCharacter(Player& player) {
	return new GuardianNPC(player);
}


NPCManager::NPCManager(Player& plyr) : factoryIndex(0), factoryBound(1), player(plyr) {
	factories.push_back(new SproutFactory);
	factories.push_back(new GuardianFactory);
	factories.push_back(new SeekerFactory);
	factories.push_back(new LighterFactory);
}
NPCManager::~NPCManager() {
	for (auto factory : factories) {
		delete factory;
	}
}
NonPlayerCharacter* NPCManager::GenerateRandomNPC() {
	srand(al_get_time());
	factoryIndex = rand() % factoryBound;
	return GenerateSelectedNPC();
}
NonPlayerCharacter* NPCManager::GenerateSelectedNPC() {
	return factories.at(factoryIndex)->CreateCharacter(player);
}
void NPCManager::SetMaxVillain(int bound) {
	factoryBound = bound;
}
