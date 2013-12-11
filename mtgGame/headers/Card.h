/*
 * Card.h
 *
 *  Created on: Nov 24, 2013
 *      Author: dstuck
 */

#ifndef CARD_H_
#define CARD_H_

#include "debug.h"
#include "Location.h"
#include <string>
#include <vector>
#include <iostream>
#include "Playable.h"
//#include "CardList.h"
using namespace std;

class Planeswalker;

class Card: public Playable {
public:
	Card();
	virtual ~Card();
//	virtual CardList::cardname GetNumber()=0;
	virtual string GetName();
	virtual string GetImage();
	virtual string GetImageURL();
	virtual vector<string> GetFlavor();
	virtual vector<string> GetSubtype();
	virtual void GetManaCost(int*); //Note: [W,U,B,R,G,O]
	void MoveLoc(Location*);
	virtual void ResetAll();
	virtual void ResetEOT();
	virtual void Play()=0;
	virtual bool Pay(bool)=0;
	virtual bool CanPay(bool)=0;
	bool DefaultCheckPay(bool);

//	CreatureType functions
	void KeywordVanilla();
	void SetVanillaVariables();
	int GetPower();
	int GetToughness();
	virtual bool CanAttack();
	virtual void Attack(Planeswalker*);
	virtual bool CanBlock(Card*);
	virtual bool CanBeBlocked(Card*);
	virtual void Block(Card*);
	virtual void TakeDamage(int);
	virtual void Destroy();
	virtual void Die();


	int mana[6];
	bool tapped;
	Location* curLoc;

	int id;
	string name;
//	int mana[6];
	int cmc;
	bool isCreature;
	bool isLand;
	bool isBasic;
	bool isInstant;
	bool isSorcery;
	bool isEnchantment;
	bool isArtifact;
	bool isLegendary;
	vector<string> subtype;
	vector<string> rulesText;
	vector<string> flavor;
	int power;
	int toughness;
	int loyalty;
	string set;
	string rarity;
	int cardNumber;
	string image;

//	Creature type variables
	int damage;
	int regenerating;
	bool summoningSick;
	Planeswalker* attacking;
	Card* blocking;
	vector<Card*> blocked;
	bool regularStrike;
//********************
//	Combat abilities
//********************
	bool vanillaCombat;
//	TODO
	bool firstStrike;
//	TODO
	bool trample;
//	TODO
	bool deathtouch;
//********************
//	Misc. abilities
//********************
	bool vanillaMisc;
	bool haste;
	bool defender;
//	TODO
	bool lifelink;
	bool vigilance;
	bool indestructable;
	bool flash;
//	TODO
	bool hexproof;
//	TODO
	bool shroud;
//********************
//	Block limitations
//********************
	bool vanillaBlocks;
	bool reach;
//********************
//	Unblockability
//********************
	bool vanillaBlockability;
	bool flying;
	bool intimidate;
	bool unblockable;
};

#endif /* CARD_H_ */
