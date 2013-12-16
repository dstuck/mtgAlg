/*
 * WindDrake.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "WindDrake.h"

WindDrake::WindDrake() {
	KeywordVanilla();
	id = 369037;
	name = "Wind Drake";
	cmc = 3;
	isCreature = true;
	subtype.push_back("Drake");
	flying = true;
	flavor.push_back("Air currents whip through the city corridors, creating wind tunnels that accelerate urban drakes toward their prey.");
	power = 2;
	toughness = 2;
	loyalty = 0;
	set = "Dragon's Maze";
	rarity = "Common";
	cardNumber = 20;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=369037&type=card";
	mana[colors::O]+=2;
	mana[colors::U]++;
	color[colors::U] = true;

	DefaultInit();
}

WindDrake::~WindDrake() {
}

