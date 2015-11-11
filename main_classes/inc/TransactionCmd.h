/*
File Description		transaction class - validates/executes "income"/"spend"
Author					calin-ciprian.popita
						
Date					10.11.2015
*/ 
#ifndef TRANSACTIONCMD_H
#define TRANSACTIONCMD_H
#include "Wallet.h"
#include "Command.h"
#include <vector>
#include <string>

class TransactionCmd : public Command {
	private:
		Wallet wallet;// wallet to execute transaction in
		WalletEntity walletEntity;// new line to append to wallet
	public:
		TransactionCmd(const std::string& command);
		//methods from Command class
		void parseParams(std::vector<std::string>& params);
		void validateParams(std::vector<std::string>& params);
		void executeCommand(std::vector<std::string>& params);
};

#endif //TRANSACTIONCMD_H