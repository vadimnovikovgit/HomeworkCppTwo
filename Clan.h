#pragma once
#include "Player.h"
#include <vector>
struct Clan {
	int clanID{};
	std::vector<Player> members;
	void addMember(const Player& member);
	bool removeMember(const std::string& name);
	bool fightResult(); //true if there players to fight; false if all dead
	bool winner{ false };
};