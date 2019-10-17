#include "expertrules.h"
#include "rules.h"


/*
 *Constructor for expert rules, initializes all necessary triggers
 *to false for the card specific rules.
*/
ExpertRules::ExpertRules() {
	Rules();
	walrusBlock = false;
	penguinFlip = false;
	octSwap = false;
}

/*
*Extends the isValid method in rules.h to check the card animal specific rules.
*/
bool ExpertRules::isValid(const Game& gg) {
	bool set;
	const Card* curr = gg.getCurrentCard();
	const Card* prev = gg.getPreviousCard();
	if (prev == NULL) {
		set = true;
	}
	else {
		FaceAnimal cur1 = *curr;
		FaceAnimal prev1 = *prev;
		FaceBackground cur2 = *curr;
		FaceBackground prev2 = *prev;

		if (cur1 == prev1 || cur2 == prev2) {
			set = true;
		}

		else { set = false; }
	}
	//Only calls an animal card rule method if the player's card selection is valid
	if (set&&!gg.allCardsUp()) {
		//checks if the current card is an octopus card and calls the octopus method
		if (*curr == FaceAnimal::Octopus) {
			std::cout << gg << std::endl;
			octopus(gg);
		}
		//checks if the current card is a turtle card and calls the turtle method
		else if (*curr == FaceAnimal::Turtle) {
			std::cout << gg << std::endl;
			turtle(gg);
		}
		//checks if the current card is a walrus card and calls the walrus method
		else if (*curr == FaceAnimal::Walrus) {
			std::cout << gg << std::endl;
			walrus();
		}
		//checks if the current card is a penguin card and calls the penguin method
		else if (*curr == FaceAnimal::Penguin) {
			std::cout << gg << std::endl;
			if (prev != NULL) {
				penguin();
			}
		}
		//checks if the current card is a penguin card and calls the crab method
		else if (*curr == FaceAnimal::Crab) {
			std::cout << gg << std::endl;
			crab(gg);
		}
	}


	return set;
}

/*
* The following method implements the octopus card rule. 
* It sets the octopus trigger to true and then prompts the user to select an adjacent card and check's if the user's selection
* is valid and if it is adjacent to the current card. The actual exchange of the card's position
* is done in main.cpp.
*/
void ExpertRules::octopus(const Game& gg) {
	octSwap = true;
	char lls[] = "ABCDE";
	char nns[] = "12345";
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	const Card* currCard = gg.getCurrentCard();
	Loc cardLoc = getCardLocation(currCard, gg);
	Loc newLoc;
	std::cout << "You picked an Octopus card! You get to switch this card with a card directly adjacent to it!" << std::endl;
	//The following while loop tests if the player's adajcent card selection is valid.
	while (true) {
		std::cout << "Please select a card directly adjacent to ";
		LocPrint(cardLoc);
		std::cout << ": ";
		char selection[] = "XX";
		std::cin >> selection;
		try {
			newLoc = toLoc(selection);
			if ((newLoc._lett == cardLoc._lett) && (newLoc._num == cardLoc._num)) {
				throw "Oops! Thats the card you just picked!";
			}
			else if ((newLoc._lett == _l[2]) && (newLoc._num == _n[2])) {
				throw OutOfRange();
			}
			else if (newLoc._lett == cardLoc._lett) {
				int ii = 0;
				bool trr = false;
				for (int ii = 0; ii < 5; ii++) {
					if (cardLoc._num == _n[ii]) {
						trr = true;
						break;
					}
				}
				if (!trr) {
					throw OutOfRange();
				}
				try {
					if (newLoc._num == _n[ii - 1]) {
						octCard = newLoc;
						return;
					}
				}
				catch (const std::out_of_range out) {

				}
				try {
					if (newLoc._num != _n[ii + 1]) {
						octCard = newLoc;
						return;
					}
					else { break; }
				}
				catch (const std::out_of_range out) {

				}
			}
			else if (newLoc._num == cardLoc._num) {
				int i = 0;
				bool trr = false;
				try {
					if (newLoc._lett == _l[i - 1]) {
						octCard = newLoc;
						return;
					}
				}
				catch (const std::out_of_range out) {

				}
				try {
					if (newLoc._lett != _l[i + 1]) {
						octCard = newLoc;
						return;
					}
					else { break; }
				}
				catch (const std::out_of_range out) {

				}
			}
			throw "Invalid Selection!";
		}
		catch (OutOfRange e) {
			std::cout << e.what() << std::endl;
		}
		catch (const char* ee) {
			std::cerr << ee << std::endl;
		}
		catch (ChangeSelection err) {
			std::cout << err.what() << std::endl;
		}
	}
	octCard = newLoc;

}

/*
* The following method implements the penguin card rule.
* It sets the penguin trigger to true and then prints a message saying the
* player has selected a penguin card. The rest of the penguin rules are implemented in main.
*/
void ExpertRules::penguin() {
	penguinFlip = true;
	std::cout << "You picked a Penguin card! You get to turn any face-up card face-down!" << std::endl;
}

/*
* The following method implements the walrus card rule.
* It sets the walrus trigger to true and then prints a message saying the
* player has selected a walrus card. The rest of the walrus rules are implemented in main.
*/
void ExpertRules::walrus() {
	walrusBlock = true;
	std::cout << "You picked a Walrus card! You get to block the next player from selecting one card!" << std::endl;
}

/*
* The following method implements the turtle card rule.
* It prints a message saying the player has selected a turtle card. 
* Then it sets the current player to be the next player so that when getNextPlayer() is called
* the next player will be skipped.
*/
void ExpertRules::turtle(const Game& gg) {
	std::cout << "You picked a Turtle card! The player after you is skipped!" << std::endl;
	int search = 0;
	int numP = 0;
	for (int i = 0; i < 4; i++) {
		try {
			if (gg.getPlayer(s[i]).isActive()) {
				numP++;
			}
		}
		catch (std::out_of_range) {
			break;
		}
	}
	for (search = 0; search < 4; search++) {
		if (currP == s[search]) {
			break;
		}
	}
	bool sides[4] = { false,false,false,false };
	for (int i = 0; i < 4; i++) {
		try {
			sides[i] = gg.getPlayer(s[i]).isActive();
		}
		catch (std::out_of_range) {
			break;
		}
	}
	int j;
	if (search == (numP - 1)) {
		j = 0;
	}
	else { j = search + 1; }
	for (j; j < numP; j++) {
		if (gg.getPlayer(s[j]).isActive()) {
			currP = s[j];
			break;
		}
		if (j == (numP - 1)) {
			j = -1;
		}
	}

}

/*
* The following method implements the crab card rule.
* It prints a message saying the player has selected a crab card.
* Then it sets the current player to be the previous player so that when getNextPlayer() is called
* the next player will be the player who just went, allowing then to immediately select another card.
*/
void ExpertRules::crab(const Game& gg) {
	std::cout << "You picked a Crab card! You get to go again!" << std::endl;
	int search = 0;
	for (search = 0; search < 4; search++) {
		if (currP == s[search]) {
			break;
		}
	}
	bool sides[4] = { false,false,false,false };
	for (int i = 0; i < 4; i++) {
		try {
			sides[i] = gg.getPlayer(s[i]).isActive();
		}
		catch (std::out_of_range) {
			break;
		}
	}
	int j;
	if (search == 0) {
		j = 3;
	}
	else {
		j = search - 1;
	}
	for (j; j >= 0; j--) {
		if (sides[j]) {
			currP = s[j];
			break;
		}
		if (j == 0) {
			j = 4;
		}
	}


}

//Static method receiving an old style C-string which returns the Location of a card.
ExpertRules::Loc ExpertRules::toLoc(char xx[]) {
	Loc location;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	char letters[] = "ABCDE";
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	char numbers[] = "12345";
	bool t1 = false;
	bool t2 = false;
	for (int i = 0; i < 5; i++) {
		if (*xx == *(letters + i)) {
			location._lett = _l[i];
			t1 = true;

		}
		if (*(xx + 1) == *(numbers + i)) {
			location._num = _n[i];
			t2 = true;

		}
	}

	if (t1&&t2) {
		return location;
	}
	else {
		throw OutOfRange();
	}
}

//Static method receiving a card Location which prints the location to the console.
void ExpertRules::LocPrint(Loc location) {
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	char letters[] = "ABCDE";
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	char numbers[] = "12345";
	char locn[] = "XX";
	for (int i = 0; i < 5; i++) {
		if (location._lett == _l[i]) {
			*locn = *(letters + i);
		}
		if (location._num == _n[i]) {
			*(locn + 1) = *(numbers + i);
		}
	}
	std::cout << locn;

}

//Static method receiving a const Card pointer and a const Game pointer that returns a card Location.
ExpertRules::Loc ExpertRules::getCardLocation(const Card* _c, const Game& gg) {
	Card* check;
	Loc spot;
	bool trig1 = false;
	bool trig2 = false;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				check = gg.getCard(_l[l], _n[n]);
				if (check == _c) {
					spot._lett = _l[l];
					spot._num = _n[n];

					trig1 = true;
					trig2 = true;
				}
			}
			if (trig1) { break; }
		}
		if (trig2) { break; }
	}
	return spot;
}

#if TEST_EXPERTRULES_
int main() {
	Game testG;
	ExpertRules testR;
	std::cout << "Testing inheritance of ExpertRules since it is derived from Rules." << std::endl;
	std::cout << "Testing ExpertRules with game of 4 players." << std::endl;
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
	std::cout << "Testing gameOver. It is round " << testG.getRound() << "." << std::endl;
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

