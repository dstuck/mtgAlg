/*
 * NessianCourser.cpp
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#include "NessianCourser.h"

NessianCourser::NessianCourser() {
	KeywordVanilla();
	id = 373581;
	name = "Nessian Courser";
	cmc = 3;
	isCreature = true;
	subtype.push_back("Centaur");
	subtype.push_back("Warrior");
	flavor.push_back("Khestes the Adamant, the Champion\'s closest ally among the centaurs, took one stone to his shoulder and another to his flank. He held his stride and his aim, and let fly the arrow that killed the giant Grinthax.");
	flavor.push_back("--The Theriad");
	power = 3;
	toughness = 3;
	loyalty = 0;
	set = "Theros";
	rarity = "Common";
	cardNumber = 165;
	image = "http://gatherer.wizards.com/Handlers/Image.ashx?multiverseid=373581&type=card";
	mana[colors::O]+=2;
	mana[colors::G]++;
	color[colors::G] = true;

	DefaultInit();
}

NessianCourser::~NessianCourser() {
}

