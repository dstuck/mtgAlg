/*
 * Swamp.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "Swamp.h"

Swamp::Swamp() {
	KeywordVanilla();
	id = 376534;
	name = "Swamp";
	cmc = 0;
	isBasic = true;
	isLand = true;
	subtype.push_back("Swamp");
	ruleText.push_back(B);
	power = 0;
	toughness = 0;
	loyalty = 0;
	set = "Commander 2013 Edition";
	rarity = "Basic Land";
	cardNumber = 347;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=376534&type=card";

	DefaultInit();
}

Swamp::~Swamp() {
}

string Swamp::GetImage() {
	return "|B|";
}

void Swamp::Play() {
	MoveLoc(thePlayer->bf);
	thePlayer->maxMana[colors::B]++;
	thePlayer->curMana[colors::B]++;
}

