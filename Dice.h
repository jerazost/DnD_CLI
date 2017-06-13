#include <string>
#include <stdlib.h> 

#ifndef DICE_H
#define DICE_H

class Dice{
private:
	unsigned int diceType;
	unsigned int multiplier;

public:
	Dice();
	Dice(const std::string &);
	~Dice();
	std::string name;
	int roll();


};

#endif