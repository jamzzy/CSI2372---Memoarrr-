#include "player.h"
#include "card.h"

//const return the name of the player.
std::string Player::getName() const { return name; }

//set the status of the player as active or inactive.
void Player::setActive(const bool status) { active = status; }

//returns true if the player is active.
bool Player::isActive() const{ return active; }

//const return the number of rubies won by this player.
int Player::getNRubies() const { return rubies; }

//dd a reward with a given number of rubies.
void Player::addReward(const Reward& _r) {
	int add = _r;
	rubies = rubies + add;
};

//Changes cout<<player to change between normal output, and end of the game output
void Player::setDisplayMode(bool endOfGame) { displayMode = endOfGame; }

//returns player's side
Side Player::getSide() const { return s; }

//sets player's side
void Player::setSide(Side _ss) { s = _ss; }

//printable with the insertion operator cout<<player
std::ostream& operator<<(std::ostream& os, const Player& pl) {
	std::string pName = pl.name;


	if (pl.displayMode == false) {

		std::string pActive, pSide;
		switch (pl.active) {
		case true: pActive = "active"; break;
		case false: pActive = "inactive"; break;
		}
		switch (pl.s) {
		case Side::top: pSide = "top"; break;
		case Side::bottom: pSide = "bottom"; break;
		case Side::left: pSide = "left"; break;
		case Side::right: pSide = "right"; break;
		}
		os << pName << ": " << pSide << "(" << pActive << ")" << std::endl;

	}
	else {
		std::string pRubs = std::to_string(pl.rubies);
		os << pName << ": " << pRubs << " rubies" << std::endl;

	}
	return os;
}

#if TEST_PLAYER_

#include "deck.h"

int main() {

	Player test("test", Side::top); 
	std::cout << "Testing player getters." << std::endl;
	std::cout << "Name: " << test.getName() << ", Active: " << test.isActive() << ", Rubies: " << test.getNRubies() << std::endl;
	std::cout << "Add Reward, will display later." << std::endl;
	test.addReward(*RewardDeck::make_RewardDeck().getNext());
	test.setActive(false);
	std::cout << "Is Top Side?: "<< (test.getSide() == Side::top) << std::endl;
	std::cout << "Set test player side to bottom." << std::endl;
	test.setSide(Side::bottom);
	std::cout << test << std::endl;
	std::cout << "Check cout<<player output when game is over." << std::endl;
	test.setDisplayMode(true);
	std::cout << test << std::endl;
	system("pause");
	return 0;
}
#endif