/*
 * Planeswalker.h
 *
 *  Created on: Nov 29, 2013
 *      Author: dstuck
 */

#ifndef PLANESWALKER_H_
#define PLANESWALKER_H_

class Planeswalker {
public:
	Planeswalker();
	virtual ~Planeswalker();

	virtual void TakeDamage(int)=0;
};

#endif /* PLANESWALKER_H_ */
