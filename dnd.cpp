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
void rollDice();
void saveData(int, string);
void getHistory();
int promptUser();
string calculateModifiers(int);

const char* FILE_PATH = "./json/5e-SRD-Monsters.json.txt";

int main(){
	//Main handles the states that the program is in
	//The states are decided by the response in promptUser()
	int state;
	while((state = promptUser()) != 6) {
		switch(state){
			case 1:
				monsterSearch();
				break;
			case 4:
				rollDice();
				break;
			case 5:
				getHistory();
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
	ifstream monsterlist(FILE_PATH);
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
	cout << "   4. Dice Roller " << endl;
	cout << "   5. View Dice History " << endl;
	cout << "   6. Exit" << endl;
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

void saveDice(int roll, string die) {
	ofstream history;
	history.open("dice-history.txt", fstream::app);
	history << die;
	history << ": ";
	history << roll << endl;
	history.close();
}

void rollDice() {
	string die;
	bool again = true;
	do {
		cout << "Enter a die to roll: ";
		cin >> die;
		if (die == "EXIT" || die == "exit") {
			again = false;
		} else {
			Dice d(die);
			int result = d.roll();
			if (result != 0) {
				cout << "Your roll was: " << result << endl;
			} if (result != 0) {
				saveDice(result, die);
			}
		} cout << endl << "Type EXIT to return to menu." << endl;
	} while (again);
}

void getHistory() {
	cout << "\nROLL HISTORY:\n";
	string str;
	vector<string> data;
	ifstream history("dice-history.txt");
	while (getline(history, str)) {
		data.push_back(str);
	}
	for (size_t i; i < data.size(); i++) {
		if (data[0] == "") {
			cout << "NO ROLL HISTORY.\n";
		} else {
		cout << data[i] << endl;
	}
	}cout << endl;
}










//
