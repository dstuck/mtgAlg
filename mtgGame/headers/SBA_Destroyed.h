/*
 * SBA_Destroyed.h
 *
 *  Created on: Dec 2, 2013
 *      Author: dstuck
 */

#ifndef SBA_DESTROYED_H_
#define SBA_DESTROYED_H_

#include "StateBasedAction.h"
//#include "Card_Creature.h"
#include "Card.h"

class SBA_Destroyed: public StateBasedAction {
public:
	SBA_Destroyed();
	SBA_Destroyed(Card*);
	virtual ~SBA_Destroyed();
	bool Check();
	void Act();
	void Print();

	Card* theCreature;
};

#endif /* SBA_DESTROYED_H_ */
