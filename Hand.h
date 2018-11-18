#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include <vector>
using namespace std;

class Hand{
public:
	vector<Card *> cards;
	int score;
	bool split;
	bool completed;
	int aces;
	float bet;
	Hand();
};




#endif