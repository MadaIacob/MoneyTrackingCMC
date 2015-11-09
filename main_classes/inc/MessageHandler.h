#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#include "MessageCodes_E.h"
#include <vector>
#include <string>

class MessageHandler {
	private:
		MessageCodes_E messageCode;
	
	public:
		MessageHandler();
		void setMessageCode(MessageCodes_E messageCode);
		bool isSetMessageCode();
		void printMessage(std::vector<std::string> parameters);
		MessageCodes_E getMessageCode();
		
};

#endif