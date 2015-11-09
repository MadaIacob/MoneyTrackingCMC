//============================================================================
// Name        : Wallet.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Implementation for class Wallet, in C++
//============================================================================

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "Wallet.h"
using namespace std;
Wallet::Wallet(const string walletName, 
				const string sign, 
				const string amount, 
				const string currency)
{
	Wallet::walletName = walletName;
	WalletEntity walletEntity(sign, amount, currency);
	walletContent.push_back(walletEntity);
}

bool Wallet::readWalletFile()
{
	ifstream file(walletName.c_str());
	bool readFile = false;
	string line = "";
	while(getline(file,line))
		{
			WalletEntity walletEntity;
			walletEntity = getWalletEntityFromLine(line);
			walletContent.push_back(walletEntity);
			readFile = true;
		}
	file.close();
	return readFile;
}
bool Wallet::createWalletFile()
{
	return true;
}
bool Wallet::appendWalletFile()
{
	return true;
}
bool Wallet::existsWalletFile()
{
	ifstream f(walletName.c_str());
	if (f.good()) {
		f.close();
		return true;
	}
	f.close();
	return false;
}

WalletEntity Wallet::getWalletEntityFromLine(const string line)
{
	
	vector <string> data;
	WalletEntity returnWalletEntity;
	//if not the first line in wallet file
	if((line[0] != '-') && (line[0] != '+'))
	{//a wallet file line different than the first
		istringstream ss(line);
		//iterates trough the string and separates it by the character ";" 
		//	and pushes every element into a vector  
		while(ss)
		{
			string parameter;
			if(!getline(ss,parameter,';')) break;
			data.push_back(parameter);
		}	
		//convert the amount from string to double
			WalletEntity walletEntity(data.at(0), data.at(1), data.at(2), data.at(3));
			returnWalletEntity = walletEntity;
	}
	else
	{//first line in a wallet file (initial amount only)
		
		
	}
	//return a walletEntity object
	return returnWalletEntity;
}
vector<WalletEntity> Wallet::getWalletContent()
{
	return walletContent;
}

/* int main () 
{
	WalletEntity walletEntity("+", "20.0", "other", "RON");
	//WalletEntity walletEntity("+", "200", "EUR");
	cout<<"walletEntity.timeStamp = "<<walletEntity.getTimeStamp()<<endl;
	cout<<"walletEntity.sign = "<<walletEntity.getSign()<<endl;
	cout<<"walletEntity.amount = "<<walletEntity.getAmount()<<endl;
	cout<<"walletEntity.category = "<<walletEntity.getCategory()<<endl;
	cout<<"walletEntity.currency = "<<walletEntity.getCurrency()<<endl;
	Wallet wallet("ceapa", "+", "50.23", "EUROI");
	cout<<"the amount is : "<<wallet.getWalletContent().at(0).getAmount()<<endl;
	
} */

