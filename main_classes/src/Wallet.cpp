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

std::string Wallet::getName()
{
	return walletName;
}

bool Wallet::readWalletFile()
{
	ifstream file(walletName.c_str());
	bool fileOperation = false;
	string line = "";
	while(getline(file,line))
		{
			WalletEntity walletEntity;
			walletEntity = getWalletEntityFromLine(line);
			walletContent.push_back(walletEntity);
			fileOperation = true;
		}
	file.close();
	return fileOperation;
}
bool Wallet::createWalletFile()
{
		//create walletName file  
	ofstream file(walletName.c_str());
	bool fileOperation = false;
	//check if walletName file was created
	if(file.good())
	{//true if none of the stream's error state flag is set - wallet created
		
		//write initialAmount into walletName file
		file << walletContent.at(0).getSign() << walletContent.at(0).getAmount()
				<< " " << walletContent.at(0).getCurrency() << "\n";
		
		//check if the writing was ok
		if(!file.good())
		{
			//if writing was not ok, print " writing file error! "
			//printMessage(5);
		} 
		else 
		{
			fileOperation = true;
			//if writing was ok, print wallet created message
			//printMessage(6, walletName, initialAmount);
		}		
	} 
	else 
	{//false if none of the stream's error state flag is set - wallet not created

		//print "error: could not create C:\path\mywallet"
		//printMessage(3, walletName);
	}		
	
	//closes the file
	file.close();
	return fileOperation;
}
bool Wallet::appendWalletFile(WalletEntity walletEntity)
{
	bool fileOperation = false;
	
	string newLine; //new entity content
	string ssTimeStamp; // time converted to string
	
	//convert from time_t to string
	std::stringstream ss;
	ss << walletEntity.getTimeStamp();
	ssTimeStamp = ss.str();
		
	//open walletName for reading
	ofstream wallet(walletName.c_str(),ios::app);
	
	//check if file/wallet was open
	if(wallet.good())
	{// file open ok

		//compose new line for the file/wallet
		newLine = ssTimeStamp + ";" +
		walletEntity.getSign() + ";" +
		walletEntity.getAmount() + ";" +
		walletEntity.getCategory() + ";" +
		walletEntity.getCurrency() + "\n";
	
		//add the new line to the file/wallet
		wallet << newLine;
		
		//check if new line was added
		if(wallet.good())
		{//append ok
			fileOperation = true;
		}
		else
		{//append not ok
		}
		
		wallet.close();
	}
	else
	{// file open not ok
	}
	
	return fileOperation;
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
			WalletEntity walletEntity(data.at(0), data.at(1), 
										data.at(2), data.at(3));
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

  int main () 
{
	/* WalletEntity walletEntity("+", "20.0", "other", "RON");
	//WalletEntity walletEntity("+", "200", "EUR");
	cout<<"walletEntity.timeStamp = "<<walletEntity.getTimeStamp()<<endl;
	cout<<"walletEntity.timeStampGMT = "<<walletEntity.getTimeStampGMT()<<endl;
	cout<<"walletEntity.sign = "<<walletEntity.getSign()<<endl;
	cout<<"walletEntity.amount = "<<walletEntity.getAmount()<<endl;
	cout<<"walletEntity.category = "<<walletEntity.getCategory()<<endl;
	cout<<"walletEntity.currency = "<<walletEntity.getCurrency()<<endl;
	Wallet wallet;
	wallet = Wallet("ceapa", "+", "60.23", "EUROI");
	cout<<"the amount is : "<<wallet.getWalletContent().at(0).getAmount()<<endl;
	cout<<"fisierul cu numele : " << wallet.getName() << "a fost creat : " << wallet.createWalletFile() << endl;
	cout<<"s-a facut append : " << wallet.appendWalletFile(walletEntity) << endl; */
} 

