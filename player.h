#pragma once
#include <string>
#include "reward.h"
#include <iostream>

//Test Driver Switch 0 OFF/1 ON
#define TEST_PLAYER_ 0

#ifndef PLAYER_H
#define PLAYER_H

enum class Side { top, right, bottom, left};

class Player {
	std::string name;
	bool active, displayMode;
	int rubies;
	Side s;

public:

	Player(std::string nom, Side _s) : name{ nom }, active{ true }, displayMode{ false }, rubies{ 0 }, s{ _s }{};
	std::string getName() const;
	void setActive(const bool status);
	bool isActive() const;
	int getNRubies() const;
	void addReward(const Reward& _r);
	void setDisplayMode(bool endOfGame);
	Side getSide() const;
	void setSide(Side _ss);
	friend std::ostream& operator<<(std::ostream& os, const Player& pl);

#if TEST_PLAYER_
	friend int main();
#endif

};

#endif

