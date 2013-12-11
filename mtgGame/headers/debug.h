/*
 * debug.h
 *
 *  Created on: Oct 19, 2013
 *      Author: dstuck
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include<iostream>

//#ifdef DEBUG
#define LINE std::cout << "file:" << __FILE__ << " line:" << __LINE__ << std::endl;
//#else
//#define LINE
//#endif

#endif /* DEBUG_H_ */
