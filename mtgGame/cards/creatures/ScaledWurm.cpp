/*
 * ScaledWurm.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "ScaledWurm.h"

ScaledWurm::ScaledWurm() {
	KeywordVanilla();
	id = 83272;
	name = "Scaled Wurm";
	cmc = 8;
	isCreature = true;
	subtype.push_back("Wurm");
	flavor.push_back("The wurms become so big, a single scale can be used as a roof for a human dwelling.");
	power = 7;
	toughness = 6;
	loyalty = 0;
	set = "Ninth Edition";
	rarity = "Common";
	cardNumber = 269;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=83272&type=card";
	mana[colors::O]+=7;
	mana[colors::G]++;

	InitDefault();
}

ScaledWurm::~ScaledWurm() {
}
