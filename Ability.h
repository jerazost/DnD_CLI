#include <string>
#include "Dice.h"

#include "lib/json.hpp"

#ifndef ABILITY_H
#define ABILITY_H
using json = nlohmann::json;

class Ability{
public:
	Ability();
	~Ability();
	Ability(const json &);

	std::string name;
	std::string description;
	int attack_bonus;
	int damage_bonus;
	Dice damage_dice;
};
#endif