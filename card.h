#pragma once
#include "player.h"
#include <iostream>

//Test Driver Switch 0 OFF/1 ON
#define TEST_CARD_ 0

#ifndef CARD_H
#define CARD_H

enum class FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum class FaceBackground { Red, Green, Purple, Blue, Yellow };


class Card {

	FaceAnimal a;
	FaceBackground b;
public:

	Card(const Card&) = delete;
	void operator= (const Card&) = delete;
	operator FaceAnimal() const;
	operator FaceBackground() const;
	std::string operator()(int n) const;
	int getNRows() const;

private:
	Card(FaceAnimal an, FaceBackground ba) : a{ an }, b{ ba }{}
	friend class CardDeck;

#if TEST_CARD_
	friend int main();
#endif
};

#endif
