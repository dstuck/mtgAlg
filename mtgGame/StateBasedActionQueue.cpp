/*
 * StateBasedActionQueue.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#include "headers/StateBasedActionQueue.h"

StateBasedActionQueue::StateBasedActionQueue() {
	isOpen = true;

}

StateBasedActionQueue::~StateBasedActionQueue() {
	// TODO Auto-generated destructor stub
}

bool StateBasedActionQueue::IsEmpty() {
	return theQueue.empty();
}

void StateBasedActionQueue::AddSBA(StateBasedAction* newSBA) {
	if(isOpen) {
		theQueue.push_back(newSBA);
	}
	else {
		backupQueue.push_back(newSBA);
	}
}

vector<StateBasedAction*> StateBasedActionQueue::AccessQueue() {
	if(isOpen) {
		isOpen = false;
		return theQueue;
	}
	else {
		cout << "Queue is already being accessed! Here's the backupQueue" << endl;
		return backupQueue;
	}
}

void StateBasedActionQueue::ResetQueue() {
	theQueue = backupQueue;
	backupQueue.clear();
	isOpen = true;
}



