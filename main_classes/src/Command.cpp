/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/

#include "Command.h"

Command::Command()
{

}

//syntax analysis of parameters given to any command
//implemented in every command class (CreateCmd, TransactionCmd etc.)
bool Command::parseParams(std::vector<std::string>& params)
{//dummy implementation to avoid warnings
	return true;
}

//value analysis for parameters given to any command
//implemented in every command class (CreateCmd, TransactionCmd etc.)
bool Command::validateParams(std::vector<std::string>& params)
{//dummy implementation to avoid warnings
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

//the execution of any command
//implemented in every command class (CreateCmd, TransactionCmd etc.)
bool Command::executeCommand(std::vector<std::string>& params)
{//dummy implementation to avoid warnings
	return true;
}

MessageHandler Command::getPtrMessage()
{
	return *ptrMessage;
}

Command::~Command()
{
	delete ptrMessage;
	ptrMessage = 0;
}
