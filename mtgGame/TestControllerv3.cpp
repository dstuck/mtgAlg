/*
 * TestControllerv3.cpp
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#include "headers/TestControllerv3.h"

TestControllerv3::TestControllerv3() {
    cout << "Need to set everything yourself!" << endl;
}

TestControllerv3::TestControllerv3(double* valueVec_) {
    valueVec = valueVec_;
    nameToIndex = CardSelector::NameToCardIndex();
    totalCards = CardList::size;
    //debugPrint = 0;
// debugPrint 2=all blocks,attacks; 3=all vals
    debugPrint = 4;
}


TestControllerv3::~TestControllerv3() {
}

vector<Card*> TestControllerv3::GetDeck() {
//	return DeckList::FrenchVanillaBlue();
    return DeckList::VanillaGreen();
}

Playable * TestControllerv3::MakePlay(bool isSorc) {
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

vector<Card*> TestControllerv3::MakeAttacks() {
    double value;
    int recur=1;
    return ProposeAttacks(myPlayer,oppPlayer,value, recur);
//	return ProposeAttacks(myPlayer,oppPlayer,value, recur, true);
}

vector<Card*> TestControllerv3::ProposeAttacks(Player* attackPlayer, Player* blockPlayer, double &value, int recur, bool needVal) {
//	TODO: Consider the number of states that must be calculated and if too large consider no attacks, all attacks and then
//		remove creatures that die, and repeat.
    vector<Card*> attacking;
    vector<Card*> potAttacks;
    vector<Card*> potBlocks;
    potAttacks = GetPotentialAttackers(attackPlayer);
    potBlocks = GetPotentialBlockers(blockPlayer);
//	for(int i=0; i<potAttacks.size(); i++) {
//		if(potAttacks[i]->CanAttack()) {
//			attacking.push_back(potAttacks[i]);
//		}
//	}
    if(potAttacks.size() == 0 && !needVal) {
        return attacking;
    }
    vector<bool> isAttacking;
    for(int i=0; i<potAttacks.size(); i++) {
        isAttacking.push_back(false);
    }
    vector<bool> bestAttacks;
    double* attackBoard = new double[CardList::size];
    double* blockBoard = new double[CardList::size];
    GetBoardVec(attackPlayer,attackBoard);
    GetBoardVec(blockPlayer,blockBoard);
    double bestVal = -0.1;

    int attackThresh = 0;
//  Run efficient code if predicted calcs greater than attackThresh
//  DES TODO: Maybe don't calculate this if you don't want to use it...
//  DES TODO: Also, doesn't include crackback...
    int numCalcs = pow(2,potAttacks.size())*pow((potAttacks.size()+1),potBlocks.size());
//****************************************
//  Efficient attack code!
//****************************************
//  Want to test all attackers on their own, alpha strike, no attacks, and combinations of single attacks with positive outcomes

//	cout << "NumCalcs = " << numCalcs << endl;
    if(numCalcs < attackThresh) {
//      Test all possible combinations of attacks
        GenerateAttacks(isAttacking,0,potAttacks.size(),bestVal, &bestAttacks, attackBoard, blockBoard, potAttacks, attackPlayer, blockPlayer, recur);
    }
    else {
        double noneVal;
        vector<double> singleVal;
        vector<Card*> attackers;
//  Get the value for no attacks
        for(int i=0; i<isAttacking.size(); i++) {
            if(isAttacking[i]) {
                attackers.push_back(potAttacks[i]);
            }
        }
        ProposeBlocks(attackers,blockPlayer,attackPlayer,value,recur,true);
        value = 1-value;
        noneVal = value;
        if(value>=bestVal) {
            bestVal = value;
            bestAttacks = isAttacking;
        }
//  Get value for all single attacks
        for(int n=0; n<potAttacks.size(); n++) {
            isAttacking[n]=true;
            attackers.clear();
            for(int i=0; i<potAttacks.size(); i++) {
                if(isAttacking[i]) {
                    attackers.push_back(potAttacks[i]);
                }
            }
            ProposeBlocks(attackers,blockPlayer,attackPlayer,value,recur,true);
            value = 1-value;
            singleVal.push_back(value);
            if(value>bestVal) {
                bestVal = value;
                bestAttacks = isAttacking;
            }
            isAttacking[n]=false;
        }
//  Consider all attackers with neutral or better value
        attackers.clear();
        for(int i=0; i<potAttacks.size(); i++) {
            if(singleVal[i]>=noneVal) {
                isAttacking[i] = true;
                attackers.push_back(potAttacks[i]);
            }
        }
         if(debugPrint>1) {
            cout << "Recur = " << recur << endl;
            cout << "Attacks: ";
            for(int i=0; i<attackers.size(); i++) {
                cout << attackers[i]->GetName() << " ";
            }
            cout << endl;
         }
        ProposeBlocks(attackers,blockPlayer,attackPlayer,value,recur,true);
        value = 1-value;
        if(value>bestVal) {
            bestVal = value;
            bestAttacks = isAttacking;
        }
//  Consider alpha strike
        attackers.clear();
        for(int i=0; i<potAttacks.size(); i++) {
            isAttacking[i] = true;
            attackers.push_back(potAttacks[i]);
        }
        ProposeBlocks(attackers,blockPlayer,attackPlayer,value,recur,true);
        value = 1-value;
        if(value>bestVal) {
            bestVal = value;
            bestAttacks = isAttacking;
        }

//  Test vs full results
//        if(recur==1) {
//            vector<bool> tempBestAttacks;
//            double tempBestVal = -0.1;
//            vector<bool> tempIsAttacking;
//            for(int i=0; i<potAttacks.size(); i++) {
//                tempIsAttacking.push_back(false);
//            }
//            GenerateAttacks(tempIsAttacking,0,potAttacks.size(),tempBestVal, &tempBestAttacks, attackBoard, blockBoard, potAttacks, attackPlayer, blockPlayer, recur);
//            if(bestVal!=tempBestVal) {
//                cout << "Bad approximation:\t" << tempBestVal << " != " << bestVal << endl;
//                cout << "Full Attacks: ";
//                for(int i=0; i<tempIsAttacking.size(); i++) {
//                    cout << tempIsAttacking[i] << " ";
//                }
//                cout << endl;
//                cout << "Approx Attacks: ";
//                for(int i=0; i<isAttacking.size(); i++) {
//                    cout << isAttacking[i] << " ";
//                }
//                cout << endl;
//            }
//        }
//****************************************
//  End of more efficient propose attacks   
//****************************************
    }


    for(int i=0; i<bestAttacks.size(); i++) {
        if(bestAttacks[i]) {
            attacking.push_back(potAttacks[i]);
        }
    }
    value = bestVal;
    delete attackBoard;
    delete blockBoard;
    return attacking;
}

double TestControllerv3::GenerateAttacks(vector<bool> isAttacking, int beg, int end, double& bestVal, vector<bool>* bestAttacks, double* attackState, double* blockState, vector<Card*> potAttacks, Player* attackPlayer, Player* blockPlayer, int recur) {
    if(beg!=end) {
        for(int i=0; i<2; i++) {
            if(i==1) {
                isAttacking[beg] = true;
            }
            double val = 0;
            val = GenerateAttacks(isAttacking,beg+1,end,bestVal,bestAttacks,attackState,blockState,potAttacks,attackPlayer,blockPlayer,recur);
//			cout << "val = " << val << endl;
            if(val>=bestVal) {
//				cout << val << " > " << bestVal << endl;
                bestVal = val;
                *bestAttacks = isAttacking;
            }
            else if(val==bestVal) {
//			Break ties by having the most creatures attack
                int newAtt=0;
                int oldAtt=0;
                for(int k=0; k<isAttacking.size(); k++) {
                    if(isAttacking[k]) {
                        newAtt++;
                    }
                    if(bestAttacks[0][k]) {
                        oldAtt++;
                    }
                }
                if(newAtt>oldAtt) {
                    bestVal = val;
                    *bestAttacks = isAttacking;
                }
            }
        }
        return 0.;
    }
    else {
//        if(recur==1) {
//            cout << "isAttacking: ";
//            for(int i=0; i<isAttacking.size(); i++) {
//                cout << isAttacking[i] << " ";
//            }
//            cout << endl;
//        }
//        else {
//            cout << "propAttack: ";
//            for(int i=0; i<isAttacking.size(); i++) {
//                cout << isAttacking[i] << " ";
//            }
//            cout << endl;
//        }
        double value;
        vector<Card*> attackers;
        for(int i=0; i<isAttacking.size(); i++) {
            if(isAttacking[i]) {
                attackers.push_back(potAttacks[i]);
            }
        }
        ProposeBlocks(attackers,blockPlayer,attackPlayer,value,recur,true);
        value = 1-value;

//        if(recur==1) {
//		    cout << "Attack Value = " << value << endl;
//        }
//        else {
//		    cout << "Prop attack Value = " << value << endl;
//        }
        if(bestVal==-0.1) {
//			cout << val << " > " << bestVal << endl;
            bestVal = value;
            *bestAttacks = isAttacking;
        }
        return value;
    }
}

vector<Planeswalker*> TestControllerv3::AssignAttacks(vector<Card*> attackers) {
    vector<Planeswalker*> targets;
    for(int i=0; i<attackers.size(); i++) {
        targets.push_back(oppPlayer);
    }
    return targets;
}

vector<Card*> TestControllerv3::MakeBlocks(vector<Card*> targets) {
    double value;
    int recur = 1;
    return ProposeBlocks(targets,myPlayer,oppPlayer,value,recur,false);
}

vector<Card*> TestControllerv3::ProposeBlocks(vector<Card*> targets, Player* blockPlayer, Player* attackPlayer, double& blockVal, int recur, bool needVal) {
    vector<Card*> willBlock;
//	No one is attacking!
//	cout << "no attacks = " << (targets.size()==0) << endl;
    if(targets.size()==0 && !needVal) {
        return willBlock;
    }
//  Add a pointer to targets for not blocking
    targets.push_back(NULL);
    vector<Card*> potBlocks = GetPotentialBlockers(blockPlayer);
//  Run efficient code if predicted calcs greater than blockThresh
//  DES TODO: Maybe don't calculate this if you don't want to use it...
//  DES TODO: Also, doesn't include crackback...
    int blockThresh = 0;
    //int numCalcs = pow(targets.size(),potBlocks.size());
    int numCalcs = 1;

//	cout << "Left to block: " << endl;
//	for(int i=0; i<potBlocks.size(); i++) {
//		cout << potBlocks[i]->GetName() << endl;
//	}

//	No creatures can block!
//	cout << "no blocks = " << (potBlocks.size()==0) << endl;
    if(potBlocks.size()==0 && !needVal) {
        blockVal=-1;
        return willBlock;
    }
//  DES Note: blocks[i][j] says that blocker j is blocking attacker i (or not blocking if i is last value)
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
//	cout << "no attackers? " << (targets.size()==1) << endl;
//	cout << "no blockers? " << (potBlocks.size()==0) << endl;
//  No decisions to make
    if(targets.size()==1 || potBlocks.size()==0) {
//		cout << "No blockers or attackers" << endl;
        double* blockBoardTemp = new double[totalCards];
        double* attackBoardTemp = new double[totalCards];
        memcpy(blockBoardTemp,blockBoard,totalCards*sizeof(double));
        memcpy(attackBoardTemp,attackBoard,totalCards*sizeof(double));
        int damage=0;
        for(int j=0; j<targets.size()-1; j++) {
            damage += targets[j]->GetPower();
        }
        if(recur>0) {
            targets.pop_back();
            PredictCrackback(blockPlayer,attackPlayer,blockBoardTemp,attackBoardTemp,targets,damage,blockVal,recur);
            targets.push_back(NULL);
//        	blockVal = 1-blockVal;
        }
        else {
            blockVal = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-damage,attackPlayer->lifeTotal);
        }
        delete blockBoardTemp;
        delete attackBoardTemp;
//		cout<< "No decisions. Final block val = " << blockVal << endl;
    }
//  Recursively decide on blocks
    else if(numCalcs<blockThresh) {
        double bestVal = -0.1;
        GenerateBlocks(blocks,0,potBlocks.size(),bestVal, &bestBlocks, blockBoard, attackBoard,targets, potBlocks, blockPlayer, attackPlayer, recur);
//		cout << "bestBlocks:\t" << bestVal << endl;
//		for(int ii=0; ii<bestBlocks.size(); ii++) {
//			for(int j=0; j<bestBlocks[ii].size(); j++) {
//				cout << bestBlocks[ii][j] << " ";
//			}
//			cout << endl;
//		}
        blockVal = bestVal;
        blockAssignment.clear();
        willBlock.clear();
        for(int i=0; i<bestBlocks.size()-1; i++) {
            for(int j=0; j<bestBlocks[i].size(); j++) {
                willBlock.push_back(potBlocks[bestBlocks[i][j]]);
                blockAssignment.push_back(targets[i]);
            }
        }
    }
    else {
      //recur=0;
        //cout << "DES Temp: I shouldn't be in here yet!" << endl;
//****************************************
//  Efficient block code!
//****************************************

//  For each attacker, consider blocks

//  No blocks
        double noneVal;
        double* blockBoardTemp = new double[totalCards];
        double* attackBoardTemp = new double[totalCards];
        memcpy(blockBoardTemp,blockBoard,totalCards*sizeof(double));
        memcpy(attackBoardTemp,attackBoard,totalCards*sizeof(double));
        int* damage = new int(0);
        for(int i=0; i<targets.size()-1; i++) {
            vector<Card*> theBlockers;
            PredictDamage(targets[i],theBlockers,attackBoardTemp,blockBoardTemp,damage);
        }
        if(blockPlayer->lifeTotal-*damage <= 0) {
            noneVal = blockPlayer->lifeTotal-*damage;
        }
        else if(recur>0) {
            targets.pop_back();
            PredictCrackback(blockPlayer,attackPlayer,blockBoardTemp,attackBoardTemp,targets,*damage,noneVal,recur);
            targets.push_back(NULL);
        }
        else  {
            noneVal = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-*damage,attackPlayer->lifeTotal);
        }
        if(debugPrint>2) {
            cout << recur << "\tNo block val = " << noneVal << endl;
        } 

//  Now consider single and double blocks for each single creature and find best value w/ least blockers
//      DES: TODO: More efficient implementation of valDoubleBlock
//      DES: TODO: Consider memory requirements of this implementation
//      valDoubleBlock[n][i][j] is the value from i and j blocking n
        vector< vector< vector<double> > > valDoubleBlock;
        vector< vector<double> > nVal;
        vector<double> baVal;
        //cout << "DES: num targets = " << targets.size()-1 << endl;
        for(int n=0; n<targets.size()-1; n++) {
            nVal.clear();
            // For first blocker
            for(int ba=0; ba<potBlocks.size(); ba++) {
                baVal.clear();
                // For second blocker (ba=bb corresponds to single blocks)
                for(int bb=ba; bb<potBlocks.size(); bb++) {
// Attacker n is being blocked by ba and bb (or none if bb=potBlocks.size())
                    bool validBlocks = potBlocks[ba]->CanBlock(targets[n]) && potBlocks[bb]->CanBlock(targets[n]);
                    if(!validBlocks) {
                        //cout << "Error: Invalid Blocks! We have a problem!" << endl;
                        baVal.push_back(-999.0);
                    }
                    else {
                        double val;
                        double* blockBoardTemp = new double[totalCards];
                        double* attackBoardTemp = new double[totalCards];
                        memcpy(blockBoardTemp,blockBoard,totalCards*sizeof(double));
                        memcpy(attackBoardTemp,attackBoard,totalCards*sizeof(double));
                        if(debugPrint>4) {
                           cout << "DES Temp: attackBoardTemp" << endl;
                           for(int t=0; t< totalCards; t++) {
                              cout << attackBoardTemp[t];
                           }
                           cout << endl;
                        }
                        int* damage = new int(0);
                        vector<Card*> theBlockers;
                        theBlockers.push_back(potBlocks[ba]);
                        if(ba!=bb) {
                            theBlockers.push_back(potBlocks[bb]);
                        }
                        vector<int> ordering;
                        double junk;
                        ordering = ProposeBlockOrder(targets[n],theBlockers,blockPlayer,attackPlayer,junk);
                        for ( int s = 1, d; s < ordering.size(); ++ s ) {
                            for ( d = ordering[s]; d < s; d = ordering[d] ) ;
                            if ( d == s ) while ( d = ordering[d], d != s ) swap(theBlockers[s], theBlockers[d] );
                        }
                        PredictDamage(targets[n],theBlockers,attackBoardTemp,blockBoardTemp,damage);
                        for(int nn=0; nn<targets.size()-1; nn++) {
                           if(nn!=n) {
                              *damage += targets[nn]->power;
                           }
                        }
                        if(recur>0) {
                            targets.pop_back();
                            if(debugPrint>1) {
                              cout << recur << "\tPredict crackback after blocking " << n << " with " << ba <<  " and " << bb << endl;
                            }
                            PredictCrackback(blockPlayer,attackPlayer,blockBoardTemp,attackBoardTemp,targets,*damage,val,recur);
                            targets.push_back(NULL);
                        }
                        else {
                           if(debugPrint==2) {
                              cout << recur << "\tBlocking " << n << " with " << ba <<  " and " << bb << endl;
                           }
                            val = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-*damage,attackPlayer->lifeTotal);
                        }
                        if(blockPlayer->lifeTotal-*damage<0) {
                           val = blockPlayer->lifeTotal-*damage;
                        }
                        if(debugPrint>2) {
                           cout << recur << "\tBlocking " << n << " with " << ba <<  " and " << bb << "\t\tval = " << val <<  endl;
                        }
                        //cout << n << " is blocked by " << ba << " and " << bb << endl;
                        //cout << "DES Temp: val = " << val << endl;
                        baVal.push_back(val);
                    }
                  //baVal is of length potBlocks.size()-ba
                }
                nVal.push_back(baVal);
            }
            valDoubleBlock.push_back(nVal);
//       valDoubleBlock[n][ba][bb] now contains the value for ba and bb blocking n
        }
// DES Notes:  How to pick out best blocks. first, pick largest val (bigger than noneVal) in valDoubleBlock and remove valDoubleBlock[n][bapicked/bbpicked] repeat
//             Store baPicked and bbPicked need to keep track for shifting size of valDoubleBlock
      int baPicked, bbPicked, nPicked;
      bool stillPicking = true;
      double maxVal;
      vector<int> blank;
      for(int i=0; i<targets.size(); i++) {
         bestBlocks.push_back(blank);
      }
      vector<bool> isBlocking;
      for(int i=0; i<potBlocks.size(); i++) {
         isBlocking.push_back(false);
      }
// DES TODO: This is super inefficient in it's current state
      while(stillPicking) {
//       Find best set of blocks
         //maxVal=max(noneVal,0.0);
         maxVal=noneVal;
         //cout << "noneVal = " << maxVal << endl;
         for(int n=0; n<valDoubleBlock.size(); n++) {
//          Check single blocks first
            for(int ba=0; ba<valDoubleBlock[n].size(); ba++) {
                  if(valDoubleBlock[n][ba][ba]>maxVal) {
                     nPicked = n;
                     baPicked = ba;
                     bbPicked = ba;
                     maxVal = valDoubleBlock[n][ba][0];
                  }
            }
            for(int ba=0; ba<valDoubleBlock[n].size(); ba++) {
               for(int bb=1; bb<valDoubleBlock[n][ba].size(); bb++) {
                  if(valDoubleBlock[n][ba][bb]>maxVal) {
                     nPicked = n;
                     baPicked = ba;
                     bbPicked = bb+ba;
                     maxVal = valDoubleBlock[n][ba][bb];
                  }
                  //cout << "valDoubleBlock["<<n<<"]["<<ba<<"]["<<bb+ba<<"] = " << valDoubleBlock[n][ba][bb] << endl;;
               }
            }
         }
         if(maxVal > noneVal) {
            bestBlocks[nPicked].push_back(baPicked);
            isBlocking[baPicked]=true;
//          Remove nPicked
            for(int ba=0; ba<valDoubleBlock[nPicked].size(); ba++) {
               for(int bb=0; bb<valDoubleBlock[nPicked][ba].size(); bb++) {
                  valDoubleBlock[nPicked][ba][bb] = -999.0;
               }
            }
//          Remove baPicked
            for(int n=0; n<valDoubleBlock.size(); n++) {
               for(int ba=0; ba<baPicked; ba++) {
                  valDoubleBlock[n][ba][baPicked] = -999.0;
               }
               for(int ba=baPicked; ba<valDoubleBlock[n][baPicked].size(); ba++) {
                  valDoubleBlock[n][baPicked][ba] = -999.0;
               }
            }

            if(baPicked!=bbPicked) {
               bestBlocks[nPicked].push_back(bbPicked);
               isBlocking[bbPicked]=true;
//          Remove bbPicked
               for(int n=0; n<valDoubleBlock.size(); n++) {
                  for(int bb=0; bb<bbPicked; bb++) {
                     valDoubleBlock[n][bb][bbPicked] = -999.0;
                  }
                  for(int bb=bbPicked; bb<valDoubleBlock[n][bbPicked].size(); bb++) {
                     valDoubleBlock[n][bbPicked][bb] = -999.0;
                  }
               }
            }
            //cout << "DES Temp: after deleting valDoubleBlock[3][1][1] = " << valDoubleBlock[3][1][0] << endl;
         }
         else {
            stillPicking=false;
         }
      }
      for(int i=0; i<isBlocking.size(); i++) {
         if(!isBlocking[i]) {
            bestBlocks[bestBlocks.size()-1].push_back(i);
         }
      }
      if(needVal) {
        //double val;
        double* blockBoardTemp = new double[totalCards];
        double* attackBoardTemp = new double[totalCards];
        memcpy(blockBoardTemp,blockBoard,totalCards*sizeof(double));
        memcpy(attackBoardTemp,attackBoard,totalCards*sizeof(double));
        int* damage = new int(0);
        for(int i=0; i<bestBlocks.size()-1; i++) {
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
//	cout << targets[i]->name << " is blocked by ";
//	for(int ii=0; ii< theBlockers.size(); ii++) {
//		cout << theBlockers[ii]->name << " ";
//	}
//	cout << endl;
            PredictDamage(targets[i],theBlockers,attackBoardTemp,blockBoardTemp,damage);
//			cout << "Damage = " << *damage << endl;
        }
//		If recur we want to generate new Players based on boardTemps and account for crack back
        if(recur>0&&(blockPlayer->lifeTotal-*damage>0)) {
            targets.pop_back();
            PredictCrackback(blockPlayer,attackPlayer,blockBoardTemp,attackBoardTemp,targets,*damage,blockVal,recur);
            targets.push_back(NULL);
        }
        else {
            blockVal = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-*damage,attackPlayer->lifeTotal);
        }
      }
      if(debugPrint > 1) {
      //if(recur==1) {
         cout << "recur = " << recur << endl;
         cout << "DES Temp: bestBlocks = " << blockVal << endl;
         //cout << "best block is size " << bestBlocks.size() << endl;
         for(int ii=0; ii<bestBlocks.size(); ii++) {
            for(int j=0; j<bestBlocks[ii].size(); j++) {
               //cout << "best blocks "<< ii <<"  is size " << bestBlocks[ii].size() << endl;
               cout << bestBlocks[ii][j] << " ";
            }
            cout << endl;
         }
      //}
      }
      blockAssignment.clear();
     for(int i=0; i<bestBlocks.size()-1; i++) {
         for(int j=0; j<bestBlocks[i].size(); j++) {
            willBlock.push_back(potBlocks[bestBlocks[i][j]]);
            blockAssignment.push_back(targets[i]);
         }
      }
//****************************************
//  End of efficient block code!
//****************************************
    }
//	cout << "Block Value = " << blockVal << endl;
    delete blockBoard;
    delete attackBoard;
    return willBlock;
}

double TestControllerv3::GenerateBlocks(vector<vector<int> > blocks, int beg, int end, double &bestVal, vector<vector<int> >* bestBlocks, double* blockState, double* attackState, vector<Card*> targets, vector<Card*> potBlocks, Player* blockPlayer, Player* attackPlayer, int recur) {
    if(beg!=end) {
        double val = 0;
        for(int i=0; i<targets.size(); i++) {
            blocks[i].push_back(beg);
            val = GenerateBlocks(blocks,beg+1,end,bestVal,bestBlocks,blockState,attackState,targets,potBlocks,blockPlayer,attackPlayer,recur);
            if(val>bestVal) {
		cout << val << " > " << bestVal << endl;
                bestVal = val;
                *bestBlocks = blocks;
		cout << "bestBlocks" << endl;
		for(int ii=0; ii<blocks.size(); ii++) {
			for(int j=0; j<blocks[ii].size(); j++) {
				cout << blocks[ii][j] << " ";
			}
			cout << endl;
		}

            }
            blocks[i].pop_back();
        }
        return -2.0;
    }
    else {
//        if(recur==1) {
//            cout << "blocks:" << endl;
//            for(int ii=0; ii<blocks.size(); ii++) {
//                for(int j=0; j<blocks[ii].size(); j++) {
//                    cout << blocks[ii][j] << " ";
//                }
//                cout << endl;
//            }
//        }
        bool validBlocks = true;
        for(int i=0; i<blocks.size()-1; i++) {
            for(int j=0; j<blocks[i].size(); j++) {
                validBlocks = validBlocks && potBlocks[blocks[i][j]]->CanBlock(targets[i]);
            }
        }
        if(!validBlocks) {
//  DES: This is not an error simply a confirmation that this subset of blocks is invalid
            //cout << "Error: Invalid Blocks! We have a problem!" << endl;
            return -1.0;
        }
        double val;
        double* blockBoardTemp = new double[totalCards];
        double* attackBoardTemp = new double[totalCards];
        memcpy(blockBoardTemp,blockState,totalCards*sizeof(double));
        memcpy(attackBoardTemp,attackState,totalCards*sizeof(double));
        int* damage = new int(0);
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
//		If recur we want to generate new Players based on boardTemps and account for crack back
        if(recur>0&&(blockPlayer->lifeTotal-*damage>0)) {
            targets.pop_back();
            PredictCrackback(blockPlayer,attackPlayer,blockBoardTemp,attackBoardTemp,targets,*damage,val,recur);
            targets.push_back(NULL);
        }
        else {
            val = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-*damage,attackPlayer->lifeTotal);
        }
//        if(recur==1) {
//    		cout<< "Block value = " << val << endl;
//        }
//        else {
//    		cout<< "Prop block value = " << val << endl;
//        }
        delete blockBoardTemp;
        delete attackBoardTemp;
        delete damage;
        return val;
    }
}

//	Returns value for blocking player assuming they all out attack next turn
void TestControllerv3::PredictCrackback(Player* blockPlayer,Player* attackPlayer,double* blockBoardTemp,double* attackBoardTemp,vector<Card*> attackers,int damage,double& val,int recur) {
//	cout << "Predicting Crackback" << endl;
    if((blockPlayer->lifeTotal-damage)<=0) {
//		cout << "Already dead!" << endl;
        val = 0.0;
        return;
    }
    int* tappedAttacks = new int[totalCards];
    for(int k=0; k<totalCards; k++) {
        tappedAttacks[k] = 0;
    }
//    Block player will untap all before the crackback
    Player* possibleBlockPlayer = BoardToPlayer(blockBoardTemp, tappedAttacks, blockPlayer->lifeTotal-damage);
    for(int i=0; i<attackPlayer->bf->cardVec.size(); i++) {
        if(find(attackers.begin(),attackers.end(), attackPlayer->bf->cardVec[i])==attackers.end()) {
//	 If the card is not attacking add it to tappedAttacks (which currently represents untapped attacks)
            tappedAttacks[nameToIndex[attackPlayer->bf->cardVec[i]->GetName()]]++;
//	    cout << "Untapped " << attackPlayer->bf->cardVec[i]->GetName() << endl;
        }
    }
//		Now convert from untapped creatures to remaining tapped creatures
    for(int k=0; k<totalCards; k++) {
        tappedAttacks[k] = attackBoardTemp[k] - tappedAttacks[k];
    }
    Player* possibleAttackPlayer = BoardToPlayer(attackBoardTemp, tappedAttacks, attackPlayer->lifeTotal);

//	vector<Card*> potAttacks = GetPotentialAttackers(possibleBlockPlayer);
//	cout << "Crackback is: " << endl;
//	for(int i=0; i<possibleBlockPlayer->bf->cardVec.size(); i++) {
//		cout << possibleBlockPlayer->bf->cardVec[i]->GetName() << endl;
//	}
//	vector<Card*> potBlocks = GetPotentialBlockers(possibleAttackPlayer);
//	cout << "Left to block: " << endl;
//	for(int i=0; i<potBlocks.size(); i++) {
//		cout << potBlocks[i]->GetName() << endl;
//	}
//	cout << "bf tapped?: " << endl;
//	for(int i=0; i<possibleAttackPlayer->bf->cardVec.size(); i++) {
//		cout << possibleAttackPlayer->bf->cardVec[i]->GetName() << " " << possibleAttackPlayer->bf->cardVec[i]->tapped << endl;
//	}
//	For a attackers and b blockers must assess 2^a*(a+1)^b board states.
    vector<Card*> pAttack = GetPotentialAttackers(possibleBlockPlayer);
    vector<Card*> pBlock = GetPotentialBlockers(possibleAttackPlayer);
    ProposeAttacks(possibleBlockPlayer,possibleAttackPlayer,val,0,true);
    /*  DES: want these thresh values set by propose attacks and blocks rather than here...
        int attackThresh = 20000;
        int recurThresh = 100000;
        int numCalcs = pow(2,pAttack.size())*pow((pAttack.size()+1),pBlock.size());
//	cout << "NumCalcs = " << numCalcs << endl;
    if(numCalcs < attackThresh) {
    ProposeAttacks(possibleBlockPlayer,possibleAttackPlayer,val,0,true);
    }
    else if(pow((pAttack.size()+1),pBlock.size()) < recurThresh) {
//		cout << "Only predicting blocks!" << endl;
    ProposeBlocks(GetPotentialAttackers(possibleBlockPlayer),possibleAttackPlayer,possibleBlockPlayer,val,0,true);
//			Convert from attack player value to block player value
    val = 1-val;
    }
    else {
//		cout << "No recur!" << endl;
    val = AssessGameState(blockBoardTemp,attackBoardTemp,blockPlayer->lifeTotal-damage,attackPlayer->lifeTotal);
    }
     */
    delete tappedAttacks;
    delete possibleBlockPlayer;
    delete possibleAttackPlayer;
}

vector<Card*> TestControllerv3::AssignBlocks(vector<Card*> blockers, vector<Card*> attackers) {
    vector<Card*> blocked;
//	for(int i=0; i<blockers.size(); i++) {
//		blocked.push_back(attackers[i%attackers.size()]);
//	}
// blockAssignment must be set earlier during MakeBlocks
    if(blockAssignment.size()!=0) {
        blocked = blockAssignment;
        blockAssignment.clear();
    }
    return blocked;
}

vector<int> TestControllerv3::OrderBlocks(Card* attacker, vector<Card*> blockers) {
    double value;
    return ProposeBlockOrder(attacker, blockers, myPlayer, oppPlayer, value);
}

vector<int> TestControllerv3::ProposeBlockOrder(Card* attacker, vector<Card*> blockers, Player* blockPlayer, Player* attackPlayer, double &value) {
    vector<int> ordering;
//	First, add unkillables to end of list
    int blockersLeft = blockers.size();
    vector<int> remaining;
    for(int i=0; i<blockers.size(); i++) {
        if((blockers[i],attacker)) {
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

double TestControllerv3::PermuteBlocks(vector<int> ordering, int beg, int end, double &bestVal, vector<int>* bestOrdering, vector<int> totalOrdering,vector<int> remaining, double* blockState, double* oppState, Card* attacker, vector<Card*> blockers, Player* blockPlayer, Player* attackPlayer) {
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
        int damage = 0;
        PredictDamage(attacker,blockers,blockBoardTemp,attackBoardTemp, &damage);
        double value = AssessGameState(blockBoardTemp,attackBoardTemp, blockPlayer->lifeTotal,attackPlayer->lifeTotal);
        delete blockBoardTemp;
        delete attackBoardTemp;
        return value;
    }
}

vector<int> TestControllerv3::AssignDamage(Card* attacker,vector<Card*> blockers) {
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

bool TestControllerv3::PredictDamage(Card* attacker, vector<Card*> blockers, double* attackState, double* blockState, int* damage) {
    bool creatureDead = false;
    int damageLeft = attacker->power;
    int blockerDamage = 0;
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

vector<Card*> TestControllerv3::ChooseDiscards(int nDiscard) {
    vector<Card*> discards;
    if(nDiscard >= myPlayer->hand->cardVec.size()) {
        for(int i=0; i< myPlayer->hand->cardVec.size(); i++) {
            discards.push_back(myPlayer->hand->cardVec[i]);
        }
        return discards;
    }
    vector<Card*> landsDown = LandsOnTable(myPlayer);
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

vector<Card*> TestControllerv3::LandsInHand() {
    vector<Card*> landHand;
    for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
        if(myPlayer->hand->cardVec[i]->isLand) {
            landHand.push_back(myPlayer->hand->cardVec[i]);
        }
    }
    return landHand;
}

vector<Card*> TestControllerv3::LandsOnTable(Player* thePlayer) {
    vector<Card*> landsPlayed;
    for(int i=0; i<thePlayer->bf->cardVec.size(); i++) {
        if(thePlayer->bf->cardVec[i]->isLand) {
            landsPlayed.push_back(thePlayer->bf->cardVec[i]);
        }
    }
    return landsPlayed;
}

vector<Card*> TestControllerv3::NonLandsInHand() {
    vector<Card*> nonLandHand;
    for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
        if(!myPlayer->hand->cardVec[i]->isLand) {
            nonLandHand.push_back(myPlayer->hand->cardVec[i]);
        }
    }
    return nonLandHand;
}

vector<Card*> TestControllerv3::CastableCreatures() {
    vector<Card*> creatureHand;
    for(int i=0; i<myPlayer->hand->cardVec.size(); i++) {
        if(myPlayer->hand->cardVec[i]->isCreature && myPlayer->HasMana(myPlayer->hand->cardVec[i]->mana)) {
            creatureHand.push_back(myPlayer->hand->cardVec[i]);
        }
    }
    return creatureHand;
}
vector<Card*> TestControllerv3::GetPotentialAttackers(Player* thePlayer) {
    vector<Card*> attackables;
    for(int i=0; i<thePlayer->bf->cardVec.size(); i++) {
        if(thePlayer->bf->cardVec[i]->CanAttack()) {
            attackables.push_back(thePlayer->bf->cardVec[i]);
        }
    }
    return attackables;
}

vector<Card*> TestControllerv3::GetPotentialBlockers(Player* thePlayer) {
    vector<Card*> potBlocks;
    for(int i=0; i<thePlayer->bf->cardVec.size(); i++) {
        if(!thePlayer->bf->cardVec[i]->tapped && thePlayer->bf->cardVec[i]->isCreature){
            potBlocks.push_back(thePlayer->bf->cardVec[i]);
        }
    }
    return potBlocks;
}

double* TestControllerv3::GetBoardVec(Player* thePlayer, double* boardVec) {
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

Player* TestControllerv3::BoardToPlayer(double* seedBoardState, int* tappedVec, int seedLife) {
    Player * newPlayer = new Player();
    newPlayer->lifeTotal = seedLife;
    for(int i=0; i<totalCards; i++) {
        for(int j=0; j<seedBoardState[i]; j++) {
            Card* newCard = CardSelector::NewCard(CardList::cardName(i));
            newPlayer->bf->cardVec.push_back(newCard);
            newCard->curLoc = newPlayer->bf;
            newCard->thePlayer = newPlayer;
            newCard->summoningSick = false;
//			cout << "Adding " << newCard->GetName() << endl;
            if(tappedVec[i]>0) {
                newCard->tapped=true;
                tappedVec[i]--;
//				cout << "Tapping " << newCard->GetName() << endl;
            }
        }
    }
    return newPlayer;
}


bool TestControllerv3::Mulligan(bool isFirst) {
    int numLands = LandsInHand().size();
    if((numLands<2 || numLands >5) && myPlayer->hand->cardVec.size() > 5) {
        return true;
    }
    else {
        return false;
    }
}

bool TestControllerv3::PlayFirst() {
    return true;
}

double TestControllerv3::AssessGameState(double* myBoard, double* oppBoard, double myLife, double oppLife) {
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

double TestControllerv3::ModifyByLife(double value, double lifeTot) {
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

bool TestControllerv3::WillKill(Card* damager, Card* damaged) {
    if(damaged->toughness>damager->power) {
        return true;
    }
    else {
        return false;
    }
}

