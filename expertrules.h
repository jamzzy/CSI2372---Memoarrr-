#pragma once

#include "game.h"
#include "rules.h"

//Test Driver Switch 0 OFF/1 ON
#define TEST_EXPERTRULES_ 0

#ifndef EXPERTRULES_H
#define EXPERTRULES_H

//ExpertRules extends Rules
class ExpertRules :public Rules {
public:
	bool penguinFlip;
	bool walrusBlock;
	bool octSwap;
	//Struct that hold's the card's location (Letter and Number combination).
	struct Loc {
		Letter _lett;
		Number _num;
	};
	Loc wBlocked;
	Loc octCard;

	ExpertRules();
	bool isValid(const Game&);
	void octopus(const Game&);
	void penguin();
	void walrus();
	void crab(const Game&);
	void turtle(const Game&);
	
	static Loc toLoc(char[]);
	static void LocPrint(Loc);
	static Loc getCardLocation(const Card*, const Game&);
#if TEST_EXPERTRULES_
	friend int main();
#endif
};

//Exception thrown when the user selects a card that is face up.
class PenguinFlipException : public std::exception {
public:
	virtual const char* what() const throw () {
		return "Please select a face-up card to flip: ";
	}
};

//Exception thrown when a user attempts to select a card that has been blocked by the previous player.
class WalrusBlockException : public std::exception {
public:
	virtual const char* what() const throw () {
		return  "That card has been Walrus Blocked! Please select a different card.";

	}
};


#endif
