/*
 * TestControllerv2.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#include "headers/TestControllerv2.h"

TestControllerv2::TestControllerv2() {
	cout << "Need to set everything yourself!" << endl;
}

TestControllerv2::TestControllerv2(double* valueVec_) {
	valueVec = valueVec_;
	nameToIndex = CardSelector::NameToCardIndex();
	totalCards = CardList::size;
}


TestControllerv2::~TestControllerv2() {
	// TODO Auto-generated destructor stub
}

vector<Card*> TestControllerv2::GetDeck() {
//	return DeckList::FrenchVanillaBlue();
	return DeckList::VanillaGreen();
}

Playable * TestControllerv2::MakePlay(bool isSorc) {
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
		vector<Card*> creatureHand = CastableCreatures();
		double* myBoard = new double[CardList::size];
		double* oppBoard = new double[CardList::size];
		GetBoardVec(myPlayer,myBoard);
		GetBoardVec(oppPlayer,oppBoard);
		double maxVal = 0;
		double newVal;
		Playable* bestCreature = NULL;
		for(int i=0; i<creatureHand.size(); i++) {
			if(creatureHand[i]->CanPay(isSorc)) {
				myBoard[nameToIndex[creatureHand[i]->name]]++;
				newVal = AssessGameState(myBoard,oppBoard,myPlayer->lifeTotal,oppPlayer->lifeTotal);
//				cout << "Test value = "<< newVal << endl;
				if(maxVal < newVal) {
					maxVal = newVal;
					bestCreature = creatureHand[i];
				}
				myBoard[nameToIndex[creatureHand[i]->name]]--;
			}
		}
		delete myBoard;
		delete oppBoard;
		return bestCreature;

//		Card* firstCard = myPlayer->hand->cardVec[0];
//		if(firstCard->Pay(isSorc)) {
//			return firstCard;
//		}
	}
	return NULL;
}

vector<Card*> TestControllerv2::MakeAttacks() {
//	vector<Card*> attacking;
//	vector<Card*> potAttacks;
//	potAttacks = GetPotentialAttackers();
////	for(int i=0; i<potAttacks.size(); i++) {
////		if(potAttacks[i]->CanAttack()) {
////			attacking.push_back(potAttacks[i]);
////		}
////	}
//	if(potAttacks.size() == 0) {
//		return attacking;
//	}
//	vector<bool> isAttacking;
//	for(int i=0; i< potAttacks.size(); i++) {
//		isAttacking.push_back(false);
//	}
//	vector<bool> bestAttacks;
//	double* myBoard = new double[CardList::size];
//	double* oppBoard = new double[CardList::size];
//	GetBoardVec(myPlayer,myBoard);
//	GetBoardVec(oppPlayer,oppBoard);
//	double bestVal = 0;
//	GenerateAttacks(isAttacking,0,potAttacks.size(),bestVal, &bestAttacks, myBoard, oppBoard, potAttacks);
//
//	for(int i=0; i<bestAttacks.size(); i++) {
//		if(bestAttacks[i]) {
//			attacking.push_back(potAttacks[i]);
//		}
//	}
//	delete myBoard;
//	delete oppBoard;
//	return attacking;
	double value;
	return ProposeAttacks(myPlayer,oppPlayer,value);
}

vector<Card*> TestControllerv2::ProposeAttacks(Player* attackPlayer, Player* blockPlayer, double &value) {
	vector<Card*> attacking;
	vector<Card*> potAttacks;
	potAttacks = GetPotentialAttackers(attackPlayer);
//	for(int i=0; i<potAttacks.size(); i++) {
//		if(potAttacks[i]->CanAttack()) {
//			attacking.push_back(potAttacks[i]);
//		}
//	}
	if(potAttacks.size() == 0) {
		return attacking;
	}
	vector<bool> isAttacking;
	for(int i=0; i< potAttacks.size(); i++) {
		isAttacking.push_back(false);
	}
	vector<bool> bestAttacks;
	double* attackBoard = new double[CardList::size];
	double* blockBoard = new double[CardList::size];
	GetBoardVec(attackPlayer,attackBoard);
	GetBoardVec(blockPlayer,blockBoard);
	double bestVal = -0.1;
	GenerateAttacks(isAttacking,0,potAttacks.size(),bestVal, &bestAttacks, attackBoard, blockBoard, potAttacks, attackPlayer, blockPlayer);

	for(int i=0; i<bestAttacks.size(); i++) {
		if(bestAttacks[i]) {
			attacking.push_back(potAttacks[i]);
		}
	}
	delete attackBoard;
	delete blockBoard;
	return attacking;
}

double TestControllerv2::GenerateAttacks(vector<bool> isAttacking, int beg, int end, double& bestVal, vector<bool>* bestAttacks, double* attackState, double* blockState, vector<Card*> potAttacks, Player* attackPlayer, Player* blockPlayer) {
	if(beg!=end) {
		for(int i=0; i<2; i++) {
			if(i==1) {
				isAttacking[beg] = true;
			}
			double val = 0;
			val = GenerateAttacks(isAttacking,beg+1,end,bestVal,bestAttacks,attackState,blockState,potAttacks,attackPlayer,blockPlayer);
//			cout << "val = " << val << endl;
			if(val>bestVal) {
//				cout << val << " > " << bestVal << endl;
				bestVal = val;
				*bestAttacks = isAttacking;
			}
		}
		return 0.;
	}
	else {
//		cout << "isAttacking: ";
//		for(int i=0; i<isAttacking.size(); i++) {
//			cout << isAttacking[i] << " ";
//		}
//		cout << endl;
		double value;
		vector<Card*> attackers;
		for(int i=0; i<isAttacking.size(); i++) {
			if(isAttacking[i]) {
				attackers.push_back(potAttacks[i]);
			}
		}
		if(attackers.size()>0) {
			ProposeBlocks(attackers,blockPlayer,attackPlayer,value);
			if(value!=-1) {
//			Convert from blocker's value to attackers value
				value = 1-value;
			}
			else {
//			If no possible blockers
				double* blockBoardTemp = new double[totalCards];
				double* attackBoardTemp = new double[totalCards];
				memcpy(blockBoardTemp,blockState,totalCards*sizeof(double));
				memcpy(attackBoardTemp,attackState,totalCards*sizeof(double));
				double damage=0;
				for(int j=0; j<attackers.size(); j++) {
					damage += attackers[j]->GetPower();
				}
				value = AssessGameState(attackBoardTemp,blockBoardTemp,attackPlayer->lifeTotal,blockPlayer->lifeTotal-damage);
				delete blockBoardTemp;
				delete attackBoardTemp;
			}
		}
		else {
			double* blockBoardTemp = new double[totalCards];
			double* attackBoardTemp = new double[totalCards];
			memcpy(blockBoardTemp,blockState,totalCards*sizeof(double));
			memcpy(attackBoardTemp,attackState,totalCards*sizeof(double));
			value = AssessGameState(attackBoardTemp,blockBoardTemp,attackPlayer->lifeTotal,blockPlayer->lifeTotal);
			delete blockBoardTemp;
			delete attackBoardTemp;
		}
//		cout << "Value = " << value << endl;
		return value;
	}
}

vector<Planeswalker*> TestControllerv2::AssignAttacks(vector<Card*> attackers) {
	vector<Planeswalker*> targets;
	for(int i=0; i<attackers.size(); i++) {
		targets.push_back(oppPlayer);
	}
	return targets;
}

vector<Card*> TestControllerv2::MakeBlocks(vector<Card*> targets) {
//	vector<Card*> willBlock;
//	if(targets.size()==0) {
//		return willBlock;
//	}
//	targets.push_back(NULL);
//	vector<Card*> potBlocks = GetPotentialBlockers();
//	if(potBlocks.size()==0) {
//		return willBlock;
//	}
//	vector< vector<int> > blocks;
//	vector<int> empty;
//	for(int i=0; i<targets.size(); i++) {
//		blocks.push_back(empty);
//	}
//	vector<vector<int> > bestBlocks;
//	double* myBoard = new double[CardList::size];
//	double* oppBoard = new double[CardList::size];
//	GetBoardVec(myPlayer,myBoard);
//	GetBoardVec(oppPlayer,oppBoard);
//	double bestVal = 0;
//	GenerateBlocks(blocks,0,potBlocks.size(),bestVal, &bestBlocks, myBoard, oppBoard,targets, potBlocks);
////	cout << "bestBlocks" << endl;
////	for(int ii=0; ii<bestBlocks.size(); ii++) {
////		for(int j=0; j<bestBlocks[ii].size(); j++) {
////			cout << bestBlocks[ii][j] << " ";
////		}
////		cout << endl;
////	}
//	blockAssignment.clear();
//	for(int i=0; i<bestBlocks.size()-1; i++) {
//		for(int j=0; j<bestBlocks[i].size(); j++) {
//			willBlock.push_back(potBlocks[bestBlocks[i][j]]);
//			blockAssignment.push_back(targets[i]);
//		}
//	}
//	delete myBoard;
//	delete oppBoard;
//	return willBlock;
	double value;
	return ProposeBlocks(targets,myPlayer,oppPlayer,value);
}

vector<Card*> TestControllerv2::ProposeBlocks(vector<Card*> targets, Player* blockPlayer, Player* attackPlayer, double& blockVal) {
	vector<Card*> willBlock;
	if(targets.size()==0) {
		return willBlock;
	}
	targets.push_back(NULL);
	vector<Card*> potBlocks = GetPotentialBlockers(blockPlayer);
	if(potBlocks.size()==0) {
		blockVal=-1;
		return willBlock;
	}
	vector< vector<int> > blocks;
	vector<int> empty;
	for(int i=0; i<targets.size(); i++) {
		blocks.push_back(empty);
	}
	vector<vector<int> > bestBlocks;
	double* blockBoard = new double[CardList::size];
	double* attackBoard = new double[CardList::size];
	GetBoardVec(blockPlayer,blockBoard);
	GetBoardVec(attackPlayer,attackBoard);
	double bestVal = -0.1;
	GenerateBlocks(blocks,0,potBlocks.size(),bestVal, &bestBlocks, blockBoard, attackBoard,targets, potBlocks, blockPlayer, attackPlayer);
//	cout << "bestBlocks:\t" << bestVal << endl;
//	for(int ii=0; ii<bestBlocks.size(); ii++) {
//		for(int j=0; j<bestBlocks[ii].size(); j++) {
//			cout << bestBlocks[ii][j] << " ";
//		}
//		cout << endl;
//	}
	blockVal = bestVal;
	blockAssignment.clear();
	for(int i=0; i<bestBlocks.size()-1; i++) {
		for(int j=0; j<bestBlocks[i].size(); j++) {
			willBlock.push_back(potBlocks[bestBlocks[i][j]]);
			blockAssignment.push_back(targets[i]);
		}
	}
	delete blockBoard;
	delete attackBoard;
	return willBlock;
}

double TestControllerv2::GenerateBlocks(vector<vector<int> > blocks, int beg, int end, double &bestVal, vector<vector<int> >* bestBlocks, double* blockState, double* attackState, vector<Card*> targets, vector<Card*> potBlocks, Player* blockPlayer, Player* attackPlayer) {
	if(beg!=end) {
		double val = 0;
		for(int i=0; i<targets.size(); i++) {
			blocks[i].push_back(beg);
			val = GenerateBlocks(blocks,beg+1,end,bestVal,bestBlocks,blockState,attackState,targets,potBlocks,blockPlayer,attackPlayer);
			if(val>bestVal) {
//				cout << val << " > " << bestVal << endl;
				bestVal = val;
				*bestBlocks = blocks;
//				cout << "bestBlocks" << endl;
//				for(int ii=0; ii<blocks.size(); ii++) {
//					for(int j=0; j<blocks[ii].size(); j++) {
//						cout << blocks[ii][j] << " ";
//					}
//					cout << endl;
//				}

			}
			blocks[i].pop_back();
		}
		return 0.;
	}
	else {
//		cout << "blocks" << endl;
//		for(int ii=0; ii<blocks.size(); ii++) {
//			for(int j=0; j<blocks[ii].size(); j++) {
//				cout << blocks[ii][j] << " ";
//			}
//			cout << endl;
//		}
		bool validBlocks = true;
		for(int i=0; i<blocks.size()-1; i++) {
			for(int j=0; j<blocks[i].size(); j++) {
				validBlocks = validBlocks && potBlocks[blocks[i][j]]->CanBlock(targets[i]);
			}
		}
		if(!validBlocks) {
			return -1;
		}
		double val;
		double* blockBoardTemp = new double[totalCards];
		double* attackBoardTemp = new double[totalCards];
		memcpy(blockBoardTemp,blockState,totalCards*sizeof(double));
		memcpy(attackBoardTemp,attackState,totalCards*sizeof(double));
		double* damage = new double(0);
		for(int i=0; i<blocks.size()-1; i++) {
			vector<Card*> theBlockers;
			for(int j=0; j<blocks[i].size(); j++) {
				theBlockers.push_back(potBlocks[blocks[i][j]]);
			}
			vector<int> ordering;
			double junk;
			ordering = ProposeBlockOrder(targets[i],theBlockers,blockPlayer,attackPlayer,junk);
			for ( int s = 1, d; s < ordering.size(); ++ s ) {
				for ( d = ordering[s]; d < s; d = ordering[d] ) ;
				if ( d == s ) while ( d = ordering[d], d != s ) swap(theBlockers[s], theBlockers[d] );
			}
//			cout << targets[i]->name << " is blocked by ";
//			for(int ii=0; ii< theBlockers.size(); ii++) {
//				cout << theBlockers[ii]->name << " ";
//			}
//			cout << endl;
			PredictDamage(targets[i],theBlockers,attackBoardTemp,blockBoardTemp,damage);
//			cout << "Damage = " << *damage << endl;
		}
//		cout << "Final life = " << blockPlayer->lifeTotal-*damage << endl;
//		cout << "Attack life = " << attackPlayer->lifeTotal << endl;
		val = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-*damage,attackPlayer->lifeTotal);
//		cout << "Value = " << val << endl;
		delete blockBoardTemp;
		delete attackBoardTemp;
		delete damage;
		return val;
	}
}

vector<Card*> TestControllerv2::AssignBlocks(vector<Card*> blockers, vector<Card*> attackers) {
	vector<Card*> blocked;
//	for(int i=0; i<blockers.size(); i++) {
//		blocked.push_back(attackers[i%attackers.size()]);
//	}
	if(blockAssignment.size()!=0) {
		blocked = blockAssignment;
		blockAssignment.clear();
	}
	return blocked;
}

vector<int> TestControllerv2::OrderBlocks(Card* attacker, vector<Card*> blockers) {
//	vector<int> ordering;
////	First, add unkillables to end of list
//	int blockersLeft = blockers.size();
//	vector<int> remaining;
//	for(int i=0; i<blockers.size(); i++) {
//		if(blockers[i]->toughness>attacker->power) {
//			ordering.push_back(blockersLeft-1);
//			blockersLeft--;
//		}
//		else {
//			remaining.push_back(i);
//			ordering.push_back(-1);
//		}
//	}
////	Only zero or one killable creature, so no decisions
//	if(blockersLeft==0) {
//		return ordering;
//	}
//	else if(blockersLeft==1) {
//		ordering[remaining[0]]=0;
//		return ordering;
//	}
////	Otherwise, we need to consider permutations to kill the most value
//	double* myBoard = new double[CardList::size];
//	double* oppBoard = new double[CardList::size];
//	GetBoardVec(myPlayer,myBoard);
//	GetBoardVec(oppPlayer,oppBoard);
//	double bestVal = 0;
//	vector<int> bestOrdering;
//	vector<int> miniOrdering;
//	for(int i=0; i<blockersLeft; i++) {
//		miniOrdering.push_back(i);
//	}
////	This is a mess!! But it should work
//	PermuteBlocks(miniOrdering, 0, blockersLeft, bestVal, &bestOrdering, ordering, remaining, myBoard, oppBoard, attacker, blockers);
////	cout << "bestOrdering is: " << endl;
////	for(int i=0; i<bestOrdering.size(); i++) {
////		cout << bestOrdering[i] << endl;
////	}
//	for(int i=0; i<blockersLeft; i++) {
//		ordering[remaining[i]] = bestOrdering[i];
//	}
//	delete myBoard;
//	delete oppBoard;
//	return ordering;
	double value;
	return ProposeBlockOrder(attacker, blockers, myPlayer, oppPlayer, value);
}

vector<int> TestControllerv2::ProposeBlockOrder(Card* attacker, vector<Card*> blockers, Player* blockPlayer, Player* attackPlayer, double &value) {
	vector<int> ordering;
//	First, add unkillables to end of list
	int blockersLeft = blockers.size();
	vector<int> remaining;
	for(int i=0; i<blockers.size(); i++) {
		if(blockers[i]->toughness>attacker->power) {
			ordering.push_back(blockersLeft-1);
			blockersLeft--;
		}
		else {
			remaining.push_back(i);
			ordering.push_back(-1);
		}
	}
//	Only zero or one killable creature, so no decisions
	if(blockersLeft==0) {
		return ordering;
	}
	else if(blockersLeft==1) {
		ordering[remaining[0]]=0;
		return ordering;
	}
//	Otherwise, we need to consider permutations to kill the most value
	double* blockBoard = new double[CardList::size];
	double* attackBoard = new double[CardList::size];
	GetBoardVec(blockPlayer,blockBoard);
	GetBoardVec(attackPlayer,attackBoard);
	double bestVal = -0.1;
	vector<int> bestOrdering;
	vector<int> miniOrdering;
	for(int i=0; i<blockersLeft; i++) {
		miniOrdering.push_back(i);
	}
//	This is a mess!! But it should work
	PermuteBlocks(miniOrdering, 0, blockersLeft, bestVal, &bestOrdering, ordering, remaining, blockBoard, attackBoard, attacker, blockers,blockPlayer,attackPlayer);
//	cout << "bestOrdering is: " << endl;
//	for(int i=0; i<bestOrdering.size(); i++) {
//		cout << bestOrdering[i] << endl;
//	}
	value = bestVal;
	for(int i=0; i<blockersLeft; i++) {
		ordering[remaining[i]] = bestOrdering[i];
	}
	delete blockBoard;
	delete attackBoard;
	return ordering;
}

double TestControllerv2::PermuteBlocks(vector<int> ordering, int beg, int end, double &bestVal, vector<int>* bestOrdering, vector<int> totalOrdering,vector<int> remaining, double* blockState, double* oppState, Card* attacker, vector<Card*> blockers, Player* blockPlayer, Player* attackPlayer) {
	if(beg!=end) {
		double val = 0;
//		int bestSwap = -1;
		for(int i=beg; i<end; i++) {
			swap(ordering[beg], ordering[i]);
			val = PermuteBlocks(ordering,beg+1,end,bestVal,bestOrdering,totalOrdering,remaining,blockState,oppState,attacker,blockers,blockPlayer,attackPlayer);
//			cout << "BestVal = " << bestVal << endl;
//			cout << val << "\t";
//			for(int j=0; j<ordering.size(); j++) {
//				cout << ordering[j] << " ";
//			}
//			cout << endl;
			if(val>bestVal) {
//				cout << val << " > " << bestVal << endl;
				bestVal = val;
//				bestSwap = i;
				*bestOrdering = ordering;
			}
			swap(ordering[beg], ordering[i]);
		}
//		bestOrdering->push_back(bestSwap);
		return 0.;
	}
	else{
		double* blockBoardTemp = new double[totalCards];
		double* attackBoardTemp = new double[totalCards];
		memcpy(blockBoardTemp,blockState,totalCards*sizeof(double));
		memcpy(attackBoardTemp,oppState,totalCards*sizeof(double));
		for(int i=0; i<end; i++) {
			totalOrdering[remaining[i]] = ordering[i];
		}
//		Reorder from http://stackoverflow.com/questions/838384/reorder-vector-using-a-vector-of-indices
		for ( int s = 1, d; s < totalOrdering.size(); ++ s ) {
			for ( d = totalOrdering[s]; d < s; d = totalOrdering[d] ) ;
			if ( d == s ) while ( d = totalOrdering[d], d != s ) swap(blockers[s], blockers[d] );
		}
		double damage = 0;
		PredictDamage(attacker,blockers,blockBoardTemp,attackBoardTemp, &damage);
		double value = AssessGameState(blockBoardTemp,attackBoardTemp, blockPlayer->lifeTotal,attackPlayer->lifeTotal);
		delete blockBoardTemp;
		delete attackBoardTemp;
		return value;
	}
}

vector<int> TestControllerv2::AssignDamage(Card* attacker,vector<Card*> blockers) {
	vector<int> damageAssigned;
	int damageLeft = attacker->power;
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

bool TestControllerv2::PredictDamage(Card* attacker, vector<Card*> blockers, double* attackState, double* blockState, double* damage) {
	bool creatureDead = false;
	double damageLeft = attacker->power;
	double blockerDamage = 0;
	if(blockers.size()==0) {
		*damage += damageLeft;
	}
	for(int i=0; i<blockers.size(); i++) {
		blockerDamage += blockers[i]->power;
		if(damageLeft < blockers[i]->toughness) {
			damageLeft = 0;
		}
		else {
			blockState[nameToIndex[blockers[i]->name]]--;
			damageLeft -= blockers[i]->toughness;
//			cout << blockers[i]->name << " dies." << endl;
			creatureDead=true;
		}
	}
	if(blockerDamage >= attacker->toughness) {
		attackState[nameToIndex[attacker->name]]--;
//		cout << attacker->name << " dies." << endl;
		creatureDead=true;
	}
	return creatureDead;
}

vector<Card*> TestControllerv2::ChooseDiscards(int nDiscard) {
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

vector<Card*> TestControllerv2::LandsInHand() {
	vector<Card*> landHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(myPlayer->hand->cardVec[i]->isLand) {
			landHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return landHand;
}

vector<Card*> TestControllerv2::LandsOnTable() {
	vector<Card*> landsPlayed;
	for(int i=0; i<myPlayer->bf->cardVec.size(); i++) {
		if(myPlayer->bf->cardVec[i]->isLand) {
			landsPlayed.push_back(myPlayer->bf->cardVec[i]);
		}
	}
	return landsPlayed;
}

vector<Card*> TestControllerv2::NonLandsInHand() {
	vector<Card*> nonLandHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(!myPlayer->hand->cardVec[i]->isLand) {
			nonLandHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return nonLandHand;
}

vector<Card*> TestControllerv2::CastableCreatures() {
	vector<Card*> creatureHand;
	for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
		if(myPlayer->hand->cardVec[i]->isCreature && myPlayer->HasMana(myPlayer->hand->cardVec[i]->mana)) {
			creatureHand.push_back(myPlayer->hand->cardVec[i]);
		}
	}
	return creatureHand;
}
vector<Card*> TestControllerv2::GetPotentialAttackers(Player* thePlayer) {
	vector<Card*> attackables;
	for(int i=0; i<thePlayer->bf->cardVec.size(); i++) {
		if(thePlayer->bf->cardVec[i]->CanAttack()) {
			attackables.push_back(thePlayer->bf->cardVec[i]);
		}
	}
	return attackables;
}

vector<Card*> TestControllerv2::GetPotentialBlockers(Player* thePlayer) {
	vector<Card*> potBlocks;
	for(int i=0; i<thePlayer->bf->cardVec.size(); i++) {
		if(!thePlayer->bf->cardVec[i]->tapped && thePlayer->bf->cardVec[i]->isCreature){
			potBlocks.push_back(thePlayer->bf->cardVec[i]);
		}
	}
	return potBlocks;
}

double* TestControllerv2::GetBoardVec(Player* thePlayer, double* boardVec) {
//	TODO: Implement for more than creatures
//	TODO: Don't reinitialize boardVec each new time, need sparse implementation
//	double* boardVec = new double[CardList::size];
	for(int i=0; i<CardList::size; i++) {
			boardVec[i] = 0;
	}
	vector<Card*> theCreatures = thePlayer->GetCreatures();
	for(int i=0; i<theCreatures.size(); i++) {
		boardVec[nameToIndex[theCreatures[i]->name]]++;
	}
	return boardVec;
}

bool TestControllerv2::Mulligan(bool isFirst) {
	int numLands = LandsInHand().size();
	if((numLands<2 || numLands >5) && myPlayer->hand->cardVec.size() > 5) {
		return true;
	}
	else {
		return false;
	}
}

bool TestControllerv2::PlayFirst() {
	return true;
}

double TestControllerv2::AssessGameState(double* myBoard, double* oppBoard, double myLife, double oppLife) {
	double myVal = 0;
	double oppVal = 0;
	for(int i=0; i<totalCards; i++) {
		if(myBoard[i]){
			myVal += myBoard[i]*valueVec[i];
		}
	}
	myVal = ModifyByLife(myVal,myLife);
//	cout << "myVal = " << myVal << endl;
	for(int i=0; i<totalCards; i++) {
		if(oppBoard[i]) {
			oppVal += oppBoard[i]*valueVec[i];
		}
	}
	oppVal = ModifyByLife(oppVal,oppLife);
//	cout << "oppVal = " << oppVal << endl;
	if(myVal==oppVal) {
		return 0.5;
	}
	else {
		return myVal/(myVal+oppVal);
	}
}

double TestControllerv2::ModifyByLife(double value, double lifeTot) {
	if(lifeTot<=0) {
		value = 0.0;
	}
	else if(lifeTot<=3) {
		value += lifeTot*2;
	}
	else if(lifeTot<=7) {
		value += lifeTot*1.5+1.5;
	}
	else if(lifeTot<=11) {
		value += lifeTot*1.0+5;
	}
	else if(lifeTot<=18) {
		value += lifeTot*0.5+10.5;
	}
	else {
		value += lifeTot*0.25+15;
	}
	return value;
}


