/*
 * Player.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Player.h"
#include "Card.h"
#include "SBA_NoLife.h"
#include "SBA_Milled.h"

Player::Player() {
	control = NULL;

	Init();
}

Player::Player(Controller* control_) {
	control = control_;

	Init();
}


Player::~Player() {
	delete hand;
	delete bf;
	delete gy;
	delete lib;
	delete ex;
}

void Player::Init() {
	winner = true;
	hand = new Hand();
	bf = new Battlefield();
	gy = new Graveyard();
	lib = new Library();
	ex = new Exile();
	lifeTotal = 20;
	maxMana[colors::W]=0;
	maxMana[colors::U]=0;
	maxMana[colors::B]=0;
	maxMana[colors::R]=0;
	maxMana[colors::G]=0;
	maxMana[colors::O]=0;
	ResetMana();
	landsToPlay = 1;
}

void Player::ResetPlayer() {
	winner = true;
	delete lib;
	delete hand;
	delete bf;
	delete gy;
	delete ex;
	hand = new Hand();
	bf = new Battlefield();
	gy = new Graveyard();
	lib = new Library();
	ex = new Exile();
	lifeTotal = 20;
	maxMana[colors::W]=0;
	maxMana[colors::U]=0;
	maxMana[colors::B]=0;
	maxMana[colors::R]=0;
	maxMana[colors::G]=0;
	maxMana[colors::O]=0;
	ResetMana();
	landsToPlay = 1;
}

void Player::PrintLibrary() {
	cout << "[[" << lib->cardVec.size() << "]]";
}

void Player::PrintHand(bool hidden) {
	for(int i=0; i<hand->cardVec.size(); i++) {
		if(i>0){
			cout << " ";
		}
		if(!hidden) {
			cout << hand->cardVec[i]->GetImage();
		}
		else {
			cout << "|?|";
		}
	}
}

void Player::PrintBattlefield() {
	for(int i=0; i<bf->cardVec.size(); i++) {
		if(i>0){
			cout << " ";
		}
		cout << bf->cardVec[i]->GetImage();
	}
	cout << "\n";
}

void Player::PrintExile() {
	if(ex->cardVec.size()>0) {
		cout << "Exile: ";
		for(int i=0; i<ex->cardVec.size(); i++) {
			if(i>0){
				cout << " ";
			}
			cout << ex->cardVec[i]->GetImage();
		}
		cout << "\n";
	}
}

void Player::PrintGameState(bool isTop, bool hidden) {
	if(isTop) {
		cout << "------------------------------------------" << endl;
		cout << "(" << lifeTotal << ")" << endl;
		PrintLibrary();
		cout << "\t";
		PrintHand();
		cout << endl;
		PrintExile();
		PrintBattlefield();
	}
	else{
		PrintBattlefield();
		PrintExile();
		PrintLibrary();
		cout << "\t";
		PrintHand(hidden);
		cout << endl;
		cout << "(" << lifeTotal << ")" << endl;
		cout << "------------------------------------------" << endl;
	}
}

void Player::DrawCards(double numCards) {
	if(lib->cardVec.size()>numCards) {
		for(int i=0; i<numCards; i++) {
			lib->cardVec[0]->MoveLoc(hand);
		}
	}
	else {
		sbaQueue->AddSBA(new SBA_Milled(this));
	}
}

void Player::DiscardCards(int nDiscard) {
	bool invalidDiscard = true;
	vector<Card*> discards;
	while(invalidDiscard) {
		invalidDiscard = false;
		discards = control->ChooseDiscards(nDiscard);
		for(int i=0; i<discards.size(); i++) {
			if(discards[i]->curLoc != hand) {
				cout << "Must discard cards from your hand!" << endl;
				invalidDiscard = true;
			}
		}
		if((discards.size()<nDiscard) && (discards.size()!=hand->cardVec.size())) {
			cout << "Discarded too few cards! Try again!" << endl;
			invalidDiscard = true;
		}
		if((discards.size()>nDiscard)) {
			cout << "Discarded too many cards! Try again!" << endl;
			invalidDiscard = true;
		}
	}
	for(int i=0; i<discards.size(); i++) {
		discards[i]->MoveLoc(gy);
	}
}

void Player::ResetMana() {
	for(int i=0; i<6; i++) {
		curMana[i] = maxMana[i];
	}
}

void Player::Reset() {
	delete hand;
	delete bf;
	delete gy;
	delete lib;
	delete ex;
	Init();
}

void Player::Shuffle() {
//	srand ( unsigned ( std::time(0) ) );
//	random_shuffle(lib->cardVec.begin(),lib->cardVec.end());
	for (int i=0; i<lib->cardVec.size(); i++) {
		swap (lib->cardVec[i],lib->cardVec[RandomNum::rand3(idum)*(lib->cardVec.size()-i)+i]);
	}
}

void Player::UntapAll() {
	for(int i=0; i<bf->cardVec.size(); i++) {
		bf->cardVec[i]->tapped = false;
	}
}

void Player::ResetEOT() {
	for(int i=0; i<bf->cardVec.size(); i++) {
		bf->cardVec[i]->ResetEOT();
	}
}

bool Player::HasMana(int* mCost) {
//	cout << "mCost = ";
//	for(int i=0; i<6; i++) {
//		cout << mCost[i] << " ";
//	}
//	cout << endl;
//	cout << "curMana = ";
//	for(int i=0; i<6; i++) {
//		cout << curMana[i] << " ";
//	}
//	cout << endl;
	int colorless = 0;
	for(int i=0; i<5; i++) {
		if(curMana[i] < mCost[i]) {
			return false;
		}
		else {
			colorless += curMana[i]-mCost[i];
		}
		colorless += curMana[5];
	}
	if(colorless < mCost[5]) {
		return false;
	}
	else {
		return true;
	}
}

void Player::PayMana(int* cost) {
//	cout << "cost = ";
//	for(int i=0; i<6; i++) {
//		cout << cost[i] << " ";
//	}
//	cout << endl;
	for(int i=0; i<5; i++) {
		curMana[i]-=cost[i];
	}
	if(curMana[5]>=cost[5]){
		curMana[5]-=cost[5];
	}
	else {
		int colorlessLeft = cost[5]-curMana[5];
		curMana[5] = 0;
		for(int i=0; i<5; i++) {
			if(curMana[i] >= colorlessLeft) {
				curMana[i] -= colorlessLeft;
				colorlessLeft = 0;
			}
			else {
				colorlessLeft -= curMana[i];
				curMana[i] = 0;
			}
		}
	}
}

vector<Card*> Player::GetCreatures() {
	vector<Card*> creatureVec;
	for(int i=0; i<bf->cardVec.size(); i++) {
		if(bf->cardVec[i]->isCreature) {
//			c-style cast
			creatureVec.push_back(bf->cardVec[i]);
		}
	}
	return creatureVec;
}


void Player::TakeDamage(int damage) {
	lifeTotal -= damage;
	if(lifeTotal <= 0) {
		sbaQueue->AddSBA(new SBA_NoLife(this));
	}
}

bool Player::IsTargetable(Player* targeter) {
	return true;
}

bool Player::IsCard() {
	return false;
}



