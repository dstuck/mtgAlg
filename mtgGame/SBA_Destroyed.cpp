/*
 * SBA_Destroyed.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: dstuck
 */

#include "headers/SBA_Destroyed.h"

SBA_Destroyed::SBA_Destroyed() {
	// TODO Auto-generated constructor stub

}

SBA_Destroyed::SBA_Destroyed(Card* theCreature_) {
	theCreature = theCreature_;
}

SBA_Destroyed::~SBA_Destroyed() {
	// TODO Auto-generated destructor stub
}

bool SBA_Destroyed::Check() {
	if((theCreature->toughness>0) && (theCreature->damage>=theCreature->toughness)) {
		return true;
	}
	else {
		return false;
	}
}

void SBA_Destroyed::Act() {
	theCreature->Destroy();
}

void SBA_Destroyed::Print() {
	cout << theCreature->GetName() << " is destroyed!" << endl;
}



