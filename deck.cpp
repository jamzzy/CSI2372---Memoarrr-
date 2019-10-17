#include "deck.h"

//Initializes static pointers in carddeck and rewarddeck
CardDeck *CardDeck::cd = NULL;
RewardDeck *RewardDeck::rd = NULL;

#if TEST_CARDDECK_REWARDDECK_
int main() {
	std::cout << "Can't create object Deck, because its abstract but pointer of Deck is possible." << std::endl;
	std::cout << "Creating both CardDeck and RewardDeck. When accesing these decks, the same deck is returned every time until the end of the program." << std::endl;
	CardDeck::make_CardDeck();
	RewardDeck::make_RewardDeck();

	Card* testCard = CardDeck::make_CardDeck().getNext();
	Reward* testReward = RewardDeck::make_RewardDeck().getNext();

	std::cout << "Testing getNext." << std::endl;
	std::cout << std::endl;
	std::cout << "Card popped from getNext." << std::endl;
	std::cout << std::endl;

	for (int r = 0; r < 3; r++) {
		std::string row = (*testCard)(r);
		std::cout << row << std::endl;
	}
	int testRub = *testReward;
	std::cout << std::endl;
	std::cout << "Rubies popped from getNext: " << testRub << std::endl;
	std::cout << std::endl;
	std::cout << "Testing shuffle." << std::endl;

	CardDeck::make_CardDeck().shuffle();
	RewardDeck::make_RewardDeck().shuffle();

	std::cout << "The next card popped should be Walrus:Blue if CardDeck is not shuffled, but it is: "<<std::endl;
	std::cout << std::endl;
	testCard = CardDeck::make_CardDeck().getNext();
	for (int r = 0; r < 3; r++) {
		std::string row = (*testCard)(r);
		std::cout << row << std::endl;
	}
	std::cout << std::endl;
	std::cout << "RewardDeck empty?: " << RewardDeck::make_RewardDeck().isEmpty() << ", CardDeck empty?: " << CardDeck::make_CardDeck().isEmpty() << std::endl;


	system("pause");
	return 0;
}
#endif