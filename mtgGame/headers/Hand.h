/*
 * Hand.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef HAND_H_
#define HAND_H_

#include "Location.h"
#include <iostream>

class Hand: public Location {
public:
	Hand();
	virtual ~Hand();
	void DrawGameState();
	string GetName();
};

#endif /* HAND_H_ */
