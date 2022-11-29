/*
 * FMSEntry.h
 *
 *  Created on: 30 mars 2016
 *      Author: cyrille
 */

#ifndef SRC_FMSENTRY_H_
#define SRC_FMSENTRY_H_
#include "datasheet.hpp"
#include "XPLMTools.hpp"
#include "XPLMNavigation.h"
#include "XPLMDataAccess.h"
#include "XPLMPlugin.h"
#include <string>
#include <sstream>
#include <vector>
/**
 * structure used for a FMS entry
 */
struct FmsEntry{
	//id of the FMS entry, usually max 5 letters but can be lat/lon in xplane
	char id[25];
	float lat;
	float lon;
	//altitude in feet (no decimal)
	int altitude;
	//type of the navigation
	XPLMNavType tp;
	//1 if fly over, 0 if pass by
	bool flyover;
};

void fmsRegisterEntries(void);
void fmsInit(void);
void fmsRegisterToDataRefsPlugin(void);
void fmsSelectEntry(int index);
void fmsSelect(int index);
int getSelectedFms(void);
void fmsAddEntry(FmsEntry e);
void fmsSetEntry(int i, FmsEntry e);
void fmsInsertBeforeEntry(int before, FmsEntry e);
void fmsUpdateXplaneStructure(int fms1or2);
void fmsClear(int index);
void fmsClearAll();


#endif /* SRC_FMSENTRY_H_ */


