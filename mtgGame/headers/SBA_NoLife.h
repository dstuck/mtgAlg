/*
 * SBA_NoLife.h
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#ifndef SBA_NOLIFE_H_
#define SBA_NOLIFE_H_

#include "StateBasedAction.h"
#include "Player.h"

class SBA_NoLife: public StateBasedAction {
public:
	SBA_NoLife();
	SBA_NoLife(Player*);
	virtual ~SBA_NoLife();
	bool Check();
	void Act();
	void Print();

	Player* thePlayer;
};

#endif /* SBA_NOLIFE_H_ */
