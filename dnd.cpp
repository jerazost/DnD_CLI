#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

//Ext json parsing library
#include "lib/json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;

void findInJson(const string & name, const json & object, json &);
void printMonsterData(const json & monsterData);

int main(){
	json jsonList;
	json monster;
	ifstream monsterlist("json/5e-SRD-Monsters.json.txt");
	monsterlist >> jsonList;
	string monsterSearch;

	cout << "Give me the name of a monster" << endl;
	cin >> monsterSearch;

	findInJson(monsterSearch, jsonList, monster);
	printMonsterData(monster);

	return 0;
}

void findInJson(const string & name, const json & object, json & monster){
	for (int i = 0; i < object.size() - 1; i++)
	{
		if(object[i]["name"] == name){
			monster = object[i];
		}
	}
}

void printMonsterData(const json & monsterData){
	json temp;

	//Actions
	cout << "Actions:" << endl;
	json actions = monsterData["actions"];
	for (int i = 0; i < actions.size(); i++)
	{
		temp = actions[i];
		cout << "\t" << temp["name"] << ": Hit Bonus: " 
		<< "+ " << temp["attack_bonus"]
		<< "Damage: " << temp["damage_dice"]
		<< " + " << temp["damage_bonus"] << endl;
	}
}

void promptUser(){
	cout << "Welcome to DM CLI Tools" << endl;
	cout << ""
}



