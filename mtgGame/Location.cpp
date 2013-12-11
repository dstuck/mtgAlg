/*
 * Location.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Location.h"
#include "Card.h"

Location::Location() {
	// TODO Auto-generated constructor stub

}

Location::~Location() {
	for(int i=0; i<cardVec.size(); i++) {
		delete cardVec[i];
	}
}

void Location::AddCard(Card* addCard) {
	cardVec.push_back(addCard);
}

void Location::DestroyCards() {
	for(int i=0; i<cardVec.size(); i++) {
		delete cardVec.back();
	}
}

