/*
 * main.C
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "BasicGame.h"
#include "TestController.h"
#include "TestControllerv2.h"
#include "HumanController.h"
#include "debug.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "MetaHandler.h"

#include <stdlib.h>
#include <sstream>
//#include "CardSelector.h"
//#include "CardList.h"
//#include "Card_Creature.h"

using namespace std;


int main(int argc, char *argv[]){

//	MetaHandler::WriteDefaultCardValues();
	double* defaults = MetaHandler::ReadDefaultCardValues();


//	HumanController * testP1 = new HumanController("Player 1");
	TestControllerv2 * testP1 = new TestControllerv2(defaults);
	HumanController * testP2 = new HumanController("Player 2");
//	TestControllerv2 * testP2 = new TestControllerv2(defaults);
//	TestController * testP2 = new TestController();

	Player * p1 = new Player(testP1);
	Player * p2 = new Player(testP2);

	int noisy = 3;

	BasicGame * game = new BasicGame(p1, p2, noisy);

// Insert Debug here:
//	Debug Attacking
	game->Init();
	Card* attacker1 = (CardSelector::NewCard(CardList::NorwoodRanger));
	Card* attacker2 = (CardSelector::NewCard(CardList::GrizzlyBears));
	Card* attacker3 = (CardSelector::NewCard(CardList::GrizzlyBears));
	Card* attacker4 = (CardSelector::NewCard(CardList::NorwoodRanger));
	Card* blocker1 = (CardSelector::NewCard(CardList::NorwoodRanger));
	Card* blocker2 = (CardSelector::NewCard(CardList::GrizzlyBears));
	blocker1->thePlayer = p2;
	blocker2->thePlayer = p2;
	attacker1->thePlayer = p1;
	attacker2->thePlayer = p1;
	attacker3->thePlayer = p1;
	attacker4->thePlayer = p1;
	blocker1->curLoc = blocker1->thePlayer->bf;
	blocker2->curLoc = blocker2->thePlayer->bf;
	attacker1->curLoc = attacker1->thePlayer->bf;
	attacker2->curLoc = attacker2->thePlayer->bf;
	attacker3->curLoc = attacker3->thePlayer->bf;
	attacker4->curLoc = attacker4->thePlayer->bf;
	blocker1->thePlayer->bf->cardVec.push_back(blocker1);
	blocker2->thePlayer->bf->cardVec.push_back(blocker2);
	attacker1->thePlayer->bf->cardVec.push_back(attacker1);
	attacker2->thePlayer->bf->cardVec.push_back(attacker2);
	attacker3->thePlayer->bf->cardVec.push_back(attacker3);
	attacker4->thePlayer->bf->cardVec.push_back(attacker4);
//	blocker1->tapped=true;
//	blocker2->tapped=true;
	attacker1->summoningSick = false;
	attacker2->summoningSick = false;
	attacker3->summoningSick = true;
	attacker4->summoningSick = true;
	p1->lifeTotal = 20;
	p2->lifeTotal = 20;
	vector<Card*> theAttacks;
	double value = 0;
	theAttacks = dynamic_cast<TestControllerv2*>(p1->control)->ProposeAttacks(p1, p2, value, 1);
//	theAttacks = p1->control->MakeAttacks();
	cout << "The attackers are: " << endl;
	for(int i=0; i<theAttacks.size(); i++) {
		cout << theAttacks[i]->GetName() << endl;
	}
	exit(-1);

	int record[3] = {};
	for(int i=0; i<10; i++) {
		game->Init();
		record[game->PlayGame()]++;
		game->ResetGame();
	}
	cout << "W: " << record[0] << "\tL: " << record[1] << endl;

////	Debug writing
//	double* v1= new double(1.0);
//	double* v2= new double(2.0);
//	double* v3= new double(1.0);
//	double* v4= new double(5.0);
//	vector<double*> vec;
//	vec.push_back(v1);
//	vec.push_back(v2);
//	vec.push_back(v3);
//	vec.push_back(v4);
//	for(int i=0; i<vec.size(); i++) {
//		cout << "v_" <<i<<" = " << *vec[i];
//		cout << endl;
//	}
//	vector<double*>::const_iterator endit = vec.end();
//	vector<double*>::const_iterator newendit = remove(vec.begin(),vec.end(),v3);
//	vec.erase(newendit,endit);
////	vec.erase(remove(vec.begin(), vec.end(), v3),vec.end());
//	for(int i=0; i<vec.size(); i++) {
//		cout << "v_" <<i<<" = " << *vec[i];
//		cout << endl;
//	}
//	double* testMat = new double[4];
//	testMat[0*2+0] = 0.0;
//	testMat[0*2+1] = 1.0;
//	testMat[1*2+0] = 2.1;
//	testMat[1*2+1] = 3.0;
//	for(int i=0; i<4; i++) {
//		cout << testMat[i] << endl;
//	}
//	MatClass::WriteBinMat(testMat,"example.bin",4);
//	int matSize;
//	double* outMat = MatClass::ReadBinMat("example.bin", &matSize);
//	for(int i=0; i<matSize; i++) {
//		cout << *(outMat+i) << endl;
//	}


//	//	Debug Block Ordering
//		game->Init();
//		Card* attacker = (CardSelector::NewCard(CardList::NettleSwine));
//		Card* blocker1 = (CardSelector::NewCard(CardList::GrizzlyBears));
//		Card* blocker2 = (CardSelector::NewCard(CardList::NessianCourser));
//		Card* blocker3 = (CardSelector::NewCard(CardList::WindDrake));
//		Card* blocker4 = (CardSelector::NewCard(CardList::WindDrake));
//		attacker->thePlayer = p1;
//		blocker1->thePlayer = p2;
//		blocker2->thePlayer = p2;
//		blocker3->thePlayer = p2;
//		blocker4->thePlayer = p2;
//		attacker->curLoc = attacker->thePlayer->bf;
//		blocker1->curLoc = blocker1->thePlayer->bf;
//		blocker2->curLoc = blocker2->thePlayer->bf;
//		blocker3->curLoc = blocker3->thePlayer->bf;
//		blocker4->curLoc = blocker4->thePlayer->bf;
//		attacker->thePlayer->bf->cardVec.push_back(attacker);
//		blocker1->thePlayer->bf->cardVec.push_back(blocker1);
//		blocker2->thePlayer->bf->cardVec.push_back(blocker2);
//		blocker3->thePlayer->bf->cardVec.push_back(blocker3);
//		blocker4->thePlayer->bf->cardVec.push_back(blocker4);
//		vector<Card*> blockers;
//		blockers.push_back(blocker1);
//		blockers.push_back(blocker2);
//		blockers.push_back(blocker3);
//		blockers.push_back(blocker4);
//		vector<int> order;
//		order = p1->control->OrderBlocks(attacker,blockers);
//		cout << "Final order is: " << endl;
//		for(int i=0; i<order.size(); i++) {
//			cout << order[i] << endl;
//		}
//		exit(-1);

////	Debug Blocking
//	game->Init();
//	Card* attacker1 = (CardSelector::NewCard(CardList::GrizzlyBears));
//	Card* attacker2 = (CardSelector::NewCard(CardList::NessianCourser));
////	Card* attacker3 = (CardSelector::NewCard(CardList::PheresBandCentaurs));
////	Card* attacker4 = (CardSelector::NewCard(CardList::NessianCourser));
//	Card* blocker = (CardSelector::NewCard(CardList::GrizzlyBears));
//	blocker->thePlayer = p1;
//	attacker1->thePlayer = p2;
//	attacker2->thePlayer = p2;
////	attacker3->thePlayer = p2;
////	attacker4->thePlayer = p2;
//	blocker->curLoc = blocker->thePlayer->bf;
//	attacker1->curLoc = attacker1->thePlayer->bf;
//	attacker2->curLoc = attacker2->thePlayer->bf;
////	attacker3->curLoc = attacker3->thePlayer->bf;
////	attacker4->curLoc = attacker4->thePlayer->bf;
//	blocker->thePlayer->bf->cardVec.push_back(blocker);
//	attacker1->thePlayer->bf->cardVec.push_back(attacker1);
//	attacker2->thePlayer->bf->cardVec.push_back(attacker2);
////	attacker3->thePlayer->bf->cardVec.push_back(attacker3);
////	attacker4->thePlayer->bf->cardVec.push_back(attacker4);
//	vector<Card*> attackers;
//	attackers.push_back(attacker1);
////	attackers.push_back(attacker2);
////	attackers.push_back(attacker3);
////	attackers.push_back(attacker4);
//	p1->lifeTotal = 20;
//	p2->lifeTotal = 18;
//	vector<Card*> theBlocks;
//	double value=-0.1;
//	theBlocks = dynamic_cast<TestControllerv2*>(p1->control)->ProposeBlocks(attackers,p1,p2,value,1,true);
////	theBlocks = p1->control->MakeBlocks(attackers);
//	cout << "The blockers are: " << endl;
//	for(int i=0; i<theBlocks.size(); i++) {
//		cout << theBlocks[i]->GetName() << endl;
//	}
//	vector<Card*> theTargets;
//	theTargets = p1->control->AssignBlocks(theBlocks, attackers);
//	cout << "The block targets are: " << endl;
//	for(int i=0; i<theTargets.size(); i++) {
//		cout << theTargets[i]->GetName() << endl;
//	}
//	exit(-1);

//






//	cout << "Test test test" << endl;
	return 0;
}
