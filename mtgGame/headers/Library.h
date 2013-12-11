/*
 * Library.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef LIBRARY_H_
#define LIBRARY_H_

#include "Location.h"
#include <iostream>

class Library: public Location {
public:
	Library();
	virtual ~Library();
	void PrintGameState();
	string GetName();
};

#endif /* LIBRARY_H_ */
