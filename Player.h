#ifndef PLAYER_H
#define PLAYER_H
#include "Dealer.h"
#include "Card.h"
#include "Hand.h"
class Dealer;
class Table;
class Hand;
#include <vector>


using namespace std;

class Player{
public:
	//int aces;
	//string id;
	float bankroll;
	float bet;
	vector<Hand *> hands;
	//bool bust;
	void doubleDown(Dealer *d, vector<Card *> &shoe, Table *t, int hand_index);
	void placeBet();
	void enterGame();
	void stay(Dealer *d, vector<Card *> &shoe, Table *t);
	void hit(Dealer *d, vector<Card *> &shoe, Table *t, int hand_index);
	void adjustScoreAces(int hand_index);
	void displayInitHolding();
	void showHand(int hand_index);
	void split(Dealer *d, vector<Card *> &shoe, Table *t, int hand_index);
	bool handSplitable(int hand_index);
	Player();
};


#endif