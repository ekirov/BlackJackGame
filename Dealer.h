#ifndef DEALER_H
#define DEALER_H
#include "Card.h"
#include "Player.h"
#include "Table.h"
#include "Hand.h"
class Player;
class Table;
class Hand;
#include <vector>
#include <iostream>


using namespace std;



class Dealer{
public:
	//int aces;
	string id;
	//int score;
	Hand *hand;
	void introduction();
	void enterGame();
	void shuffleDeck(vector<Card *> &shoe);
	void giveInitCards(Player *p, vector<Card *> &d, Table *t);
	void giveSelfCards(vector<Card *> &d, Table *t);
	void givePlayerCard(Player *p, vector<Card *> &d, Table *t, int hand_index);
	void payBlackjack(Player *p);
	void payPlayer(Player *p, int hand_index);
	void takeMoney(Player *p);
	void showHand();
	void insertCutCard(vector<Card *> &d);
	void displayInitHolding();
	void adjustScoreAces();
	Dealer(string str);
};


#endif