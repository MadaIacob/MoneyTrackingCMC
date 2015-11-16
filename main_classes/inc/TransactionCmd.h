/*
File Description		transaction class - validates/executes "income"/"spend"
Author					calin-ciprian.popita

Date					10.11.2015
*/
#ifndef TRANSACTIONCMD_H
#define TRANSACTIONCMD_H
#include "Wallet.h"
#include "WalletEntity.h"
#include "Command.h"
#include "TransactionType.h"
#include <vector>
#include <string>

class TransactionCmd : public Command {
	private:
		Wallet wallet;// wallet to execute transaction in
		WalletEntity walletEntity;// new line to append to wallet
	public:
		TransactionCmd(Transaction_E transaction);
		//methods from Command class
		bool parseParams(std::vector<std::string>& params);
		bool validateParams(std::vector<std::string>& params);
		bool executeCommand(std::vector<std::string>& params);
};

#endif //TRANSACTIONCMD_H
