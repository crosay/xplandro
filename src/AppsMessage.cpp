/*
 * AppsMessage.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rosaycy
 */

#include "datasheet.hpp"
#include "AppsMessage.hpp"
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <stdio.h>
#include "XPLMTools.hpp"
#include <regex>
#include <functional>

#define sep ":"
using namespace std;

AppsMessage::AppsMessage() {
	datarefName = "";
	dataType = xplmType_Unknown;
	dataref = NULL;
	outAddress = "";
	sentBoolean = false;
	cycle = 1;
	count = 0;
	loop = true;
	valid = true;
	updateRequired = false;
	value = 0;
	strValue = "";
}

/**
 * aCycle: the number of Xplane loop cycles between 2 sendings.
 * if negative, then the data will be checked every cycle and send only if changed
 */
AppsMessage::AppsMessage(string addrs, string aDataRefName, long aCycle, bool aLoop) {

	datarefName = aDataRefName;
	if (&datarefName != NULL){
		dataref = XPLMFindDataRef(datarefName.c_str());
		if (dataref == NULL){
			cout <<  datarefName + " not found\n";
			valid = false;
		}else{
			valid = true;
		}
		dataType = XPLMGetDataRefTypes(dataref);
	}else{
		valid = true;
		dataref = NULL;
	}
	if (aCycle < 0){
		cycle = -aCycle;
		sendOnChange = true;
	}else{
		cycle = aCycle;
		sendOnChange = false;
	}
	count = 0;
	loop = aLoop;
	outAddress = addrs;
	sentBoolean = false;
	updateRequired = false;
	value = 0;
	strValue = "";
}

string AppsMessage::toString(){
	ostringstream debugMessage;
	debugMessage << outAddress << ", " << datarefName << ", count " << count << " every " << cycle << ", repeat" << loop << "\n";
	return debugMessage.str();
}

bool AppsMessage::isValid(void) {
	return valid;
}
/**
 * true if the message was succesfully sent the previous attempt
 */
bool AppsMessage::isSent(void) {
	return sentBoolean;
}

void AppsMessage::setSent(void) {
	sentBoolean = true;
}

void AppsMessage::programSend() {
	sentBoolean = false;
}

void AppsMessage::setValue(double v){
	value = v;
	setValue(std::to_string(v));
	//set the boolean to the dataref with value at the next main loop
	updateRequired = true;
}

void AppsMessage::setValue(int v){
	setValue((double)v);
	//set the boolean to the dataref with value at the next main loop
	updateRequired = true;
}

void AppsMessage::setValue(string v){
	oldValue = strValue;
	strValue = v;
	//set the boolean to the dataref with value at the next main loop
	updateRequired = true;
}

void AppsMessage::setValue(std::vector<float> v) {
	//set the array value
	oldValues = values;
	values = v;
	//set the boolean to the dataref with value at the next main loop
	updateRequired = true;
}


void AppsMessage::parseAndSetValue(string v){
	smatch match;
	//if the value matches a float
	/**regular expression for integer */
	regex integerRe("[-+]?\\d+");
	/**regular expression for float */
	regex floatRe("[+-]?\\d+.+\\d+");

	if (regex_search(v, match, floatRe) && match.size() > 1) {
		string res = match.str(1);
		setValue(atof(res.c_str()));
	}
	//else if a value matches an integer
	else if (regex_search(v, match, integerRe) && match.size() > 1) {
		string res = match.str(1);
		setValue(atoi(res.c_str()));
	}
	//it is then a string (or whatever, consider a string)
	else{
		setValue(v);
	}
}

bool AppsMessage::hasChanged(){
	return (oldValue != strValue);
}


AppsMessage::~AppsMessage() {
}

/**
 * buid a key that can identify a unique means to address a data (ip address and dataref)
 */
int buildKey(std::string addrs, std::string dataref) {
	std::hash<std::string> str_hash;
	return str_hash(addrs + dataref);
}

