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
		if(data.at(1) == "-")
		{
			amount = 0 - atof(data.at(2).c_str()); 
		}
		else
		{
			amount = atof(data.at(2).c_str());
		}
	}
	else
	{//first line in a wallet file (initial amount only)
		amount = atof(line.c_str());
	}
	//return the amount as a duble
	return amount;
}

//gets the category as string from an entity (line) received as a parameter 
string getCategory(const string line)
{	
	//returned value
	string category = "";
	//if not the first line in wallet file
	if((line[0] != '-') && (line[0] != '+'))
	{//a wallet file line different than the first
		//isolate category information from the line formatted like
		//"1446029428;+;200.00;other;RON"
		category = line.substr(line.find_first_of(';') + 
				   3,line.length() - line.find_first_of(';') - 3);
		category = category.substr(category.find_first_of(';') + 
				   1,category.length() - category.find_first_of(';') - 5);
	}
	else
	{
		//first line in a wallet file (initial amount only)
	}
	//return the amount as a duble
	return category;
}

//reads the content of a wallet 
//arguments is a pointer to an array of strings containing
// arguments[0]=walletName
// arguments[1]=category
//returns balance as a string
//if category is specified, balance is calculated only for that category
//if no category specified, balance for all wallet is calculated
string getBalance(string* arguments)
{
	//open the wallet file for reading 
	ifstream wallet(arguments[0].c_str());
	
	string line;
	double balance = 0;
	//check if category is not specified
	if(arguments[1].length() == 0)
	{// category is not specified -> calculate balance for all lines
		while(getline(wallet,line))
		{
			//add the amount from each entity to the balance
			balance += getAmount(line);
		}
	}
	else
	{// category is specified -> calculate balance for specified lines
		while(getline(wallet,line))
		{
			//add the amount from each entity to the balance
			if(arguments[1] == getCategory(line))
			{
				balance += getAmount(line);
			}
			else
			{}
		}
	}
	
	//convert the balance from double to string 
	//	with the sign "+" or "-" included
	string convertedBalance;
	ostringstream sstream;
	sstream << fixed << setprecision(2) << balance;
	convertedBalance = sstream.str();
	if (balance >= 0) 
	{
		convertedBalance = '+' + convertedBalance;
	}
	else
	{}
	
	//return balance as string having +/- sign as first character
	return convertedBalance;
}

//searches the amount and optional flags within command line arguments
//returns a pointer (arguments) to an array of strings containing:
// arguments[0]=amount
// arguments[1]=category
// arguments[2]=walletName
//first two command line arguments(application name and command) are ignored 
string* getArgumentsForIncomeSpend(int argNumber, char* argv[])
{
	
	// returned pointer that contains:
	// arguments[0] amount
	// arguments[1] category
	// arguments[2] walletName
	string* arguments = new string[3];//note: PLEASE MODIFY ALLOCATED MEMORY WHEN ADDING/REMOVING A TAG!
	arguments[0] = "";
	arguments[1] = "";
	arguments[2] = "";
	
	// a string containing the remaining arguments after taking out 
	//the first category found and its tag and
	//the first wallet name found and its tag
	string remainingArguments = "";
	
	//at least one argument provided for income/spend command
	if (argNumber >= 1) 
	{
		//signalises the first category flag found;
		bool categoryFound = false;
		//signalises the first wallet flag found;
		bool walletFound = false;
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
			else if(((strcmp(argv[i], "-w") == 0) || 
			    (strcmp(argv[i], "--wallet") == 0)) &&
			     walletFound == false)
			{
				//first wallet flag found
				walletFound = true;
				//jump over "-w" or "--wallet" flag
				i++;
				//put the next command line argument into returned pointer
				arguments[2] = argv[i]; 				
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
			remainingArguments = remainingArguments + argv[i]+" ";
		}
		else
		{}
		
		//check if more than one remaining argument left by
		//checking if first " " found is the same as last " " found in string
		if (remainingArguments.find(" ") == remainingArguments.rfind(" "))
		{//one remaining argument
			//amount should be the only word into remainingArguments string
			//put the word into returned pointer 
			arguments[0] = remainingArguments.substr(0, remainingArguments.find_first_of(" "));
		}
		else
		{//more than one remaining arguments
		}
	}
	else
	{}
	//return only relevant arguments
	return arguments;
}

//searches for optional flags within command line arguments
//returns a pointer (arguments) to an array of strings containing:
// arguments[0]=validation tag
// arguments[1]=walletName
// arguments[2]=category
//first two command line arguments(application name and command) are ignored 
string* getArgumentsForBalance(int argNumber, char* argv[])
{
	
	// returned pointer that contains:
	// arguments[0]=validation tag -> empty string if all arguments are valid 
	// arguments[1]=walletName
	// arguments[2]=category
	string* arguments = new string[3];//note: PLEASE MODIFY ALLOCATED MEMORY WHEN ADDING/REMOVING A TAG!
	arguments[0] = "";
	arguments[1] = "";
	arguments[2] = "";
	
	//at least one argument provided for balance command
	if (argNumber >= 1) 
	{
		//signalises the first category flag found;
		bool categoryFound = false;
		//signalises the first wallet flag found;
		//bool walletFound = false;
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
				arguments[2] = argv[i]; 				
			}/*
			//check for the first "-w" or "--wallet" flag among command line arguments
			else if(((strcmp(argv[i], "-w") == 0) || 
			    (strcmp(argv[i], "--wallet") == 0)) &&
			     walletFound == false)
			{
				//first wallet flag found
				walletFound = true;
				//jump over "-w" or "--wallet" flag
				i++;
				//put the next command line argument into returned pointer
				arguments[0] = argv[i]; 				
			}*/
			else
			{//there are arguments that invalidate "balance" command
				//set validation tag to "invalid"
				arguments[0] = "invalid";
			}
		}
		// check if there's one more argument left after flags search
		// this is the case where the last but one argument is not a flag
		if(i == (argNumber - 1))
		{//one more argument after flags
			//set validation tag to "invalid"
			arguments[0] = "invalid";
		}
		else
		{}
	}
	else
	{}
	
	//return only relevant arguments
	return arguments;
}

/*string* getArgumentsForConfig(int argNumber, char* argv[])
{
	// returned pointer that contains:
	// arguments[0]=defaultWalletName
	string* arguments = new string[2];//note: PLEASE MODIFY ALLOCATED MEMORY WHEN ADDING/REMOVING A TAG!
	arguments[0] = "";
	arguments[1] = "";

	//at least one argument provided for config command
	if (argNumber >= 1) 
	{
		//signalises the first tag found;
		bool defaultWalletFound = false;
		string defaultWallet = "default_wallet";
		int i = 0;
		//go through command line arguments
		for(; i <= argNumber - 1 ; i++)
		{
			string aux = argv[i];
			//check for the first "default_wallet" flag among command line arguments
			std::size_t foundStr = aux.find(defaultWallet);
			
			//if((foundStr != string::npos) && (!defaultWalletFound))
				
				aux = argv[i];
				//first "=" flag found
				foundStr = aux.find("=");
				defaultWalletFound = true;
				if(foundStr != std::string::npos) 
				{
					if (!(foundStr>=aux.length()-1))  
					{
						//cazul in care "=" este in mijlocul primului argument
						//exemplu "default_wallet=mywallet"
						arguments[0] = aux.substr(0, foundStr);
						arguments[1] = aux.substr(foundStr+1);
					} 
					else 
					{
						//cazul in care "=" este in capatul primului argument
						//exemplu "default_wallet= mywallet"
						i++;
						if (i <= argNumber-1) 
						{
							arguments[0] = aux.substr(0, foundStr);
							arguments[1] = argv[i];
						}
					}
				} 
				else if ((i+1 <= argNumber-1) && (strcmp(argv[i+1], "=") == 0))
				{
					//cazul in care "=" este un argument separat
					//exemplu "default_wallet = mywallet"
					i+=2;
					if (i <= argNumber-1) 
					{
						arguments[0] = argv[i-2];
						arguments[1] = argv[i];
					}
				} 
				else  
				{
					//cazul in care "=" este la inceputul argumentului doi
					//exemplu "default_wallet =mywallet"
					i++;
					if (i <= argNumber-1) 
					{
						aux = argv[i];
						if (aux.find("=") != string::npos) 
						{
							arguments[0] = argv[i-1];
							arguments[1] = aux.substr(1);
						}
						
					}
				}		
			
		}
	}
	else
	{}
	//return only relevant arguments
	return arguments;
}*/

string* getArgumentsForConfig(int argNumber, char* argv[])
{
	// returned pointer that contains:
	// arguments[0]=defaultWalletName
	string* arguments = new string[argNumber];//note: PLEASE MODIFY ALLOCATED MEMORY WHEN ADDING/REMOVING A TAG!
	for (int i = 0; i < argNumber; i++) {
		arguments[i] = "";
	}
	int k = 0;
	//at least one argument provided for config command
	if (argNumber >= 1) 
	{
		//signalises the first tag found;
		//bool defaultWalletFound = false;
		//string defaultWallet = "default_wallet";
		int i = 0;
		//go through command line arguments
		for(; i <= argNumber - 1 ; i++)
		{
			string aux = argv[i];
			//check for the first "default_wallet" flag among command line arguments
			//std::size_t foundStr = aux.find(defaultWallet);
			
			//if((foundStr != string::npos) && (!defaultWalletFound))
				
				aux = argv[i];
				//first "=" flag found
				size_t foundStr = aux.find("=");
				//defaultWalletFound = true;
				if(foundStr != std::string::npos) 
				{
					if (!(foundStr>=aux.length()-1))  
					{
						//cazul in care "=" este in mijlocul primului argument
						//exemplu "default_wallet=mywallet"
						arguments[k] = aux.substr(0, foundStr);
						arguments[k+1] = aux.substr(foundStr+1);
						k += 2;
					} 
					else 
					{
						//cazul in care "=" este in capatul primului argument
						//exemplu "default_wallet= mywallet"
						i++;
						if (i <= argNumber-1) 
						{
							arguments[k] = aux.substr(0, foundStr);
							arguments[k+1] = argv[i];
							k += 2;
						}
					}
				} 
				else if ((i+1 <= argNumber-1) && (strcmp(argv[i+1], "=") == 0))
				{
					//cazul in care "=" este un argument separat
					//exemplu "default_wallet = mywallet"
					i+=2;
					if (i <= argNumber-1) 
					{
						arguments[k] = argv[i-2];
						arguments[k+1] = argv[i];
						k += 2;
					}
				} 
				else  if (i <= argNumber-2) 
				{
					//cazul in care "=" este la inceputul argumentului doi
					//exemplu "default_wallet =mywallet"
					i++;
					
						aux = argv[i];
						if (aux.find("=") != string::npos) 
						{
							arguments[k] = argv[i-1];
							arguments[k+1] = aux.substr(1);
							k += 2;
						}
						else 
						{
							for (int i = 0; i < argNumber; i++) {
							arguments[i] = "";
							}
							break;
						}
				}		
		}
	}
	else
	{}
	//return only relevant arguments
	for (int i = 0; i < argNumber; i++) {
		cout<<" "<<arguments[i]<<endl;
	}
	return arguments;
}


bool writeConfig(string configTag,
   string configValue,
   string configFileName)
{
   string line;
   string newLine;
   string containt;
   
   bool changed = false;
   size_t foundTag;
   
   fstream configFile;
   configFile.open(configFileName.c_str(), std::fstream::in | std::fstream::out |std::fstream::app);
   
   while(getline(configFile,line))
   {
				  //remove spaces and tags from current line
				  line.erase(remove(line.begin(), line.end(), ' '), line.end());
				  line.erase(remove(line.begin(), line.end(), '\t'), line.end());
				  newLine = line;                  
				  
				  //check if the configTag is correct
				  foundTag = line.find(configTag);
				  if(line[line.size() -1] != '=' &&
					 foundTag == 0 &&
					 line[foundTag + configTag.size()] == '=' &&
					 !changed)
				  {
								 foundTag = line.find("=");
								 
								 size_t end = foundTag + line.size();
								 
								 newLine.replace(foundTag+1, end, configValue);
								 foundTag = foundTag + configValue.length();
								 newLine = newLine;
								 
								 changed = true;
				  }
				  containt = containt+newLine + "\n";
   }
   
   configFile.close();
   
   //move the containt to config file
   ofstream myNewConfig(configFileName.c_str());
   myNewConfig << containt;
   myNewConfig.close();
   
   return changed;
}



