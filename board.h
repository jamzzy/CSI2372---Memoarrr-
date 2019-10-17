#pragma once
#include "card.h"
#include <iostream>
#include <exception>
#include <string>
#include "deck.h"

//Test Driver Switch 0 OFF/1 ON
#define TEST_BOARD_ 0

#ifndef BOARD_H
#define BOARD_H

enum class Letter { A, B, C, D, E };
enum class Number { one, two, three, four, five };

class Board {

public:
	Board();

	bool isFaceUp(const Letter&, const Number&) const;
	bool turnFaceUp(const Letter&, const Number&);
	bool turnFaceDown(const Letter&, const Number&);
	Card* getCard(const Letter&, const Number&) const;
	void setCard(const Letter&, const Number&, Card*);
	void reset();
	friend std::ostream& operator<<(std::ostream& os, const Board& bo);

	//Needed For Special Condition: When all cards are face-up but there are still active players.
	bool allCardsUp() const;
	
private:
	std::string gBoard[21];
	bool cardState[5][5];
	Card* bCards[5][5];

	int getRowLetter(const Letter&) const;
	int getColumnNum(const Number&) const;
	bool isValidLN(const Letter&, const Number&) const;
	void updateBoard();
	Number getNumber(const Card*) const;
	Letter getLetter(const Card*) const;

#if TEST_BOARD_
	friend int main();
#endif
};

class OutOfRange : public std::exception {
public:
	virtual const char* what() const throw () {
		return "OutOfRange exception: Thats an invalid letter and number combination!";
	}
};

class NoMoreCards : public std::exception {
public:
	virtual const char* what() const throw () {
		return "NoMoreCards exception: There are no more cards available to construct the board!";
	}
};


#endif
