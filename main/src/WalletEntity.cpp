/*
File Description		Implementation file representing WalletEntity class' 
						methods implementation
Author					madalina.iacob
Date					8.10.2015
*/

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>
#include <stdlib.h>

#include "WalletEntity.h"
#include "PrintMessage.h"

using namespace std;

//default constructor
WalletEntity::WalletEntity()
{	
	//no implementation
}

//connstructor. Creates WalletEntity object
WalletEntity::WalletEntity(
	const time_t timeEntity,
	const string signEntity,
	const string amountEntity,
	const string categoryEntity,
	const string currencyEntity):
		timeEntity(timeEntity),
		signEntity(signEntity),
		amountEntity(amountEntity),
		categoryEntity(categoryEntity),
		currencyEntity(currencyEntity)
{
}

//creates a wallet by making a new file with a given name and a given amount
//if amount is not specified then it is by default 00.00
void WalletEntity::createWallet(
	const string walletName,
	const string initialAmount )
{
	//create walletName file  
	ofstream outFile(walletName.c_str());
	
	//check if walletName file was created
	if(outFile.good())
	{//true if none of the stream's error state flag is set - wallet created
		
		//write initialAmount into walletName file
		outFile << initialAmount << " " << "RON\n";
		
		//check if the writing was ok
		if(!outFile.good())
		{
			//if writing was not ok, print " writing file error! "
			printMessage(5);
		} 
		else 
		{
			//if writing was ok, print wallet created message
			printMessage(6, walletName, initialAmount);
		}		
	} 
	else 
	{//false if none of the stream's error state flag is set - wallet not created

		//print "error: could not create C:\path\mywallet"
		printMessage(3, walletName);
	}		
	
	//closes the file
	outFile.close();
}

//adds new wallet entity
bool WalletEntity::addWalletEntity(const string walletName)
{
	bool isAdded = false;
	
	string newLine; //new entity content
	string timeEntityString; // time converted to string
	
	//convert from time_t to string
	std::stringstream ss;
	ss << timeEntity;
	timeEntityString = ss.str();
		
	//open walletName for reading
	ofstream wallet(walletName.c_str(),ios::app);
	
	//check if file/wallet was open
	if(wallet.good())
	{// file open ok

		//compose new line for the file/wallet
		newLine = timeEntityString + ";" +
			  signEntity + ";" +
			  amountEntity + ";" +
			  categoryEntity + ";" +
			  currencyEntity + "\n";
	
		//add the new line to the file/wallet
		wallet << newLine;
		
		//check if new line was added
		if(wallet.good())
		{//append ok
			isAdded = true;
		}
		else
		{//append not ok
		}
		
		wallet.close();
	}
	else
	{// file open not ok
	}
	
	return isAdded;
}


