/*
 * StateBasedActionQueue.h
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#ifndef STATEBASEDACTIONQUEUE_H_
#define STATEBASEDACTIONQUEUE_H_

#include <vector>
#include <debug.h>
using namespace std;

class StateBasedAction;

class StateBasedActionQueue {
public:
	StateBasedActionQueue();
	virtual ~StateBasedActionQueue();
	bool IsEmpty();
	void AddSBA(StateBasedAction*);
	vector<StateBasedAction*> AccessQueue();
	void ResetQueue();

	bool isOpen;
	vector<StateBasedAction*> theQueue;
	vector<StateBasedAction*> backupQueue;
};

#endif /* STATEBASEDACTIONQUEUE_H_ */
