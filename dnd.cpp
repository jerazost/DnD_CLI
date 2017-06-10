#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>

//For case insensitive compares
#include "lib/utility.cpp"

//Ext json parsing library
#include "lib/json.hpp"

// for convenience
using json = nlohmann::json;
using namespace std;

void findInJson(const string & name, const json & object, json &);
void printMonsterData(const json & monsterData);
void monsterSearch();
int promptUser();

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

void findInJson(const string & name, const json & object, json & monster){

	for (int i = 0; i < object.size() - 1; i++){
		if(icompare(object[i]["name"],name)){
			monster = object[i];
		}
	}
}

void printMonsterData(const json & monsterData){
	json temp;

	//Actions
	if(monsterData.is_null()) {
		throw "No result for argument";
	}

	cout << " HP: " << monsterData["hit_points"]
		<< " Armor Class: " << monsterData["armor_class"] << endl
		<< " STR: " << monsterData["strength"]
		<< " DEX: " << monsterData["dexterity"]
		<< " CON: " << monsterData["constitution"]
		<< " INT: " << monsterData["intelligence"]
		<< " WIS: " << monsterData["wisdom"]
		<< " CHA: " << monsterData["charisma"] << endl;

	cout << "  Actions    " << endl;
	json actions = monsterData["actions"];
	for (int i = 0; i < actions.size(); i++)
	{
		temp = actions[i];
		if (temp["damage_dice"].is_null()) //The ability is not an attack
		{
			cout << "  " << temp["name"] << ": "
				<< temp["desc"] << endl << endl;
		}else{	//The ability is an attack
			cout << "  " << temp["name"] << ": Hit Bonus: " 
				<< "+ " << temp["attack_bonus"]
				<< " Damage: " << temp["damage_dice"]
				<< " + " << temp["damage_bonus"] << endl;
		}
	}
	cout << endl;
}

void monsterSearch(){

	 //The Monster object in JSON
	json jsonList; //The list of all monsters from the external file
	
	ifstream monsterlist("json/5e-SRD-Monsters.json.txt");
	monsterlist >> jsonList;
	string monsterSearch;
	bool again = true; 
	do{
		json monster;
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

	cout << "Welcome to DM CLI Tools" << endl;
	cout << "   1. Monster Stats" << endl;
	cout << "   2. Encounters " << endl;
	cout << "   3. Party Manager" << endl;
	cout << "   4. Exit" << endl;

	cin >> response;
	cin.ignore();

	return response;
}



