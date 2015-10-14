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
void WalletEntity::createWallet(
	const string walletName,
	const string initialAmount )
{
	//stream's state
	bool checkStream = false; 
	
	//create walletName file  
	ofstream outFile(walletName.c_str());
	
	//check if walletName file was created
	//will be true if none of the stream's error state flag is set
	checkStream = outFile.good();

	if(checkStream)
	{
		//write initialAmount into walletName file
		outFile << initialAmount << " " << "RON\n";
		
		//check if the writing was ok
		checkStream = outFile.good();
		if(!checkStream)
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
	{
		//print "error: characters  < > : \" / \\ | ? *  are not allowed for naming files!"
		printMessage(3);
	}		
	
	//closes the file
	outFile.close();
}
