#include "Player.h"
#include <iostream>
#include <string>
using namespace std;

Player::Player(){
	//this->id = str;
	this->bankroll = 0;
	this->bet = 0;
	//this->score = 0;
	//this->aces = 0;
}

/*
	Display the first two cards of the hand
*/
void Player::displayInitHolding(){
	cout << endl;
	cout << "Your Cards: ";
	vector<Card *> hand = this->hands[0]->cards;
	for (vector<Card *>::iterator it = hand.begin(); it != hand.end(); ++it){
		cout << (*it)->type << (*it)->suit << " "; //print players cards
	}
}

/*
	Calculate the 
*/
void Player::stay(Dealer *dealer, vector<Card *> &shoe, Table *t){
	/*
	If dealer's score is less than 17 then deal the dealer cards until greater than 17.
	Then figure out who the winner is and hand out or take money.
	*/
	
	int busts = 0;
	dealer->showHand();
	for (int hand_index = 0; hand_index < this->hands.size(); hand_index++){
		this->showHand(hand_index);
	}
	cout << "=====================================================" << endl;
	for (int hand_index = 0; hand_index < this->hands.size(); hand_index++){
		if (this->hands[hand_index]->score > 21){ //check if player has busted
			cout << "RESULTS: HAND " << hand_index + 1 << " BUSTED" << endl;
			cout << "HAND " << hand_index + 1 << " LOSES $" << this->hands[hand_index]->bet << endl;
			busts++;
		}
	}
	if (busts != this->hands.size()){
		if (dealer->hand->score < 17 || (dealer->hand->score == 17 && dealer->hand->aces == 1)){
			cout << "Dealer is drawing for cards..." << endl;
			dealer->giveSelfCards(shoe, t);
			for (int hand_index = 0; hand_index < this->hands.size(); hand_index++){
				this->showHand(hand_index);
				cout << endl;
			}
		}
		if (dealer->hand->score > 21){ //check if dealer has busted
			cout << "RESULTS: Dealer has BUSTED" << endl;
			for (int hand_index = 0; hand_index < this->hands.size(); hand_index++){
				if (this->hands[hand_index]->score <= 21){
					cout << "HAND " << hand_index + 1 << " WINS $" << this->hands[hand_index]->bet << endl;
					dealer->payPlayer(this, hand_index);
				}
			}
		}
		else if (dealer->hand->score <= 21){
			for (int hand_index = 0; hand_index < this->hands.size(); hand_index++){
				if (this->hands[hand_index]->score <= 21){
					if (dealer->hand->score == this->hands[hand_index]->score){//PUSH
						cout << "RESULTS: PUSH" << endl;
						cout << "Bet from HAND " << hand_index + 1 << " returned." << endl;
						this->bankroll += this->hands[hand_index]->bet;
					}
					else if (dealer->hand->score > this->hands[hand_index]->score){ // DEALER WIN
						cout << "RESULTS: Dealer beats HAND " << hand_index + 1 << endl;
						cout << "HAND " << hand_index + 1 << " LOSES $" << this->hands[hand_index]->bet << endl;
					}
					else if (dealer->hand->score < this->hands[hand_index]->score) //PLayer WIN
					{
						cout << "RESULTS: YOU WIN, HAND " << hand_index + 1 << " beats Dealer" << endl;
						cout << "HAND " << hand_index + 1 << " WINS $" << this->hands[hand_index]->bet << endl;
						dealer->payPlayer(this, hand_index);
					}
				}
			}
		}
	}
	cout << "Your current bankroll is $" << this->bankroll << endl;
	
}

//done
void Player::showHand(int hand_index){
	cout << "HAND "<<hand_index+1 <<": ";
	for (vector<Card *>::iterator it = this->hands[hand_index]->cards.begin(); it != this->hands[hand_index]->cards.end(); ++it){
		cout << (*it)->type << (*it)->suit << " ";
	}
	cout << endl << "Hand "<<hand_index+1<<" score: " << this->hands[hand_index]->score << endl;
}

//done
void Player::doubleDown(Dealer *d, vector<Card *> &shoe, Table *t, int hand_index){
	this->bankroll -= this->hands[hand_index]->bet;
	this->hands[hand_index]->bet = this->bet * 2;
	
	d->givePlayerCard(this, shoe, t, hand_index);
	
	if (hand_index+1 == this->hands.size())
		this->stay(d, shoe, t);
}

//done
void Player::hit(Dealer *dealer, vector<Card *> &shoe, Table *t, int hand_index){
	dealer->givePlayerCard(this, shoe, t, hand_index);
}

//done
void Player::placeBet(){
	this->bet = 0;
	while (true){
		cout << "Please input your bet and press enter: " << endl;
		cout << "$";
		cin >> this->bet;
		if (this->bet > this->bankroll){
			cout << "You do not have the bankroll to make this bet, please make a smaller bet." << endl;
		}
		else{
			this->bankroll = this->bankroll - this->bet;
			break;
		}
		
	}
	
}

//done
void Player::adjustScoreAces(int hand_index){
	this->hands[hand_index]->aces -= 1;
	this->hands[hand_index]->score -= 10;
}


void Player::split(Dealer *d, vector<Card *> &shoe, Table *t, int hand_index){
	Hand *hand2 = new Hand();
	hand2->bet = this->bet;
	Card *card2 = this->hands[hand_index]->cards.back(); //take one of the cards from the current hand
	if (card2->type == "A"){
		this->hands[hand_index]->aces -= 1; //if the card was an ace decrement the ace value for the hand
		hand2->aces += 1; //increment the new hand's ace value by one.
	}
	this->hands[hand_index]->score -= card2->value; //decrement the score of the hand
	this->hands[hand_index]->cards.pop_back(); //remove the card from the hand
	this->hands[hand_index]->split = true;

	hand2->cards.push_back(card2);
	hand2->score += card2->value;
	hand2->split = true;
	
	if (this->hands.size() == hand_index + 1)
		this->hands.push_back(hand2);
	else
		this->hands.insert(hands.begin() + hand_index + 1, hand2);

	//now add new card to the current hand
	d->givePlayerCard(this, shoe, t, hand_index);
	this->bankroll -= this->bet;

}


bool Player::handSplitable(int hand_index){
	int temp = 0;
	for (vector<Card *>::iterator it = this->hands[hand_index]->cards.begin(); it != this->hands[hand_index]->cards.end(); ++it){
		if (it == this->hands[hand_index]->cards.begin())
			temp = (*it)->value;
		else{
			if (temp == (*it)->value){
				return true;
			}
		}
	}
	return false;
}


