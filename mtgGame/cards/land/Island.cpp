/*
 * Island.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "Island.h"

Island::Island() {
	KeywordVanilla();
	id = 376376;
	name = "Island";
	cmc = 0;
	isLand = true;
	isBasic = true;
	subtype.push_back("Island");
	rulesText.push_back("U");
	power = 0;
	toughness = 0;
	loyalty = 0;
	set = "Commander 2013 Edition";
	rarity = "Basic Land";
	cardNumber = 343;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=376376&type=card";
}

Island::~Island() {
}

string Island::GetImage() {
	return "|U|";
}

void Island::Play() {
	MoveLoc(thePlayer->bf);
	thePlayer->maxMana[colors::U]++;
	thePlayer->curMana[colors::U]++;
}

