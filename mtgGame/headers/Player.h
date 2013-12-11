/*
 * Player.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include "Random.h"
//#include "Card.h"
#include "Hand.h"
#include "Battlefield.h"
#include "Graveyard.h"
#include "Library.h"
#include "Exile.h"
#include <iostream>
#include <iterator>
#include "Colors.h"
#include "debug.h"
#include "Planeswalker.h"
#include "StateBasedActionQueue.h"
#include "StateBasedAction.h"
#include "Controller.h"


class SBA_NoLife;
class SBA_Milled;
class Card;
class Controller;

class Player: public Planeswalker {
public:
	Player();
	Player(Controller*);
	virtual ~Player();
	void Init();
	void ResetPlayer();
	void PrintGameState(bool,bool=false);
	void PrintHand(bool=false);
	void PrintLibrary();
	void PrintBattlefield();
	void PrintExile();
	vector<Card*> GetCreatures();
	void DrawCards(double=1);
	void DiscardCards(int=1);
	void ResetMana();
	void ResetEOT();
	void UntapAll();
	void Reset();
	void Shuffle();
	bool HasMana(int*);
	void PayMana(int*);
	void TakeDamage(int);

	Controller * control;
	Hand * hand;
	Battlefield * bf;
	Graveyard * gy;
	Library * lib;
	Exile * ex;
	StateBasedActionQueue * sbaQueue;
	bool winner;
	double lifeTotal;
	int maxMana[6];
	int curMana[6];
	int landsToPlay;

	int* idum;

};

////	Trying to fix incomplete class problem by putting SBA in Player header like http://stackoverflow.com/questions/19962812/error-member-access-into-incomplete-type-forward-declaration-of
//class SBA_NoLife: public StateBasedAction {
//public:
//	SBA_NoLife();
//	SBA_NoLife(Player*);
//	virtual ~SBA_NoLife();
//	bool Check();
//	void Act();
//
//	Player* thePlayer;
//};

#endif /* PLAYER_H_ */
