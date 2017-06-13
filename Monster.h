#include <string>
#include <vector>
#include "Ability.h"
#include "Dice.h"
#include "lib/json.hpp"

#ifndef MONSTER_H
#define MONSTER_H

using json = nlohmann::json;

class Monster{

public:
	Monster();
	Monster(const json &);
	~Monster();
	Monster & operator=(const Monster &);
	std::string name;
	std::string type;
	std::string alignment;
	unsigned int armor_class;
	int hit_points;
	Dice hit_dice;
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;
	bool alive;

	std::vector<Ability*> actions;

	double challenge_rating;

private:
	std::vector<Ability*> parseActions(const json &);
	double parseChallengeRating(std::string);
};

#endif