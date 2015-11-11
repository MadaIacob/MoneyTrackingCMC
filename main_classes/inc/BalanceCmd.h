/*
File Description		Balance class
Author					cosmin.farcau
						
Date					11.11.2015
*/ 
#ifndef BALANCE_CMD_H
#define BALANCE_CMD_H
#include "Wallet.h"
#include "Command.h"
#include <vector>
#include <string>

class BalanceCmd : public Command {
	private:
		Wallet wallet;// wallet from which to get balance
	public:
		BalanceCmd();
		//methods from Command class
		void parseParams(std::vector<std::string>& params);
		void validateParams(std::vector<std::string>& params);
		void executeCommand(std::vector<std::string>& params);
};

#endif 