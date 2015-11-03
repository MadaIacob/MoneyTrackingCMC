///not used for the moment

#include <fstream>
#include <string>
#include <ctime>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "WalletEntity.h"
#include "CreateWalletTestHelper.h"

using namespace std;

//helper function
//add a new entry to the wallet
bool helperAddWalletEntity(
	const time_t time,
	const string sign,
	const string amount,
	const string category,
	const string currency,
	const string walletName)
{
	WalletEntity wallet(time,sign,amount,category,currency);
	
	return wallet.addWalletEntity(walletName);
}
//helper function
//calls createWallet method from WalletEntity class
void helperCreateWallet(const string walletName, const string amount)
{
	WalletEntity newWallet;
	newWallet.createWallet(walletName, amount);
}

//helper function
//reads from the file created and returns the content
string readWallet(const string walletName)
{
	
	ifstream wallet(walletName.c_str());
	
	string walletContent;
	string line;
	//read from the given file
	//getline(wallet,walletContent);
	
	while(getline(wallet,line))
	{
		walletContent += line;
	}
	return walletContent;
}

//helper function 
//check if the file has been created
bool walletCreated(const string walletName)
{
	bool isCreated = false;
	ifstream wallet(walletName.c_str());
	
	if(wallet.good())
	{
		wallet.close();
		isCreated = true;
	}
	else 
	{
		isCreated = false;
	}
	
	return isCreated;
}

//helper function
//returns the last line from the file
string readLastLine(const string fileName)
{
	ifstream file(fileName.c_str());
	string lastLine;
	string line;
	if(file.is_open())
	{
		while(getline(file,line))
		{
			bool isEmpty = true;
			for(unsigned int i = 0; i< line.size(); i++)
			{
				char ch = line[i];
				isEmpty = isEmpty && isspace(ch);
			}
			if(!isEmpty)
			{
				lastLine = line; 
			}
		}
				
		file.close();
	}
	return lastLine;
}

//helper function
//creates a new file with given name and containt
void createFile(const string fileName,const string containt)
{
	ofstream testFileConfig(fileName.c_str());
	
	testFileConfig << containt << '\n';
}

string getConfigValue(const std::string configTag, const std::string configFileName)
{
	ifstream configFile(configFileName.c_str());
	string line;
	string word = "";
	//size_t foundTag;
	size_t foundEqual;
	while(getline(configFile, line))
	{	
		//if configTag was found start storing default wallet name
		std::size_t foundTag = line.find(configTag);
		if(foundTag != std::string::npos)
		{	
			//remove spaces and tags from current line
			line.erase(remove(line.begin(), line.end(), ' '), line.end());
			line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			
			std::size_t foundDef = line.find(configTag);

			if(foundDef == 0 && line[foundDef + configTag.size()] == '=')
			{
				foundEqual = line.find("=");
				size_t pos = foundEqual +1;
				while(pos < line.size())
				{
					word = word + line[pos];
					pos++;				
				}
			break;
			}
		}
	}
	return word;
}