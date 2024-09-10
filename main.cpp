#include <iostream>
#include "Fightclub.h"

int main() {
	Clan first{};
	first.clanID = 0;
	Clan second{};
	second.clanID = 1;
	Lobby lobby{};
	lobby.fighters.push_back(first);
	lobby.fighters.push_back(second);
	while (true) {
		int command{};
		std::cout << "Enter comand: ";
		std::cin >> command;
		lobby.commandParser(command);
	}
	
}