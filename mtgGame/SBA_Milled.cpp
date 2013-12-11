/*
 * SBA_Milled.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#include "headers/SBA_Milled.h"

SBA_Milled::SBA_Milled() {
}

SBA_Milled::SBA_Milled(Player* thePlayer_) {
	thePlayer = thePlayer_;
}

SBA_Milled::~SBA_Milled() {
	// TODO Auto-generated destructor stub
}

bool SBA_Milled::Check() {
	if(thePlayer->winner) {
		return true;
	}
	else {
		return false;
	}
}

void SBA_Milled::Act() {
	thePlayer->winner=false;
}

void SBA_Milled::Print() {
	cout << "Milled out!" << endl;
}





