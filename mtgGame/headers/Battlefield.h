/*
 * Battlefield.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef BATTLEFIELD_H_
#define BATTLEFIELD_H_

#include "Location.h"

class Battlefield: public Location {
public:
	Battlefield();
	virtual ~Battlefield();
	string GetName();
};

#endif /* BATTLEFIELD_H_ */
