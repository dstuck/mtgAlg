/*
 * Forest.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "Forest.h"

Forest::Forest() {
	KeywordVanilla();
	id = 376341;
	name = "Forest";
	cmc = 0;
	isLand = true;
	isBasic = true;
	subtype.push_back("Forest");
	rulesText.push_back("G");
	power = 0;
	toughness = 0;
	loyalty = 0;
	set = "Commander 2013 Edition";
	rarity = "Basic Land";
	cardNumber = 355;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=376341&type=card";
}

Forest::~Forest() {
}

string Forest::GetImage() {
	return "|G|";
}

void Forest::Play() {
	MoveLoc(thePlayer->bf);
	thePlayer->maxMana[colors::G]++;
	thePlayer->curMana[colors::G]++;
}
