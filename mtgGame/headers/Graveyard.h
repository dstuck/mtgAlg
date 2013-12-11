/*
 * Graveyard.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef GRAVEYARD_H_
#define GRAVEYARD_H_

#include "Location.h"

class Graveyard: public Location {
public:
	Graveyard();
	virtual ~Graveyard();
	string GetName();
};

#endif /* GRAVEYARD_H_ */
