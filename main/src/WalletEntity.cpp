/*
File Description		Implementation file representing WalletEntity class' 
						methods implementation
Author					madalina.iacob
Date					8.10.2015
*/

#include <string>
#include <fstream>
#include <iostream>

#include "WalletEntity.h"
#include "PrintMessage.h"

using namespace std;

//default constructor
WalletEntity::WalletEntity()
{
	
}

//creates a wallet by making a new file with a given name and a given amount
//if amount is not specified then it is by default 00.00
void WalletEntity::createWallet(const string walletName,const string initialAmount )
{
	//keep stream's state
	bool checkStream = false; 
	
	//creates the file for writing with the given name
	ofstream outFile(walletName.c_str());
	
	//take stream's state before writing
	//will be true if none of the stream's error state flag is set
	checkStream = outFile.good();

	if(checkStream == true)
	{
		//writes into the new file the initial amount
		outFile << initialAmount << " " << "RON";
		
		//take stream's state after writing
		checkStream = outFile.good();
		if(checkStream != true)
		{
			printMessage(3);
		} 
		else 
		{
		}		
	} 
	else 
	{
		printMessage(3);
	}		
	
	//closes the file
	outFile.close();
}
