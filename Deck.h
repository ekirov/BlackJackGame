
#ifndef DECK_H
#define DECK_H
#include "Card.h"
#include <vector>
#include <iostream>


using namespace std;


class Deck{
public:
	vector<Card *> shoe;
	void addCards();
};

#endif