/*
 * TestController.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#include "headers/TestController.h"

TestController::TestController() {
	// TODO Auto-generated constructor stub

}

TestController::~TestController() {
	// TODO Auto-generated destructor stub
}

vector<Card*> TestController::GetDeck() {
	vector<Card*> cardVec;
	Card* deckCard;
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::NorwoodRanger);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<7; i++) {
		deckCard = CardSelector::NewCard(CardList::GrizzlyBears);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<6; i++) {
		deckCard = CardSelector::NewCard(CardList::NessianCourser);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<4; i++) {
		deckCard = CardSelector::NewCard(CardList::NettleSwine);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::PheresBandCentaurs);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<17; i++) {
		deckCard = CardSelector::NewCard(CardList::Forest);
		cardVec.push_back(deckCard);
	}
	return cardVec;
}

Playable * TestController::MakePlay(bool isSorc) {
	if(isSorc) {
//		Play a land if possible
		if(myPlayer->landsToPlay>0) {
			vector<Card*> landHand = LandsInHand();
			if(landHand.size()>0) {
				if(landHand[0]->CanPay(isSorc)) {
					return landHand[0];
				}
			}
		}
//		Play a creature if possible
		vector<Card*> creatureHand = CastableCreatures();;
		if(creatureHand.size()>0) {
			if(creatureHand[0]->CanPay(isSorc)) {
				return creatureHand[0];
			}
		}

//		Card* firstCard = myPlayer->hand->cardVec[0];
//		if(firstCard->Pay(isSorc)) {
//			return firstCard;
//		}
	}
	return NULL;
}

vector<Card*> TestController::MakeAttacks() {
	vector<Card*> attacking;
	vector<Card*> tempCreatures;
	tempCreatures = myPlayer->GetCreatures();
	for(int i=0; i<tempCreatures.size(); i++) {
		if(tempCreatures[i]->CanAttack()) {
			attacking.push_back(tempCreatures[i]);
		}
	}
	return attacking;
}

vector<Planeswalker*> TestController::AssignAttacks(vector<Card*> attackers) {
	vector<Planeswalker*> targets;
	for(int i=0; i<attackers.size(); i++) {
		targets.push_back(oppPlayer);
	}
	return targets;
}

vector<Card*> TestController::MakeBlocks(vector<Card*> attackers) {
	vector<Card*> blocking;
	vector<Card*> tempCreatures;
	tempCreatures = myPlayer->GetCreatures();
	for(int i=0; i<tempCreatures.size(); i++) {
		bool alreadyBlocking = false;
		for(int j=0; j<attackers.size() && !alreadyBlocking; j++) {
			if(tempCreatures[i]->CanBlock(attackers[j])) {
				blocking.push_back(tempCreatures[i]);
				alreadyBlocking = true;
			}
		}
	}
	return blocking;
}

vector<Card*> TestController::AssignBlocks(vector<Card*> blockers, vector<Card*> attackers) {
	vector<Card*> blocked;
	for(int i=0; i<blockers.size(); i++) {
		bool invalidBlock = true;
		int target = i%attackers.size();
		while(invalidBlock) {
			if(blockers[i]->CanBlock(attackers[target])) {
				blocked.push_back(attackers[target]);
				invalidBlock = false;
			}
			else {
				target = (target+1)%attackers.size();
			}
		}
	}
	return blocked;
}



vector<int> TestController::OrderBlocks(Card* attacker, vector<Card*> blockers) {
	vector<int> ordering;
	for(int i=0; i<blockers.size(); i++) {
		ordering.push_back(i);
	}
	return ordering;
}

vector<int> TestController::AssignDamage(Card* attacker,vector<Card*> blockers) {
	int damage = attacker->power;
	vector<int> damageAssigned;
	int damageLeft = damage;
	for(int i=0; i<blockers.size(); i++) {
		if(damageLeft <= blockers[i]->toughness) {
			damageAssigned.push_back(damageLeft);
			damageLeft = 0;
		}
		else {
			damageAssigned.push_back(blockers[i]->toughness);
			damageLeft -= blockers[i]->toughness;
		}
	}
	return damageAssigned;
}

vector<Card*> TestController::ChooseDiscards(int nDiscard) {
	vector<Card*> discards;
	if(nDiscard >= myPlayer->hand->cardVec.size()) {
		for(int i=0; i< myPlayer->hand->cardVec.size(); i++) {
			discards.push_back(myPlayer->hand->cardVec[i]);
		}
		return discards;
	}
	vector<Card*> landsDown = LandsOnTable();
	vector<Card*> landsInHand = LandsInHand();
	vector<Card*> nonLandsInHand = NonLandsInHand();
	if(landsDown.size()<=1) {
//	Discard all but 2 lands if able
		while(nDiscard>0 && landsInHand.size()>2) {
			discards.push_back(landsInHand.back());
			landsInHand.pop_back();
			nDiscard--;
		}
	}
	else if(landsDown.size()<=3 && landsDown.size()>1) {
//	Discard all but 1 lands if able
		while(nDiscard>0 && landsInHand.size()>1) {
			discards.push_back(landsInHand.back());
			landsInHand.pop_back();
			nDiscard--;
		}
	}
	else if(landsDown.size()>3) {
//	Discard all lands
		while(nDiscard>0 && landsInHand.size()>1) {
			discards.push_back(landsInHand.back());
			landsInHand.pop_back();
			nDiscard--;
		}
	}
	while(nDiscard>0 && nonLandsInHand.size()>0) {
		discards.push_back(nonLandsInHand.back());
		nonLandsInHand.pop_back();
		nDiscard--;
	}
	while(nDiscard>0 && landsInHand.size()>0) {
		discards.push_back(landsInHand.back());
		landsInHand.pop_back();
		nDiscard--;
	}
	return discards;
}

vector<Card*> TestController::LandsInHand() {
	vector<Card*> landHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(myPlayer->hand->cardVec[i]->isLand) {
			landHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return landHand;
}

vector<Card*> TestController::LandsOnTable() {
	vector<Card*> landsPlayed;
	for(int i=0; i<myPlayer->bf->cardVec.size(); i++) {
		if(myPlayer->bf->cardVec[i]->isLand) {
			landsPlayed.push_back(myPlayer->bf->cardVec[i]);
		}
	}
	return landsPlayed;
}

vector<Card*> TestController::NonLandsInHand() {
	vector<Card*> nonLandHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(!myPlayer->hand->cardVec[i]->isLand) {
			nonLandHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return nonLandHand;
}

bool TestController::Mulligan(bool isFirst) {
	return false;
}

bool TestController::PlayFirst() {
	return true;
}

vector<Card*> TestController::CastableCreatures() {
	vector<Card*> creatureHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(myPlayer->hand->cardVec[i]->isCreature && myPlayer->HasMana(myPlayer->hand->cardVec[i]->mana)) {
			creatureHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return creatureHand;
}

