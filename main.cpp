//CSI 2372: Project Fall 2018
//James Lim 7344055
//Viran Daluwatte 7276119

#include <iostream>
#include "player.h"
#include "deck.h"
#include "card.h"
#include "reward.h"
#include "board.h"
#include "game.h"
#include "rules.h"
#include <string.h>
#include <ctype.h>
#include <algorithm>
#include <vector>
#include "expertrules.h"

//returns true if player i has less rubies than player j
bool wayToSort(const Player& i, const Player& j) { return i.getNRubies() < j.getNRubies(); }

//Switch to turn the main 0 OFF/1 ON
#define MAIN_ 1
#if MAIN_ 

int main() {
	//helper variables
	Side s[4] = { Side::top,Side::right,Side::bottom,Side::left };
	Letter l[5] = { Letter::A,Letter::B ,Letter::C ,Letter::D ,Letter::E };
	Number n[5] = { Number::one,Number::two,Number::three,Number::four,Number::five };
	char letters[] = "ABCDE";
	char nums[] = "12345";
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Initialize some variables corresponding to game options
	int numP = 0;
	int gameMode = 0;
	int gameDisplay = 0;
	std::cout << "----------     WELCOME TO MEMOARRR!     ----------" << std::endl;
	std::cout << "By James Lim 7344055 && By Viran Daluwatte 7276119" << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Determing which rules to use
	std::cout << "Enter 0 for Normal Rules or 1 for Expert Rules: ";
	while (true) {
		std::cin >> gameMode;

		if (!std::cin) {
			std::cout << "Invalid Entry: Please enter 0 for Normal Rules or 1 for Expert Rules: ";
			std::cin.clear(); // reset failbit
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input	
			std::cout << gameMode << std::endl;
		}
		else {
			if (gameMode == 0 || gameMode == 1) {
				break;
			}
			else {
				std::cout << "Invalid Entry: Please enter 0 for Normal Rules or 1 for Expert Rulesdfdfdfdfd: ";
				std::cout << gameMode << std::endl;
				std::cin.clear(); // reset failbit
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input	
			}
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Determining which display to use
	std::cout << "Enter 0 for Normal Display or 1 for Expert Display: ";
	while (true) {
		std::cin >> gameDisplay;

		if (!std::cin) {
			std::cout << "Invalid Entry: Please enter 0 for Normal Display or 1 for Expert Display: ";
			std::cin.clear(); // reset failbit
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input	
			std::cout << gameMode << std::endl;
		}
		else {
			if (gameDisplay == 0 || gameDisplay == 1) {
				break;
			}
			else {
				std::cout << "Invalid Entry: Please enter 0 for Normal Display or 1 for Expert Display: ";
				std::cin.clear(); // reset failbit
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input	
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Create game and both rule variables, configuring game according to user input
	Game mygame;
	Rules myBaseRules;
	ExpertRules myrules;
	bool expertMode = false;

	if (gameDisplay == 1) {

		mygame.setExpertDisplay(true);
	}
	if (gameMode == 1) {
		expertMode = true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Determining number of players
	std::cin.clear();
	std::cout << "Select number of players (2-4): ";
	while (true) {
		std::cin >> numP;
		if (!std::cin || numP > 4 || numP < 2) {
			std::cout << "Invalid Entry: Please enter a number from 2 to 4:";
			std::cin.clear(); // reset failbit
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input	
		}
		else {
			break;
		}
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Creating and adding players to game
	std::vector<std::string> names;
	std::string nom;
	while (true) {
		for (int i = 0; i < numP; i++) {
			std::cout << "Enter the name of Player " << i + 1 << ": ";
			std::cin >> nom;
			if (names.empty()) {
				names.push_back(nom);
			}
			else {
				std::string dup = "";
				int size = static_cast<int> (names.size());
				bool duplicate = false;
				for (int i = 0; i < size; i++) {
					if (nom == names[i]) {
						duplicate = true;
						dup = names[i];
					}
					if (duplicate) {
						break;
					}
				}
				if (duplicate) {
					while (nom == dup) {
						std::cout << "Player already exists, choose different name: ";
						std::cin >> nom;
					}
					names.push_back(nom);
				}
			}
			(mygame).addPlayer(Player(nom, s[i]));
		}
		break;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Start of game, each player see the first 3 cards in the before the first round
	
	std::cout << std::endl;

	if (mygame.getRound() == 0) {
		int x = 0;
		while (x < numP) {
			if (x == 0) {
				for (int i = 0; i < 3; i++) {
					std::cout << (*mygame.getCard(Letter::A, Number::two))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::A, Number::three))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::A, Number::four))(i) << std::endl;
				}
				std::cout << std::endl;
				std::cout << " A2   A3   A4" << std::endl;
				std::cout << std::endl;
				std::cout << mygame.getPlayer(Side::top).getName() << " these are the 3 cards in front of you." << std::endl;
				
			}
			else if (x == 1) {
				for (int i = 0; i < 3; i++) {
					std::cout << (*mygame.getCard(Letter::B, Number::five))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::C, Number::five))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::D, Number::five))(i) << std::endl;
				}
				std::cout << std::endl;
				std::cout << " B5   C5   D5" << std::endl;
				std::cout << std::endl;
				std::cout << mygame.getPlayer(Side::right).getName() << " these are the 3 cards in front of you." << std::endl;
				
			}
			else if (x == 2) {
				for (int i = 0; i < 3; i++) {
					std::cout << (*mygame.getCard(Letter::E, Number::two))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::E, Number::three))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::E, Number::four))(i) << std::endl;

				}
				std::cout << std::endl;
				std::cout << " E2   E3   E4" << std::endl;
				std::cout << std::endl;
				std::cout << mygame.getPlayer(Side::bottom).getName() << " these are the 3 cards in front of you." << std::endl;
				
			}
			else if (x == 3) {
				for (int i = 0; i < 3; i++) {
					std::cout << (*mygame.getCard(Letter::B, Number::one))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::C, Number::one))(i) << "  ";
					std::cout << (*mygame.getCard(Letter::D, Number::one))(i) << std::endl;

				}
				std::cout << std::endl;
				std::cout << " B1   C1   D1" << std::endl;
				std::cout << std::endl;
				std::cout << mygame.getPlayer(Side::left).getName() << " these are the 3 cards in front of you." << std::endl;
				
			}
			std::cout << std::endl;
			system("pause");
			std::cout << std::endl;
			x++;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Game running, expertMode is false then run base rules, thus base game
	if (!expertMode) {
		while (!myBaseRules.gameOver(mygame)) {
			std::cout << mygame << std::endl;

			while (!myBaseRules.roundOver(mygame)) {
				char selection[] = "XX";
				std::cout << "----- ROUND " << mygame.getRound() + 1 << " ----- " << std::endl;
				Player current = myBaseRules.getNextPlayer(mygame);

				std::string nom = current.getName();

				while (true) {
					Letter ll;
					Number nn;
					bool lTrigger = false;
					bool nTrigger = false;

					std::cout << nom << " its your turn! Please select a card: ";

					std::cin >> *selection >> *(selection + 1);

					std::cout << "--------------------------------------------" << std::endl;
					for (int i = 0; i < 5; i++) {
						if (*selection == *(letters + i)) {
							ll = l[i];
							lTrigger = true;

						}
						if (*(selection + 1) == *(nums + i)) {
							nn = n[i];
							nTrigger = true;

						}
					}

					try {
						if (!lTrigger || !nTrigger) {
							throw OutOfRange();
						}

						mygame.setCurrentCard(mygame.getCard(ll, nn));
						break;

					}

					catch (ChangeSelection e) {
						std::cout << e.what() << std::endl;
						std::cin.clear();
						std::cin.ignore();
					}
					catch (OutOfRange ex) {
						std::cout << ex.what() << std::endl;
						std::cin.clear();
						std::cin.ignore();
					}
				}
				if (!myBaseRules.isValid(mygame)) {
					current.setActive(false);
					mygame.addPlayer(current);
				}
				std::cout << mygame << std::endl;
				if (mygame.allCardsUp()) {
					std::cout << "ALL CARDS ARE FACE UP! Everyone after this player will lose until one is left!" << std::endl;
					while (!myBaseRules.roundOver(mygame)) {
						Player loser = myBaseRules.getNextPlayer(mygame);
						loser.setActive(false);
						mygame.addPlayer(loser);
						std::cout << mygame << std::endl;
						system("pause");
					}
				}
			}
			Player winRound = myBaseRules.getNextPlayer(mygame);
			winRound.addReward(*RewardDeck::make_RewardDeck().getNext());
			mygame.addPlayer(winRound);
			std::cout << "END OF ROUND" << std::endl;
			std::cout << std::endl;
			mygame.nextRound();
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//if expertmode true, run expert rules, thus expert game
	//following code is identical to above but additionally implements the expert rules when applicable
	//refer to expertrules.h and expertrules.cpp to find further descriptions of methods if necessary
	else {
		while (!myrules.gameOver(mygame)) {
			std::cout << mygame << std::endl;
			while (!myrules.roundOver(mygame)) {
				char selection[] = "XX";
				std::cout << "----- ROUND " << mygame.getRound() + 1 << " ----- " << std::endl;
				Player current = myrules.getNextPlayer(mygame);
				std::string nom = current.getName();

				while (true) {
					Letter ll;
					Number nn;
					bool lTrigger = false;
					bool nTrigger = false;
					std::cout << nom << " its your turn! Please select a card: ";
					std::cin >> *selection >> *(selection + 1);
					for (int i = 0; i < 5; i++) {
						if (*selection == *(letters + i)) {
							ll = l[i];
							lTrigger = true;

						}
						if (*(selection + 1) == *(nums + i)) {
							nn = n[i];
							nTrigger = true;

						}
					}

					try {
						if (!lTrigger || !nTrigger) {
							throw OutOfRange();
						}
						
						if (myrules.walrusBlock) {//If the walrus trigger is activated, check's if the player's card selection is valid/has been blocked.
							if (myrules.wBlocked._lett == ll && myrules.wBlocked._num == nn) {
								throw WalrusBlockException();
							}
							else if (mygame.checkFaceUp(false, ll, nn)) {
								throw ChangeSelection();
							}
						}
						mygame.setCurrentCard(mygame.getCard(ll, nn));

						myrules.walrusBlock = false;//If this stage is reached, the walrus rules have been implemented and the trigger is set to false.

						break;

					}

					catch (ChangeSelection e) {
						std::cout << e.what() << std::endl;
						std::cin.clear();
						std::cin.ignore();
					}
					catch (OutOfRange ex) {
						std::cout << ex.what() << std::endl;
						std::cin.clear();
						std::cin.ignore();
					}
					catch (WalrusBlockException exx) {
						std::cout << exx.what() << std::endl;
					}
				}

				if (!myrules.isValid(mygame)) {
					current.setActive(false);
					mygame.addPlayer(current);
				}
				if (mygame.allCardsUp()) {
					std::cout << "ALL CARDS ARE FACE UP! Everyone after this player will lose until one is left!" << std::endl;
					while (!myrules.roundOver(mygame)) {
						Player loser = myrules.getNextPlayer(mygame);
						loser.setActive(false);
						mygame.addPlayer(loser);
						std::cout << mygame << std::endl;
						system("pause");
					}
				}
				else {
					while (true) {
						try {
							if (myrules.walrusBlock) {//If walrus trigger is active, receives the player's card selection to be blocked.
								//Handles invalid chard entries or card choices.
								while (true) {
									std::cout << "Please select a card to Walrus Block: ";
									char chn[] = "XX";
									std::cin >> chn;
									myrules.wBlocked = ExpertRules::toLoc(chn);
									try {
										if (!mygame.checkFaceUp(true, myrules.wBlocked._lett, myrules.wBlocked._num)) {
											std::cout << "You have blocked ";
											ExpertRules::LocPrint(myrules.wBlocked);
											std::cout << "!" << std::endl;
											break;
										}
										else {
											
											throw "That card is face-up! Please select a card that is face-down.\n";
										}
									}
									catch (const char* errrr) {
										std::cerr << errrr << std::endl;
									}
									catch (OutOfRange exep) {
										std::cout << exep.what() << std::endl;

									}
								}

							}
							if (myrules.penguinFlip) {//If the penguin trigger is active, receives a player's selection for a face up card to flip.
								//Handles invalid card entries or card choices.
								char cho[] = "XX";
								while (true) {
									std::cout << "Please select a face-up card to flip: " << std::endl;
									std::cin >> cho;
									ExpertRules::Loc pFlipLoc = ExpertRules::toLoc(cho);
									try {
										if (mygame.checkFaceUp(true, pFlipLoc._lett, pFlipLoc._num)) {
											std::cout << "You have flipped ";
											ExpertRules::LocPrint(pFlipLoc);
											std::cout << "!" << std::endl;
											break;
										}
										//throws exception if player selects a card that is already face down and goes back into the loop.
										else {
											throw "That card is already face-down!\n";
										}
									}
									catch (const char* errrr) {
										std::cerr << errrr << std::endl;
									}
									catch (OutOfRange exep) {
										std::cout << exep.what() << std::endl;

									}
								}
								myrules.penguinFlip = false;
							}
							if (myrules.octSwap) {//If the octopus trigger is active, the current card is switched with the adjacent card the player has selected.
								ExpertRules::Loc currentCardLoc = ExpertRules::getCardLocation(mygame.getCurrentCard(), mygame);
								Card* AcurrentCard = mygame.getCard(currentCardLoc._lett, currentCardLoc._num);
								mygame.setCard(myrules.octCard._lett, myrules.octCard._num, AcurrentCard);
								myrules.octSwap = false;
							}
							break;
						}
						catch (const Card* ccc) {
							try {
								mygame.setCurrentCard(ccc);
							}
							catch (ChangeSelection xx) {
								std::cout << xx.what() << std::endl;
							}
						}
					}
				}
				std::cout << mygame << std::endl;
			}
			Player winRound = myrules.getNextPlayer(mygame);
			winRound.addReward(*RewardDeck::make_RewardDeck().getNext());
			std::cout << "END OF ROUND" << std::endl;
			std::cout << std::endl;
			mygame.addPlayer(winRound);
			mygame.nextRound();
		}
	}
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//End of Game, displaying players sorted by least to greatest rubies, finally displaying winner.
	std::cout << "----------END OF GAME------------" << std::endl;
	std::cout << std::endl;
	std::vector<Player> gameFini;
	for (int x = 0; x < numP; x++) {
		gameFini.push_back(mygame.getPlayer(s[x]));
	}
	sort(gameFini.begin(), gameFini.end(), wayToSort);
	for (Player &n : gameFini) {
		n.setDisplayMode(true);
		std::cout << n;;
	}
	std::cout << std::endl;
	std::cout << "THE WINNER IS: " << gameFini.back().getName() << std::endl;
	system("pause");
}
#endif

//James Lim 7344055
//Viran Daluwatte 7276119
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
