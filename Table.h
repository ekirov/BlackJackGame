#ifndef TABLE_H
#define TABLE_H
#include "Dealer.h"
#include "Shoe.h"
#include "Player.h"
#include <iostream>
#include <string>
class Dealer;
class Player;
class Shoe;
using namespace std;

class Table{
public:
	Dealer *dlr;
	Player *plr;
	Shoe *shoe;
	void startGame();
	bool lastHand;
	Table();
};




#endif