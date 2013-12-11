/*
 * AirElemental.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "AirElemental.h"

AirElemental::AirElemental() {
	KeywordVanilla();
	id = 221985;
	name = "Air Elemental";
	cmc = 5;
	isCreature = true;
	subtype.push_back("Elemental");
	flying = true;
	flavor.push_back("These spirits of the air are winsome and wild and cannot be truly contained. Only marginally intelligent, they often substitute whimsy for strategy, delighting in mischief and mayhem.");
	power = 4;
	toughness = 4;
	loyalty = 0;
	set = "Masters Edition IV";
	rarity = "Uncommon";
	cardNumber = 37;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=221985&type=card";
	mana[colors::O]+=3;
	mana[colors::U]++;
	mana[colors::U]++;

	InitDefault();
}

AirElemental::~AirElemental() {
}

