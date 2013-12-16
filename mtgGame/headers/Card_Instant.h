/*
 * Card_Instant.h
 *
 *  Created on: Dec 10, 2013
 *      Author: dstuck
 */

#ifndef CARD_INSTANT_H_
#define CARD_INSTANT_H_

#include "Card.h"
#include "Player.h"

class Card_Instant: public Card {
public:
	Card_Instant();
	virtual ~Card_Instant();
	void DefaultInit();
	virtual string GetImage();
	virtual void Play();
	virtual bool Pay(bool);
	virtual bool CanPay(bool);
};

#endif /* CARD_INSTANT_H_ */
