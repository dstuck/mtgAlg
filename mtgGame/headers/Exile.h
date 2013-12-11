/*
 * Exile.h
 *
 *  Created on: Nov 25, 2013
 *      Author: dstuck
 */

#ifndef EXILE_H_
#define EXILE_H_

#include "Location.h"

class Exile: public Location {
public:
	Exile();
	virtual ~Exile();
	string GetName();
};

#endif /* EXILE_H_ */
