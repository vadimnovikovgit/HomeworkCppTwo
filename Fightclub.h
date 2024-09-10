#pragma once
#include <optional>
#include "Clan.h"

struct Lobby {
	std::vector<Clan> fighters;

	void commandParser(int comand);
	void pushMember();
	void removePlayer();
	void startFight();
	int getRandomNumber(int min, int max);
	std::optional<Clan*> findClan(int id);
};