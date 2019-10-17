#pragma once
#include "card.h"

//conversion operator to type FaceAnimal
Card::operator FaceAnimal() const {
	return a;
}

//conversion operator to type FaceBackground
Card::operator FaceBackground() const {
	return b;
}

//“printable” as one string per row
std::string Card::operator()(int n) const {
	std::string animal;
	std::string colour;

	switch (a)
	{
	case FaceAnimal::Crab: animal = "C"; break;
	case FaceAnimal::Penguin: animal = "P"; break;
	case FaceAnimal::Octopus: animal = "O"; break;
	case FaceAnimal::Turtle: animal = "T"; break;
	case FaceAnimal::Walrus: animal = "W"; break;
	default: animal = "Q"; break;
	}

	switch (b)
	{
	case FaceBackground::Red: colour = "r"; break;
	case FaceBackground::Green: colour = "g"; break;
	case FaceBackground::Purple: colour = "p"; break;
	case FaceBackground::Blue: colour = "b"; break;
	case FaceBackground::Yellow: colour = "y"; break;
	default: colour = "Z"; break;
	}

	if (n == 0 || n == 2) {
		return colour + colour + colour;
	}
	else if (n == 1) {
		return colour + animal + colour;
	}
	else
		return "";

}

//returns number of rows in a card
int Card::getNRows() const {
	return 3;
}

#if TEST_CARD_
int main() {
	std::cout << "Printing card, row by row." << std::endl;
	std::cout << std::endl;
	Card c(FaceAnimal::Penguin, FaceBackground::Red); // This constructor will be private
	for (int row = 0; row < c.getNRows(); ++row) {
		std::string rowString = c(row);
		std::cout << rowString << std::endl;
	}
std::cout << std::endl;
	FaceAnimal a;
	FaceBackground b;
	a = c;
	b = c;
	if (a == FaceAnimal::Penguin && b == FaceBackground::Red) {
		std::cout << "Conversion operators work. " << std::endl;
	}
	system("pause");
	return 0;
}
#endif