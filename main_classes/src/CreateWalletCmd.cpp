/*
File Description		Implementation of WalletCreateCmd class 
Author					cosmin.farcau
Date					09.11.2015
*/

#include "WalletCreateCmd.h"



CreateWalletCmd::CreateWalletCmd(string walletName, string sign, string amount):
		wallet()
{
	
	
}

void CreateWalletCmd::parseParams(vector<string> params) 
{

	// create command with only wallet name
	if ( params.size() == 3 )
	{
		walletName = params.at(2) ;
	//	amount = 0 ;
	}
	// create command with wallet name and amount
	else if ( params.size() == 4 )
	{
		walletName = params.at(2) ;
		amount = params.at(3) ;
	}
	// create with three arguments or more
	else
	{
		// set error message
	}
	
}

void CreateWalletCmd::validateParams(vector<string> & params) 
{
	if ( params.size() == 3 )
	{ // validate walletName = params.at(2) ;
	
	}
	// create command with wallet name and amount
	else if ( params.size() == 4 )
	{// validate walletName = params.at(2) ;
		// validate amount = params.at(3) ;
	}
	
}


void CreateWalletCmd::executeCommand()
{
	
} 


class CreateWalletCmd : public Command 
{
	private:
		Wallet wallet;
	public:
		CreateWallet(string walletName, double amount);
		//methods from Command class
		void parseParams(vector<string> params) ;
		void validateParams(vector<string> &params) ;
		void executeCommand() ;
}







