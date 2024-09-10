#include "Clan.h"

void Clan::addMember(const Player& member)
{
	members.push_back(member);
}

bool Clan::removeMember(const std::string& name)
{
	auto it{ std::find_if(members.begin(), members.end(), [name](const Player& pl) {
		return pl.name == name; }) };

	if (it == members.end()) {
		return false;
	}
	members.erase(it);
	return true;
}

bool Clan::fightResult()
{
	for (auto& player : members) {
		if (player.health <= 0) {
			removeMember(player.name);
		}
	}
	if (members.size() == 0) {
		return false;
	}
	winner = true;
	return true;
}
