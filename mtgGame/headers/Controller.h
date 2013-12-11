/*
 * Controller.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

//#include "Player.h"
#include <vector>
#include "colors.h"
#include "CardList.h"
#include "DeckList.h"
#include "CardSelector.h"

class Planeswalker;
class Card_Land;
class Card;
class Player;

class Controller {
public:
	Controller();
	virtual ~Controller();
//	Return true to mulligan
	virtual bool Mulligan(bool) = 0;
//	Return true to be on the play
	virtual bool PlayFirst() = 0;
//	Return NULL if no play
	virtual Playable* MakePlay(bool) = 0;
//	MakeAttacks chooses which creatures will attack
	virtual vector<Card*> MakeAttacks() = 0;
//	TargetAttacks chooses which planeswalker attackers will attack
	virtual vector<Planeswalker*> AssignAttacks(vector<Card*>) = 0;
//	MakeBlocks returns vector of blockers
	virtual vector<Card*> MakeBlocks(vector<Card*>) = 0;
//	AssignBlocks needs to return a vector of which creature each blocker is blocking
	virtual vector<Card*> AssignBlocks(vector<Card*>,vector<Card*>) = 0;
//	OrderBlocks takes in an attacker and a vector of blockers and returns an ordering (vector of integers 0 through blocker.size() in new ordering)
	virtual vector<int> OrderBlocks(Card*,vector<Card*>) = 0;
//	AssignDamage takes the attacker and ordered set of blockers and returns a vector of the damage for each one
	virtual vector<int> AssignDamage(Card*,vector<Card*>) = 0;
//	Generate and return a vector of new cards
	virtual vector<Card*> GetDeck()=0;
	virtual vector<Card*> ChooseDiscards(int) = 0;

	Player* myPlayer;
	Player* oppPlayer;
};

#endif /* CONTROLLER_H_ */
