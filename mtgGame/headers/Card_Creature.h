/*
 * Card_Creature.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef CARD_CREATURE_H_
#define CARD_CREATURE_H_

#include "Card.h"
#include "Colors.h"
#include "Player.h"

//	Note: 	Being a Card_Creature does not make you a creature!
//			Setting isCreature = true makes you a creature.
//			This class simply has some handy defaults for intialization, pay, and play
class Card_Creature: public Card {
public:
	Card_Creature();
	virtual ~Card_Creature();
	void DefaultInit();
	virtual string GetImage();
	virtual void Play();
	virtual bool Pay(bool);
	virtual bool CanPay(bool);
//	void KeywordVanilla();
//	void SetVanillaVariables();
//	int GetPower();
//	int GetToughness();
//	virtual bool CanAttack();
//	virtual void Attack(Planeswalker*);
//	virtual bool CanBlock(Card_Creature*);
//	virtual bool CanBeBlocked(Card_Creature*);
//	virtual void Block(Card_Creature*);
//	virtual void TakeDamage(int);
//	virtual void Destroy();
//	virtual void Die();
//	virtual void ResetAll();
//	virtual void ResetEOT();

//	int power;
//	int toughness;
//	int damage;
//	int regenerating;
//	Planeswalker* attacking;
//	Card_Creature* blocking;
//	vector<Card_Creature*> blocked;
//	bool summoningSick;

//	bool regularStrike;
////********************
////	Combat abilities
////********************
//	bool vanillaCombat;
////	TODO
//	bool firstStrike;
////	TODO
//	bool trample;
////	TODO
//	bool deathtouch;
////********************
////	Misc. abilities
////********************
//	bool vanillaMisc;
//	bool haste;
////	TODO
//	bool lifelink;
//	bool vigalance;
//	bool indestructable;
//	bool flash;
////	TODO
//	bool hexproof;
////	TODO
//	bool shroud;
////********************
////	Block limitations
////********************
//	bool vanillaBlocks;
//	bool reach;
////********************
////	Unblockability
////********************
//	bool vanillaBlockability;
//	bool flying;
//	bool intimidate;
//	bool unblockable;
};

#endif /* CARD_CREATURE_H_ */
