/*
 * CardSelector.h
 *
 *  Created on: Nov 25, 2013
 *      Author: dstuck
 */

#ifndef CARDSELECTOR_H_
#define CARDSELECTOR_H_

#include "Card.h"
#include "CardList.h"
#include <map>

namespace CardSelector{

	Card* NewCard(CardList::cardName);
	map<string,int> NameToCardIndex();

}


#endif /* CARDSELECTOR_H_ */
