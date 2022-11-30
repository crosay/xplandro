/*
 * clientThread.hpp
 *
 *  Created on: 14 mars 2016
 *      Author: cyrille
 */

#ifndef SRC_CLIENTTHREAD_HPP_
#define SRC_CLIENTTHREAD_HPP_

#if LIN
typedef unsigned int DWORD;
#endif
#include <string>
#ifdef __MINGW-64__
#include <pthreads.h>
#else
#include <thread>
#endif
#include <map>
#include "version.hpp"
#include "PracticalSocket.hpp"
#include "AppsMessage.hpp"
#include "json.hpp"
typedef map<int, AppsMessage> MessagesMap;
using json = nlohmann::json;

class ClientThread {
private:
	string name;
	string machine;
	string address;
	TCPSocket *pTcpSock = NULL;
	int libVersion = 1;
	thread hThread;
	bool terminated = false;
	bool dataToSend = false;
	//stores the list of messages to pass during the next xpl iteration
	MessagesMap mapMessages;

	void addDataToCycle(string address, string dataref, int aCycle, bool aLoop);
	void setFMSEntry(int index, string id, float lat, float lon, float altitude, int type, bool flyover);
	void addFMSEntry(string id, float lat, float lon, float altitude, int type, bool flyover);
	void insertFMSEntry(int before, string id, float lat, float lon, int altitude, int type, bool flyover);

	void removeMessageRequestsFrom(const string address);
public:	ClientThread() : hThread(){}
	ClientThread(TCPSocket *tcps);
	~ClientThread();
	DWORD run();
	void clean(void);
	string getName();
	string getMachine();
	void setName(string v);
	void setMachine(string v);
	string getAddress();
	json buildMessage(string header);
	bool isTerminated(){return terminated;}
	bool hasDataToSend(){return dataToSend;}
	void clearDataToSend(){dataToSend=false;}
	void sendData(string msg){if (pTcpSock != NULL) pTcpSock->send(msg.c_str() , msg.length());}
};

#endif /* SRC_CLIENTTHREAD_HPP_ */
