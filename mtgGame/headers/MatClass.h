/*
 * MatClass.h
 *
 *  Created on: Dec 4, 2013
 *      Author: dstuck
 */

#ifndef MATCLASS_H_
#define MATCLASS_H_

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
using namespace std;

namespace MatClass{

void WriteBinMat(double*, string, int);
double* ReadBinMat(string, int*);
void WriteTxtMat(double*, string, int);
double* ReadTxtMat(string, int*);
void PrintMat(double*, int, int=1, ostream& = cout);

}

#endif /* MATCLASS_H_ */
