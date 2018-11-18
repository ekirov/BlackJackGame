#ifndef TABLE_H
#define TABLE_H
#include "Dealer.h"
#include "Deck.h"
#include "Player.h"
#include <iostream>
#include <string>
class Dealer;
class Player;
class Deck;
using namespace std;

class Table{
public:
	Dealer *dlr;
	Player *plr;
	Deck *deck;
	void startGame();
	bool lastHand;
	Table();
};




#endif