#include "Hand.h"
#include <iostream>
#include <string>
using namespace std;

Hand::Hand(){
	this->score = 0;
	this->aces = 0;
	this->completed = false;
	this->split = false;
	this->bet = 0;
}