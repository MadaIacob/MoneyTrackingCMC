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

BalanceCmd::BalanceCmd(string configFileName) : configFile(configFileName) {}

bool BalanceCmd::parseParams(vector<string>& params)
{
	// balance command with no parameters
	if ( params.empty() )
	{
		// do nothing, allow to get balance
	}
	// balance command with 2 parameters
	else if ( ( params.size()==2 ) &&
			  ( (params.at(0) == "-c") || (params.at(0) == "--category")
			  || (params.at(0) == "-w") || (params.at(0) == "--wallet") ) )
	{
		// do nothing, allow to get balance
	}
	// balance command with 4 parameters
	else if ( ( params.size()==4 ) &&
			  ( ( ((params.at(0) == "-c") || (params.at(0) == "--category"))
			    && ((params.at(2) == "-w") || (params.at(2) == "--wallet")) )
			   ||
			  ( ((params.at(0)=="-w") || (params.at(0)=="--wallet"))
			    && ((params.at(2)=="-c") || (params.at(2)=="--category")) )	)
			)
	{
		// do nothing, allow to get balance
	}
	// balance command with 1 or more than 2 parameters
	else
	{
		params.clear();
		params.push_back("balance");
		ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
		return false ;
	}
	return true;
}

bool BalanceCmd::validateParams(vector<string>& params)
{

	// verify if 'moneytracker.config' can be opened to get default_wallet
	if	( !configFile.readConfigFile() && ( params.empty() ||
			( params.size()==2 && ( params.at(0) == "-c" || params.at(0) == "--category" )))
		)
	{
			params.clear();
			params.push_back(configFile.getConfigFileName()) ;
			ptrMessage->setMessageCode(COULD_NOT_OPEN_CONFIG_ERR) ;
			return false ;
	}
	else{} //in all other cases wallet is specified by the user

	//error: no default wallet configured in 'moneytracker.config'
	if ( configFile.getTagValue("default_wallet") == "" && ( params.empty() ||
				( params.size()==2 && ( params.at(0) == "-c" || params.at(0) == "--category" )))
		)
	{
			params.clear();
			params.push_back("moneytracker.config") ;
			ptrMessage->setMessageCode(NO_DEFAULT_WALLET_ERR) ;
			return false ;
	}
	else {} // in all other cases the default wallet is not needed

	// get name of default wallet
	configFile.readConfigFile() ;
	string defaultWallet = configFile.getTagValue ("default_wallet") ;
	string categForBalance = "" ;

	// set walletName and category according to case: command with -w/-c or no
	if( params.size()==2 )
	{
		if( params.at(0)=="-c" || params.at(0)=="--category" )
		{
			wallet.setName(defaultWallet) ;
			categForBalance = params.at(1) ;
			}
		else //else is the case with params.at(0)== "-w"
		{
			wallet.setName(params.at(1)) ;
		}
	}
	else if ( params.size()==4 )
	{
		if( params.at(0)=="-c" || params.at(0)=="--category")
		{
			categForBalance = params.at(1) ;
			wallet.setName(params.at(3)) ;
		}
		else // this is the case with params.at(0)=="-w"
		{
			categForBalance = params.at(3) ;
			wallet.setName(params.at(1)) ;
		}
	}
	else // case with params.empty
	{
		wallet.setName(defaultWallet) ;
	}
	// verify that file specified as wallet for use exists
	if ( !wallet.existsWalletFile() )
	{
			params.clear();
			params.push_back(wallet.getName()) ;
			ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_BAL_ERR) ;
			return false ;
	}
	else {}

	wallet.readWalletFile() ;

	if ( params.size()==2 || params.size()==4 )
	{

		// validate that specified category exists in wallet
		bool existsCategory = false ;
		// len = length of walletContent = number of lines in wallet
		int len = wallet.getWalletContent().size() ;
		for( int i=0; i < len ; i++ )
		{
			if( categForBalance == wallet.getWalletContent().at(i).getCategory() )
			{
				// allow to get balance for category
				existsCategory = true ;
				break ;
			}
			else {}// category not found in wallet file line
		}

		//  check if existsCategory was changed to true
		if(existsCategory == false)
		{	// set error message
			params.at(0)= wallet.getName() ;
			params.at(1)= categForBalance ;
			ptrMessage->setMessageCode(NO_TRANSACTION_REG_ERR) ;
			return false ;
		}
		else{}
	}
	else // case with params.empty()
	{}

	return true;
}

bool BalanceCmd::executeCommand(vector<string>& params)
{
	// set category for balance
	string categForBalance = "" ;
	if( params.size()==2 && ( params.at(0) == "-c" ||
		   params.at(0) == "--category" )
	  )
	{
		categForBalance = params.at(1) ;
	}
	else if ( params.size()==4 )
	{
		if( params.at(0)=="-c" || params.at(0)=="--category")
		{
			categForBalance = params.at(1) ;
		}
		else // this is the case with params.at(0)=="-w"
		{
			categForBalance = params.at(3) ;
		}
	}
	else{}

	double balance = 0 ;
	int len = wallet.getWalletContent().size() ;
	// get balance for entire wallet for params.empty and size=2 with '-w'
	if ( params.empty() ||
		 ( params.size()==2 && ( params.at(0) == "-w" ||
		   params.at(0) == "--wallet" )
		 )
	   )
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
			if( categForBalance == wallet.getWalletContent().at(i).getCategory() )
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

	// truncate amount to add + to positive balance
	balanceString = truncateAmount(balanceString) ;

	// prepare vector for printing function
	if ( params.empty() ||
		 ( params.size()==2 && ( params.at(0) == "-w" ||
		   params.at(0) == "--wallet" )
		 )
	   )
	{
		params.clear() ;
		params.push_back(balanceString) ;
		params.push_back("RON") ;
		params.push_back(wallet.getName()) ;
	}
	else // 2 params with -c or 4 params
	{

		params.clear() ;
		params.push_back(balanceString) ;
		params.push_back("RON") ;
		params.push_back(wallet.getName()) ;
		params.push_back(categForBalance) ;
	}

	ptrMessage->setMessageCode(BALANCE_IS_MSG) ;

	return true;
}
