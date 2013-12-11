/*
 * HumanController.h
 *
 *  Created on: Dec 7, 2013
 *      Author: dstuck
 */

#ifndef HUMANCONTROLLER_H_
#define HUMANCONTROLLER_H_

#include "Controller.h"
#include "Cardlist.h"
#include "Controller.h"
#include "Player.h"
#include "Card.h"
#include "Card_Land.h"
#include "Debug.h"
#include <string>
#include <stdlib.h>
#include <sstream>
#include <iomanip>

class HumanController: public Controller {
public:
	HumanController();
	HumanController(string);
	virtual ~HumanController();
	vector<Card*> GetDeck();
	bool Mulligan(bool);
	bool PlayFirst();
	Playable* MakePlay(bool);
	vector<Card*> MakeAttacks();
	vector<Planeswalker*> AssignAttacks(vector<Card*>);
	vector<Card*> MakeBlocks(vector<Card*>);
	vector<Card*> AssignBlocks(vector<Card*>,vector<Card*>);
	vector<int> OrderBlocks(Card*,vector<Card*>);
	vector<int> AssignDamage(Card*,vector<Card*>);
	vector<Card*> ChooseDiscards(int);

//	vector<Card*> CastableCreatures();
	void PrintHand();
	void PrintCards(vector<Card*>,string = "Cards: ", bool=true);
	void PrintCards(Card*,string = "Cards: ", bool=false);
	vector<Card*> GetAttackables();
	vector<Card*> GetPotentialBlockers();
	void WriteOut(string, bool=false);
	bool GetBool(bool*, bool=true);
	bool GetIntVec(vector<int>*, int=9999);
	bool GetInt(int*, int=9999);

	string myName;
};

#endif /* HUMANCONTROLLER_H_ */
