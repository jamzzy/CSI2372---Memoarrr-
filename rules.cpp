#include "rules.h"

//returns true is previous and current card match; false otherwise.
bool Rules::isValid(const Game& gg) const{
	
	const Card* curr = gg.getCurrentCard();
	const Card* prev = gg.getPreviousCard();
	if (prev == NULL) {
		return true;
	}
	else {
		FaceAnimal cur1 = *curr;
		FaceAnimal prev1 = *prev;
		FaceBackground cur2 = *curr;
		FaceBackground prev2 = *prev;

		if (cur1 == prev1 || cur2 == prev2) {
			return true;
		}

		else { return false; }
	}
}

//returns true if the number of rounds has reached 7.
bool Rules::gameOver(const Game& gg)const {
	if (gg.getRound() >= 7) {
		return true;
	}
	else { return false; }
}

//returns true if there is only one active Player left.
bool Rules::roundOver(const Game& gg)  {

	int temp = 0;
	int count = 0;
	
	for (int i = 0; i < 4;i++) {

		try {
			if (gg.getPlayer(s[i]).isActive()) {
				count++;
				temp = i;
			}
		}
		catch (std::out_of_range) {
			break;
		}
	}
	if (count == 1) {
		winner = temp;
		if (temp == 0)
		{
			temp = 3;
			
		}
		else {
			temp = temp - 1;
		}
		currP = s[temp];
	
		return true;
	}
	else { 
		winner = -1;
		
		return false; }

}

//returns next active player in the game the order is top,right,bottom,left
const Player& Rules::getNextPlayer(const Game& gg)  {
	
	if (roundOver(gg)) {
	
		return gg.getPlayer(s[winner]);
	}
	else {
		
			bool top = false;
			bool right = false;
			bool bottom = false;
			bool left = false;
			
			for (int i = 0; i < 4; i++) {
				try {
					if (i == 0) {
						top = gg.getPlayer(s[0]).isActive();
						
					}
					else if (i == 1) {
						right = gg.getPlayer(s[1]).isActive();
					}
					else if (i == 2) {
						bottom = gg.getPlayer(s[2]).isActive();
					}
					else if (i == 3) {
						left = gg.getPlayer(s[3]).isActive();
					}
				}
				catch (std::out_of_range) {
					break;
				}
			}
			
			if (currP == s[0])
			{
				if (right) {
					currP = s[1];
				}
				else if (bottom) {
					currP = s[2];
				}
				else if (left) {
					currP = s[3];
				}

			}

			else if (currP == s[1])
			{
				if (bottom) {
					currP = s[2];
				}
				else if (left) {
					currP = s[3];
				}
				else if (top) {
					currP = s[0];
				}
			}

			else if (currP == s[2])
			{
				if (left) {
					currP = s[3];
				}
				else if (top) {
					currP = s[0];
				}
				else if (right) {
					currP = s[1];
				}
			}

			else
			{
				if (top) {
					currP = s[0];
				}
				else if (right) {
					currP = s[1];
				}
				else if (bottom) {
					currP = s[2];
				}
			}
			
			return gg.getPlayer(currP);
		
	}
}

#if TEST_RULES_
int main() {
	Game testG;
	Rules testR;
	std::cout << "Testing Rules with game of 4 players." << std::endl;
	Player test1("test1", Side::top);
	Player test2("test2", Side::right);
	Player test3("test3", Side::bottom);
	Player test4("test4", Side::left);
	testG.addPlayer(test1);
	testG.addPlayer(test2);
	testG.addPlayer(test3);
	testG.addPlayer(test4);
	std::cout << "Flipping up two cards, A1 and B5 to test rules." << std::endl;
	testG.setCurrentCard(testG.getCard(Letter::A, Number::one));
	testG.setCurrentCard(testG.getCard(Letter::B, Number::five));

	std::cout << testG << std::endl;
	std::cout << "Testing isValid" << std::endl;
	std::cout << "isValid?: " << testR.isValid(testG) << std::endl;
	std::cout << "Testing gameOver. It is round " << testG.getRound() <<"."<< std::endl;
	std::cout << "gameOver?: " << testR.gameOver(testG) << std::endl;
	
	std::cout << "Testing roundOver. Making 3 players inactive." << std::endl;
	test1.setActive(false);
	test2.setActive(false);
	test3.setActive(false);
	testG.addPlayer(test1);
	testG.addPlayer(test2);
	testG.addPlayer(test3);
	std::cout << "roundOver?: " << testR.roundOver(testG) << std::endl;
	std::cout << testG << std::endl;
	test1.setActive(true);
	test2.setActive(true);
	test3.setActive(true);
	testG.addPlayer(test1);
	testG.addPlayer(test2);
	testG.addPlayer(test3);
	
	std::cout << "Testing getNextPlayer." << std::endl;
	Player test5 = testR.getNextPlayer(testG);
	std::cout << test5 << std::endl;
	Player test6 = testR.getNextPlayer(testG);
	std::cout << test6 << std::endl;

	system("pause");
	return 0;
}
#endif