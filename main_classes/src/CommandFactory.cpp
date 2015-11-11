/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "CommandFactory.h"
#include "Command.h"
#include <string>

//creates the right command object for a given argument
Command* CommandFactory::makeCommand(const std::string& command) 
{
	//"create" command
	if ("create" == command) 
	{
		//the Command object needed is a CreateWallet object
		//CreateWalletCmd aux = CreateWalletCmd();
		ptrCmd = new CreateWalletCmd();
		//ptrCmd = &aux;
	}
	//"income" or "spend" command
	else if (("income" == command) || ("spend" == command))
	{
		//the Command object needed is a Transaction object
		ptrCmd = new TransactionCmd(command);
	}
	//"balance" command
	else if ("balance" == command) 
	{
		//the Command object needed is a Balance object
		//ptrCmd = new Balance();
	}
	//"config" command
	else if ("config" == command) 
	{
		//the Command object needed is a Config object
		//ptrCmd = new Config();
	}
	else 
	{}
	
	return ptrCmd;
}


CommandFactory::~CommandFactory() 
{
	//destroy the Command object
	delete ptrCmd;
	ptrCmd = 0;
}
