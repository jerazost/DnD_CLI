#include "Ability.h"
#include "Dice.h"

Ability::Ability(const json & jsonAbility){
	name = jsonAbility["name"];
	attack_bonus = jsonAbility["attack_bonus"];
	try{
		damage_dice = Dice(jsonAbility.at("damage_dice").get<std::string>());
		damage_bonus = jsonAbility["damage_bonus"];
	}catch(std::out_of_range){
		description = jsonAbility["desc"];
	}
}

Ability::Ability(){

}
Ability::~Ability(){

}
