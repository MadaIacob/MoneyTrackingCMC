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


using namespace std;


CreateWalletCmd::CreateWalletCmd(){}
		


void CreateWalletCmd::parseParams(vector<string>& params) 
{
	// create command with more than two arguments /parameters
	if ( params.size() > 2)
	{
		cout << "error 1" << endl;// set error message
	}
	
}

void CreateWalletCmd::validateParams(vector<string>& params) 
{
	if ( params.size() == 3 )
	{ // validate walletName
		if ( validateFileName(params.at(0)) == false )
		{
			cout << "error 2" << endl;// set error file already exists
		}
		else {}
	}
	// create command with wallet name and amount
	else if ( params.size() == 4 )
	{
		// validate filename
		if ( validateFileName(params.at(0)) == false )
		{
			cout << "error 3" << endl;// set error file already exists
		}
		else {}
		
		// validate amount
		string str = params.at(1) ;
		const char *cstr = str.c_str() ;
		// delete [] cstr; //mai jos
		if (validateAmount( cstr ) == false )
		{
			cout << "error 4" << endl;// set error invalid amount
		}
		else {}
	}
	
}


void CreateWalletCmd::executeCommand(vector<string>& params)
{
	// set sign, category, amount ... ;
	string walletName = params.at(0) ;
	
	string amount = params.at(1) ;
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
	
	wallet = Wallet(walletName, sign, amount) ;
	
	wallet.createWalletFile() ;
	cout << "end of executeCommand" << endl;
} 









