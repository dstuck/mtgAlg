/*
 * MetaHandler.h
 *
 *  Created on: Dec 4, 2013
 *      Author: dstuck
 */

#ifndef METAHANDLER_H_
#define METAHANDLER_H_

#include <string>
#include <iostream>
#include <fstream>
#include "MatClass.h"
#include "CardList.h"
#include "CardSelector.h"
using namespace std;

namespace MetaHandler {

//	For calling in program
	void WriteDefaultCardValues();
	double* ReadDefaultCardValues();
	string GetCardValueBinFileName();
	string GetCardValueTxtFileName();

//	Throw away functions for debug
	void PrintIdToIndex();

}

#endif /* METAHANDLER_H_ */
