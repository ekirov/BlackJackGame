#include "Dealer.h"
#include <algorithm>
#include <string>
#include <time.h>

Dealer::Dealer(string str){
	this->id = str;
	this->hand = nullptr;
	//this->score = 0;
	//this->aces = 0;
}


void Dealer::introduction(){
	cout << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << endl;
	cout << "WELCOME TO THE BLACKJACK TABLE!" << endl;
	cout << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << char(3) << char(4) << char(5) << char(6) << endl;
	cout << "Casino Rules:" << endl;
	cout << "1. Blackjack pays 3:2" << endl;
	cout << "2. Dealer must hit on soft 17." << endl;
	cout << "3. Doubling down after a split is allowed." << endl;
	cout << "4. Action after splitting Aces is allowed." << endl;
	cout << endl;
}

/*
	give the dealer and the player their initial hands as well as update the scores of the hands
*/
void Dealer::giveInitCards(Player *p, vector<Card *> &d, Table *t){
	Hand *dhand = new Hand();
	this->hand = nullptr;
	p->hands.clear();
	
	Hand *phand = new Hand();
	phand->bet = p->bet;
	for (int i = 0; i < 2; i++){
		if (d.back()->type == "cut"){
			t->lastHand = true;
			d.pop_back();
		}
		if (d.back()->type == "A"){
			phand->aces += 1;
		}
		phand->cards.push_back(d.back());
		phand->score += d.back()->value; //update player score
		d.pop_back();
		if (d.back()->type == "cut"){
			t->lastHand = true;
			d.pop_back();
		}
		if (d.back()->type == "A"){
			dhand->aces += 1;
		}
		dhand->cards.push_back(d.back());
		dhand->score += d.back()->value; //update dealer score
		d.pop_back();
	}
	if (dhand->score > 21 && dhand->aces > 0){
		dhand->aces -= 1;
		dhand->score -= 10;
	}
	this->hand = dhand;
	p->hands.push_back(phand);
}

/*
	give the player one card and update the score of his hand
*/
void Dealer::givePlayerCard(Player *p, vector<Card *> &d, Table *t, int hand_index){
	Card *c = d.back();
	if (c->type == "cut"){
		t->lastHand = true;
		d.pop_back();
		c = d.back();
	}
	if (c->type == "A"){
		p->hands[hand_index]->aces += 1;
	}
	d.pop_back();
	p->hands[hand_index]->cards.push_back(c);
	p->hands[hand_index]->score += c->value;
	if (p->hands[hand_index]->aces > 0 && p->hands[hand_index]->score > 21){
		p->adjustScoreAces(hand_index);
	}
}

/*
	Display the face up card of the dealer
*/
void Dealer::displayInitHolding(){
	cout << "Dealer Card: ";
	for (vector<Card *>::iterator it = this->hand->cards.begin(); it != this->hand->cards.end(); ++it){
		if (it == this->hand->cards.begin()){
			cout << (*it)->type << (*it)->suit << endl; //print dealers card
			cout << "Dealer Score: " << (*it)->value << endl;
		}
	}
}

/*
	randomise the deck of 6 cards
*/
void Dealer::shuffleDeck(vector<Card *> &shoe){
	srand(time(0));
	random_shuffle(shoe.begin(), shoe.end());
}

/*
	Pay blackjack to the player
*/
void Dealer::payBlackjack(Player *p){
	cout << endl;
	cout << "=====================================================" << endl;
	cout << "RESULTS: BLACKJACK! Pays 3:2" << endl;
	float winnings = p->bet * 1.5;
	cout << "HAND WINS $" << winnings <<endl;
	p->bankroll += p->bet + winnings;
	cout << "Your current bankroll is $" << p->bankroll << endl;
	//reset everything
}

/*
	Pay the player his winning hand based on the bet of the hand.
*/
void Dealer::payPlayer(Player *p, int hand_index){
	//cout << endl;
	//cout << "============";
	//cout << "Results:" << endl;
	float winnings = p->hands[hand_index]->bet;
	p->bankroll += winnings + winnings;
}

/*
	Once all the action from the player is complete give the dealer cards until he hits 17 or busts.
*/
void Dealer::giveSelfCards(vector<Card *> &d, Table *t){
	do{
		if (d.back()->type == "cut"){
			t->lastHand = true;
			d.pop_back();
		}
		Card *cur = d.back();
		this->hand->cards.push_back(cur);
		d.pop_back();
		this->hand->score += cur->value;
		if (cur->type == "A")
			this->hand->aces += 1;
		if (this->hand->aces > 0 && this->hand->score > 21){
			this->adjustScoreAces();
		}
	} while (this->hand->score < 17);

	this->showHand();

}

/*
	If a player is over 21 and has an ace then adjust the score of his hand
*/
void Dealer::adjustScoreAces(){
	this->hand->aces -= 1;
	this->hand->score -= 10;
}

/*
	Display all the cards that the dealer has
*/
void Dealer::showHand(){
	cout << "Dealers Cards: ";
	for (vector<Card *>::iterator it = this->hand->cards.begin(); it != this->hand->cards.end(); ++it){
		cout << (*it)->type << (*it)->suit << " ";
	}
	cout << endl;
	cout << "Dealer's Score: " << this->hand->score << endl;
	cout << endl;
}

/*
	Insert the cut card 1.5 decks into the 6 decks.
*/
void Dealer::insertCutCard(vector<Card *> &shoe){
	vector<Card *>::iterator it = shoe.begin();
	Card *cut = new Card();
	cut->suit = 'c';
	cut->type = "cut";
	cut->value = 0;
	shoe.insert(it + 78, cut);
}