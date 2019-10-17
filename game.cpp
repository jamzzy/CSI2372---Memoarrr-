#include "game.h"

//Constructor to game, default expert display is off
Game::Game() : bbb(Board()) {

	expertDisplay = false;
	round = 0;
	pCard = nullptr;
	cCard = nullptr;
}

//returns a number between 0 and 6 corresponding to the current round of the game
int Game::getRound() const { return round; }

//increments the number of rounds and resets the Game state for the next round.
void Game::nextRound() {
	round++;
	bbb.reset();
	pCard = nullptr;
	cCard = nullptr;
	flipped.clear();
	for (int i = 0; i < numPlayers(); i++) {
		players[i].setActive(true);
		addPlayer(players[i]);
	}
}

//adds or updates a player. If Player is already in Game, the player is
//updated, and if not it is added.
void Game::addPlayer(const Player& _p) {
	bool found = false;

	for (int i = 0; i < numPlayers(); i++) {
		if (players.at(i).getName() == _p.getName()) {
			players.at(i) = _p;
			found = true;
			break;
		}
	}

	if (!found) {
		players.push_back(_p);
	}
}

//returns player given side
const Player& Game::getPlayer(Side _s) const {
	int i = 0;
	for (i; i < numPlayers(); i++) {
		if (players.at(i).getSide() == _s) {
			break;
		}
	}
	return players.at(i);
}

//returns previous card
const Card* Game::getPreviousCard() const {
	return pCard;
}

//returns current card
const Card* Game::getCurrentCard() const {
	return cCard;
}

//sets current card, also flips it in board
void Game::setCurrentCard(const Card* _c) {
	Card *check;
	bool trig1 = false;
	bool trig2 = false;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				try {
					check = bbb.getCard(_l[l], _n[n]);
				}
				catch (OutOfRange e) {
					throw OutOfRange();
				}
				if (check == _c) {
					if (bbb.isFaceUp(_l[l], _n[n])) {
						throw ChangeSelection();
					}
					else {
						bbb.turnFaceUp(_l[l], _n[n]);
						flipped.push_back(check);
						trig1 = true;
						trig2 = true;
					}

				}

			}
			if (trig1) { break; }
		}
		if (trig2) { break; }
	}
	pCard = cCard;
	cCard = _c;
}

//calls the corresponding method in Board.
Card* Game::getCard(const Letter& _lett, const Number& _num) const {
	return bbb.getCard(_lett, _num);
}

//calls the corresponding method in Board
void Game::setCard(const Letter& _lett, const Number& _num, Card* _cc) {
	bbb.setCard(_lett, _num, _cc);
}

//printable with the insertion operator cout << game
//display the board and all players
//responsible for expert display as well
std::ostream& operator<<(std::ostream& os, const Game& ga) {
	if (!ga.expertDisplay) {
		os << ga.bbb;
	}

	else {
		if (!ga.flipped.empty()) {
			int size = static_cast<int>(ga.flipped.size());
			std::vector<Card*> print;
			for (int i = 0; i < size; i++) {
				Card* check = ga.flipped[i];

				if (ga.bbb.isFaceUp(ga.getLetter(check), ga.getNumber(check))) {
					print.push_back(check);
				}
			}

			std::string pos = "";
			int size2 = static_cast<int>(print.size());

			std::string line = "";
			for (int x = 0; x < 3; x++) {

				for (int y = 0; y < size2; y++) {
					Card* printCard = print[y];
					line = line + (*printCard)(x) + " ";

					if (x == 0) {
						pos = pos + ga.getPos(printCard) + " ";
					}
				}
				os << line << std::endl;
				line = "";
			}
			os << std::endl;
			os << pos << std::endl;
			os << std::endl;
		}
		else {
			os << "THIS IS EXPERT DISPLAY MODE! ONLY FACE UP CARDS AND THEIR POSITION WILL BE SEEN!" << std::endl;
			os << std::endl;
		}
	}
	for (int x = 0; x < ga.numPlayers(); x++) {

		os << ga.players.at(x);
	}
	return os;
}

//returns number of players
int Game::numPlayers() const {
	return static_cast<int>(players.size());
}

//calls corresponding method in board
bool Game::allCardsUp() const {
	return bbb.allCardsUp();
}

//Toggles expertdisplay
void Game::setExpertDisplay(const bool set) {
	expertDisplay = set;
}

//Method for Expert Rules
//given false, calls corresponding method in board for is FaceUp
//given true, calls corresponding method in board for turnFaceDown
bool Game::checkFaceUp(bool turn, const Letter& ccL, const Number& ccN) {
	if (!turn) {
		return bbb.isFaceUp(ccL, ccN);
	}

	else {
		return bbb.turnFaceDown(ccL, ccN);
	}
}

//returns letter position corresponding to given card
Letter Game::getLetter(const Card* _c) const {
	Card* check = NULL;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				try { check = bbb.getCard(_l[l], _n[n]); }
				catch (OutOfRange) {
					//std::cout << "how is this out of range" << std::endl;
				}

				if (check == _c) {
					return _l[l];
				}
			}
		}
	}
}

//returns number position according to given card 
Number Game::getNumber(const Card* _c) const {
	Card* check = NULL;
	Letter _l[5] = { Letter::A,Letter::B,Letter::C ,Letter::D ,Letter::E };
	Number _n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	for (int l = 0; l < 5; l++) {
		for (int n = 0; n < 5; n++) {
			if (!(n == 2 && l == 2)) {
				try { check = bbb.getCard(_l[l], _n[n]); }
				catch (OutOfRange) {
					//std::cout << "how is this out of range" << std::endl;
				}
				if (check == _c) {
					return _n[n];
				}
			}
		}
	}
}

//returns a string representing the coordinate of a give card
std::string Game::getPos(const Card* _c) const {
	Letter _l = getLetter(_c);
	Number _n = getNumber(_c);
	std::string pos = "";
	switch (_l) {
	case Letter::A: pos = "A"; break;
	case Letter::B: pos = "B"; break;
	case Letter::C: pos = "C"; break;
	case Letter::D: pos = "D"; break;
	case Letter::E: pos = "E"; break;
	default: pos = "Z"; break;
	}
	switch (_n) {
	case Number::one: pos = pos + "1"; break;
	case Number::two: pos = pos + "2"; break;
	case Number::three: pos = pos + "3"; break;
	case Number::four: pos = pos + "4"; break;
	case Number::five: pos = pos + "5"; break;
	default: pos = pos + "Z"; break;
	}
	return pos;

}

#if TEST_GAME_
int main() {
	Game testG;
	std::cout << "Testing Game, adding four players." << std::endl;
	Player test1("test1", Side::top);
	Player test2("test2", Side::right);
	Player test3("test3", Side::bottom);
	Player test4("test4", Side::left);
	testG.addPlayer(test1);
	testG.addPlayer(test2);
	testG.addPlayer(test3);
	testG.addPlayer(test4);
	std::cout << testG << std::endl;
	std::cout << "Testing updating a player. test3 will go inactive." << std::endl;
	test3.setActive(false);
	testG.addPlayer(test3);
	std::cout << testG << std::endl;
	std::cout << "Testing getRound and nextRound." << std::endl;
	std::cout << "Round: " << testG.getRound() << std::endl;
	std::cout << "Next round." << std::endl;
	testG.nextRound();
	std::cout << "Round: " << testG.getRound() << std::endl;

	Player get = testG.getPlayer(Side::right);
	std::cout << "Testing getPlayer. Getting player on right side." << std::endl;
	std::cout << get;

	std::cout << "Testing getCard. Getting 2 cards from A1 and E4." << std::endl;

	Card* t1 = testG.getCard(Letter::A, Number::one);
	Card* t2 = testG.getCard(Letter::E, Number::four);

	for (int i = 0; i < 3; i++) {
		std::string row = (*t1)(i);
		std::cout << row << " ";
		row = (*t2)(i);
		std::cout << row << std::endl;
	}
	

	std::cout << "Testing setCurrentCard. Setting card from E4, and then A1." << std::endl;
	testG.setCurrentCard(t1);
	testG.setCurrentCard(t2);
	std::cout << testG << std::endl;
	std::cout << "Testing Expert Display." << std::endl;
	testG.setExpertDisplay(true);
	std::cout << testG << std::endl;
	testG.setExpertDisplay(false);
	std::cout << "Testing getPreviousCard and getCurrentCard. Since we set E4 first and then A1, the previous is E4, and current is A1. " << std::endl;
	const Card* t3 = testG.getPreviousCard();
	const Card* t4 = testG.getCurrentCard();

	for (int i = 0; i < 3; i++) {
		std::string row = (*t3)(i);
		std::cout << row << "-----------------------";
		row = (*t4)(i);
		std::cout << row << std::endl;
	}
	std::cout << "Previous Card E4 ------  Current Card A1" << std::endl;
	std::cout << "Testing setCard. Setting Card at E4 at A1." << std::endl;
	testG.setCard(Letter::A, Number::one, t2);
	std::cout << testG << std::endl;
	
	std::cout << "Tested cout<<game." << std::endl;

	system("pause");
	return 0;
}
#endif