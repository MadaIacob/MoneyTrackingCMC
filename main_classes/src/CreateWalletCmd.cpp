/*
File Description		Implementation of WalletCreateCmd class 
Author					cosmin.farcau
Date					09.11.2015
*/

#include "WalletCreateCmd.h"



// CreateWalletCmd::CreateWalletCmd(){}
		


void CreateWalletCmd::parseParams(vector<string> params) 
{
	// create command with more than two arguments /parameters
	if ( params.size() > 2)
	{
		// set error message
	}
	
}

void CreateWalletCmd::validateParams(vector<string> & params) 
{
	if ( params.size() == 3 )
	{ // validate walletName
		if ( validateFileName(params.at(0)) == false )
		{
			// set error file already exists
		}
		else {}
	}
	// create command with wallet name and amount
	else if ( params.size() == 4 )
	{
		// validate filename
		if ( validateFileName(params.at(0)) == false )
		{
			// set error file already exists
		}
		else {}
		
		// validate amount
		if (validateAmount( params.at(1) ) == false )
		{
			// set error invalid amount
		}
		else {}
	}
	
}


void CreateWalletCmd::executeCommand()
{
	// set sign, category, amount ... ;
	string walletName = params.at(0) ;
	
	string amount = params.at(1) ;
	
	string sign = "" ;
	if (amount.at(0) == "+")
	{
		sign = "+" ;
	}
	else
	{
		sign = "-" ;
	}
	
	wallet = Wallet(walletName, sign, amount) ;
	
	wallet.createWalletFile() ;
	
} 









