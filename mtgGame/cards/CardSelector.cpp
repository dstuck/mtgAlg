/*
 * CardSelector.cpp
 *
 *  Created on: Nov 25, 2013
 *      Author: dstuck
 */

#include "CardSelector.h"
//Basic Lands
#include "Forest.h"
#include "Swamp.h"
#include "Island.h"
#include "Mountain.h"
#include "Plains.h"
//Vanilla Green Creatures
#include "NorwoodRanger.h"
#include "GrizzlyBears.h"
#include "NessianCourser.h"
#include "RumblingBaloth.h"
#include "NettleSwine.h"
#include "SpinedWurm.h"
#include "PheresBandCentaurs.h"
#include "HollowhengeBeast.h"
#include "CrawWurm.h"
#include "VastwoodGorger.h"
#include "AxebaneStag.h"
#include "ScaledWurm.h"
#include "FlyingMen.h"
#include "KrakenHatchling.h"
#include "CoralMerfolk.h"
#include "SeacoastDrake.h"
#include "HornedTurtle.h"
#include "PhantomWarrior.h"
#include "WindDrake.h"
#include "BlindPhantasm.h"
#include "AzureDrake.h"
#include "SnappingDrake.h"
#include "AirElemental.h"
#include "SkylinePredator.h"
#include "GoliathSphinx.h"

Card* CardSelector::NewCard(CardList::cardName theName) {
	Card* theCard;

	switch(theName) {
//	 Basic Lands
        case CardList::Forest:
                theCard = new Forest();
                break;
        case CardList::Swamp:
                theCard = new Swamp();
                break;
        case CardList::Island:
                theCard = new Island();
                break;
        case CardList::Mountain:
                theCard = new Mountain();
                break;
        case CardList::Plains:
                theCard = new Plains();
                break;
// Vanilla Green Creatures
        case CardList::NorwoodRanger:
                theCard = new NorwoodRanger();
                break;
        case CardList::GrizzlyBears:
                theCard = new GrizzlyBears();
                break;
        case CardList::NessianCourser:
                theCard = new NessianCourser();
                break;
        case CardList::RumblingBaloth:
                theCard = new RumblingBaloth();
                break;
        case CardList::NettleSwine:
                theCard = new NettleSwine();
                break;
        case CardList::SpinedWurm:
                theCard = new SpinedWurm();
                break;
        case CardList::PheresBandCentaurs:
                theCard = new PheresBandCentaurs();
                break;
        case CardList::HollowhengeBeast:
                theCard = new HollowhengeBeast();
                break;
        case CardList::CrawWurm:
                theCard = new CrawWurm();
                break;
        case CardList::VastwoodGorger:
                theCard = new VastwoodGorger();
                break;
        case CardList::AxebaneStag:
                theCard = new AxebaneStag();
                break;
        case CardList::ScaledWurm:
                theCard = new ScaledWurm();
                break;
	case CardList::FlyingMen:
		theCard = new FlyingMen();
		break;
	case CardList::KrakenHatchling:
		theCard = new KrakenHatchling();
		break;
	case CardList::CoralMerfolk:
		theCard = new CoralMerfolk();
		break;
	case CardList::SeacoastDrake:
		theCard = new SeacoastDrake();
		break;
	case CardList::HornedTurtle:
		theCard = new HornedTurtle();
		break;
	case CardList::PhantomWarrior:
		theCard = new PhantomWarrior();
		break;
	case CardList::WindDrake:
		theCard = new WindDrake();
		break;
	case CardList::BlindPhantasm:
		theCard = new BlindPhantasm();
		break;
	case CardList::AzureDrake:
		theCard = new AzureDrake();
		break;
	case CardList::SnappingDrake:
		theCard = new SnappingDrake();
		break;
	case CardList::AirElemental:
		theCard = new AirElemental();
		break;
	case CardList::SkylinePredator:
		theCard = new SkylinePredator();
		break;
	case CardList::GoliathSphinx:
		theCard = new GoliathSphinx();
		break;
        case CardList::size:
        		theCard = NULL;
                break;
	}

	return theCard;
}

map<string, int> CardSelector::NameToCardIndex() {
	map<string,int> nameToIndex;
	nameToIndex["Forest"] = 0;
	nameToIndex["Swamp"] = 1;
	nameToIndex["Island"] = 2;
	nameToIndex["Mountain"] = 3;
	nameToIndex["Plains"] = 4;
	nameToIndex["Norwood Ranger"] = 5;
	nameToIndex["Grizzly Bears"] = 6;
	nameToIndex["Nessian Courser"] = 7;
	nameToIndex["Rumbling Baloth"] = 8;
	nameToIndex["Nettle Swine"] = 9;
	nameToIndex["Spined Wurm"] = 10;
	nameToIndex["Pheres-Band Centaurs"] = 11;
	nameToIndex["Rumbling Baloth"] = 12;
	nameToIndex["Craw Wurm"] = 13;
	nameToIndex["Vastwood Gorger"] = 14;
	nameToIndex["Axebane Stag"] = 15;
	nameToIndex["Scaled Wurm"] = 16;
	nameToIndex["Flying Men"] = 17;
	nameToIndex["Kraken Hatchling"] = 18;
	nameToIndex["Coral Merfolk"] = 19;
	nameToIndex["Seacoast Drake"] = 20;
	nameToIndex["Horned Turtle"] = 21;
	nameToIndex["Phantom Warrior"] = 22;
	nameToIndex["Wind Drake"] = 23;
	nameToIndex["Blind Phantasm"] = 24;
	nameToIndex["Azure Drake"] = 25;
	nameToIndex["Snapping Drake"] = 26;
	nameToIndex["Air Elemental"] = 27;
	nameToIndex["Skyline Predator"] = 28;
	nameToIndex["Goliath Sphinx"] = 29;
	return nameToIndex;
}

