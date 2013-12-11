/*
 * SBA_Milled.h
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#ifndef SBA_MILLED_H_
#define SBA_MILLED_H_

#include "StateBasedAction.h"
#include "Player.h"


class SBA_Milled: public StateBasedAction {
public:
	SBA_Milled();
	SBA_Milled(Player*);
	virtual ~SBA_Milled();
	bool Check();
	void Act();
	void Print();

	Player* thePlayer;
};

#endif /* SBA_MILLED_H_ */
