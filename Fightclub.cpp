#include <iostream>
#include <random>
#include <algorithm>
#include "Clan.h"
#include "Fightclub.h"

void Lobby::commandParser(int comand) {
	switch (comand) {
	case 0:
		pushMember();
		break;
	case 1:
		removePlayer();
		break;
	case 2:
		startFight();
	}
}

void Lobby::pushMember()
{
	Player newPlayer;
	std::cout << "Enter player's clanID: ";
	std::cin >> newPlayer.clanID;

	auto clan{ findClan(newPlayer.clanID) };
	if (clan == std::nullopt) {
		std::cout << "Clan Id not found!\n";
		return;
	}

	std::cout << "Enter player's name: ";
	std::cin >> newPlayer.name;
	std::cout << "\nEnter players health: ";
	std::cin >> newPlayer.health;
	std::cout << "\nEnter players damage: ";
	std::cin >> newPlayer.damage;
	clan.value()->addMember(newPlayer);

}

void Lobby::removePlayer()
{
	std::cout << "Enter clan ID: ";
	int id{};
	std::cin >> id;
	auto clan{ findClan(id) };
	if (clan == std::nullopt) {
		std::cout << "Clan Id not found!\n";
		return;
	}
	std::cout << "\nEnter player's name to remove: ";
	std::string name;
	std::cin >> name;
	if (!clan.value()->removeMember(name)) {
		std::cout << "\nPlayer not found!\n";
		return;
	}
	std::cout << "\nPlayer removed\n";
}


std::optional<Clan*> Lobby::findClan(int id)
{
	auto it{ std::find_if(fighters.begin(), fighters.end(), [id](const Clan& cl) {
		return cl.clanID == id; }) };

	if (it == fighters.end()) {
		return std::nullopt;
	}

	return std::make_optional(&(*it));
}

void Lobby::startFight()
{
	Clan& first{ fighters[0] };
	Clan& second{ fighters[1] };
	while (true) {
		Player& leftSide{ first.members[getRandomNumber(0,first.members.size() - 1)] };
		Player& rightSide{ second.members[getRandomNumber(0,second.members.size() - 1)] };
		leftSide.health -= rightSide.damage;
		std::cout << "Fighter from clan " << first.clanID << " named " << leftSide.name << " damaged " << rightSide.name << " hp left: " << rightSide.health << std::endl;
		rightSide.health -= leftSide.damage;
		std::cout << "Fighter from clan " << second.clanID << " named " << rightSide.name << " damaged " << leftSide.name << " hp left: " << leftSide.health << std::endl;
		if (!first.fightResult() || !second.fightResult()) {
			break;
		}
	}
	if (first.winner) {
		std::cout << "Clan " << first.clanID << " won the battle\n";
		return;
	}
	if (second.winner) {
		std::cout << "Clan " << second.clanID << " won the battle\n";
		return;
	}
}

int Lobby::getRandomNumber(int min, int max)
{
	std::random_device rd;
	std::mt19937 rng{ rd() };
	std::uniform_int_distribution<int> uid(min, max);
	return uid(rng);
}

