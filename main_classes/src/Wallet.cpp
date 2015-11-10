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

Wallet::Wallet(const std::string walletName) : walletName(walletName) {}

Wallet::Wallet(const string walletName, WalletEntity walletEntity)
{
	Wallet::walletName = walletName;
	walletContent.push_back(walletEntity);
}

std::string Wallet::getName()
{
	return walletName;
}

void Wallet::setName(string walletName) 
{
	Wallet::walletName = walletName;
}
bool Wallet::readWalletFile()
{
	ifstream file(walletName.c_str());
	bool fileOperation = false;
	string line = "";
	while(getline(file,line) && line != "")
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
cout << "error 1. size of data vector: " << walletContent.size() << endl;		
		
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
		//create a walletEntity from the line
			WalletEntity walletEntity(data.at(0), data.at(1), 
										data.at(2), data.at(3), data.at(4));
			returnWalletEntity = walletEntity;
	}
	else 
	{//first line in a wallet file (sign, initial amount only, currency)
		size_t foundTag;
		string sign = line.substr(0, 1);
		//get ridd of the sign
		string newLine = line.substr(1);
		//push the sign into the vector
		data.push_back(sign);
		foundTag = newLine.find(" ");
		string amount = newLine.substr(0, foundTag);
		//push the amount into the vector
		data.push_back(amount);
		string currency = newLine.substr(foundTag+1);
		//push the currency into the vector
		data.push_back(currency);
		WalletEntity walletEntity(data.at(0), data.at(1), data.at(2));
		returnWalletEntity = walletEntity;
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
	WalletEntity walletEntity1("+", "30.0", "other", "RON");
	WalletEntity walletEntity2("+", "40.0", "other", "RON");
	//WalletEntity walletEntity("+", "200", "EUR");
	cout<<"walletEntity.timeStamp = "<<walletEntity.getTimeStamp()<<endl;
	cout<<"walletEntity.timeStampGMT = "<<walletEntity.getTimeStampGMT()<<endl;
	cout<<"walletEntity.sign = "<<walletEntity.getSign()<<endl;
	cout<<"walletEntity.amount = "<<walletEntity.getAmount()<<endl;
	cout<<"walletEntity.category = "<<walletEntity.getCategory()<<endl;
	cout<<"walletEntity.currency = "<<walletEntity.getCurrency()<<endl; 
	Wallet wallet("ceapa",walletEntity);
	wallet.createWalletFile();
	wallet.appendWalletFile(walletEntity1);
	wallet.appendWalletFile(walletEntity2);
	
	Wallet wal("ceapa");
	wal.readWalletFile();
	vector<WalletEntity> v = wal.getWalletContent();
	cout <<"dimensiunea vectorului este : " << v.size() << endl;
	for (unsigned int i = 0; i < v.size(); i++) 
	{
		WalletEntity w = v.at(i);
		cout << "elementele sunt : " << endl;
		cout <<	" " << w.getTimeStamp();
		cout <<	" " << w.getSign();
		cout << " " << w.getAmount();
		cout << " " << w.getCategory();
		cout << " " << w.getCurrency() << endl;
	}
}   */
 

