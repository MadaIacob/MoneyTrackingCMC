/*
File Description		Implementation of BalanceCmd class 
Author					cosmin.farcau
Date					11.11.2015
*/

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <sstream>
#include "BalanceCmd.h"
#include "HelperFunctions.h"
#include "FileHelper.h"
#include "Wallet.h"
#include "Config.h"

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
	Config configFile;
	// verify default wallet in config
	// 'moneytracker.config' can not be opened
	if( !configFile.readConfigFile() )
	{
		ptrMessage->setMessageCode(COULD_NOT_OPEN_CONFIG_ERR)  ;
	}
	else{}
	
	//error: no default wallet configured in 'moneytracker.config'
	if( !configFile.existsTag("default_wallet") )
	{
		ptrMessage->setMessageCode(NO_DEFAULT_WALLET_ERR) ;
	}
	else {}
	
	// get name of default wallet
	configFile.readConfigFile() ;
	string defaultWallet = configFile.getTagValue ("default_wallet") ;
	
	//set walletName with value from config file
	wallet.setName(defaultWallet) ; 
	
	// verify that file specified as default exists
	if ( ! wallet.existsWalletFile() )
	{	
		ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_ERR) ;
	}
	else {}
	
	if ( params.size()==2 )
	{	
	
	// validate that specified category exists in wallet 
		bool existsCategory = false ;
		wallet.readWalletFile() ;
		// len - length of walletContent = number of lines in wallet
		int len = wallet.getWalletContent().size() ;
		for( int i=0; i < len ; i++ )
		{
			if( params.at(1) == wallet.getWalletContent().at(i).getCategory() )
			{
				// allow to get balance for category
				existsCategory = true ;
				break ;
			}
		
			else {}// category not found in wallet file line
		}
		//  check if existsCategory was changed to true
		if(existsCategory == false)
		{
			ptrMessage->setMessageCode(NO_TRANSACTION_REG_ERR) ;
		}
		else{}
	}
	else {}	
}

void BalanceCmd::executeCommand(vector<string>& params)
{
	// get balance for entire wallet
	double balance = 0 ;
	int len = wallet.getWalletContent().size() ;
	
	if ( params.empty() )
	{ 
		// do stuff to get balance 
		for( int i=0; i < len ; i++ )
		{
			string amnt = wallet.getWalletContent().at(i).getAmount() ;
			double amont = atof(amnt.c_str()) ;
			if( "-" == wallet.getWalletContent().at(i).getSign() )
			{
				balance = balance - amont ;
			}
			else
			{
				balance = balance + amont ;
			}
		}
	}
	// get balance for category; params.size()==2
	else 	
	{
		// do stuff  
		for( int i=0; i < len ; i++ )
		{
			if( params.at(1) == wallet.getWalletContent().at(i).getCategory() )
			{
				string amnt = wallet.getWalletContent().at(i).getAmount() ;
				double amont = atof(amnt.c_str()) ;
				if( "-" == wallet.getWalletContent().at(i).getSign() )
				{
					balance = balance - amont ;
				}
				else
				{
					balance = balance + amont ;
				}
			}
		
			else {}// category not found in wallet file line
		}
	}
	//convert double to string
	string balanceString;
	ostringstream sstream;
	sstream <<  balance;
	balanceString = sstream.str();
	if ( params.empty() )
	{
		params.push_back(balanceString) ;
		params.push_back("RON") ;
		params.push_back(wallet.getName()) ;
	}
	else
	{	
		string tempCategory = params.at(1) ;
		params.at(0) = balanceString ;
		params.at(1) = "RON" ;
		params.push_back(wallet.getName()) ;
		params.push_back(tempCategory) ;
	}
	ptrMessage->setMessageCode(BALANCE_IS_MSG) ;
}








