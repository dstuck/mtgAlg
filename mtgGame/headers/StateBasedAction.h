/*
 * StateBasedAction.h
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#ifndef STATEBASEDACTION_H_
#define STATEBASEDACTION_H_

#include<iostream>

class StateBasedAction {
public:
	StateBasedAction();
	virtual ~StateBasedAction();
	virtual bool Check() = 0;
	virtual void Act() = 0;
	virtual void Print() = 0;
};

#endif /* STATEBASEDACTION_H_ */
