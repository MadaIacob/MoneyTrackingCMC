/*
File Description		Balance class
Author					cosmin.farcau
						
Date					11.11.2015
*/ 
#ifndef BALANCE_CMD_H
#define BALANCE_CMD_H
#include "Wallet.h"
#include "Command.h"
#include "Config.h"
#include <vector>
#include <string>

class BalanceCmd : public Command {
	private:
		Wallet wallet;// wallet from which to get balance
		Config configFile ;
	public:
		BalanceCmd();
		BalanceCmd(std::string configFileName) ;
		//methods from Command class
		bool parseParams(std::vector<std::string>& params);
		bool validateParams(std::vector<std::string>& params);
		bool executeCommand(std::vector<std::string>& params);
};

#endif 