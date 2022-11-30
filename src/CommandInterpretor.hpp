/*
 * CommandInterpretor.h
 *
 *  Created on: 31 janv. 2018
 *      Author: cyrille
 */

#ifndef SRC_COMMANDINTERPRETOR_HPP_
#define SRC_COMMANDINTERPRETOR_HPP_
#include <string>
#include <vector>
#include <regex>

enum class Commands {
	INVALID=0,
	HELLO=1,
	COMMAND=2,
	SET_VALUE=3,
	GET_VALUE=4,
	FMS_INIT=5,
	FMS_CLR=6,
	FMS_SET=7,
	FMS_ADD=8,
	FMS_INSERT=9,
	FMS_COUNT=10,
	FMS_DIR_TO=11,
	QUIT=12,
	HELP=13,
	GET_DARAREF=14, //get a dataref by a string reference e.g. get sim/aircraft/view/acf_Vso
	SET_DATAREF=15};//set the value of a dataref given by direct reference e.g. sim/aircraft/view/acf_Vso

class CommandInterpretor {
public:
	Commands cmd;
    std::vector<std::string> group;
	std::string source;

	CommandInterpretor(std::string msg);
	virtual ~CommandInterpretor();
	Commands parseCmd(std::string msg);

	Commands getCmd() const {
		return cmd;
	}

	const std::vector<std::string>& getGroup() const {
		return group;
	}
	const int getGroupAsInt(const unsigned int i){
		return atoi(getGroupAsString(i).c_str());
	}
	const double getGroupAsFloat(const unsigned int i){
		return atof(getGroupAsString(i).c_str());
	}
	const bool getGroupAsBool(const unsigned int i){
		return getGroupAsString(i) == "true" ? true : false;
	}
	const std::string getGroupAsString(const unsigned int i){
		if (i>=0 && i< group.size()) return group[i];
		return "";
	}
	const std::string getHelp();
	const bool isDataref();

	const std::regex getIntRegex();
	const std::regex getFloatRegex();
	const std::regex getBooleanRegex();
	const std::regex getArrayRegex();

};

#endif /* SRC_COMMANDINTERPRETOR_HPP_ */
