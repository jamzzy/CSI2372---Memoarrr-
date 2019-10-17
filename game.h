#pragma once

#include "board.h"
#include "player.h"
#include "card.h"
#include <vector>

//Test Driver Switch 0 OFF/1 ON
#define TEST_GAME_ 0

#ifndef GAME_H

#define GAME_H

class Game {
	Board bbb;
	int round;
	std::vector<Player> players;
	const Card* pCard;
	const Card* cCard;
	bool expertDisplay;
	std::vector<Card*> flipped;
public:
	Game();
	int getRound() const;
	void nextRound();
	void addPlayer(const Player&);
	const Player& getPlayer(Side) const;
	const Card* getPreviousCard() const;
	const Card* getCurrentCard() const;
	void setCurrentCard(const Card*);
	Card* getCard(const Letter&, const Number&) const;
	void setCard(const Letter&, const Number&, Card*);
	friend std::ostream& operator<<(std::ostream& os, const Game& ga);

	//Needed For Special Condition: When all cards are face-up but there are still active players.
	bool allCardsUp() const;

	//For ExpertDisplay
	void setExpertDisplay(const bool);

	//For ExpertRules
	bool checkFaceUp(bool, const Letter&, const Number&);
protected:
	int numPlayers() const;
	Number getNumber(const Card*) const;
	Letter getLetter(const Card*) const;
	std::string getPos(const Card* _c) const;
#if TEST_GAME_ 
	friend int main();
#endif
};

class ChangeSelection : public std::exception {
public:
	virtual const char* what() const throw () {
		return "Oops! The card you selected is already face up! Please select a card that is face down.";
	}
};

#endif // !GAME_H


