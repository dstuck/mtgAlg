/*
 * HornedTurtle.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "HornedTurtle.h"

HornedTurtle::HornedTurtle() {
	KeywordVanilla();
	id = 190178;
	name = "Horned Turtle";
	cmc = 3;
	isCreature = true;
	subtype.push_back("Turtle");
	flavor.push_back("It\'s a mistake to say turtles hide in their shells. They merely need time to contemplate how best to bite your head off.");
	power = 1;
	toughness = 4;
	loyalty = 0;
	set = "Magic 2010";
	rarity = "Common";
	cardNumber = 55;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=190178&type=card";
	mana[colors::O]+=2;
	mana[colors::U]++;
	color[colors::U] = true;

	DefaultInit();
}

HornedTurtle::~HornedTurtle() {
}

