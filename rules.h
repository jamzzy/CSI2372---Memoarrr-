#pragma once
#include "game.h"

//Test Driver Switch 0 OFF/1 ON
#define TEST_RULES_ 0

#ifndef RULES_H
#define RULES_H

class Rules {
protected:
	Side currP;
	Side s[4];
	int winner;
public:
	Rules() : currP{ Side::left }, s{ Side::top, Side::right, Side::bottom, Side::left }, winner{ -1 }{}
	bool isValid(const Game&) const;
	bool gameOver(const Game&) const;
	bool roundOver(const Game&) ;
	const Player& getNextPlayer(const Game&) ;
#if TEST_RULES_
	friend int main();
#endif
};

#endif