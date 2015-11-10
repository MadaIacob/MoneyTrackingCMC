/*
File Description		wallet creator class - validates/executes "create" 
Author					madalina.iacob, sas.catalin.raul, calin-ciprian.popita
						cosmin.farcau
Date					09.11.2015
*/ 
#ifndef CREATEWALLETCMD_H
#define CREATEWALLETCMD_H
#include "Wallet.h"
#include "Command.h"
#include <vector>
#include <string>

class CreateWalletCmd : public Command {
	private:
		Wallet wallet;
	public:
		CreateWalletCmd();
		//methods from Command class
		void parseParams(std::vector<std::string> params) ;
		void validateParams(std::vector<std::string> &params) ;
		void executeCommand(std::vector<std::string> &params) ;
};

#endif //CREATEWALLETCMD_H
