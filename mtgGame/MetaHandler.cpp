/*
 * MetaHandler.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: dstuck
 */

#include "headers/MetaHandler.h"

void MetaHandler::WriteDefaultCardValues() {
	double* valVec = new double[CardList::size];
	for(int i=0; i<CardList::size; i++) {
		if(CardSelector::NewCard(CardList::cardName(i))->cmc>0) {
//			valVec[i] = CardSelector::NewCard(CardList::cardName(i))->cmc;
			valVec[i] = 2*CardSelector::NewCard(CardList::cardName(i))->cmc;
		}
		else {
			valVec[i] = 1;
		}
	}
//	MatClass::WriteBinMat(valVec,GetCardValueBinFileName(),CardList::size);
	MatClass::WriteTxtMat(valVec,GetCardValueTxtFileName(),CardList::size);
	delete valVec;
}

double* MetaHandler::ReadDefaultCardValues() {
	int matSize;
//	double* returnVal = MatClass::ReadBinMat(GetCardValueBinFileName(),&matSize);
	double* returnVal = MatClass::ReadTxtMat(GetCardValueTxtFileName(),&matSize);
	if(matSize!=CardList::size) {
		cout << "Error! DefaultCardValueFile is of size " << matSize << " but there are " << CardList::size << " cards!" << endl;
		return NULL;
	}
	return returnVal;
}

string MetaHandler::GetCardValueBinFileName() {
	return "/Users/dstuck/projects/mtgAlg/mtgGame/DefaultCardVal.bin";
}

string MetaHandler::GetCardValueTxtFileName() {
	return "/Users/dstuck/projects/mtgAlg/mtgGame/DefaultCardVal.txt";
}




void MetaHandler::PrintIdToIndex() {
//	int* valVec = new double[CardList::size];
	for(int i=0; i<CardList::size; i++) {
		cout << "idToIndex[" << CardSelector::NewCard(CardList::cardName(i))->id << "] = " << i << ";" << endl;
	}
}


