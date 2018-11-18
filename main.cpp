#include "Card.h"
#include "Dealer.h"
#include "Table.h"
#include "Player.h"
#include "Deck.h"
#include "Hand.h"
using namespace std;




int main(){
	Table *bj_table = new Table();
	Dealer *d = new Dealer("Bob");
	Player *p = new Player();
	Deck * dk = new Deck();
	bj_table->dlr = d;
	bj_table->plr = p;
	bj_table->deck = dk;
	bj_table->startGame();
	return 0;
}