#include "board.h"

//Constructor for board, throws NoMoreCards when no cards left to make board
Board::Board() {
	CardDeck::make_CardDeck().shuffle();
	RewardDeck::make_RewardDeck().shuffle();
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cardState[i][j] = false;
			if (CardDeck::make_CardDeck().isEmpty()) {
				throw NoMoreCards();
			}
			else {
				bCards[i][j] = CardDeck::make_CardDeck().getNext();
			}
		}
	}
	updateBoard();
}

//returns true if the card at a given position is
//face up.Letter and Number are enumerations.Throws an exception of type OutOfRange if an invalid
//Letter and Number combination was given.
bool Board::isFaceUp(const Letter& _l, const Number& _n) const {
	if (isValidLN(_l, _n)) {

		return cardState[getRowLetter(_l)][getColumnNum(_n)];
	}
	else throw OutOfRange();
}

//changes the state of the specified card return false
//if card was up already.Throws an exception of type OutOfRange if an invalid Letter and Number
//combination was given.
bool Board::turnFaceUp(const Letter& _l, const Number&_n) {
	if (isValidLN(_l, _n)) {
		if (cardState[getRowLetter(_l)][getColumnNum(_n)]) {

			return false;
		}
		else {
			cardState[getRowLetter(_l)][getColumnNum(_n)] = true;
			updateBoard();

			return cardState[getRowLetter(_l)][getColumnNum(_n)];
		}
	}
	else throw OutOfRange();
}

//changes the state of the specified card return
//false if card was down already.Throws an exception of type OutOfRange if an invalid Letter and
//Number combination was given.
bool Board::turnFaceDown(const Letter& _l, const Number& _n) {
	if (isValidLN(_l, _n)) {
		if (cardState[getRowLetter(_l)][getColumnNum(_n)]) {
			cardState[getRowLetter(_l)][getColumnNum(_n)] = false;
			updateBoard();
			return !cardState[getRowLetter(_l)][getColumnNum(_n)];
		}
		else {
			return false;
		}
	}
	else throw OutOfRange();
}

//returns a pointer to the card at a given location.
//Throws an exception of type OutOfRange if an invalid Letter and Number combination was given
Card* Board::getCard(const Letter& _l, const Number& _n) const {

	if (isValidLN(_l, _n)) {
		return bCards[getRowLetter(_l)][getColumnNum(_n)];
	}
	else throw OutOfRange();
}

//updates the pointer to card at a given location.
//Throws an exception of type OutOfRange if an invalid Letter and Number combination was given.
void Board::setCard(const Letter& _l, const Number& _n, Card* set) {
	if (isValidLN(_l, _n)) {
		Card* temp = getCard(_l, _n);
		bool temps = cardState[getRowLetter(_l)][getColumnNum(_n)];

		Letter setL = getLetter(set);
		Number setN = getNumber(set);
		bool temp2 = cardState[getRowLetter(setL)][getColumnNum(setN)];

		bCards[getRowLetter(_l)][getColumnNum(_n)] = set;
		cardState[getRowLetter(_l)][getColumnNum(_n)] = temp2;

		bCards[getRowLetter(setL)][getColumnNum(setN)] = temp;
		cardState[getRowLetter(setL)][getColumnNum(setN)] = temps;

		updateBoard();
	}
	else throw OutOfRange();
}

//changes the state to all cards to be face down.
void Board::reset() {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			cardState[i][j] = false;
		}
	}
	updateBoard();
}

//printable with the insertion operator cout << board.
std::ostream& operator<<(std::ostream& os, const Board& bo) {
	for (int f = 0; f < 21; f++) {
		os << bo.gBoard[f] << std::endl;
	}
	return os;
}

//returns an int corresponding to row in 2d array given Letter
int Board::getRowLetter(const Letter& rL) const {
	switch (rL) {
	case Letter::A: return 0; break;
	case Letter::B: return 1; break;
	case Letter::C: return 2; break;
	case Letter::D: return 3; break;
	case Letter::E: return 4; break;
	default: return 5; break;
	}
}

//returns an int corresponding to column in 2d array given Number
int Board::getColumnNum(const Number& cN) const {
	switch (cN) {
	case Number::one: return 0; break;
	case Number::two: return 1; break;
	case Number::three: return 2; break;
	case Number::four: return 3; break;
	case Number::five: return 4; break;
	default: return 5; break;
	}
}

//returns true if letter and number combination is valid
bool Board::isValidLN(const Letter& _l, const Number& _n) const {

	if (getRowLetter(_l) == 5 || getColumnNum(_n) == 5) {
		return false;
	}
	else if (getRowLetter(_l) == 2 && getColumnNum(_n) == 2) {
		return false;
	}
	else return true;
}

//updates the string array which represents the board
void Board::updateBoard() {
	for (int l = 0; l < 21; l++) {
		gBoard[l] = " ";
	}
	for (int r1 = 0; r1 < 3; r1++) {
		for (int c1 = 0; c1 < 5; c1++) {
			if (cardState[0][c1]) {
				gBoard[r1] = gBoard[r1] + "  " + (*(bCards[0][c1]))(r1);
			}
			else {
				gBoard[r1] = gBoard[r1] + "  zzz";
			}
		}
	}
	gBoard[1].replace(0, 1, "A");

	for (int r2 = 4; r2 < 7; r2++) {
		for (int c2 = 0; c2 < 5; c2++) {
			if (cardState[1][c2]) {
				gBoard[r2] = gBoard[r2] + "  " + (*(bCards[1][c2]))(r2 - 4);
			}
			else {
				gBoard[r2] = gBoard[r2] + "  zzz";
			}
		}
	}
	gBoard[5].replace(0, 1, "B");

	for (int r3 = 8; r3 < 11; r3++) {
		for (int c3 = 0; c3 < 5; c3++) {
			if (c3 == 2) {
				gBoard[r3] = gBoard[r3] + "     ";
			}
			else {
				if (cardState[2][c3]) {
					gBoard[r3] = gBoard[r3] + "  " + (*(bCards[2][c3]))(r3 - 8);
				}
				else {
					gBoard[r3] = gBoard[r3] + "  zzz";
				}
			}
		}
	}
	gBoard[9].replace(0, 1, "C");

	for (int r4 = 12; r4 < 15; r4++) {
		for (int c4 = 0; c4 < 5; c4++) {
			if (cardState[3][c4]) {
				gBoard[r4] = gBoard[r4] + "  " + (*(bCards[3][c4]))(r4 - 12);
			}
			else {
				gBoard[r4] = gBoard[r4] + "  zzz";
			}
		}
	}
	gBoard[13].replace(0, 1, "D");

	for (int r5 = 16; r5 < 19; r5++) {
		for (int c5 = 0; c5 < 5; c5++) {
			if (cardState[4][c5]) {
				gBoard[r5] = gBoard[r5] + "  " + (*(bCards[4][c5]))(r5 - 16);
			}
			else {
				gBoard[r5] = gBoard[r5] + "  zzz";
			}
		}
	}
	gBoard[17].replace(0, 1, "E");

	gBoard[20] = "    1    2    3    4    5";
}

//Needed for Special Case: When all cards are face up but there are still active players.
bool Board::allCardsUp() const {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (!(i == 2 && j == 2)) {
				if (!cardState[i][j]) return false;
			}
			
		}
	}
	return true;
}

//returns Letter location for a given Card
Letter Board::getLetter(const Card* _c) const {
	Card* check = NULL;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				/*try { check = bbb.getCard(_l[l], _n[n]); }
				catch (OutOfRange) {
					std::cout << "how is this out of range" << std::endl;
				}*/
				

				if (bCards[l][n] == _c) {
					return _l[l];
				}
			}
		}
	}
}

//returns Number location for a given Card
Number Board::getNumber(const Card* _c) const {
	Card* check = NULL;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				if (bCards[l][n] == _c) {
					return _n[n];
				}
			}
		}
	}
}

#if TEST_BOARD_
int main() {
	Board testB;
	std::cout << "Testing cout<<board, all cards initialized to facedown." << std::endl;
	std::cout << std::endl;
	std::cout << testB << std::endl;
	std::cout << "Testing isFaceUp." << std::endl;
	std::cout << "Is A1 Faceup? No, therefore should return false/0. A1 isFaceUp: " << testB.isFaceUp(Letter::A, Number::one) << std::endl;
	std::cout << "Testing turnFaceUp." << std::endl;
	std::cout << "Turning up A1." << std::endl;
	testB.turnFaceUp(Letter::A, Number::one);
	std::cout << testB << std::endl;
	std::cout << "Testing turnFaceDown." << std::endl;
	std::cout << "Turning down A1." << std::endl;
	testB.turnFaceDown(Letter::A, Number::one);
	std::cout << testB << std::endl;
	std::cout << "Testing getCard" << std::endl;
	std::cout << "Getting A2, and printing here." << std::endl;
	Card* a2 = testB.getCard(Letter::A, Number::two);
	for (int i = 0; i < 3; i++) {
		std::string row = (*a2)(i);
		std::cout << row << std::endl;
	}
	testB.turnFaceUp(Letter::A, Number::two);
	std::cout << testB << std::endl;
	std::cout << "Testing setCard." << std::endl;
	std::cout << "Setting card from A2 to C4." << std::endl;
	testB.turnFaceUp(Letter::C, Number::four);
	std::cout << testB << std::endl;
	testB.setCard(Letter::C, Number::four, a2);
	
	std::cout << testB << std::endl;
	std::cout << "Testing reset." << std::endl;
	testB.reset();
	std::cout << testB << std::endl;
	std::cout << "Testing OutOfRange, invalid input is centre or C3." << std::endl;
	try {
		testB.isFaceUp(Letter::C, Number::three);
	}
	catch(OutOfRange o){
		std::cout << o.what() << std::endl;
		std::cout << "------isFaceUp------" << std::endl;
	}

	try {
		testB.turnFaceUp(Letter::C, Number::three);
	}
	catch (OutOfRange o) {
		std::cout << o.what() << std::endl;
		std::cout << "------turnFaceUp------" << std::endl;
	}

	try {
		testB.turnFaceDown(Letter::C, Number::three);
	}
	catch (OutOfRange o) {
		std::cout << o.what() << std::endl;
		std::cout << "------turnFaceDown------" << std::endl;
	}

	try {
		a2 = testB.getCard(Letter::C, Number::three);
	}
	catch (OutOfRange o) {
		std::cout << o.what() << std::endl;
		std::cout << "------getCard------" << std::endl;
	}
	a2 = testB.getCard(Letter::C, Number::four);
	try {
		testB.setCard(Letter::C, Number::three,a2);
	}
	catch (OutOfRange o) {
		std::cout << o.what() << std::endl;
		std::cout << "------setCard------" << std::endl;
	}

	std::cout << "Testing NoMoreCards Exception." << std::endl;
	try {
		Board no;
	}
	catch (NoMoreCards n) {
		std::cout << n.what() << std::endl;
		std::cout << "Exception was thrown." << std::endl;
	}

	system("pause");
	return 0;
}
#endif