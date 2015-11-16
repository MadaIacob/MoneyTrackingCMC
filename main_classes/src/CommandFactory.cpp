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
	else if ("income" == command)
	{
		//the Command object needed is a Transaction object
		//Transaction_E transaction = INCOME;
		ptrCmd = new TransactionCmd(INCOME);
	}
	else if ("spend" == command)
	{
		//the Command object needed is a Transaction object
		//Transaction_E transaction = SPEND;
		ptrCmd = new TransactionCmd(SPEND);
	}
	//"balance" command
	else if ("balance" == command)
	{
		//the Command object needed is a BalanceCmd object
		ptrCmd = new BalanceCmd() ;
	}
	//"config" command
	else if ("config" == command)
	{
		//the Command object needed is a Config object
		ptrCmd = new ConfigCmd();
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
