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
	private:
		MessageHandler* ptrMessage;
	public:
		Command();
		virtual void parseParams(std::vector<std::string> params) = 0;
		virtual void validateParams(std::vector<std::string> &params) = 0;
		void setMessageHandler(MessageHandler& message);
		virtual void executeCommand() = 0;
		virtual ~Command();

		
	protected:
		void setMessageCode(MessageCodes_E messageCode);		
};

#endif // COMMAND_H