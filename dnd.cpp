#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <fstream>
#include "Dice.h"
#include "Ability.h"
#include "Monster.h"

//For case insensitive compares
#include "lib/utility.cpp"

//Ext json parsing library
#include "lib/json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;

void findInJson(const string &, const json &, Monster &);
void printMonsterData(Monster &);
void monsterSearch();
int promptUser();
string calculateModifiers(int);

const char* FILE_PATH = "/home/jsteinberg/Documents/Projects/C++/dnd/";

int main(){
	//Main handles the states that the program is in
	//The states are decided by the response in promptUser()
	int state;
	while((state = promptUser()) != 4) {
		switch(state){
			case 1: 
				monsterSearch();
				break;
			default:
				cout << "Case " << state << " not recongnized" << endl;
		}
	}
	return 0;
}

void findInJson(const string & name, const json & object, Monster & monster){

	for (size_t i = 0; i < object.size() - 1; i++){
		if(icompare(object[i]["name"],name)){
			monster = Monster(object[i]);
			break;
		}
	}
}


void printMonsterData(Monster & monster){
	Ability* temp;

	//Actions
	if(monster.name == "") {
		throw "No result for argument";
	}

	cout << " HP: " << monster.hit_points
		<< " AC: " << monster.armor_class 
		<< " CR: " << monster.challenge_rating << endl
		<< " STR: " << monster.strength 
			<< calculateModifiers(monster.strength) 
		<< " DEX: " << monster.dexterity 
			<< calculateModifiers(monster.dexterity) 
		<< " CON: " << monster.constitution
			<< calculateModifiers(monster.constitution) 
		<< " INT: " << monster.intelligence 
			<< calculateModifiers(monster.intelligence) 
		<< " WIS: " << monster.wisdom
			<< calculateModifiers(monster.wisdom) 
		<< " CHA: " << monster.charisma
			<< calculateModifiers(monster.charisma)
		<< endl;

	cout << "  Actions    " << endl;
	for (size_t i = 0; i < monster.actions.size(); i++)
	{
		temp = monster.actions[i];
		if (temp->damage_dice.name == "") //The ability is not an attack
		{
			cout << "  " << temp->name << ": "
				<< temp->description << endl << endl;
		}else{	//The ability is an attack
			cout << "  " << temp->name << ": Hit Bonus: " 
				<< "+ " << temp->attack_bonus
				<< " Damage: " << temp->damage_dice.name
				<< " + " << temp->damage_bonus << endl;
		}
	}
	cout << endl;
}

void monsterSearch(){

	 //The Monster object in JSON
	json jsonList; //The list of all monsters from the external file
	ifstream monsterlist("/home/jsteinberg/Documents/Projects/C++/dnd/json/5e-SRD-Monsters.json.txt");
	if(!monsterlist) {
		ofstream out("testdir.txt");
		out << "test";
	}
	monsterlist >> jsonList;
	string monsterSearch;
	bool again = true; 
	do{
		Monster monster;
		cout  << endl << "Give me the name of a monster" << endl << endl;
		getline(cin, monsterSearch);
		try{

			if(icompare(monsterSearch, "exit")){
				again = false;
			}else{
				findInJson(monsterSearch, jsonList, monster);
				printMonsterData(monster);
				cout << endl << "Type EXIT to return to menu." << endl;
			}
		}
		catch(const char*){
			cout << "Could not find " << monsterSearch << " try again." << endl;
			again = true;
		}
	}while (again);

}

int promptUser(){
	
	int response;

	cout << " Welcome to DM CLI Tools" << endl;
	cout << "   1. Monster Stats" << endl;
	cout << "   2. Encounters " << endl;
	cout << "   3. Party Manager" << endl;
	cout << "   4. Exit" << endl;
	cout << " ";

	cin >> response;
	cin.ignore();

	return response;
}
string calculateModifiers(int ability_score){
	stringstream stringModifier;
	int mod = (ability_score - 10) / 2;
	if(mod >= 0){
		stringModifier << "(+" << mod << ")"; 
	}else{
		stringModifier << "(" << mod << ")";
	}
	return stringModifier.str();
}