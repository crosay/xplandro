/*
 * FMSEntry.cpp
 *
 *  Created on: 30 mars 2016
 *      Author: cyrille
 */

#include "FmsTools.hpp"

#include <string.h>
//message to send to the plugin datarefEditor
#define MSG_ADD_DATAREF 0x01000000



std::vector<FmsEntry> fms1;
std::vector<FmsEntry> fms2;
int fms1SelectedEntry = 0;
int fms2SelectedEntry = 0;
int selectedFms = 0;
/**
 * get the data for the FMS entries. the result is returned as a formatted string.
 * the format is:
 * fms entries;id entry 1;type of entry 1;latitude 1; longitude1; is flyover 1;id entry 2;type of entry 2;...
 */
int getFmsDataAccessor(void*, void* destination, int offset, int length){
	std::ostringstream os;
	os << fms1.size() << ";";

	for (int i = 0; i < fms1.size(); i++){
		FmsEntry fe = fms1.at(i);
		os <<  fe.id << ";" << fe.tp << ";" << fe.lat << ";" << fe.lon << ";" << fe.altitude << ";" << fe.flyover<<";";
	}
	int len = os.tellp();
	//pass NULL to get the size of the data
	if (destination != NULL) {
		strcpy((char*)destination, os.str().c_str());
	}
	return len;
}

int fms1NumberAccessor(void* inReference){
//    (void*) inReference;
	return fms1.size();
}

int fms2NumberAccessor(void* inReference){
    (void*) inReference;
	return fms2.size();
}

int fms1SelectedAccessor(void* inReference){
    (void*) inReference;
	return fms1SelectedEntry;
}

int fms2SelectedAccessor(void* inReference){
    (void*) inReference;
	return fms2SelectedEntry;
}
int fmsActiveAccessor(void* inReference){
    (void*) inReference;
	return selectedFms;
}

/**
 * register the FMS data
 */
void fmsRegisterEntries(void){
	XPLMRegisterDataAccessor(getDataRef(FMS1_ENTRIES_NUMBER).c_str(),
			xplmType_Int, 0,
			fms1NumberAccessor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr);
	XPLMRegisterDataAccessor(getDataRef(FMS2_ENTRIES_NUMBER).c_str(),
			xplmType_Int, 0,
			fms2NumberAccessor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr);

	XPLMRegisterDataAccessor(getDataRef(FMS1_SELECTED_ENTRY).c_str(),
			xplmType_Int, 0,
			fms1SelectedAccessor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr);

	XPLMRegisterDataAccessor(getDataRef(FMS2_SELECTED_ENTRY).c_str(),
			xplmType_Int, 0,
			fms2SelectedAccessor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr);

	XPLMRegisterDataAccessor(getDataRef(FMS_ACTIVE).c_str(),
			xplmType_Int, 0,
			fmsActiveAccessor, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			nullptr, nullptr, nullptr);

	XPLMDataRef dataref = XPLMRegisterDataAccessor(getDataRef(FMS1_ENTRIES_DATA).c_str(),
			xplmType_Data, 1,
			nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
			getFmsDataAccessor, nullptr, nullptr, nullptr);

	std::ostringstream debugMessage;
	debugMessage << "FmsRegisterEntries : " << dataref << "\n";
	debugPrintInXplnLog(debugMessage.str().c_str());

}


int getFms1number(void){
	return fms1.size();
}

int getFms2number(void){
	return fms2.size();
}

void fmsSetEntry(int i, FmsEntry e){
	fms1[i] = e;
}

void fmsAddEntry(FmsEntry e){
	fms1.push_back(e);
}

void fmsInsertBeforeEntry(int before, FmsEntry e){
	auto at = fms1.begin()+before;
	fms1.insert(at, e);
}

void fmsClear(int index){
	fms1.erase(fms1.begin()+index);
}

void fmsClearAll(){
	fms1.clear();
}

void fmsUpdateXplaneStructure(int fms1or2){
	std::vector<FmsEntry> fms = (fms1or2 == 0)? fms1 : fms2;
	char s[255];
	for( int i = 0; i < fms.size(); i++){
		FmsEntry e = fms [i];
		sprintf(s, "searching for id:%s (%f-%f) type=%d\n", e.id, e.lat, e.lon, e.tp);
		printInXplnLog(s);
		XPLMNavRef navRef = XPLMFindNavAid(
				NULL,
				e.id,
				&e.lat,
				&e.lon,
				NULL,
				e.tp);
		bool found = navRef != XPLM_NAV_NOT_FOUND;
		if (found){
			XPLMNavType  tp;   /* Can be NULL */
			float lat2;    /* Can be NULL */
			float  lon2;    /* Can be NULL */
			float  height;    /* Can be NULL */
			int  freq;    /* Can be NULL */
			float  hdg;    /* Can be NULL */
			char id2[255];    /* Can be NULL */
			char  name2[255];    /* Can be NULL */
			char  reg[255];    /* Can be NULL */
			XPLMGetNavAidInfo(navRef, &tp, &lat2, &lon2, &height, &freq, &hdg, id2, name2, reg);
			if (((int)lon2 == (int)e.lon) && ((int)lat2 == (int)e.lat)){
				sprintf(s, "found %s (%f-%f)\n", id2, lat2, lon2);
				printInXplnLog(s);
				XPLMSetFMSEntryInfo(i, navRef, e.altitude);
			}else{
				found = false;
			}
		}
		//either nafRef = NOT FOUND or lat and lon does not mach
		// create a new entry
		if (!found){
			XPLMSetFMSEntryLatLon(i, e.lat, e.lon, e.altitude);
			sprintf(s, "id:%s not found in x-plane database, create new latlon\n", e.id);
			printInXplnLog(s);
		}

	}

}

/**
 * select the active line in the fms 1
 */
void fmsSelectEntry(int index){
	if (index >= 0 && index < fms1.size()){
		if (selectedFms == 0){
			fms1SelectedEntry = index;
		}else{
			fms2SelectedEntry = index;
		}
		XPLMSetDestinationFMSEntry(index);
	}
}

/**
 * select the fms in use
 */
void fmsSelect(int index){
	if (index >= 0 && index <= 1){
		selectedFms = index;
	}
}

int getSelectedFms(void){return selectedFms;}

void fmsInit(void){

	XPLMNavType type;
	char id[256];
	XPLMNavRef ref;
	int altitude;
	float lat;
	float lon;

	std::ostringstream debugMessage;
	debugMessage << "listing FMS entries :" << XPLMCountFMSEntries() << " entrie(s) \n";
	debugPrintInXplnLog(debugMessage.str().c_str());
	fmsSelectEntry(XPLMGetDestinationFMSEntry());

	for (int i=0; i < XPLMCountFMSEntries(); i++){
		XPLMGetFMSEntryInfo(i, &type, id, &ref,&altitude, &lat,&lon);
		debugMessage.str("");
		debugMessage << "fms entry " << id << " : " << lat << "/" << lon << "\n";
		debugPrintInXplnLog(debugMessage.str().c_str());
		FmsEntry e;
		strcpy(e.id, id);
		e.lat = lat;
		e.lon = lon;
		e.altitude = altitude;
		e.tp = type;
		fms1.push_back(e);
	}
}

void fmsRegisterToDataRefsPlugin(void){

	//search for dataref editor plugin
	XPLMPluginID PluginID = XPLMFindPluginBySignature("xplanesdk.examples.DataRefEditor");
	if (PluginID != XPLM_NO_PLUGIN_ID){
		//if found add this new dataref
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS1_ENTRIES_DATA).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS2_ENTRIES_DATA).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS1_ENTRIES_NUMBER).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS2_ENTRIES_NUMBER).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS1_SELECTED_ENTRY).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS2_SELECTED_ENTRY).c_str());
		XPLMSendMessageToPlugin(PluginID, MSG_ADD_DATAREF, (void*)getDataRef(FMS_ACTIVE).c_str());

	}

}


