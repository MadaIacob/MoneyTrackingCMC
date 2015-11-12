/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/

#include "Command.h"

Command::Command()
{

}

bool Command::parseParams(std::vector<std::string>& params)
{
	return true;
}

bool Command::validateParams(std::vector<std::string>& params)
{
	return true;
}

//associates a message object to the command
void Command::setMessageHandler(MessageHandler& message)
{
	ptrMessage = &message;
}

//sets the message code for the message object
void Command::setMessageCode(MessageCodes_E messageCode)
{
	ptrMessage->setMessageCode(messageCode);

}

bool Command::executeCommand(std::vector<std::string>& params)
{
	return true;
}

MessageCodes_E Command::getPtrMessage()
{
	return ptrMessage;
}

Command::~Command()
{
	delete ptrMessage;
	ptrMessage = 0;
}
