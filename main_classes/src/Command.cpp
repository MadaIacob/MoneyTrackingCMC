/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "Command.h"
#include "MessageCodes_E.h"
#include "MessageHandler.h"

//associates a message object to the command
void setMessageHandler(MessageHandler& message)
{
	ptrMessage = message;
};

//sets the message code for the message object
void setMessageCode(MessageCodes_E messageCode)
{
	ptrMessage->setMessage(messageCode);

};
