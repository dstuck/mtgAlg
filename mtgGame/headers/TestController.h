/*
 * TestController.h
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#ifndef TESTCONTROLLER_H_
#define TESTCONTROLLER_H_

#include "Controller.h"
#include "Player.h"
#include "Card.h"
#include "Card_Land.h"
#include "Planeswalker.h"

class TestController: public Controller {
public:
	TestController();
	virtual ~TestController();
	bool Mulligan(bool);
	bool PlayFirst();
	Playable* MakePlay(bool);
	vector<Card*> MakeAttacks();
	vector<Planeswalker*> AssignAttacks(vector<Card*>);
	vector<Card*> MakeBlocks(vector<Card*>);
	vector<Card*> AssignBlocks(vector<Card*>,vector<Card*>);
	vector<int> OrderBlocks(Card*,vector<Card*>);
	vector<int> AssignDamage(Card*,vector<Card*>);
	vector<Card*> GetDeck();
	vector<Card*> ChooseDiscards(int);

	vector<Card*> LandsInHand();
	vector<Card*> LandsOnTable();
	vector<Card*> NonLandsInHand();
	vector<Card*> CastableCreatures();
};

#endif /* TESTCONTROLLER_H_ */
