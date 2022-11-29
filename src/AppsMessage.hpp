/*
 * AppsMessage.h
 *
 *  Created on: Oct 13, 2013
 *      Author: rosaycy
 */

#ifndef APPSMESSAGE_H_
#define APPSMESSAGE_H_
#include "datasheet.hpp"
#include "XPLMDataAccess.h"
#include <stdlib.h>
#include <string>
#include <regex>
using namespace std;

class AppsMessage {
private:

public:
	//the name of the dataref to point to inX-PLANE
	string datarefName;
	//the address to send datagram packet to
	string outAddress;
	//the dataref structure
	XPLMDataRef dataref;
	//dataref type of data
	XPLMDataTypeID dataType;
	//index of the datasheet as specified in datasheet.hpp, used to synchronize data with the client
	int index;
	//true if need to send the data at each iteration; false = only one shot
	bool loop;
	//true if the data was sent during the previous cycle
	bool sentBoolean;
	//number of cycles between 2 send
	long cycle;
	//the actual cycle
	long count;
	bool valid;
	//true if the main loop has to change the Xplane dataref with value
	bool updateRequired;
	//the value is always in float converted via (int) to integer
	float value;
	//the value as string (can be non numeric)
	string strValue;
	//the old value as sent to the client
	string oldValue = "";
	//send only when the data change
	bool sendOnChange = false;
	//for arrays
	std::vector<float> values, oldValues;


	AppsMessage();
	AppsMessage(std::string addrs, std::string aDataRefName, int anIndex, long aCycle, bool aLoop);
	bool isValid(void);
	bool isSent(void);
	void setSent(void);
	void programSend();
	void setValue(double v);
	void setValue(int v);
	void setValue(string v);
	void setValue(std::vector<float> v);
	void parseAndSetValue(string v);
	int getIntValue(){return (int)value;}
	float getFloatValue(){return value;}
	string getStringValue(){return strValue;}
	bool hasChanged();
	string toString();
	virtual ~AppsMessage();

};

int buildKey(std::string addrs, int dr, std::string dataref);

#endif /* APPSMESSAGE_H_ */

