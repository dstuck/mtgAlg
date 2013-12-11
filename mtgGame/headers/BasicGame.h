/*
 * BasicGame.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef BASICGAME_H_
#define BASICGAME_H_

#include "Random.h"
#include "debug.h"
#include <vector>
#include <iostream>
#include <algorithm>
//#include <cmath>
#include "Player.h"
#include "Controller.h"
#include "Playable.h"
#include "Card_Creature.h"
#include "Card_Land.h"
#include "StateBasedActionQueue.h"
#include "StateBasedAction.h"
using namespace std;

class BasicGame {
public:
	BasicGame();
	BasicGame(Player*, Player*, int=0);
	virtual ~BasicGame();
	void Init();
	void ResetGame();
	bool FlipCoin();
	void PickFirst();
	void PrintGameState();
	bool GetNextPlay(bool,int,bool=true,bool=false);
	void ApplyStateBasedActions();
	void DealDamage();
	int PlayGame();
	void BeginGame();
	void Upkeep();
	void Main();
	void Combat();
	void End();

	void UnsickenAll(int);

	StateBasedActionQueue * sbaQueue;
	vector<Player*> players;
	vector<Playable*> theStack;
	bool gameOver;
	int* idum;
	int turnNum;
	int firstPlayer;
	int activePlayer;

	int noisy;
};

#endif /* BASICGAME_H_ */
