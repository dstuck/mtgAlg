/*
 * DeckList.cpp
 *
 *  Created on: Dec 10, 2013
 *      Author: dstuck
 */

#include "DeckList.h"
#include "CardList.h"
#include "CardSelector.h"

vector<Card*> DeckList::FrenchVanillaBlue() {
	vector<Card*> cardVec;
	Card * deckCard;
	for(int i=0; i<18; i++) {
		deckCard = CardSelector::NewCard(CardList::Island);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<0; i++) {
		deckCard = CardSelector::NewCard(CardList::FlyingMen);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::KrakenHatchling);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::SeacoastDrake);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<4; i++) {
		deckCard = CardSelector::NewCard(CardList::WindDrake);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::PhantomWarrior);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<2; i++) {
		deckCard = CardSelector::NewCard(CardList::AzureDrake);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<4; i++) {
		deckCard = CardSelector::NewCard(CardList::SnappingDrake);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::AirElemental);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<0; i++) {
		deckCard = CardSelector::NewCard(CardList::SkylinePredator);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<1; i++) {
		deckCard = CardSelector::NewCard(CardList::GoliathSphinx);
		cardVec.push_back(deckCard);
	}
	return cardVec;
}

vector<Card*> DeckList::VanillaGreen() {
	vector<Card*> cardVec;
	Card * deckCard;
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::NorwoodRanger);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<7; i++) {
		deckCard = CardSelector::NewCard(CardList::GrizzlyBears);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<6; i++) {
		deckCard = CardSelector::NewCard(CardList::NessianCourser);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<4; i++) {
		deckCard = CardSelector::NewCard(CardList::NettleSwine);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<3; i++) {
		deckCard = CardSelector::NewCard(CardList::PheresBandCentaurs);
		cardVec.push_back(deckCard);
	}
	for(int i=0; i<17; i++) {
		deckCard = CardSelector::NewCard(CardList::Forest);
		cardVec.push_back(deckCard);
	}
	return cardVec;
}
