#include "Monster.h"
#include "Dice.h"
#include <string>

Monster::Monster(){}
Monster::~Monster(){
	for (size_t i = 0; i < actions.size(); i++)
	{
		delete(actions[i]);
	}
}

Monster::Monster(const json & monsterData ){
	name = monsterData["name"];
	type = monsterData["type"];
	alignment = monsterData["alignment"];
	armor_class = monsterData["armor_class"];
	hit_dice = Dice(monsterData["hit_dice"].get<std::string>());
	strength = monsterData["strength"];
	dexterity = monsterData["dexterity"];
	constitution = monsterData["constitution"];
	intelligence = monsterData["intelligence"];
	wisdom = monsterData["wisdom"];
	charisma = monsterData["charisma"];
	hit_points = this->hit_dice.roll();

	actions = parseActions(monsterData);
	challenge_rating = parseChallengeRating(monsterData["challenge_rating"].get<std::string>());
	alive = true;
}

Monster& Monster::operator=(const Monster &monster){
	
	name = monster.name;
	type = monster.type;
	alignment = monster.alignment;
	armor_class = monster.armor_class;
	hit_dice = monster.hit_dice;
	strength = monster.strength;
	dexterity = monster.dexterity;
	constitution = monster.constitution;
	intelligence = monster.intelligence;
	wisdom = monster.wisdom;
	charisma = monster.charisma;
	hit_points = monster.hit_points;
	challenge_rating = monster.challenge_rating;
	alive = monster.alive;
	for (size_t i = 0; i < monster.actions.size(); i++)
	{
		actions.push_back(new Ability(*(monster.actions[i])));
	}

	return *this;
}

std::vector<Ability*> Monster::parseActions(const json & monsterData){
	json actions = monsterData["actions"];
	Ability* currentAbility;
	std::vector<Ability*> abilityContainer;
	for (size_t i = 0; i < actions.size(); i++)
	{
		currentAbility = new Ability(actions[i]);
		abilityContainer.push_back(currentAbility);
	}

	return abilityContainer;
}

double Monster::parseChallengeRating(std::string CRS){
	size_t slash = CRS.find("/");
	if(slash == std::string::npos) {
		return std::stod(CRS);
	}
	double numerator = std::stod(CRS.substr(0,slash));
	double denominator = std::stod(CRS.substr(slash + 1));
	return numerator / denominator;
}