/*
 * Card_Land.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef CARD_LAND_H_
#define CARD_LAND_H_

#include "Card.h"
#include "Colors.h"
#include "Player.h"

class Card_Land: public Card {
public:
	Card_Land();
	virtual ~Card_Land();
	void DefaultInit();
//	virtual string GetName()=0;
//	virtual vector<string> GetSubtype()=0;
	void KeywordVanilla();
	virtual void Play();
	virtual bool Pay(bool);
	virtual bool CanPay(bool);
};

#endif /* CARD_LAND_H_ */
