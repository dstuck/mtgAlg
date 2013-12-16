/*
 * Playable.h
 *
 *  Created on: Nov 26, 2013
 *      Author: dstuck
 */

#ifndef PLAYABLE_H_
#define PLAYABLE_H_

//#include "Player.h"
class Player;

class Playable {
public:
	Playable();
	virtual ~Playable();
	virtual void Play()=0;
	virtual bool Pay(bool)=0;
	virtual bool CanPay(bool)=0;

	bool instantSpeed;
	bool usesStack;
	Player* thePlayer;
};

#endif /* PLAYABLE_H_ */
