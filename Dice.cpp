#include "Dice.h"
//DEBUG
#include <iostream>
using namespace std;

Dice::Dice(){

}

Dice::~Dice(){

}

Dice::Dice(const std::string & diceString){
	try {
		name = diceString;
		size_t d = diceString.find("d");
		diceType = std::stoi(diceString.substr(d + 1));
		multiplier = std::stoi(diceString.substr(0,d));
	} catch (const std::invalid_argument& ia) {
		cout << "Invalid dice, format: [amount]d[maximum]" << endl;
	}
}

int Dice::roll(){
	int runningTotal;
	for (size_t i = 0; i < this->multiplier; i++){
		runningTotal += (rand() % this->diceType + 1);
	}
	return runningTotal;
}
