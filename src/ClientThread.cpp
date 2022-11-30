/*
 * ClientThread.cpp
 *
 *  Created on: 14 mars 2016
 *      Author: cyrille
 */

#include "ClientThread.hpp"
#include "FmsTools.hpp"
#include "json.hpp"
#include "XPLMTools.hpp"
#include <thread>
#include <vector>
#include <regex>
#include "XPLMNavigation.h"
#include "XPLMUtilities.h"
#include "CommandInterpretor.hpp"
#if LIN
#define TRUE 1
#define FALSE 0
#endif
#define BUFFER_SIZE 1024
// for convenience
using json = nlohmann::json;

void splitInFloatArray(const string &str, char del, std::vector<float> &elements){
	stringstream ss(str);
	string sub;
	while (getline(ss, sub, del)){
		elements.push_back(atof(sub.c_str()));
	}
}

ClientThread::ClientThread(TCPSocket *tcps){
	name = "no_name";
	machine = "not_defined";
	libVersion = 1;
	address = tcps->getForeignAddress();
	pTcpSock = tcps;
	debugPrintlnInXplnLog("ClientThread::ClientThread");
	hThread = thread(&ClientThread::run, this);
}

/**

*/
DWORD ClientThread::run(){
	json dataArray;
	try{
		string address = pTcpSock->getForeignAddress();
		while (!terminated) {
			char charBuffer[BUFFER_SIZE];
			bool eot = false;
			int total = 0;
			while(!eot){
				try{
					int ret = pTcpSock->recv(&charBuffer[total], 1);
					if (ret != 0){
						eot = (total >= BUFFER_SIZE || ((charBuffer[total] == (char)10) && (total>2)));
						total+= ret;
						if (eot){
							total--; //ignore the \n in the message
						}
					}else {
						cout << "read() == 0 : client disconnected\n";
						printInXplnLog("read() == 0 : client disconnected\n");
#if SPEAK
						XPLMSpeakString(string("connection lost with " + name).c_str());
#endif
						//an error has occurred, or the client has disconnected
						terminated = true;
						break;
					}
				}catch (SocketException& e){
					debugPrintlnInXplnLog(e.what());
					clean();
					terminated = true;
					break;
				}
			}
			if (!terminated){
				//mark end of message (-1 to remove the \n)
				charBuffer[total-1] = '\0';

				// end of line detected, analyse message
				string message(charBuffer);
				CommandInterpretor ci(message);
				Commands cmd = ci.getCmd();
				ostringstream reply, os;
				string cmdName = "";
				string value = "";
				int key;
				string id = "";
				float lat =0;
				float lon = 0;
				int altitude = 0;
				int type = 0;
				bool flyover = false;
				int index = 0;
				XPLMCommandRef cmdref;
				XPLMDataRef ref;//XPLN data ref
				string dataref; //dataref as string

				switch (cmd) {
				case Commands::INVALID:
					reply << "unknown command " << message << "\n";
					pTcpSock->send(reply.str().c_str(), reply.str().length());
					break;
				case Commands::HELLO:
					name = ci.getGroupAsString(0); //the name of the client
					machine = ci.getGroupAsString(1); // it should also give the name of the host
					os << "hello " << name << " on " << machine << "\n";
					printInXplnLog(os.str().c_str());
					os.clear();
					os << PLUGIN_NAME << " V-" << PLUGIN_VERSION << "." << PLUGIN_RELEASE << "\n";
					pTcpSock->send(os.str().c_str(), os.str().length());
					break;
				case Commands::COMMAND:
					cmdName = ci.getGroupAsString(0);
					ref = XPLMFindCommand(cmdName.c_str());
					if (ref != NULL) {
						if (ci.getGroupAsString(1) == "start") {
							XPLMCommandBegin(ref);
						}
						else if (ci.getGroupAsString(1) == "once") {
							XPLMCommandOnce(ref);
						}
						else {
							XPLMCommandEnd(ref);
						}
					}
					break;
				case Commands::SET_VALUE:
					//set value datarefm str
					//require the data given in dataref (field 1) to be changed with the value in field 2
					if (ci.isDataref()) {
						index = -1;
						dataref = ci.getGroupAsString(0);
					}
					else {
						index = ci.getGroupAsInt(0);
						dataref = getDataRef(index);
					}
					if ((&dataref != NULL) && (dataref!="")){
						value = ci.getGroupAsString(1);
						key = buildKey(address, dataref);
						if (mapMessages.find(key) == mapMessages.end()) {
							//data does not exit, create the dataref first with no request for update
							addDataToCycle(address, dataref, 0, false);
						}
						ref = (mapMessages)[key].dataref;
						if (ref != NULL) {
							if (regex_match(value, ci.getIntRegex())) {
								int iValue = atoi(value.c_str());
								(mapMessages)[key].setValue(iValue);
							}
							else if (regex_match(value, ci.getFloatRegex())) {
								float fValue = atof(value.c_str());
								(mapMessages)[key].setValue(fValue);
							}
							else if (regex_match(value, ci.getBooleanRegex())) {
								bool bValue = value == "true" ? TRUE : FALSE;
								(mapMessages)[key].setValue(bValue);
							}
							else if (regex_match(value, ci.getArrayRegex())) {
								value = value.substr(1, value.length() - 1);
								std::vector<float> values;
								splitInFloatArray(value, ',', values);
								(mapMessages)[key].setValue(values);
							}
							(mapMessages)[key].setValue(value);
						}
					}

					break;
				case Commands::GET_VALUE:
					//get value numdata cycle loop
					//require the data given in dataref index (field 1) to be send every x cycles (field 2)
					//continuously if loop (field 3) is true
					addDataToCycle(address, ci.getGroupAsString(0), ci.getGroupAsInt(1), ci.getGroupAsBool(2));
					break;
				case Commands::QUIT:
					eot = true;
					terminated = true;
					pTcpSock->send(string("bye\n").c_str(), 4);
					break;
				case Commands::HELP:
					const string answer = ci.getHelp();
					int lenght = answer.length();
					pTcpSock->send(answer.c_str(), lenght);
					break;
				}			
			}
		}
	}catch(exception &ex){
		ostringstream oss;
		oss<<"exception:" <<ex.what() <<"\n";
		printInXplnLog(oss.str().c_str());
	}

	printInXplnLog("client thread terminated\n");
	return 0;
}

json ClientThread::buildMessage(string header){
	json res;
	MessagesMap::iterator mit(mapMessages.begin()), mend(mapMessages.end());
	vector<json> datas;
	for (; mit != mend; mit++) {
		//get the next message
		AppsMessage msg = (mit->second);
		//does this dataref needs to be set (requested by a SETDATA)?
		if (msg.updateRequired){
			if (msg.dataref != NULL){
				//can it be be modified?
				if (XPLMCanWriteDataRef(msg.dataref)){
					//yes, set the data according to its type
					switch (msg.dataType){
					case  xplmType_Int:
						XPLMSetDatai(msg.dataref, msg.getIntValue());
						break;
					case xplmType_Float:
					case xplmType_Double:
						XPLMSetDataf(msg.dataref, msg.getFloatValue());
						break;
					default:
						debugPrintInXplnLog(string(msg.datarefName + " modification for this type not implemented \n").c_str());
						break;
					}
					debugPrintInXplnLog(string(msg.datarefName + " modified \n").c_str());
				}else{
					debugPrintInXplnLog(string(msg.datarefName + " not modifiable\n").c_str());
				}
				//reset the update requested flag
				mit->second.updateRequired = false;
			}
		}

		if (msg.loop || !msg.isSent()) {
			//decrease the cycle counter (how many cycles between sending)
			mit->second.count--;
			//when reach 0, time to send
			if(mit->second.count<=0){
				dataToSend = true;
				int size = 0;
				json data;
				data["ref"] = msg.datarefName;
				json value;
				//reset the counter
				mit->second.count = msg.cycle;
				//depending on the type of data
				switch (msg.dataType){
				case xplmType_Unknown :
					break;

				case  xplmType_Int:
					data["value"] = XPLMGetDatai(msg.dataref);
					break;

				case xplmType_Float:
					data["value"] = XPLMGetDataf(msg.dataref);
					break;

				case  xplmType_Double:
					data["value"] = XPLMGetDatad(msg.dataref);
					break;

				case  xplmType_FloatArray:
					size = XPLMGetDatavf(msg.dataref, NULL, 0, 0);
					if (size > 0) {
						float *array = new float[size];
						vector<json> v;
						XPLMGetDatavf(msg.dataref, array, 0, size - 1);
						for (int i=0; i < size; i++){
							json j;
							j[std::to_string(i)] = array[i];
							v.push_back( j);
						}
						data["value"]  = v;

						delete [] array;
					}
					break;

				case  xplmType_IntArray:
					size = XPLMGetDatavi(msg.dataref, NULL, 0, 0);
					if (size > 0) {
						int *array = new int[size];
						vector<json> v;
						XPLMGetDatavi(msg.dataref, array, 0, size - 1);
						for (int i=0; i < size; i++){
							json j;
							j[std::to_string(i)] = array[i];
							v.push_back( j);
						}
						data["value"]  = v;
						delete [] array;
					}
					break;

				case  xplmType_Data:
					size = XPLMGetDatab(msg.dataref, NULL, 0, 0);
					if (size > 0) {
						char *array = new char[size];
						XPLMGetDatab(msg.dataref, array, 0, size);
						data["value"]  = string(array);
						delete[] array;
					}
					break;

				default:
					data["value"] = XPLMGetDataf(msg.dataref);
				}
				//mark the message as being sent
				mit->second.setSent();
				datas.push_back(data);
			}
		}
	}
	res["data"] = datas;

	return res;
}

/**
 * remove the list of messages to be send on UDP at this address.
 */
void ClientThread::removeMessageRequestsFrom(const string address){
	debugPrintlnInXplnLog("ClientThread::removeMessageRequestsFrom");
	debugPrintlnInXplnLog(string("cleaning ("+address+")\n").c_str());
	//clean clients
	map<int, AppsMessage>::iterator msgIterator;
	for (msgIterator = mapMessages.begin(); msgIterator != mapMessages.end();){
		AppsMessage msg = (*msgIterator).second;
		debugPrintlnInXplnLog(string(" removing message"+msg.datarefName+"\n").c_str());
		mapMessages.erase(msgIterator++);
	}
}

void ClientThread::clean(){
	removeMessageRequestsFrom(address);
	printInXplnLog("client cleaned\n");
}


/**
*address is the IP address of the cient
* dataref is the string referencing a xplane dataref eg: sim/autopilot/...
* aCycle is the number of plugin main cycles between 2 data update
* aLoop is true if it is a repetitive sending, false if one shot
*/
void ClientThread::addDataToCycle(string address, string dataref, int aCycle, bool aLoop) {
	debugPrintlnInXplnLog("ClientThread::addDataToCycle\n");
	try {
		if (&dataref != NULL) {
			debugPrintlnInXplnLog(dataref.c_str());
			//create a new message object
			//address to send the message to
			//dataref point to the data reference
			AppsMessage msg(address, dataref, aCycle, aLoop);
			if (msg.isValid()) {
				int key = buildKey(address, dataref);
				if ((mapMessages)[key].dataref == NULL) {
					(mapMessages)[key] = msg;
				}
				else {
					(mapMessages)[key].sentBoolean = false; //should trigger a new send;
					(mapMessages)[key] = msg;
				}
			}
			else {
				const string answer = "invalid dataref " + dataref;
				int lenght = answer.length();
				pTcpSock->send(answer.c_str(), lenght);
			}
		}
		else {
			debugPrintlnInXplnLog(dataref.c_str());
		}
	}
	catch (SocketException& e) {
		debugPrintlnInXplnLog(e.what());
	}

}

void ClientThread::setFMSEntry(int index, string id, float lat, float lon, float altitude, int type, bool flyover){
	FmsEntry e;
	strcpy(e.id, id.c_str());
	e.lat = lat;
	e.lon = lon;
	e.altitude = altitude;
	e.tp = type;
	e.flyover = flyover;
	fmsSetEntry(index, e);
}

void ClientThread::addFMSEntry(string id, float lat, float lon, float altitude, int type, bool flyover){
	FmsEntry e;
	strcpy(e.id, id.c_str());
	e.lat = lat;
	e.lon = lon;
	e.altitude = altitude;
	e.tp = type;
	e.flyover = flyover;
	fmsAddEntry(e);
}

void ClientThread::insertFMSEntry(int before, string id, float lat, float lon, int altitude, int type, bool flyover){
	FmsEntry e;
	strcpy(e.id, id.c_str());
	e.lat = lat;
	e.lon = lon;
	e.altitude = altitude;
	e.tp = type;
	e.flyover = flyover;
	fmsInsertBeforeEntry(before, e);

}


string ClientThread::getName(){
	return name;
}

string ClientThread::getMachine(){
	return machine;
}

void ClientThread::setName(string v){
	name = v;
}

void ClientThread::setMachine(string v){
	machine = v;
}
string ClientThread::getAddress(){
	return address;
}

ClientThread::~ClientThread() {
	debugPrintlnInXplnLog("ClientThread::~ClientThread");
	clean();
	terminated = true;
	//TODO test this: pTcpSock->~Socket();
	delete pTcpSock;
	//wait for the threat to end the loop
	hThread.join();
}
