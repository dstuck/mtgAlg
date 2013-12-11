/*
 * RumblingBaloth.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "RumblingBaloth.h"

RumblingBaloth::RumblingBaloth() {
	KeywordVanilla();
	id = 370764;
	name = "Rumbling Baloth";
	cmc = 4;
	isCreature = true;
	subtype.push_back("Beast");
	flavor.push_back("In the dim light beneath the vast trees of Deepglade, baloths prowl in search of prey. Their guttural calls are more felt than heard, but their attack scream carries for miles.");
	power = 4;
	toughness = 4;
	loyalty = 0;
	set = "Magic 2014 Core Set";
	rarity = "Common";
	cardNumber = 193;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=370764&type=card";
	mana[colors::O]+=2;
	mana[colors::G]++;
	mana[colors::G]++;

	InitDefault();
}

RumblingBaloth::~RumblingBaloth() {
}

