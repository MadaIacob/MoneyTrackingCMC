/*
File Description		command - abstract general description
Author					madalina.iacob, sas.catalin.raul, calin-ciprian.popita
Date					09.11.2015
*/

#ifndef COMMAND_H
#define COMMAND_H

#include "MessageCodes_E.h"
#include "MessageHandler.h"
#include <vector>
#include <string>

class Command {
	protected:
		MessageHandler* ptrMessage;
	public:
		Command();
		virtual bool parseParams(std::vector<std::string>& params) = 0;
		virtual bool validateParams(std::vector<std::string>& params) = 0;
		void setMessageHandler(MessageHandler& message);
		virtual bool executeCommand(std::vector<std::string>& params) = 0;
		MessageHandler& getPtrMessage();
		virtual ~Command();


	protected:
		void setMessageCode(MessageCodes_E messageCode);
};

#endif // COMMAND_H
