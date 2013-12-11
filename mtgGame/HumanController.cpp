/*
 * HumanController.cpp
 *
 *  Created on: Dec 7, 2013
 *      Author: dstuck
 */

#include "headers/HumanController.h"

HumanController::HumanController() {
}

HumanController::HumanController(string name_) {
	myName = name_;
}


HumanController::~HumanController() {
	// TODO Auto-generated destructor stub
}

vector<Card*> HumanController::GetDeck() {
	return DeckList::VanillaGreen();
//	return DeckList::FrenchVanillaBlue();
}

bool HumanController::Mulligan(bool isFirst) {
	bool theResult;
	if(isFirst) {
		WriteOut("On the play.");
	}
	else {
		WriteOut("On the draw.");
	}
	myPlayer->PrintHand();
	cout << endl;
	WriteOut("Will you mulligan?",true);
	while(!GetBool(&theResult, false)) {}
	return theResult;
}

bool HumanController::PlayFirst() {
	bool theResult;
	WriteOut("Will you play first?",true);
	while(!GetBool(&theResult)) {}
	return theResult;
}

Playable* HumanController::MakePlay(bool isSorc) {
//	For now, just display cards and choose one
	if(isSorc) {
		PrintHand();
		cout << endl;
		WriteOut("Which card will you play?",true);
		int cardToPlay;
		while(!GetInt(&cardToPlay,myPlayer->hand->cardVec.size())) {}
		if(cardToPlay == 0) {
			return NULL;
		}
		else{
			return myPlayer->hand->cardVec[cardToPlay-1];
		}
	}
	else{
		return NULL;
	}
}

vector<Card*> HumanController::MakeAttacks() {
	vector<Card*> attackers;
	vector<Card*> attackables = GetAttackables();
	if(attackables.size()==0) {
		WriteOut("No legal attacks.");
		return attackers;
	}
	vector<int> cardIndices;
	PrintCards(attackables);
	cout << endl;
	WriteOut("Which creatures will attack?",true);
	while(!GetIntVec(&cardIndices,attackables.size())) {}
	for(int i=0; i<cardIndices.size(); i++) {
		attackers.push_back(attackables[cardIndices[i]-1]);
	}
	return attackers;
}

vector<Planeswalker*> HumanController::AssignAttacks(vector<Card*> attackers) {
	vector<Planeswalker*> targets;
	for(int i=0; i<attackers.size(); i++) {
		targets.push_back(oppPlayer);
	}
	return targets;
}

vector<Card*> HumanController::MakeBlocks(vector<Card*> attackers) {
	vector<Card*> blocking;
	if(attackers.size()==0){
		return blocking;
	}
	PrintCards(attackers, "Attackers: ", false);
	cout << endl;
	vector<Card*> potBlocks = GetPotentialBlockers();
	if(potBlocks.size()==0) {
		WriteOut("No legal blockers.");
		return blocking;
	}
	vector<int> cardIndices;
	PrintCards(potBlocks);
	cout << endl;
	WriteOut("Which creatures will block?",true);
	while(!GetIntVec(&cardIndices,potBlocks.size())) {}
	for(int i=0; i<cardIndices.size(); i++) {
		blocking.push_back(potBlocks[cardIndices[i]-1]);
	}
	return blocking;
}

vector<Card*> HumanController::AssignBlocks(vector<Card*> blockers, vector<Card*> attackers) {
	vector<Card*> blocked;
	if(blockers.size()==0) {
		return blocked;
	}
	if(attackers.size()==1) {
		for(int i=0; i< blockers.size(); i++) {
			blocked.push_back(attackers[0]);
		}
		return blocked;
	}
	vector<int> cardIndices;
	WriteOut("Assign attacker to each blocker.",true);
	while(!GetIntVec(&cardIndices,attackers.size())) {}
	for(int i=0; i<cardIndices.size(); i++) {
		blocked.push_back(attackers[cardIndices[i]-1]);
	}
	return blocked;
}

vector<int> HumanController::OrderBlocks(Card* attacker, vector<Card*> blockers) {
	vector<int> ordering;
	if(blockers.size()==1) {
		ordering.push_back(0);
		return ordering;
	}
	PrintCards(attacker, "Attacker: ", false);
	cout << endl;
	PrintCards(blockers, "Blockers: ", true);
	cout << endl;
	WriteOut("Order blockers.",true);
	while(!GetIntVec(&ordering,blockers.size())) {}
	for(int i=0; i<ordering.size(); i++) {
		ordering[i]--;
	}
	return ordering;
}

vector<int> HumanController::AssignDamage(Card* attacker, vector<Card*> blockers) {
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

vector<Card*> HumanController::ChooseDiscards(int nDiscard) {
	vector<Card*> discards;
	if(nDiscard <= 0 || myPlayer->hand->cardVec.size()==0) {
		return discards;
	}
	PrintCards(myPlayer->hand->cardVec, "Hand: ");
	cout << endl;
	vector<int> cardIndices;
	while(!GetIntVec(&cardIndices,myPlayer->hand->cardVec.size())) {}
	WriteOut("Choose "+to_string(nDiscard)+" cards to discard.");
	for(int i=0; i<cardIndices.size(); i++) {
		discards.push_back(myPlayer->hand->cardVec[cardIndices[i]-1]);
	}
	return discards;
}





void HumanController::WriteOut(string message, bool fullWrite) {
	if(fullWrite) {
		cout << myName << ":\t" << message << endl;
	}
	else{
		cout << message << endl;
	}
}

void HumanController::PrintHand() {
//	TODO: Add Player->playablesVec
	cout << setw(7) << "Cards: ";
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		cout << setw(6) << myPlayer->hand->cardVec[i]->GetImage();
		cout << " ";
	}
	cout << endl;
	cout << setw(7) << "Index: ";
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		cout << setw(6) << i+1;
		cout << " ";
	}
}

void HumanController::PrintCards(vector<Card*> theCards, string notice , bool displayIndex) {
	cout << left << setw(12) << notice;
	for(int i=0; i<theCards.size(); i++) {
		cout << setw(6) << theCards[i]->GetImage();
		cout << " ";
	}
	cout << endl;
	if(displayIndex) {
		cout << left << setw(12) << "Index: ";
		for(int i=0; i<theCards.size(); i++) {
			cout << setw(6) << i+1;
			cout << " ";
		}
	}
}

void HumanController::PrintCards(Card* theCard, string notice , bool displayIndex) {
	cout << left << setw(12) << notice;
	cout << setw(6) << theCard->GetImage();
	cout << " ";
	cout << endl;
	if(displayIndex) {
		cout << left << setw(12) << "Index: ";
		cout << setw(6) << 1;
		cout << " ";
	}
}

vector<Card*> HumanController::GetAttackables() {
	vector<Card*> attackables;
	for(int i=0; i<myPlayer->bf->cardVec.size(); i++) {
		if(!myPlayer->bf->cardVec[i]->tapped && !myPlayer->bf->cardVec[i]->defender && !myPlayer->bf->cardVec[i]->summoningSick && myPlayer->bf->cardVec[i]->isCreature){
			attackables.push_back(myPlayer->bf->cardVec[i]);
		}
	}
	return attackables;
}

vector<Card*> HumanController::GetPotentialBlockers() {
	vector<Card*> potBlocks;
	for(int i=0; i<myPlayer->bf->cardVec.size(); i++) {
		if(!myPlayer->bf->cardVec[i]->tapped && myPlayer->bf->cardVec[i]->isCreature){
			potBlocks.push_back(myPlayer->bf->cardVec[i]);
		}
	}
	return potBlocks;
}

bool HumanController::GetBool(bool* theResult, bool defaultBool) {
	string readIn;
	getline(cin,readIn);
	if(readIn.empty()) {
		*theResult = defaultBool;
		return true;
	}
	istringstream iss(readIn);
	char readNum;
	while(iss.good()) {
		if(iss >> readNum) {
			if(readNum=='y'||readNum=='Y'||readNum=='t'||readNum=='T'||readNum=='1'||readNum=='2'||readNum=='3'||readNum=='4'||readNum=='5') {
				*theResult = true;
				return true;
			}
			if(readNum=='n'||readNum=='N'||readNum=='f'||readNum=='F'||readNum=='0') {
				*theResult = false;
				return true;
			}
		}
	}
	WriteOut("Invalid bool! Try 1 or 0.");
	return false;
}

bool HumanController::GetIntVec(vector<int>* readInts, int maxVal) {
	readInts->clear();
	string readIn;
	getline(cin,readIn);
	if(readIn.empty()) {
		return true;
	}
	istringstream iss(readIn);
	int readNum;
	bool badRead =false;
	while(iss.good()) {
		if(iss >> readNum) {
			if(readNum>maxVal) {
				WriteOut("Bad read! Enter a number smaller than "+to_string(maxVal+1)+".");
				return false;
			}
			if(readNum<=0) {
							WriteOut("Bad read! Number must be > 0.");
							return false;
						}
			readInts->push_back(readNum);
		}
		else{
			badRead = true;
		}
	}
	if(badRead) {
		WriteOut("Bad read! Please enter numbers and spaces only.");
		return false;
	}
	else {
		return true;
	}
}

bool HumanController::GetInt(int* readInt, int maxVal) {
	string readIn;
	getline(cin,readIn);
	if(readIn.empty()) {
		*readInt = 0;
		return true;
	}
	istringstream iss(readIn);
	int readNum;
	while(iss.good()) {
		if(iss >> readNum) {
			if(readNum>=0) {
				if(readNum>maxVal) {
					WriteOut("Bad read! Enter a number smaller than "+to_string(maxVal+1)+".");
					return false;
				}
				else {
					*readInt=readNum;
					return true;
				}
			}
			else {
				WriteOut("Bad read! Please enter a positive integer.");
				return false;
			}
		}
		else{
			WriteOut("Bad read! Please enter a single integer.");
			return false;
		}
	}
	WriteOut("Bad read! Please enter a single integer.");
	return false;
}



