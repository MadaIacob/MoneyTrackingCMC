/*
File Description		Smaller functions used accross the application 
Author					cosmin.farcau, madalina.iacob, calin-ciprian.popita
Date					15.10.2015
*/
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <vector>
#include <cstring>


#include "HelperFunctions.h"
#include "PrintMessage.h"

using namespace std;

// this cut the first char; this function is called after truncateAmount
string cutSign(string validAmount)
{
	string cutAmount = "" ;
	int len = validAmount.length();
	for(int i = 1; i < len; i++)
		{
			cutAmount += validAmount[i] ;
		}
	return cutAmount;
}

// searches for default_wallet in config file and returns true if found
// and '=' found and some text after '=' is found
bool existsConfigTag(string configTag,string configFileName)
{
	// open config file
	ifstream fileToOpen ;
	fileToOpen.open (configFileName.c_str()) ;
	
	if(!fileToOpen.is_open())
	{
		//print message like 
		//error: could not open 'moneytracker.config'
		printMessage(13, configFileName);
		return false;
	}
	else {}

	// value to return
	bool valid = false ;
	// while below reads each line in the file and puts it in string lineRead
	string lineRead = "";
	//position of default_wallet, if found
	std::size_t foundDef;
	while (getline(fileToOpen, lineRead) && !valid)
	{
		foundDef = lineRead.find(configTag);
		if (foundDef!=std::string::npos)
		{
			//remove spaces and tags from current line
			lineRead.erase(remove(lineRead.begin(), lineRead.end(), ' '), lineRead.end());
			lineRead.erase(remove(lineRead.begin(), lineRead.end(), '\t'), lineRead.end());
			
			//check if the configTag is correct
			foundDef = lineRead.find(configTag);
			
			if(lineRead[lineRead.size() -1] != '=' &&
			   foundDef == 0 &&
			   lineRead[foundDef + configTag.size()] == '=')
			{
				valid = true;
			}
		}
	}
	
	fileToOpen.close() ;
	if(valid == false)
	{
		//error: no default wallet configured in 'moneytracker.config'
		printMessage(14, configFileName);
	}
	return valid;
}

string readConfig(string configTag, string configFileName)
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
			if(line[line.size() -1] != '=' && foundDef == 0 &&
			   line[foundDef + configTag.size()] == '=')
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
			/* foundEqual = line.find("=");
			size_t pos = foundEqual +1;
			
			//save the file name to word string 
			while(pos < line.size())
			{
				word = word + line[pos];
				pos++;				
			}
				
			break; */
		}
	}
	return word;
}

//converts windows path to c++ accepted path 
//(replaces all '\' characters with '/')
string convertPath(string givenPath)
{
	for(unsigned int i = 0; i < givenPath.length(); i++)
	{
		if(givenPath[i] == '\\')
		{
			givenPath[i] = '/';
		}
	}
	
	return givenPath;
}

//checks if the file fileName already exists. 
//Returns true if fileName is not already in use and false otherwise
bool validateFileName(string fileName)
{
	//save first position on which '\' was found in fileName
	size_t firstFound = fileName.find("\\");
	//if at least one '\' found
	if(!firstFound)
	{
		//replace all '\' with '/' in fileName
		fileName = convertPath(fileName);
	}
	else
	{
		//keep fileName unchanged
	}

	bool isValidFileName = true;
	
	ifstream fileChecking(fileName.c_str());
	
	//check if fileName already exists
	if(fileChecking.good())
	{
		fileChecking.close();
		isValidFileName = false;
		//print "error: wallet "<< fileName << " already exists!\n"
		//printMessage(4,fileName);
	}
	else
	{
		//valid fileName, so keep isValidFileName=true
	}

	return isValidFileName;
	
} 

//gets unix timestamp format 
//returns a string containing GMT calculated time, formatted like:
//"Thu, 08 Oct 2015 10:52:40 GMT"
string displayGMT(const time_t myTime)
{
  struct tm * timeinfo;
  char buffer [100];//buffer for streaming time
  
  //calculate GMT format for myTime
  timeinfo = gmtime (&myTime);

  //stream GMT formatted time to buffer
  strftime (buffer,100,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

  return buffer;
  
}

//gets the amount as a double from an entity (line) received as a parameter 
double getAmount(const string line)
{
	
	vector <string> data;
	double amount;
	
	istringstream ss(line);
	//iterates trough the string and separates it by the character ";" 
	//	and pushes every element into a vector  
	while(ss)
	{
		string parameter;
		if(!getline(ss,parameter,';')) break;
		data.push_back(parameter);
	}	
	//convert the amount form string to double
	if(data.at(1) == "-")
	{
		amount = 0 - atof(data.at(2).c_str()); 
	}
	else
	{
		amount = atof(data.at(2).c_str());
	}
	//return the amount as a duble
	return amount;
	
}
//reads the content of the default wallet and returns the sum of all entries
//	as a string with the sign "+" or "-" included
//if there is no content in the file it returns the string "+0.00"
string getBalance(const string walletName)
{
	//open the file for reading
	ifstream wallet(walletName.c_str());
	string line;
	vector <string> data;
	double balance = 0;
	//read the first linefrom the given file
	if(getline(wallet,line)) 
	{
		string sign = "";
		string result = "" ;
		//get the sign of the first entity
		sign = line[0];
		int len = line.length();
		double firstAmount = 0;
		//get the amount as a string character by character 
		for(int i = 1; i < len; i++)
			{
				if (line[i]!=' ')
				{
					result += line[i];
				}
				else 
				{
					//convert the amount form string to double
					if(sign == "-")
					{
						firstAmount = 0 - atof(result.c_str()); 
					}
					else
					{
						firstAmount = atof(result.c_str());
					}
				}
			}
			//add the first amount to the balance
			balance += firstAmount;
		//iterate trough the rest of the entityes from the file
		while(getline(wallet,line))
		{
			//add the amount from each entity to the balance
			balance += getAmount(line);
		}
	}
	//convert the balance from double to string 
	//	with the sign "+" or "-" included
	string amountConverted;
	ostringstream sstream;
	sstream << fixed << setprecision(2) << balance;
	amountConverted = sstream.str();
	if (balance >= 0) amountConverted = '+' + amountConverted;
	//return the balance as a string
	return amountConverted;
}

//searches the amount and optional flags within command line arguments
//returns a pointer (arguments) to an array of strings containing:
// arguments[0]=amount
// arguments[1]=category
//first two command line arguments(application name and command) are ignored 
string* getArgumentsForIncomeSpend(int argNumber, char* argv[])
{
	
	// returned pointer that contains:
	// arguments[0] amount
	// arguments[1] category
	string* arguments = new string[2];
	
	// a string containing the remaining arguments after taking out the first category found and its tag
	string remainingArguments = "";
	
	//at least one argument provided for income/spend command
	if (argNumber >= 1) 
	{
		//signalises the first category flag found;
		bool categoryFound = false;
		int i = 0;
		//go through command line arguments
		for(; i < argNumber - 1 ; i++)
		{
			//check for the first "-c" or "--category" flag among command line arguments
			if(((strcmp(argv[i], "-c") == 0) || 
			    (strcmp(argv[i], "--category") == 0)) &&
			     categoryFound == false)
			{
				//first category flag found
				categoryFound = true;
				//jump over "-c" or "--category" flag
				i++;
				//put the next command line argument into returned pointer
				arguments[1] = argv[i]; 				
			}
			else
			{
				//put command line argument into remainingArguments string
				remainingArguments = remainingArguments + argv[i] + " ";
			}
		}
		// check if there's one more argument left after flags search
		// this is the case where the last but one argument is not a flag
		if(i == (argNumber - 1))
		{
			//put last command line argument into remainingArguments string
			remainingArguments = remainingArguments + argv[i];
		}
		else
		{}
		
		//amount should be the first word into remainingArguments string
		//put the first word into returned pointer 
		arguments[0] = remainingArguments.substr(0, remainingArguments.find_first_of(" "));
	}
	else
	{}
	//return only relevant arguments
	return arguments;
}


