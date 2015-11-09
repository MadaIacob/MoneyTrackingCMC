/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "../inc/CommandFactory.h"
#include "../inc/Command.h"
#include <string>

Command* CommandFactory::makeCommand(const std::string& command) 
{
	if ("create" == command) 
	{
		ptrCmd = new CreateWallet();
	}
	else if ("income" == command) 
	{
		//ptrCmd = new Transaction(command);
	}
	else if ("spend" == command) 
	{
		//ptrCmd = new Transaction(command);
	}
	else if ("balance" == command) 
	{
		//ptrCmd = new Balance();
	}
	else if ("config" == command) 
	{
		//ptrCmd = new Config();
	}
	else 
	{}
	
	return ptrCmd;
}

CommandFactory::~CommandFactory() 
{
	delete ptrCmd;
	ptrCmd = 0;
}
