/*
 * KrakenHatchling.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "KrakenHatchling.h"

KrakenHatchling::KrakenHatchling() {
	KeywordVanilla();
	id = 279699;
	name = "Kraken Hatchling";
	cmc = 1;
	isCreature = true;
	subtype.push_back("Kraken");
	flavor.push_back("A spike and a maul are needed to crack their shells, but the taste is worth the effort.");
	power = 0;
	toughness = 4;
	loyalty = 0;
	set = "Magic 2013";
	rarity = "Common";
	cardNumber = 58;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=279699&type=card";
	mana[colors::U]++;

	InitDefault();
}

KrakenHatchling::~KrakenHatchling() {
}
