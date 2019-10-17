#include "reward.h"

//conversion operators to type int returning the number of rubies
Reward::operator int() const {
	return numRubies;
}

//printable with the insertion operator cout << reward
std::ostream& operator<<(std::ostream& os, const Reward& r) {
	os << r.numRubies << std::endl;
	return os;
}


#if TEST_REWARD_
#include <iostream>
int main() {
	std::cout << "Creating reward of 3 rubies." << std::endl;
	Reward test(3);
	int testRubies = test;
	std::cout << "Testing reward int conversion operator. Rubies: " << testRubies << std::endl;
	std::cout << "Testing cout<<reward: " << test << std::endl;
	system("pause");
	return 0;
}
#endif