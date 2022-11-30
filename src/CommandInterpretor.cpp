/*
 * CommandInterpretor.cpp
 *
 */

#include "CommandInterpretor.hpp"
#include <regex>
#include <iostream>
#include <sstream>
#include <vector>
#include "version.hpp"
using namespace std;

const std::string DATAREF_RE = "(?<dataref>(?:\\d+)|(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+)";
const std::string ACURACY_RE = "(?<acc>\\d+\\.*\\d*)*";
/**regular expression for xplane dataref abc/abdc... */
//regex datarefRe("(.+\\/.+)+");
regex datarefRe("(?:(?:(?:[a-z]|[A-Z]|[0-9]|_)+)\\/)+(?:[a-z]|[A-Z]|[0-9]|_)+");

/**regular expression for command
 * start with 'cmd' separate by one or more space then the command then start or stop
 * */
const regex cmdRe("(?<cmd>cmd)\\s+" + DATAREF_RE + "\\s*(?<action>start|stop|once)", regex_constants::icase);
/**
 * set value (dataref) (value)
 */
const regex setRe("(?<cmd>set)\\s+" + DATAREF_RE + "\\s * (? <val>(? : \\d + \\.*\\d*) | (? : . + ))", regex_constants::icase);

/**
 * get dataref
 */
const regex getRe("(?<cmd>get)\\s+" + DATAREF_RE + "\\s*(\\d*)\\s*",regex_constants::icase);

/**
 * sub dataref
 */
const regex subRe("(?<cmd>sub)\\s+" + DATAREF_RE + "\\s*" + ACURACY_RE, regex_constants::icase);

/**
 * fmsinit or fms init
 */
const regex fmsInitRe("fms\\s*init",regex_constants::icase);
/**
 * fmsclear or fms clear
 */
const regex fmsClearRe("fms\\s*clear[\\s +]?((\\d+)|(all))",regex_constants::icase);
/**
 * fms count or fms count
 */
const regex fmsCountRe("fms\\s*count",regex_constants::icase);

/**
 * fmsset index name lat lon altitude type (overfly-optional)
 */
const regex fmsSetRe("fms\\s*set[\\s +](\\d+)[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fmsins index name lat lon altitude type (overfly-optional)
 */
const regex fmsInsRe("fms\\s*inse?r?t?[\\s +](\\d+)[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fmsadd name lat lon altitude type (overfly-optional)
 */
const regex fmsAddRe("fms\\s*add[\\s +]([a-zA-Z0-9]+)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +]([+-]?\\d+\\.*\\d*)[\\s +](\\d+)[\\s +](\\d+)[\\s +]?(true|false)?",regex_constants::icase);

/**
 * fms dir (to) index
 * or fmd dir (to), index
 */
const regex fmsDtoRe( "fms\\s+dir\\s*t?o?[\\s +](\\d+)",regex_constants::icase);

/**
 * quit or exit
 */

const regex quitRe("(quit|exit|disconnect)",regex_constants::icase);
/**
 * help
 */
const regex helpRe("(help|\\?)",regex_constants::icase);

/**regular expression for integer */
const regex integerRe("[-+]?\\d+");
/**regular expression for float */
const regex floatRe("[+-]?\\d+.+\\d+");
/**regular expression for boolean (true or false only) */
const regex booleanRe("(true|false)");
/**regular expression for array ([xxx, xxx, xxx...]) */
const regex arrayRe("\\[((?:\\d+\\.*\\d*,*\\s*)+)\\]");

CommandInterpretor::CommandInterpretor(string msg) {
	source = msg;
	cmd = parseCmd(msg);
}

CommandInterpretor::~CommandInterpretor() {
}

Commands CommandInterpretor::parseCmd(string msg){
	Commands res = Commands::INVALID;
	group.clear();
	smatch matches;
	regex re;
	if (regex_match(msg, cmdRe)){
		res = Commands::COMMAND;
		re = cmdRe;
	}else if (regex_match(msg, setRe)){
		res = Commands::SET_VALUE;
		re = setRe;
	}else if (regex_match(msg, getRe)){
		res = Commands::GET_VALUE;
		re = getRe;
	}else if (regex_match(msg, fmsInitRe)){
		res = Commands::FMS_INIT;
		re = fmsInitRe;
	}else if (regex_match(msg, fmsClearRe)){
		res = Commands::FMS_CLR;
		re = fmsClearRe;
	}else if (regex_match(msg, fmsSetRe)){
		res = Commands::FMS_SET;
		re = fmsSetRe;
	}else if (regex_match(msg, fmsInsRe)){
		res = Commands::FMS_INSERT;
		re = fmsInsRe;
	}else if (regex_match(msg, fmsAddRe)){
		res = Commands::FMS_ADD;
		re = fmsAddRe;
	}else if (regex_match(msg, fmsCountRe)){
		res = Commands::FMS_COUNT;
		re = fmsCountRe;
	}else if (regex_match(msg, fmsDtoRe)){
		res = Commands::FMS_DIR_TO;
		re = fmsDtoRe;
	}else if (regex_match(msg, quitRe)){
		res = Commands::QUIT;
		re = quitRe;
	}else if (regex_match(msg, helpRe)){
		res = Commands::HELP;
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

