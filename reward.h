#pragma once

#include <iostream>

//Test Driver Switch 0 OFF/1 ON
#define TEST_REWARD_ 0

#ifndef REWARD_H
#define REWARD_H
class Reward {
	int numRubies;
public:
	operator int() const;
	
private:
	Reward(int rubies) :numRubies{ rubies } {}
	friend std::ostream& operator<<(std::ostream& os, const Reward& r);
	friend class RewardDeck;
#if TEST_REWARD_
	friend int main();
#endif
};
#endif