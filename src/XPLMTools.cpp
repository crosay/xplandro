/*
 * XPLMTools.cpp
 *
 *  Created on: Oct 13, 2013
 *      Author: rosaycy
 */
#include "datasheet.hpp"
#include "XPLMTools.hpp"
#include "XPLMUtilities.h"
#include "version.hpp"
#include "global.hpp"

void printFormatInXplnLog(const char *s) {
	XPLMDebugString(PLUGIN_NAME);
	XPLMDebugString(":");
	XPLMDebugString(s);
}

void debugFormatInXplnLog(std::string *s) {
	if (global_vars::options.debug){
		XPLMDebugString(PLUGIN_NAME);
		XPLMDebugString(":");
		XPLMDebugString(s->c_str());

	}
}

void debugFormatInXplnLog(std::string s) {
	if (global_vars::options.debug) {
		XPLMDebugString(PLUGIN_NAME);
		XPLMDebugString(":");
		XPLMDebugString(s.c_str());
	}
}


void printInXplnLog(const char *s) {
	XPLMDebugString(s);
}

void debugPrintInXplnLog(const char *s) {
	if (global_vars::options.debug) {
		XPLMDebugString(PLUGIN_NAME);
		XPLMDebugString(":");
		XPLMDebugString(s);
	}
}

void debugPrintlnInXplnLog(const char *s) {
	if (global_vars::options.debug) {
		XPLMDebugString(PLUGIN_NAME);
		XPLMDebugString(":");
		XPLMDebugString(s);
		XPLMDebugString("\n");
	}
}

void debugPrintlnInXplnLog(std::string *s) {
	if (global_vars::options.debug) {
		XPLMDebugString(PLUGIN_NAME);
		XPLMDebugString(":");
		XPLMDebugString(s->c_str());
		XPLMDebugString("\n");
	}
}




