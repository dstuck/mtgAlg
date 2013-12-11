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
	isCreature=false;
	isLand=true;
	isInstant=false;
	isSorcery=false;
	isEnchantment=false;
	isArtifact=false;
	usesStack=false;
	isInst=false;
	mana[colors::W]=0;
	mana[colors::U]=0;
	mana[colors::B]=0;
	mana[colors::R]=0;
	mana[colors::G]=0;
	mana[colors::O]=0;
}

void Card_Land::Play() {
	this->MoveLoc(this->thePlayer->bf);
}

void Card_Land::KeywordVanilla() {
	isCreature=false;
	isLand=true;
	isBasic=false;
	isInstant=false;
	isSorcery=false;
	isEnchantment=false;
	isArtifact=false;
	isLegendary=false;
	power = 0;
	toughness = 0;
	mana[colors::W]=0;
	mana[colors::U]=0;
	mana[colors::B]=0;
	mana[colors::R]=0;
	mana[colors::G]=0;
	mana[colors::O]=0;
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

