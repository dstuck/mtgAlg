/*
 * Library.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Library.h"

Library::Library() {
	// TODO Auto-generated constructor stub

}

Library::~Library() {
	// TODO Auto-generated destructor stub
}

void Library::PrintGameState() {
	cout << "[[" << cardVec.size() << "]]";
}

string Library::GetName() {
	return "Library";
}



