/*
 * Location.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef LOCATION_H_
#define LOCATION_H_

//#include "Card.h"
#include <vector>
#include <string>
using namespace std;

// DES: Note to self! The following is a forward declaration and only
//		works since Location only ever works with pointers to Cards
//		See website: http://www.cplusplus.com/forum/articles/10627/
class Card;

class Location {
public:
	Location();
	virtual ~Location();
	void AddCard(Card*);
	void DestroyCards();
	virtual string GetName()=0;

	vector<Card*> cardVec;
};

#endif /* LOCATION_H_ */
