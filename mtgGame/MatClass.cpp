/*
 * MatClass.cpp
 *
 *  Created on: Dec 4, 2013
 *      Author: dstuck
 */

#include "headers/MatClass.h"

void MatClass::WriteBinMat(double* theMat, string filename, int matSize) {
	cout.flush();
	ofstream file (filename, ios::out|ios::binary|ios::trunc);
	if (file.is_open()) {
		file.write(reinterpret_cast<char*>(theMat), matSize*sizeof(double));
		file.close();
	}
}

double* MatClass::ReadBinMat(string filename, int* matSize) {
	cout.flush();
	streampos size;
	double* outMat;
//	char * memblock;
	ifstream infile(filename, ios::binary|ios::ate);
	if (infile.is_open()) {
		size = infile.tellg();
		*matSize = size/sizeof(double);
//		cout << "Size is " << size << endl;
		outMat = new double(size);
//		memblock = new char [size];
		infile.seekg (0, ios::beg);
		infile.read (reinterpret_cast<char*>(outMat), size);
		infile.close();
	}
	else{
		cout << "Error reading in file " << filename << endl;
		outMat = NULL;
	}
	return outMat;
}

void MatClass::WriteTxtMat(double* theMat, string filename, int matSize) {
	ofstream outfile;
	outfile.open(filename.c_str(), ios::out | ios::trunc);
	cout << "Writing " << filename << endl;
	if (outfile.is_open()) {
		outfile << matSize << endl;
		for(int i=0; i<matSize; i++) {
			outfile << theMat[i] << endl;
//			outfile << theMat[i] << " ";
		}
		outfile.close();
	}
	else {
		cout << "Error: Can't open " << filename << endl;
	}
}

double* MatClass::ReadTxtMat(string filename, int* matSize) {
	cout.flush();
	int size;
	double* outMat;
//	char * memblock;
	ifstream infile(filename, ios::in);
	if (infile.is_open()) {
		infile >> size;
//		cout << "size is " << size << endl;
		*matSize = size;
		outMat = new double[size];
		for(int i=0; i<size; i++) {
			infile >> outMat[i];
		}
		infile.close();
	}
	else{
		cout << "Error reading in file " << filename << endl;
		outMat = NULL;
	}
	return outMat;
}

void MatClass::PrintMat(double* theMat, int sizeM, int sizeN, ostream& outfile) {
	for(int i=0; i<sizeM; i++) {
		for(int j=0; j<sizeN; j++) {
			outfile << theMat[i+j*sizeM] << "\t";
		}
		outfile << endl;
	}
}



