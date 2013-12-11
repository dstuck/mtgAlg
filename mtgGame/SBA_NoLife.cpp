/*
 * SBA_NoLife.cpp
 *
 *  Created on: Dec 1, 2013
 *      Author: dstuck
 */

#include "headers/SBA_NoLife.h"

SBA_NoLife::SBA_NoLife() {
	// TODO Auto-generated constructor stub
}

SBA_NoLife::SBA_NoLife(Player* thePlayer_) {
	thePlayer = thePlayer_;
}

SBA_NoLife::~SBA_NoLife() {
	// TODO Auto-generated destructor stub
}

bool SBA_NoLife::Check() {
	if((thePlayer->lifeTotal > 0) || (!thePlayer->winner)) {
		return false;
	}
	else {
		return true;
	}
}

void SBA_NoLife::Act() {
	thePlayer->winner=false;
}

void SBA_NoLife::Print() {
	cout << "Zero life!" << endl;
}



