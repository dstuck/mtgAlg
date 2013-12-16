/*
 * Card_Land.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Card_Land.h"


Card_Land::Card_Land() {
	// TODO Auto-generated constructor stub
	DefaultInit();
}

Card_Land::~Card_Land() {
	// TODO Auto-generated destructor stub
}

void Card_Land::DefaultInit() {
	KeywordVanilla();
	isLand=true;
	defaultValue=1;
}

void Card_Land::Play() {
	this->MoveLoc(this->thePlayer->bf);
}

bool Card_Land::CanPay(bool isSorc) {
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->landsToPlay <= 0) {
//		Already played your lands!
		return false;
	}
	else {
		return true;
	}
}

bool Card_Land::Pay(bool isSorc) {
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->landsToPlay == 0) {
		cout << "Already played your lands!" << endl;
		return false;
	}
	else {
		thePlayer->landsToPlay--;
		this->MoveLoc(this->thePlayer->ex);
		return true;
	}
}

