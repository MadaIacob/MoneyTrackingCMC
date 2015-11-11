/*
File Description		Implementation of BalanceCmd class 
Author					cosmin.farcau
Date					11.11.2015
*/

#include <iostream>
#include <vector>
#include "BalanceCmd.h"
#include "HelperFunctions.h"
#include "FileHelper.h"
#include "Wallet.h"

#include "WalletEntity.h" 

#include "MessageHandler.h"
#include "MessageCodes_E.h"

using namespace std;

BalanceCmd::BalanceCmd(){}

void BalanceCmd::parseParams(vector<string>& params)
{
	// balance command with no parameters
	if ( params.empty() )
	{ 
		// do nothing, allow to get balance
	}
	// balance command with 2 parameters
	else if ( ( params.size()==2 ) &&
			  ( (params.at(0) == "-c") || (params.at(0) == "--category") ) )
	{
		// do nothing, allow to get balance
	}
	// balance command with 1 or more than 2 parameters
	else
	{
		ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
	}
} 

void BalanceCmd::validateParams(vector<string>& params)
{

	// verify default wallet in config
		
		// 'moneytracker.config' can not be created
		ptrMessage->setMessageCode(COULD_NOT_OPEN_CONFIG_ERR); 
	
		//error: no default wallet configured in 'moneytracker.config'
		ptrMessage->setMessageCode(NO_DEFAULT_WALLET_ERR);
	
	// verify that file specified as default exists
	if ( ! wallet.existsWalletFile() )
	{	
		ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_ERR) ;
	}
	else {}
	
	if ( params.size()==2 )
	{	
	// validate that specified category exists in wallet 
		if(1) // if category ( params.at(1) ) exists
		{
			// allow to get balance for category
		}
		
		else // category not found in wallet file
		{
			ptrMessage->setMessageCode(NO_TRANSACTION_REG_ERR) ;
		}
	}
	else 
	{}	
}

void BalanceCmd::executeCommand(vector<string>& params)
{
	// get balance for entire wallet
	if ( params.empty() )
	{ 
		// do stuff to get balance 
		
	}
	// get balance for category; params.size()==2
	else 	
	{
		// do stuff  
	}
	
	
}

		