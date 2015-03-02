/*
 * TestControllerv2v2.h
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#ifndef TESTCONTROLLERV2V2_H_
#define TESTCONTROLLERV2V2_H_

#include <map>
#include <algorithm>
#include <cmath>
#include "Cardlist.h"
#include "Controller.h"
#include "Player.h"
#include "Card.h"
#include "Card_Land.h"
#include "Planeswalker.h"


class TestControllerv2: public Controller {
public:
	TestControllerv2();
	TestControllerv2(double*);
	virtual ~TestControllerv2();
	bool Mulligan(bool);
	bool PlayFirst();
	Playable* MakePlay(bool);
	vector<Card*> MakeAttacks();
	vector<Planeswalker*> AssignAttacks(vector<Card*>);
	vector<Card*> MakeBlocks(vector<Card*>);
	vector<Card*> AssignBlocks(vector<Card*>,vector<Card*>);
	vector<int> OrderBlocks(Card*,vector<Card*>);
	vector<int> AssignDamage(Card*,vector<Card*>);
	vector<Card*> GetDeck();
	vector<Card*> ChooseDiscards(int);

	double* GetBoardVec(Player*,double*);
	double AssessGameState(double*, double*, double, double);
	double ModifyByLife(double, double);
	vector<Card*> ProposeAttacks(Player*, Player*, double&, int=0, bool=false);
	vector<Card*> ProposeBlocks(vector<Card*>, Player*, Player*, double&,int=0,bool=false);
	vector<int> ProposeBlockOrder(Card*,vector<Card*>, Player*, Player*, double&);
//	Predict results of combat of attacker with blockers and modify attackerState and blockerState with the result return false if no change
	bool PredictDamage(Card*,vector<Card*>,double*,double*,int*);

	void PredictCrackback(Player*,Player*,double*,double*,vector<Card*>,int,double&);
	double GenerateAttacks(vector<bool>, int, int, double&, vector<bool>*, double*, double*, vector<Card*>,Player*,Player*,int=0);
	double GenerateBlocks(vector<vector<int> >, int, int, double&, vector<vector<int> >*, double*, double*, vector<Card*>, vector<Card*>,Player*,Player*,int=0);
	double PermuteBlocks(vector<int>, int, int, double&, vector<int>*, vector<int>, vector<int>, double*, double*, Card*, vector<Card*>,Player*,Player*);
	Player* BoardToPlayer(double*, int*, int);

	vector<Card*> LandsInHand();
	vector<Card*> LandsOnTable(Player*);
	vector<Card*> NonLandsInHand();
	vector<Card*> CastableCreatures();
	vector<Card*> GetPotentialAttackers(Player*);
	vector<Card*> GetPotentialBlockers(Player*);

	//	TODO: implement oppMat and
//	double * oppMat;
	double* valueVec;
	int totalCards;
	map<string,int> nameToIndex;
	vector<Card*> blockAssignment;
	vector<Playable*> nextPlays;
};

#endif /* TESTCONTROLLERV2_H_ */
