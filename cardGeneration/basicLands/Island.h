/*
 * Island.h
 *
 * Autogenerated by generateCards.py
 *	Author: dstuck
*/

#ifndef ISLAND_H_
#define ISLAND_H_

#include "Card_Land.h"

class Island: public Card_Land {
public:
	Island();
	virtual ~Island();
	string GetImage();
	void Play();
};

#endif /* ISLAND_H_ */
