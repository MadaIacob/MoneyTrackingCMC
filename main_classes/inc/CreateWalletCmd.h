/*
File Description		wallet creator class - validates/executes "create" 
Author					madalina.iacob, sas.catalin.raul, calin-ciprian.popita
Date					09.11.2015
*/ 
#ifndef CREATEWALLET_H
#define CREATEWALLET_H
#include "Wallet.h"
#include <vector>
#include <string>

class CreateWallet : public Command {
	private:
		Wallet wallet;
	public:
		CreateWallet();
		//methods from Command class
		void parseParams(std::vector<std::string> params) ;
		void validateParams(std::vector<std::string> &params) ;
		void executeCommand() ;
};

#endif //CREATEWALLET_H