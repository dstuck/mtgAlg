/*
 * Swamp.h
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#ifndef SWAMP_H_
#define SWAMP_H_

#include "Card_Land.h"

class Swamp: public Card_Land {
public:
	Swamp();
	virtual ~Swamp();
	string GetImage();
	void Play();
};

#endif /* SWAMP_H_ */
