#pragma once
#include <vector>
#include <algorithm>
#include "card.h"
#include "reward.h"
#include <iostream>

//Test Driver Switch 0 OFF/1 ON
#define TEST_CARDDECK_REWARDDECK_ 0

#ifndef DECK_H
#define DECK_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Deck Abstract Factory Class
template<class C>
class Deck {
protected:
	std::vector<C*> deck;
public:
	//shuffles the cards in the deck.
	void shuffle() {
		std::random_shuffle(deck.begin(), deck.end());
	}
	//pure virtual function
	virtual C* getNext() = 0;

	//const returns true if the deck is empty.
	bool isEmpty() const { return deck.empty(); }
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CardDeck class

class CardDeck : public Deck<Card> {

	Card cR, cG, cP, cB, cY, pR, pG, pP, pB, pY, oR, oG, oP, oB, oY, tR, tG, tP, tB, tY, wR, wG, wP, wB, wY;
public:

	//creates and returns the same CardDeck during the execution of the program
	static CardDeck& make_CardDeck() {
		if (cd == NULL) {
			cd = new CardDeck();
		}
		return *cd;
	}
	//returns the next card or reward by pointer. Will return nullptr if no more cards or rewards are available.
	Card* getNext() {	
			if (CardDeck::make_CardDeck().isEmpty()) {
				return NULL;
			}
			else{ 
				Card* next;
				next = deck.back();
				deck.pop_back();
				return next; 
			}		
	}
private:
	//CardDeck constructor
	CardDeck() :
		cR(FaceAnimal::Crab, FaceBackground::Red), cG(FaceAnimal::Crab, FaceBackground::Green), cP(FaceAnimal::Crab, FaceBackground::Purple), cB(FaceAnimal::Crab, FaceBackground::Blue), cY(FaceAnimal::Crab, FaceBackground::Yellow),
		pR(FaceAnimal::Penguin, FaceBackground::Red), pG(FaceAnimal::Penguin, FaceBackground::Green), pP(FaceAnimal::Penguin, FaceBackground::Purple), pB(FaceAnimal::Penguin, FaceBackground::Blue), pY(FaceAnimal::Penguin, FaceBackground::Yellow),
		oR(FaceAnimal::Octopus, FaceBackground::Red), oG(FaceAnimal::Octopus, FaceBackground::Green), oP(FaceAnimal::Octopus, FaceBackground::Purple), oB(FaceAnimal::Octopus, FaceBackground::Blue), oY(FaceAnimal::Octopus, FaceBackground::Yellow),
		tR(FaceAnimal::Turtle , FaceBackground::Red), tG(FaceAnimal::Turtle, FaceBackground::Green), tP(FaceAnimal::Turtle, FaceBackground::Purple), tB(FaceAnimal::Turtle, FaceBackground::Blue), tY(FaceAnimal::Turtle, FaceBackground::Yellow),
		wR(FaceAnimal::Walrus, FaceBackground::Red), wG(FaceAnimal::Walrus, FaceBackground::Green), wP(FaceAnimal::Walrus, FaceBackground::Purple), wB(FaceAnimal::Walrus, FaceBackground::Blue), wY(FaceAnimal::Walrus, FaceBackground::Yellow) {
		
		deck.clear();
		
		deck.push_back(&cR);
		deck.push_back(&cG);
		deck.push_back(&cP);
		deck.push_back(&cB);
		deck.push_back(&cY);

		deck.push_back(&pR);
		deck.push_back(&pG);
		deck.push_back(&pP);
		deck.push_back(&pB);
		deck.push_back(&pY);

		deck.push_back(&oR);
		deck.push_back(&oG);
		deck.push_back(&oP);
		deck.push_back(&oB);
		deck.push_back(&oY);

		deck.push_back(&tR);
		deck.push_back(&tG);
		deck.push_back(&tP);
		deck.push_back(&tB);
		deck.push_back(&tY);

		deck.push_back(&wR);
		deck.push_back(&wG);
		deck.push_back(&wP);
		deck.push_back(&wB);
		deck.push_back(&wY);

		
	}
	CardDeck(const CardDeck&);                 // Prevent copy-construction
	CardDeck& operator=(const CardDeck&);
	static CardDeck* cd;
#if TEST_CARDDECK_REWARDDECK_
	friend int main();
#endif

};

 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//RewardDeck Class

class RewardDeck : public Deck<Reward> {
	Reward one1, one2, one3, two1, two2, three1, four1;
public:
	//creates and return the same CardDeck during the execution of the program
	static RewardDeck& make_RewardDeck() {
		if (rd == NULL) {
			rd = new RewardDeck();
		}
		return *rd;
	}
	Reward* getNext() {

		

		if (RewardDeck::make_RewardDeck().isEmpty()) {
			return NULL;
		}
		else {
			Reward* next;
			next = deck.back();
			deck.pop_back();
			return next;
		}

	}
	
private:
	//RewardDeck constructor
	RewardDeck():one1(1), one2(1), one3(1), two1(2), two2(2), three1(3), four1(4) {
		deck.clear();

		deck.push_back(&one1);
		deck.push_back(&one2);
		deck.push_back(&one3);

		deck.push_back(&two1);
		deck.push_back(&two2);

		deck.push_back(&three1);

		deck.push_back(&four1);
	}
	RewardDeck(const RewardDeck&);                 // Prevent copy-construction
	RewardDeck& operator=(const RewardDeck&);
	static RewardDeck* rd;
#if TEST_CARDDECK_REWARDDECK_
	friend int main();
#endif

};



#endif