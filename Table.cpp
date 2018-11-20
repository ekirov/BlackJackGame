
#include "Table.h"


Table::Table(){
	this->plr = nullptr;
	this->dlr = nullptr;
	this->shoe = nullptr;
	this->lastHand = false;
}

void Table::startGame(){
	Player *player = this->plr;
	Shoe *shoe = this->shoe;
	Dealer *dealer = this->dlr;
	dealer->introduction();

	/*
		Get player's bankroll
	*/
	cout << "How much money would you like to play with? Then press enter" << endl;
	cout << "$";
	cin >> player->bankroll;
	if (player->bankroll <= 0){
		cout << "Player does not have enough money to play." << endl;
		return;
	}
	
	/*
		Add cards to the shoe and shuffle them
	*/
	shoe->addCards();
	cout << "New deck of cards being added to table." << endl;
	cout << "Dealer will now shuffle the cards..." << endl;
	dealer->shuffleDeck(shoe->cards);
	dealer->insertCutCard(shoe->cards);
	shoe->cards.pop_back();//burn card
	

	/*
		Game starts here, player places a bet and dealer hands out the cards
	*/
	while (player->bankroll > 0){
		if (!lastHand)
		{
			string play = "";
			cout << endl;
			cout << "-------------------------------------------------------------" << endl;
			cout << "Would you like to play, yes (y) or no(n)? Then press enter." << endl;
			cin >> play;
			if (play == "no" || play == "n")
				return; //if player no longer wishes to play then return.
			cout << "-------------------------------------------------------------" << endl;
			cout << "-------------------------------------------------------------" << endl;
			cout << "\t\t\tNEW HAND" << endl;
			cout << "-------------------------------------------------------------" << endl;
			cout << "-------------------------------------------------------------" << endl;
			
			/*
				Player places initial bet
			*/
			cout << "You have $" << player->bankroll << endl;
			player->placeBet();
			cout << endl;
			dealer->giveInitCards(player, shoe->cards, this);

			/*
				If player has blackjack then player wins.
			*/
			int hand_index = 0;
			if (player->hands[0]->score == 21 && dealer->hand->score != 21){
				player->showHand(0);
				dealer->payBlackjack(player);
			}
			/*
				If player has blackjack and dealer has blackjack then it is a push.
			*/
			else if (player->hands[0]->score == 21 && dealer->hand->score == 21){
				player->showHand(0);
				dealer->showHand();
				cout << "RESULTS: PUSH" << endl;
				cout << "Bet from HAND " << hand_index + 1 << " returned." << endl;
				player->bankroll += player->bet;
			}
			/*
				If dealer has blackjack and player does not then dealer wins.
			*/
			else if (dealer->hand->score == 21 && player->hands[0]->score != 21){
				cout << endl;
				cout << "-------------------------------------------------------------" << endl;
				cout << "Results:" << endl;
				cout << "Dealer has blackjack. You Lose." << endl;;
				dealer->showHand();
				player->showHand(0);
			}
			/*
				If player and dealer do not have blackjack then give them the option to stay, hit, or double down.
			*/
			else {
				int count = 0; //number of actions in the current hand
				bool splitable = false; //whether current is hand is able to be split
				/*
					Loop through each hand the player has.
				*/
				while (hand_index < player->hands.size()){
					/*
						If the current player's hand score is <= 21 then action is allowed  
					*/
					if (player->hands[hand_index]->score < 22){
						
						/*
							Check whether the current hand is able to be split
						*/
						if (count== 0 && player->hands[hand_index]->cards.size()==2){
							splitable = player->handSplitable(hand_index);
						}
						else if (player->hands[hand_index]->cards.size() == 1){
							dealer->givePlayerCard(player, shoe->cards, this, hand_index);
							splitable = player->handSplitable(hand_index);
						}
						else if (player->hands[hand_index]->cards.size()>2){
							splitable = false;
						}

						/*
							Display information about the cards for the player
						*/
						dealer->displayInitHolding();
						cout << endl;
						player->showHand(hand_index);
						
						/*
							Get the player's decision. 
						*/
						string decision = "";
						cout << "-------------------------------------------------------------" << endl;
						cout << "HAND " << hand_index + 1 << endl;
						cout << "Would you like to stay (type s), hit (type h), double-down (type dd), or split (type split)? Then press enter." << endl;
						cin >> decision;
						cout << "-------------------------------------------------------------" << endl;
						
						/*
							Depending on the decision perform certain actions.
						*/
						/* stay */
						if (decision == "s"){
							if (hand_index+1 == player->hands.size())
								player->stay(dealer, shoe->cards, this);
							hand_index++;
							count = 0;
						}
						/* hit */
						else if (decision == "h"){
							player->hit(dealer, shoe->cards, this, hand_index);
							if (player->hands[hand_index]->score > 21 && hand_index + 1 != player->hands.size()){
								cout << "This hand has busted!" << endl;
								hand_index++;
								count = 0;
							}
							else if (player->hands[hand_index]->score > 21 && hand_index + 1 == player->hands.size()){
								cout << "This hand has busted!" << endl;
								player->stay(dealer, shoe->cards, this);
								hand_index++;
								count = 0;
							}
							else{
								count++;
							}
							
						}
						/* double down */
						else if (decision == "dd"){
							if (player->bankroll < player->hands[hand_index]->bet){
								cout << "ERROR: You do not have enough money to double down. Please select another action." << endl;
								cout << "-------------------------------------------------------------" << endl;
							}
							else if (count == 0){
								player->doubleDown(dealer, shoe->cards, this, hand_index);
								hand_index++;
								count = 0;
							}
							else{
								cout << "ERROR: You may only double down on your first action. Please select another action." << endl;
								cout << "-------------------------------------------------------------" << endl;
							}

						}
						/* split */
						else if (decision == "split"){
							if (player->bankroll < player->hands[hand_index]->bet){
								cout << "Error: You do not have enough money to split. Please select another action." << endl;
								cout << "-------------------------------------------------------------" << endl;
							}
							else if (splitable){
								/*
								Will split the current hand into two hands and leave the hand index on the current hand.
								*/
								player->split(dealer, shoe->cards, this, hand_index);
							}
							else
							{
								cout << "Error: Your two cards are not of equal value and cannot be split. Please select another action." << endl;
								cout << "-------------------------------------------------------------" << endl;
							}
						}
						else{
							cout << "Error: Your input must be from the above options. Please select another action." << endl;
							cout << "-------------------------------------------------------------" << endl;
						}
					}
					else{
						hand_index += 1;
					}
					

				}

			}
		}
		else{
			/*
				Once the cut card has been pulled then the last hand of the table has been played and new cards are shuffled and put into play.
			*/
			shoe->cards.empty();
			shoe->addCards();
			cout << endl;
			cout << endl;
			cout << "New deck of cards being added to table." << endl;
			cout << "Dealer will now shuffle the cards..." << endl;
			dealer->shuffleDeck(shoe->cards);
			dealer->insertCutCard(shoe->cards);
			lastHand = false;
		}

		if (player->bankroll <= 0){
			/*
				If player has run out of money ask them if they would like to add more money.
			*/
			cout << "-------------------------------------------------------------" << endl;
			cout << "Would you like to add on more money? (y) or (n). Then press enter" << endl;
			string decision = "";
			cin >> decision;
			if (decision == "n" || decision == "no")
				return;
			else{
				cout << "How much money would you like to add on? Then press enter." << endl;
				cin >> player->bankroll;
			}
		}
		
	}
	

	


}