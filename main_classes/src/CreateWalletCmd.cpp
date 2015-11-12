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
		else {
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
		else {
		}
		// validate amount
		string str = params.at(1) ;
		const char *amnt = str.c_str() ;
		// delete [] cstr; //mai jos
		if (validateAmount( amnt ) == false )
		{
			ptrMessage->setMessageCode(INVALID_AMOUNT_ERR) ;
		}
		else {
		}
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
		amount = "00.00" ;
	}

	const char *amn = amount.c_str() ;
	amount = truncateAmount(amn) ; //could modify this function to take string
	// set sign according to amount
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
	// cut + or - from amount
	string validAmount (amount) ;
	amount = cutSign(validAmount) ;
	//create line object in wallet file
	WalletEntity entity(sign, amount);
	//initialize wallet
	wallet = Wallet(walletName,entity);

// problema cand un folder are space in nume !?
	//create wallet and check if creation worked
	if (wallet.createWalletFile())
	{
		if (params.size() == 2 )
		{
			params.pop_back() ;
		}
		else {}
		// set members in params, to use for print in main
		params.push_back(entity.getSign()) ;
		params.push_back(entity.getAmount()) ;
		params.push_back(entity.getCurrency()) ;

		ptrMessage->setMessageCode(WALLET_CRETED_MSG) ;
	}
	else
	{
		ptrMessage->setMessageCode(COULD_NOT_CREATE_ERR) ;
	}
}

CreateWalletCmd::~CreateWalletCmd()
{

}
