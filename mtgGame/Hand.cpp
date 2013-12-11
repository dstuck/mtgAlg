/*
 * Hand.cpp
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#include "headers/Hand.h"

Hand::Hand() {
	// TODO Auto-generated constructor stub

}

Hand::~Hand() {
	// TODO Auto-generated destructor stub
}

void Hand::DrawGameState() {
	for(int i=0; i<cardVec.size(); i++) {
		if(i>0){
			cout << " ";
		}
//		cout << cardVec[i]->GetImage();
	}
}

string Hand::GetName() {
	return "Hand";
}



