/*
 * CommandInterpretor.cpp
 *
 *  Created on: 31 janv. 2018
 *      Author: cyrille
 */

#include "CommandInterpretor.hpp"
#include <regex>
#include <iostream>
#include <sstream>
#include <vector>
#include "version.hpp"
using namespace std;

/**regular expression for hello command
 * start with 'hello' separate by either one space or one , then (user) (machine)
 * */
regex helloRe("hello[\\s+](avandro)(.+)\\s+(.+)",regex_constants::icase);
/**regular expression for command
 * start with 'command' or 'cmd' separate by one or more space then the command then start or stop
 * */
regex cmdRe("(?:co?mm?a?n?d)\\s+((?:\\d+)|(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+)\\s*(start|stop|once)",regex_constants::icase);
/**
 * set value (dataref) (value)
 */
regex setValueRe("(?:set\\s*v?a?l?u?e?)\\s+((?:\\d+)|(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+)\\s*((?:\\d+\\.*\\d*)|(?:.+))", regex_constants::icase);

/**
 * get value (index) (frequency - optional) (repeat - optional)
 */
regex getValueRe("(?:get\\s*v?a?l?u?e?)\\s+((?:\\d+)|(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+)\\s*(\\d*)\\s*(true|false)?",regex_constants::icase);
/**
 * get value ([index1, index2,index3...]) (frequency - optional) (repeat - optional)
 */
regex getMultIndexRe("get\\s*v?a?l?u?e?[\\s +](\\[(.+[\\s +])*.d+\\])[\\s +](\\d+)?[\\s +]?(true|false)?",regex_constants::icase);
/**
 * fmsinit or fms init
 */
regex fmsInitRe("fms\\s*init",regex_constants::icase);
/**
 * fmsclear or fms clear
 */
regex fmsClearRe("fms\\s*clear[\\s +]?((\\d+)|(all))",regex_constants::icase);
/**
 * fms count or fms count
 */
regex fmsCountRe("fms\\s*count",regex_constants::icase);

/**
 * fmsset index name lat lon altitude type (overfly-optional)
 */
regex fmsSetRe("fms\\s*set[\\s +](\\d+)[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fmsins index name lat lon altitude type (overfly-optional)
 */
regex fmsInsRe("fms\\s*inse?r?t?[\\s +](\\d+)[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fmsadd name lat lon altitude type (overfly-optional)
 */
regex fmsAddRe("fms\\s*add[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fms dir (to) index
 * or fmd dir (to), index
 */
regex fmsDtoRe( "fms\\s+dir\\s*t?o?[\\s +](\\d+)",regex_constants::icase);

/**
 * quit or exit
 */
regex quitRe("(quit|exit)",regex_constants::icase);
/**
 * help
 */
regex helpRe("(help|\\?)",regex_constants::icase);

/**regular expression for xplane dataref abc/abdc... */
//regex datarefRe("(.+\\/.+)+");
regex datarefRe("(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+");
/**regular expression for integer */
regex integerRe("[-+]?\\d+");
/**regular expression for float */
regex floatRe("[+-]?\\d+.+\\d+");
/**regular expression for boolean (true or false only) */
regex booleanRe("(true|false)");
/**regular expression for array ([xxx, xxx, xxx...]) */
regex arrayRe("\\[((?:\\d+\\.*\\d*,*\\s*)+)\\]");

CommandInterpretor::CommandInterpretor(string msg) {
	source = msg;
	cmd = parseCmd(msg);
}

CommandInterpretor::~CommandInterpretor() {
}

commands CommandInterpretor::parseCmd(string msg){
	commands res = INVALID;
	group.clear();
	smatch matches;
	regex re;
	if (regex_match( msg, helloRe)){
		res = HELLO;
		re = helloRe;
	}else if (regex_match(msg, cmdRe)){
		res = COMMAND;
		re = cmdRe;
	}else if (regex_match(msg, setValueRe)){
		res = SET_VALUE;
		re = setValueRe;
	}else if (regex_match(msg, getValueRe)){
		res = GET_VALUE;
		re = getValueRe;
	}else if (regex_match(msg, getMultIndexRe)){
		res = GET_VALUE;
		re = getMultIndexRe;
	}else if (regex_match(msg, fmsInitRe)){
		res = FMS_INIT;
		re = fmsInitRe;
	}else if (regex_match(msg, fmsClearRe)){
		res = FMS_CLR;
		re = fmsClearRe;
	}else if (regex_match(msg, fmsSetRe)){
		res = FMS_SET;
		re = fmsSetRe;
	}else if (regex_match(msg, fmsInsRe)){
		res = FMS_INSERT;
		re = fmsInsRe;
	}else if (regex_match(msg, fmsAddRe)){
		res = FMS_ADD;
		re = fmsAddRe;
	}else if (regex_match(msg, fmsCountRe)){
		res = FMS_COUNT;
		re = fmsCountRe;
	}else if (regex_match(msg, fmsDtoRe)){
		res = FMS_DIR_TO;
		re = fmsDtoRe;
	}else if (regex_match(msg, quitRe)){
		res = QUIT;
		re = quitRe;
	}else if (regex_match(msg, helpRe)){
		res = HELP;
		re = helpRe;
	}
	if(regex_search(msg, matches, re)) {
		if (matches.size()>0){
			for (size_t i = 1; i < matches.size(); ++i) {
				group.push_back(matches[i].str());
			}
		}
	}

	return res;

}

const string CommandInterpretor::getHelp(){
	ostringstream helpMsg;
	helpMsg << "command interpretor " << PLUGIN_NAME <<" V." << PLUGIN_VERSION << "." << PLUGIN_RELEASE <<"\n";
	helpMsg << "hello application platform : creates a client thread\n";
	helpMsg << "command <xplane-command> start|stop|once : start or stop a plugin command, or run it only once\n";
	helpMsg << "\t<xplane-command> implemented to date:\n";
	helpMsg << "\t<none>\n";
	helpMsg << "get val(ue) index... (rate:freq) (true|false) : program the data at index to be sent at the frequency (1 by default), true: repeat, false (by default): only once\n";
	helpMsg << "set val(ue) index value : set the data at index to the value\n";
	helpMsg << "fms init : initialises the fms\n";
	helpMsg << "fms clear (index)(all) : clear the fms entry at index or all entries if 'all'\n";
	helpMsg << "fms set entry at index with a waypoint name, its lat, lon, altitude and type. optionally set if overfly is true, default is false\n";
	helpMsg << "fms insert index name lat lon alt tp (ovf): insert before entry at index with a waypoint name, its lat, lon, altitude and type. optionally set if overfly is true, default is false\n";
	helpMsg << "fms add name lat lon alt tp (ovf): add a waypoint name, its lat, lon, altitude and type. optionally set if overfly is true, default is false\n";
	helpMsg << "fms count: returns the number of waypoints\n";
	helpMsg << "fms dir to index : direct to the entry in the fms (select the line at index)\n";
	helpMsg << "quit or exit: terminate the client\n";
	return helpMsg.str();
}

/**
returns true if the first element of the command is a dataref 
*/
const bool CommandInterpretor::isDataref(){
	return group.size()>0? 
		regex_match(group[0], datarefRe)
		:false;
}

const regex CommandInterpretor::getIntRegex(){
	return integerRe;
}
const regex CommandInterpretor::getFloatRegex(){
	return floatRe;
}

const regex CommandInterpretor::getBooleanRegex(){
	return booleanRe;
}

const regex CommandInterpretor::getArrayRegex() {
	return arrayRe;
}

