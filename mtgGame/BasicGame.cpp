/*
 * BasicGame.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/BasicGame.h"

BasicGame::BasicGame() {
	cout << "Wrong BasicGame constructor!" << endl;
//
//	Player* p1 = new Player();
//	Player* p2 = new Player();
//	players.push_back(p1);
//	players.push_back(p2);
//
//    idum = new int;
//    *idum = -time(0);
//    for(int i=0; i<players.size(); i++) {
//    	players[i]->idum = idum;
//    }
//
//    Init();
}

BasicGame::BasicGame(Player* player1, Player* player2, int noisy_) {
	noisy = noisy_;
	players.push_back(player1);
	players.push_back(player2);
	sbaQueue = new StateBasedActionQueue();
	for(int i=0; i<players.size(); i++) {
		players[i]->sbaQueue = sbaQueue;
	}

    idum = new int;
    *idum = -time(0);
    for(int i=0; i<players.size(); i++) {
    	players[i]->idum = idum;
    }
	players[0]->control->myPlayer = players[0];
	players[0]->control->oppPlayer = players[1];
	players[1]->control->myPlayer = players[1];
	players[1]->control->oppPlayer = players[0];

//    Init();
}

BasicGame::~BasicGame() {
	// TODO Auto-generated destructor stub
}

void BasicGame::Init() {
	gameOver = false;
	turnNum = 0;
	if(players.empty()){
		cout << "ERROR: NO PLAYERS!" << endl;
		exit(-1);
	}
	if(players[0]->control == players[1]->control) {
		cout << "ERROR: Controllers are the same!" << endl;
		exit(-1);
	}

	PickFirst();
//	firstPlayer=0;

//	Get decks and initialize cards
	for(int i=0; i<2; i++) {
		players[i]->lib->cardVec = players[i]->control->GetDeck();
		for(int j=0; j<players[i]->lib->cardVec.size(); j++) {
			players[i]->lib->cardVec[j]->curLoc = players[i]->lib;
			players[i]->lib->cardVec[j]->thePlayer = players[i];
		}
		players[i]->Shuffle();
	}
}

void BasicGame::ResetGame() {
	for(int i=0; i<2; i++) {
		players[i]->ResetPlayer();
	}
}


bool BasicGame::FlipCoin() {
    if(RandomNum::rand3(idum)>0.5){
    	return true;
    }
    else {
    	return false;
    }
}

void BasicGame::PickFirst() {
	if(FlipCoin()) {
		firstPlayer=0;
	}
	else {
		firstPlayer=1;
	}
}

void BasicGame::PrintGameState() {
//	for(int i=0; i<6; i++) {
//		cout << players[firstPlayer]->manaMax[i] << "\t";
//	}
//	cout << endl;
//	for(int i=0; i<6; i++) {
//		cout << players[firstPlayer]->manaCur[i] << "\t";
//	}
//	cout << endl;
	cout << endl;
	if(abs(noisy)>1) {
		cout << "Turn " << turnNum/2+1 << "." << (turnNum%2)*5 << endl;
	}
	if(noisy>0) {
		players[0]->PrintGameState(true);
	}
	else if(noisy<0) {
		players[0]->PrintGameState(true, true);
	}
//	players[0]->PrintGameState(true);
	cout << "        --------------------------        " << endl;
	players[1]->PrintGameState(false);
//	if(noisy>0) {
//		players[1]->PrintGameState(false);
//	}
//	else if(noisy<0) {
//		players[1]->PrintGameState(false, true);
//	}
}




int BasicGame::PlayGame() {
	try {
		BeginGame();
		while(!gameOver) {
			Upkeep();
			if(noisy) {
				PrintGameState();
			}
			Main();
			Combat();
			Main();
			End();

			activePlayer = (activePlayer+1)%2;
			turnNum++;
			if(turnNum>200){
				cout << "Error: turn limit reached!" << endl;
				for(int j=0; j<players.size(); j++) {
					players[j]->winner=false;
				}
				gameOver=true;
			}
		}
	}
	catch(vector<bool>& winner) {
		if(winner[0]) {
			if(abs(noisy)>1) {
				cout << "Player 1 wins!" << endl;
			}
			return 0;
		}
		else if(winner[1]) {
			if(abs(noisy)>1) {
				cout << "Player 2 wins!" << endl;
			}
			return 1;
		}
		else {
			if(abs(noisy)>1) {
				cout << "Draw!" << endl;
			}
			return 2;
		}
	}
	return -1;
}


void BasicGame::BeginGame() {
//	Choose who goes first
	if(players[firstPlayer]->control->PlayFirst()) {
		activePlayer=firstPlayer;
		firstPlayer = activePlayer;
	}
	else {
		activePlayer=(firstPlayer+1)%2;
		firstPlayer = activePlayer;
	}
//	Draw initial hands
	players[activePlayer]->DrawCards(7);
	players[(activePlayer+1)%2]->DrawCards(7);
//	Mulligans
	int mullNum = 6;
	bool done [2] = {false,false};
	while ((!done[0] || !done[1]) && (mullNum>0)) {
//		cout << "Mullnum is " << mullNum << endl;
		for(int j=0; j<2; j++) {
			if(!done[(activePlayer+j)%2]) {
//				cout << "Player " << (activePlayer+j)%2+1 << " deciding to mulligan" << endl;
				if(players[(activePlayer+j)%2]->control->Mulligan(((activePlayer+j)%2)==firstPlayer)) {
					if(abs(noisy)>1) {
						cout << "Player " << (activePlayer+j)%2+1 << " is mulling to " << mullNum << endl;
					}
					for (int i=0; i<mullNum+1; i++) {
						players[(activePlayer+j)%2]->hand->cardVec.back()->MoveLoc(players[(activePlayer+j)%2]->lib);
					}
					players[(activePlayer+j)%2]->Shuffle();
					players[(activePlayer+j)%2]->DrawCards(mullNum);
				}
				else {
					done[(activePlayer+j)%2] = true;
				}
			}
		}
		mullNum--;
	}
}

void BasicGame::Upkeep() {
	if(abs(noisy)>10) {
		cout << "Entering player " << activePlayer+1 << "'s upkeep." << endl;
	}
	players[activePlayer]->landsToPlay=1;
//	This is technically the untap step
	UnsickenAll(activePlayer);
	players[activePlayer]->UntapAll();
	players[activePlayer]->ResetMana();

//	This is technically the upkeep
	while(GetNextPlay(false,activePlayer));

//	This is technically the draw step
	players[activePlayer]->DrawCards();

//	cout << "curMana = ";
//	for(int i=0; i<6; i++) {
//		cout << players[activePlayer]->curMana[i] << " ";
//	}
//	cout << endl;
}

void BasicGame::Main() {
	if(abs(noisy)>10) {
		cout << "Entering player " << activePlayer+1 << "'s main phase." << endl;
	}
	while(GetNextPlay(true,activePlayer));
}

void BasicGame::Combat() {
	if(abs(noisy)>10) {
		cout << "Entering player " << activePlayer+1 << "'s combat." << endl;
	}
//	Beginning of combat
	while(GetNextPlay(false,activePlayer));


//	Declare attackers
	vector<Card*> attackers;
	bool invalidAttackers = true;
	while(invalidAttackers) {
		invalidAttackers = false;
		attackers = players[activePlayer]->control->MakeAttacks();
		for(int i=0; i<attackers.size(); i++) {
			if(!attackers[i]->CanAttack()) {
				cout << "Not all attackers can attack! Try again!" << endl;
				invalidAttackers = true;
			}
		}
	}
	vector<Planeswalker*> targets;
	bool invalidTargets = true;
	while(invalidTargets) {
		targets = players[activePlayer]->control->AssignAttacks(attackers);
		if(targets.size()!=attackers.size()) {
			cout << "Returned the wrong number of targets! Try again!" << endl;
		}
		else {
			invalidTargets = false;
		}
	}
	for(int i=0; i<attackers.size(); i++) {
		if(abs(noisy)>1) {
			cout << attackers[i]->GetName() << " is attacking!" << endl;
		}
		attackers[i]->Attack(targets[i]);
	}

	while(GetNextPlay(false,activePlayer));


//	Declare blockers
	if(attackers.size()>0) {
		vector<Card*> blockers;
		vector<Card*> blockTargets;
		bool invalidBlockers = true;
		while(invalidBlockers) {
			invalidBlockers = false;
			blockers = players[(activePlayer+1)%2]->control->MakeBlocks(attackers);
			blockTargets = players[(activePlayer+1)%2]->control->AssignBlocks(blockers,attackers);
			for(int i=0; i<blockers.size(); i++) {
				if(!blockers[i]->CanBlock(blockTargets[i])) {
					cout << "Not all blockers can block! Try again!" << endl;
					invalidBlockers = true;
				}
			}
		}
		for(int i=0; i<blockers.size(); i++) {
			if(abs(noisy)>1) {
				cout << blockers[i]->GetName() << " is blocking " << blockTargets[i]->GetName() << "!" << endl;
			}
			blockers[i]->Block(blockTargets[i]);
		}
	}

	while(GetNextPlay(false,activePlayer));


//	Deal combat damage
	if(attackers.size()>0) {
		DealDamage();
	}
//	End of combat
	while(GetNextPlay(false,activePlayer));
}

void BasicGame::End() {
//	Technically end step
	if(abs(noisy)>10) {
		cout << "Entering player " << activePlayer+1 << "'s end step." << endl;
	}
	while(GetNextPlay(false,activePlayer));
//	Cleanup Step
	for(int i=0; i<2; i++) {
		if(players[activePlayer]->hand->cardVec.size()>7) {
			players[activePlayer]->DiscardCards(players[activePlayer]->hand->cardVec.size()-7);
		}
	}
	players[activePlayer]->ResetEOT();
	players[(activePlayer+1)%2]->ResetEOT();
}



void BasicGame::DealDamage() {
//	Get vector of attackers
	vector<Card*> activeCreatures = players[activePlayer]->GetCreatures();
	vector<Card*> inactiveCreatures = players[(activePlayer+1)%2]->GetCreatures();
	vector<Card*> attackers;
	for(int i=0; i<activeCreatures.size(); i++) {
		if(activeCreatures[i]->attacking) {
			if(abs(noisy)>3) {
				cout << activeCreatures[i]->GetName() << " deals damage!" << endl;
			}
			attackers.push_back(activeCreatures[i]);
		}
	}
	vector<Card*> blockers;
	vector<int> ordering;
	vector<int> damage;
	for(int i=0; i<attackers.size(); i++) {
		blockers.clear();
		blockers = attackers[i]->blocked;
		if(attackers[i]->vanillaCombat) {
			if(blockers.size()>0) {
				bool invalidOrder=true;
				while(invalidOrder) {
					ordering = players[activePlayer]->control->OrderBlocks(attackers[i],blockers);
					if(ordering.size()==blockers.size()) {
						invalidOrder=false;
	//					Make sure it's numbers 0 to blockers.size()-1
						for(int j=0; j<ordering.size(); j++) {
							if(find(ordering.begin(),ordering.end(),j)==ordering.end()) {
								invalidOrder=true;
							}
						}
						if(invalidOrder) {
							cout << "Need to order blockers properly! Try again!" << endl;
						}
					}
					else {
						cout << "Incorrect blocker ordering! Try again!" << endl;
					}
				}
//			Next reorder and assign damage
//		Reorder from http://stackoverflow.com/questions/838384/reorder-vector-using-a-vector-of-indices
				for ( int s = 1, d; s < ordering.size(); ++ s ) {
					for ( d = ordering[s]; d < s; d = ordering[d] ) ;
					if ( d == s ) while ( d = ordering[d], d != s ) swap(blockers[s], blockers[d] );
				}
				bool invalidDamage=true;
				bool prevDead;
				double damageTotal;
				while(invalidDamage) {
					damage = players[activePlayer]->control->AssignDamage(attackers[i],blockers);
					damageTotal=0;
					prevDead=true;
					invalidDamage=false;
					for(int j=0; j< damage.size(); j++) {
						if(damage[j]>0) {
							damageTotal+=damage[j];
							if(!prevDead) {
								cout << "Must kill first creatures before dealing damage to the rest! Try again!" << endl;
								invalidDamage=true;
							}
						}
					}
//				Make sure damage = attacker power or they killed everything and didn't assign the rest and we didn't already fail
					if((damageTotal > attackers[i]->power) || (!prevDead && (damageTotal != attackers[i]->power))) {
						cout << "Total damage is incorrect! Try again!" << endl;
						invalidDamage=true;
					}
				}
				for(int j=0; j<damage.size(); j++) {
					if(abs(noisy)>3) {
						cout << "Blocking " << blockers[j]->GetName() << " deals " << blockers[j]->power << " damage." << endl;
					}
					attackers[i]->TakeDamage(blockers[j]->power);
					if(abs(noisy)>3) {
						cout << "Attacking " << attackers[i]->GetName() << " deals " << damage[j] << " damage." << endl;
					}
					blockers[j]->TakeDamage(damage[j]);
				}
			}
			else {
//			No blockers
				if(abs(noisy)>1) {
					cout << attackers[i]->GetName() << " is unblocked!" << endl;
				}
				attackers[i]->attacking->TakeDamage(attackers[i]->power);
			}
		}
		else {
			cout << "French vanilla creatures not implemented yet!" << endl;
			exit(-1);
		}
	}
}



bool BasicGame::GetNextPlay(bool isSorc, int atPlay, bool playMade, bool hasCast) {
//	cout << "Sorcery = " << isSorc << "\tAtPlay= = " << atPlay+1 << endl;
	ApplyStateBasedActions();
	bool noValidPlay = true;
	Playable * newPlayable;
	while(noValidPlay) {
		newPlayable = players[atPlay]->control->MakePlay(isSorc);
		if(newPlayable) {
			if(newPlayable->Pay(isSorc)) {
				theStack.push_back(newPlayable);
				noValidPlay = false;
			}
		}
		else {
			theStack.push_back(newPlayable);
			noValidPlay = false;
		}
	}
	if(theStack.back()) {
//		Current player made a play
		if(theStack.back()->usesStack) {
			if(abs(noisy)>1) {
				cout << "Player " << atPlay+1 << " is casting " << static_cast<Card*>(theStack.back())->GetName() << endl;
			}
//			The Play uses the stack so continue making plays
			hasCast = GetNextPlay(false,atPlay,true,true);
		}
		else {
//			Not that this technically isn't the correct implementation of the rules but it's pretty damn close
//			Land or mana ability immediately resolves
			theStack.back()->Play();
			if(abs(noisy)>1) {
				cout << "Player " << atPlay+1 << " is playing " << static_cast<Card*>(theStack.back())->GetName() << endl;
			}
			theStack.pop_back();
			hasCast = GetNextPlay(false,atPlay,true,true);
		}
	}
	else {
//		Current player has no play (MakePlay returned NULL)
		theStack.pop_back();
		if(!playMade) {
//			The previous player passed priority already so resolve the top Playable
			if(theStack.size()==0) {
//				Done with plays for now
				return hasCast;
			}
			else {
//			*** This is where spells actually resolve ***
//				Play the top spell on the stack
				theStack.back()->Play();
				if(abs(noisy)>1) {
					cout << static_cast<Card*>(theStack.back())->GetName() << " resolves."<< endl;
//					cout << "manaCur = "<< players[atPlay]->manaCur[4] << " " << players[atPlay]->manaCur[5] << endl;
				}
				theStack.pop_back();
				hasCast = GetNextPlay(false,activePlayer, true, true);
			}
		}
		else {
//			Pass priority to other player
			hasCast = GetNextPlay(false,(atPlay+1)%2,false,hasCast);
		}
	}
	return hasCast;
}

void BasicGame::ApplyStateBasedActions() {

//	for(int i=0; i<players.size(); i++) {
//		if(players[i]->lifeTotal <= 0) {
//			players[i]->winner = false;
//			gameOver = true;
//		}
//	}
	if(!sbaQueue->IsEmpty()) {
		vector<StateBasedAction*> sbaVec;
		sbaVec = sbaQueue->AccessQueue();
		for(int i=0; i<sbaVec.size(); i++) {
			if(sbaVec[i]->Check()) {
				sbaVec[i]->Act();
				if(abs(noisy)>1) {
					sbaVec[i]->Print();
				}
			}
			delete sbaVec[i];
		}
		sbaQueue->ResetQueue();
	}

//	Check if someone lost
	for(int i=0; i<players.size(); i++) {
		if(!players[i]->winner) {
			gameOver = true;
		}
	}
	if(gameOver) {
		if(abs(noisy)) {
			cout << "Gameover!" << endl;
		}
		vector<bool> winner;
		winner.push_back(players[0]->winner);
		winner.push_back(players[1]->winner);
		throw winner;
	}
}

void BasicGame::UnsickenAll(int atPlay) {
	for(int i=0; i<players[atPlay]->bf->cardVec.size(); i++) {
		if(players[atPlay]->bf->cardVec[i]->isCreature) {
			players[atPlay]->bf->cardVec[i]->summoningSick = false;
		}
	}
}

