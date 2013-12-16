/*
 * Target.h
 *
 *  Created on: Dec 10, 2013
 *      Author: dstuck
 */

#ifndef TARGET_H_
#define TARGET_H_

class Player;

class Target {
public:
	Target();
	virtual ~Target();
	virtual bool IsTargetable(Player*) = 0;
	virtual bool IsCard() = 0;
};

#endif /* TARGET_H_ */
