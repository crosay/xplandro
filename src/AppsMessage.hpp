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
	string datarefName;//the name of the dataref to point to inX-PLANE
	string outAddress;//the address to send datagram packet to
	XPLMDataRef dataref;//the dataref structure
	XPLMDataTypeID dataType;//dataref type of data
	bool loop;//true if need to send the data at each iteration; false = only one shot
	bool sentBoolean;//true if the data was sent during the previous cycle
	long cycle;//number of cycles between 2 send
	long count;//the actual cycle
	bool valid;//true if the data is valid
	bool updateRequired;//true if the main loop has to change the Xplane dataref with value
	float value;//the value is always in float converted via (int) to integer
	string strValue;//the value as string (can be non numeric)
	string oldValue = "";//the old value as sent to the client
	bool sendOnChange = false;//send only when the data change
	std::vector<float> values, oldValues;//for arrays

	AppsMessage();
	AppsMessage(std::string addrs, std::string aDataRefName, long aCycle, bool aLoop);
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

int buildKey(std::string addrs, std::string dataref);

#endif /* APPSMESSAGE_H_ */

