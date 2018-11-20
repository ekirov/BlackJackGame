#ifndef SHOE_H
#define SHOE_H
#include "Card.h"
#include <vector>
#include <iostream>


using namespace std;


class Shoe{
public:
	vector<Card *> cards;
	void addCards();
};

#endif