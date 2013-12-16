/*
 * Card_Creature.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Card_Creature.h"
#include "SBA_Destroyed.h"

Card_Creature::Card_Creature() {
	DefaultInit();
}

Card_Creature::~Card_Creature() {
	// TODO Auto-generated destructor stub
}

void Card_Creature::DefaultInit() {
	isCreature=true;
	usesStack=true;
	if(!flash) {
		instantSpeed=false;
	}
	else {
		instantSpeed=true;
	}
	regenerating = 0;
	SetVanillaVariables();
}

string Card_Creature::GetImage() {
	string image;
	if(!tapped) {
		image = "|"+to_string(power)+"/"+to_string(toughness)+"|";
	}
	else {
		image = "\\"+to_string(power)+"/"+to_string(toughness)+"\\";
	}
	if(flying) {
		image = image+"V";
	}
	if(unblockable) {
		image = image+"Ub";
	}
	if(flash) {
		image = image+"*";
	}
	return image;
}

void Card_Creature::Play() {
	MoveLoc(thePlayer->bf);
}

bool Card_Creature::CanPay(bool isSorc) {
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->HasMana(mana)) {
		return true;
	}
	else {
//		Not enough mana
		return false;
	}
}

bool Card_Creature::Pay(bool isSorc) {
//	Make sure card is in hand and allowed to cast at this speed
	if(!DefaultCheckPay(isSorc)) {
		return false;
	}
	if(thePlayer->HasMana(mana)) {
//	Pay that mana! Notice that remaining colorless mana is paid in color order!
//	Convert colored to colorless if you want to chose for yourself.
		thePlayer->PayMana(mana);
//	Put the card in exile while the spell is on the stack.
//	TODO: Could make a stack zone for the physical cards to wait while the pointer sits on the stack.
		MoveLoc(thePlayer->ex);
		return true;
	}
	else {
		cout << "Not enough mana!" << endl;
		return false;
	}
}


//int Card_Creature::GetPower() {
//	return power;
//}
//
//
//int Card_Creature::GetToughness() {
//	return toughness;
//}
//void Card_Creature::KeywordVanilla() {
//	firstStrike = false;
//	regularStrike = true;
//	trample = false;
//	deathtouch = false;
//	haste = false;
//	lifelink = false;
//	vigalance = false;
//	indestructable = false;
//	flash = false;
//	reach = false;
//	flying = false;
//	intimidate = false;
//	unblockable = false;
//	isCreature=true;
//	isLand=false;
//	isBasic=false;
//	isInstant=false;
//	isSorcery=false;
//	isEnchantment=false;
//	isArtifact=false;
//	isLegendary=false;
//	power = 0;
//	toughness = 0;
//	mana[colors::W]=0;
//	mana[colors::U]=0;
//	mana[colors::B]=0;
//	mana[colors::R]=0;
//	mana[colors::G]=0;
//	mana[colors::O]=0;
//}

//void Card_Creature::ResetEOT() {
//	damage=0;
////	At some point I'll have to include EOT effects to this function, but for now damage is the only real EOT effect
////	Might as well make sure these are reset as well...
//	attacking = NULL;
//	blocking = NULL;
//	blocked.clear();
//}

//void Card_Creature::ResetAll() {
//	tapped = false;
//	attacking = NULL;
//	blocking = NULL;
//	blocked.clear();
//	damage = 0;
//	summoningSick = true;
//}
//
//void Card_Creature::SetVanillaVariables() {
//	vanillaCombat = !(firstStrike||trample||deathtouch);
//	vanillaMisc = !(haste||lifelink||vigalance||indestructable);
//	vanillaBlocks = !(reach||flying);
//	vanillaBlockability = !(flying||intimidate||unblockable);
//}
//
//void Card_Creature::TakeDamage(int damageDealt) {
////	cout << "Damage starts as " << damage << endl;
//	damage += damageDealt;
////	cout << "Damage is " << damage << endl;
//	if((toughness>0) && (damage>=toughness)) {
////		Destroy();
//		thePlayer->sbaQueue->AddSBA(new SBA_Destroyed(this));
//	}
//}
//
//void Card_Creature::Destroy() {
////	cout << GetName() << " is destroyed!" << endl;
//	if(indestructable) {
//		cout << "Indestructable!" << endl;
//		return;
//	}
//	if(regenerating>0) {
//		cout << "Regenerating!" << endl;
//		regenerating--;
//		tapped = true;
//	}
//	else {
//		Die();
//	}
//}
//
//void Card_Creature::Die() {
//	MoveLoc(thePlayer->gy);
//}

//bool Card_Creature::CanAttack() {
//	if(tapped||!isCreature) {
//		return false;
//	}
//	else if(summoningSick && !haste) {
//		return false;
//	}
//	else {
//		return true;
//	}
//}
//
//void Card_Creature::Attack(Planeswalker* target) {
//	if(!vigalance) {
//		tapped = true;
//	}
//	attacking = target;
//}
//
//bool Card_Creature::CanBlock(Card_Creature* blockTarget) {
////	TODO: Need this to call is blockable from blockTarget to deal with only blockable by X or more spire chaser...
//	if(tapped) {
//		return false;
//	}
//	else if(blockTarget->CanBeBlocked(this)) {
//		return true;
//	}
//	else {
//		return false;
//	}
//}
//
//bool Card_Creature::CanBeBlocked(Card_Creature* blocker) {
//	if(!(blocker->flying||blocker->reach) && flying) {
//		return false;
//	}
//	else if(unblockable) {
//		return false;
//	}
//	else if(intimidate) {
//		bool sharedColor = false;
//		for(int i=0; i<5; i++) {
//			if(mana[i]>0 && blocker->mana[i]>0) {
//				sharedColor = true;
//			}
//		}
//		return true;
//	}
//	else {
//		return true;
//	}
//}
//
//void Card_Creature::Block(Card_Creature* blockTarget) {
//	blocking = blockTarget;
//	blockTarget->blocked.push_back(this);
//}





