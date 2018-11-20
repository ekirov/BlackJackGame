#include "Shoe.h"
#include <algorithm>
#include <string>

/*
Add 6 decks worth of cards
*/
void Shoe::addCards(){
	this->cards.empty();
	vector<char> suits{ 3, 4, 5, 6 };

	for (int i = 2; i <= 10; i++){
		for (vector<char>::iterator it = suits.begin(); it != suits.end(); ++it){
			Card *cur = new Card();
			cur->suit = *it;
			cur->type = to_string(i);
			cur->value = i;
			for (int j = 0; j < 6; j++){
				this->cards.push_back(cur);
			}
		}
	}
	vector<string> face_cards{ "J", "Q", "K" };
	for (vector<string>::iterator it = face_cards.begin(); it != face_cards.end(); ++it){
		for (vector<char>::iterator it2 = suits.begin(); it2 != suits.end(); ++it2){
			Card *cur = new Card();
			cur->suit = *it2;
			cur->type = *it;
			cur->value = 10;
			for (int j = 0; j < 6; j++){
				this->cards.push_back(cur);
			}
		}
	}
	for (vector<char>::iterator it = suits.begin(); it != suits.end(); ++it){
		for (int i = 0; i < 6; i++){
			Card *cur = new Card();
			cur->suit = *it;
			cur->type = "A";
			cur->value = 11;
			this->cards.push_back(cur);
		}
	}
}

