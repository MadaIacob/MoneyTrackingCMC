/*
File Description		command - abstract general description 
Author					madalina.iacob, sas.catalin.raul, calin-ciprian.popita
Date					09.11.2015
*/ 

#ifndef COMMAND_H
#define COMMAND_H


#include "MessageHandler.h"
#include <vector>
#include <string>

class Command {
	public:
		MessageHandler* ptrMessage;
	public:
		Command();
		virtual void parseParams(std::vector<std::string>& params);
		virtual void validateParams(std::vector<std::string>& params);
		void setMessageHandler(MessageHandler& message);
		virtual void executeCommand(std::vector<std::string>& params);
		virtual ~Command();

		
	protected:
		void setMessageCode(MessageCodes_E messageCode);		
};

#endif // COMMAND_H