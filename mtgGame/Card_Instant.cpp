/*
 * Card_Instant.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: dstuck
 */

#include "headers/Card_Instant.h"

Card_Instant::Card_Instant() {
	// TODO Auto-generated constructor stub

}

Card_Instant::~Card_Instant() {
	// TODO Auto-generated destructor stub
}

void Card_Instant::DefaultInit() {
	KeywordVanilla();
	isInstant = true;
	instantSpeed = true;
}

string Card_Instant::GetImage() {
	return "|"+to_string(cmc)+"inst|";
}

void Card_Instant::Play() {
	MoveLoc(thePlayer->gy);
}

bool Card_Instant::Pay(bool isSorc) {
//	Make sure card is in hand and allowed to cast at this speed
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->HasMana(mana)) {
//	Pay that mana! Notice that remaining colorless mana is paid in color order!
//	Convert colored to colorless if you want to chose for yourself.
		thePlayer->PayMana(mana);
//	Put the card in exile while the spell is on the stack.
//	TODO: Could make a stack zone for the physical cards to wait while the pointer sits on the stack.
		MoveLoc(thePlayer->ex);
		return true;
	}
	else {
		cout << "Not enough mana!" << endl;
		return false;
	}
}

bool Card_Instant::CanPay(bool isSorc) {
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->HasMana(mana)) {
		return true;
	}
	else {
//		Not enough mana
		return false;
	}
}


