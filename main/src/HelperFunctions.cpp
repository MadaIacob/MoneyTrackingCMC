/*
File Description		Smaller functions used accross the application 
Author					cosmin.farcau, madalina.iacob
Date					15.10.2015
*/

#include <string>
#include <fstream>
#include "HelperFunctions.h"

using namespace std;

// function that checks if the first character of a string is a '-'
bool isFirstMinus (string amount)
{
	if (amount[0] == '-')
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

// this cut the first char if '-'; this function is called after truncateAmount
string cutSign(string validAmount)
{
	string cutAmount = "" ;
	int len = validAmount.length();
	if (validAmount[0] == '-')
		for(int i = 1; i < len; i++)
		{
			cutAmount += validAmount[i] ;
		}
	else
	{
		cutAmount = validAmount ;
	}	
	return cutAmount;
}

// searches for default_wallet in config file and returns true if found
// and '=' found and some text after '=' is found
bool existsConfigTag(string configTag)
{
	// open config file
	ifstream fileToOpen ;
	fileToOpen.open ("moneytracker.config") ;
	// value to return
	bool valid = false ;
	// while below reads each line in the file and puts it in string lineRead
	string lineRead ;
	//n counts lines that are read
	int n = 0; 
	while (getline(fileToOpen, lineRead))
	{
		n++ ;
		//position of default_wallet, if found
		std::size_t foundDef = lineRead.find("default_wallet");
		if (foundDef!=std::string::npos)
		{
			//position of the first char after "default_wallet"
			int pos = foundDef + 14 ;
			//check if after default_wallet there is an '=', if a char
			//different than space or tab enter else
			while (lineRead[pos] != '=')
			{
				if(lineRead[pos] == ' ' || lineRead[pos] == '\t' )
				{
					pos++ ;
				}
				else
				{
					return false ;
				}
			}
			//check if after the '=' some char is found
			while(!valid && lineRead[pos] != '\n')
			{
				if(lineRead[pos] != ' ' && lineRead[pos] != '\t')
				{
					pos++ ;
				}
				else
				{
					valid = true ;
				}
			}
		}
	}
	
	fileToOpen.close() ;
	
	return valid;
}

string readConfig(string configTag)
{
	ifstream configFile("..\\..\\moneytracker.config");
	string line;
	string word = "";
	
	
	while(getline(configFile, line))
	{
		size_t foundTag = line.find(configTag);
		if(foundTag != std::string::npos)
		{
			foundTag = line.find("=");
			unsigned int pos = foundTag +1;
			while(pos < line.size())
			{
				if(line[pos] != ' ' && line[pos] != '\t')
				{
					word = word + line[pos];
					pos++;
				}
				else
				{
					pos++;
				}					
			}
			break;
		}
	}
	return word;
}
