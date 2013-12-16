/*
 * Card.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Card.h"
#include "Player.h"
#include "SBA_Destroyed.h"

Card::Card() {
	// TODO Auto-generated constructor stub

}

Card::~Card() {
	// TODO Auto-generated destructor stub
}

string Card::GetImage() {
	return "No image available";
}

string Card::GetImageURL() {
	return image;
}

vector<string> Card::GetFlavor() {
	return flavor;
}

void Card::GetManaCost(int* mana_) {
	for(int i=0; i<6; i++) {
		mana_[i] = mana[i];
	}
}

void Card::MoveLoc(Location* newLoc) {
//	Removes self from old location list
	vector<Card*>::const_iterator endit = curLoc->cardVec.end();
//	cout << "Currently in " << curLoc->GetName() << ".\tMoving to " << newLoc->GetName() << endl;
	vector<Card*>::const_iterator newendit = remove(curLoc->cardVec.begin(),curLoc->cardVec.end(),this);
	curLoc->cardVec.erase(newendit,endit);
//	Resets all previous information the card may have had on the battlefield
	ResetAll();
//	Add self to the new location
	newLoc->AddCard(this);
//	Recognize new location
	curLoc = newLoc;
}

void Card::ResetAll() {
	tapped = false;
	attacking = NULL;
	blocking = NULL;
	blocked.clear();
	damage = 0;
	summoningSick = true;

}

void Card::ResetEOT() {
	damage=0;
//	At some point I'll have to include EOT effects to this function, but for now damage is the only real EOT effect
//	Might as well make sure these are reset as well...
	attacking = NULL;
	blocking = NULL;
	blocked.clear();
}

string Card::GetName() {
	return name;
}

vector<string> Card::GetSubtype() {
	return subtype;
}

int Card::GetPower() {
	return power;
}

int Card::GetToughness() {
	return toughness;
}


void Card::KeywordVanilla() {
	firstStrike = false;
	regularStrike = true;
	trample = false;
	deathtouch = false;
	haste = false;
	defender = false;
	lifelink = false;
	vigilance = false;
	indestructable = false;
	flash = false;
	reach = false;
	flying = false;
	intimidate = false;
	unblockable = false;
	isCreature=false;
	isLand=false;
	isBasic=false;
	isInstant=false;
	isSorcery=false;
	isEnchantment=false;
	isArtifact=false;
	isLegendary=false;
	power = 0;
	toughness = 0;
	mana[colors::W]=0;
	mana[colors::U]=0;
	mana[colors::B]=0;
	mana[colors::R]=0;
	mana[colors::G]=0;
	mana[colors::O]=0;
	color[colors::W]=false;
	color[colors::U]=false;
	color[colors::B]=false;
	color[colors::R]=false;
	color[colors::G]=false;
	color[colors::O]=false;
	defaultValue = cmc;

	tapped=false;
        summoningSick=true;
}

void Card::SetVanillaVariables() {
	vanillaCombat = !(firstStrike||trample||deathtouch);
	vanillaMisc = !(haste||lifelink||vigilance||indestructable);
	vanillaBlocks = !(reach||flying);
	vanillaBlockability = !(flying||intimidate||unblockable);
}

bool Card::CanAttack() {
	if(tapped||!isCreature) {
		return false;
	}
	else if(summoningSick && !haste) {
		return false;
	}
	else {
		return true;
	}
}

void Card::Attack(Planeswalker* target) {
	if(!vigilance) {
		tapped = true;
	}
	attacking = target;
}

bool Card::CanBlock(Card* blockTarget) {
//	TODO: Need this to call is blockable from blockTarget to deal with only blockable by X or more spire chaser...
	if(tapped||!isCreature) {
		return false;
	}
	else if(blockTarget->CanBeBlocked(this)) {
		return true;
	}
	else {
		return false;
	}
}

bool Card::CanBeBlocked(Card* blocker) {
	if(!(blocker->flying||blocker->reach) && flying) {
		return false;
	}
	else if(unblockable) {
		return false;
	}
	else if(intimidate) {
		bool sharedColor = false;
		for(int i=0; i<5; i++) {
			if(mana[i]>0 && blocker->mana[i]>0) {
				sharedColor = true;
			}
		}
		return true;
	}
	else {
		return true;
	}
}

void Card::Block(Card* blockTarget) {
	blocking = blockTarget;
	blockTarget->blocked.push_back(this);
}

void Card::TakeDamage(int damageDealt) {
//	cout << "Damage starts as " << damage << endl;
	damage += damageDealt;
//	cout << "Damage is " << damage << endl;
	if((toughness>0) && (damage>=toughness)) {
//		Destroy();
		thePlayer->sbaQueue->AddSBA(new SBA_Destroyed(this));
	}
}

void Card::Destroy() {
//	cout << GetName() << " is destroyed!" << endl;
	if(indestructable) {
		cout << "Indestructable!" << endl;
		return;
	}
	if(regenerating>0) {
		cout << "Regenerating!" << endl;
		regenerating--;
		tapped = true;
	}
	else {
		Die();
	}
}

void Card::Die() {
	MoveLoc(thePlayer->gy);
}


bool Card::DefaultCheckPay(bool isSorc) {
	if(!isSorc) {
		if(!instantSpeed) {
			cout << "Can't cast sorceries at instant speed!" << endl;
			return false;
		}
	}
	if(this->curLoc->GetName()!="Hand") {
		cout << "Card is not in your hand!" << endl;
		return false;
	}
	else {
		return true;
	}

}

bool Card::IsTargetable(Player* targeter) {
	if(shroud) {
		return false;
	}
	if(hexproof && targeter!= thePlayer) {
		return false;
	}
	return true;
}

bool Card::IsCard() {
	return true;
}


