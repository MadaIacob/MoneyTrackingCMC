/*
File Description		Implementation of WalletCreateCmd class 
Author					cosmin.farcau
Date					09.11.2015
*/

#include <iostream>
#include <vector>
#include "CreateWalletCmd.h"
#include "HelperFunctions.h"
#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "MessageCodes_E.h"


using namespace std;


CreateWalletCmd::CreateWalletCmd(){}
		


void CreateWalletCmd::parseParams(vector<string>& params) 
{
	// create command with more than two arguments /parameters
	if ( !params.empty() )
	{
		if ( params.size() > 2)
		{
			ptrMessage->setMessageCode(INVALID_COM_ERR) ;
		}
		else {}
	}
	else 
	{
		ptrMessage->setMessageCode(FILENAME_NOT_SPEC_ERR) ;
	}
}

void CreateWalletCmd::validateParams(vector<string>& params) 
{
	if ( params.size() == 1 )
	{ // validate walletName
		if ( validateFileName(params.at(0)) == false )
		{
			ptrMessage->setMessageCode(WALLET_EXISTS_ERR) ;
		}
		else 
		{
			
		}
	}
	// create command with wallet name and amount
	else if ( params.size() == 2 )
	{
		// validate filename
		if ( validateFileName(params.at(0)) == false )
		{
			ptrMessage->setMessageCode(WALLET_EXISTS_ERR) ;
		}
		else {}
		
		// validate amount
		string str = params.at(1) ;
		const char *amnt = str.c_str() ;
		// delete [] cstr; //mai jos
		if (validateAmount( amnt ) == false )
		{
			ptrMessage->setMessageCode(INVALID_AMOUNT_ERR) ;
		}
		else {}
	}
	
}


void CreateWalletCmd::executeCommand(vector<string>& params)
{
	// set sign, category, amount ... ;
	string walletName = params.at(0) ;
	string amount = "" ;
	if ( params.size() == 2 )
	{
		amount = params.at(1) ;
	}
	else
	{
		amount = "0" ;
	}
	
	char s = amount.at(0) ;
	string sign = "" ;
	if (s == '+')
	{
		sign = "+" ;
	}
	else
	{
		sign = "-" ;
	}
	
	WalletEntity entity(sign, amount);
	wallet = Wallet(walletName,entity);
	
	wallet.createWalletFile() ;
	
	ptrMessage->setMessageCode(WALLET_CRETED_MSG) ;
} 

CreateWalletCmd::~CreateWalletCmd()
{
	
}







