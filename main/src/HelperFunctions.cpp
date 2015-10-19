/*
File Description		Smaller functions used accross the application 
Author					cosmin.farcau, madalina.iacob
Date					15.10.2015
*/
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>

#include "HelperFunctions.h"
#include "PrintMessage.h"

using namespace std;

// this cut the first char if '-'; this function is called after truncateAmount
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
	//n counts lines that are read
	int n = 0; 
	while (getline(fileToOpen, lineRead))
	{
		n++ ;
		//position of default_wallet, if found
		std::size_t foundDef = lineRead.find("default_wallet");
		if (foundDef!=std::string::npos)
		{
			size_t pos = foundDef;
			while(pos > 0)
			{
				if(lineRead[pos -1] != ' ' && lineRead[pos - 1] != '\t')
				{
					//print message like
					//error: no default wallet configured in 'moneytracker.config'
					printMessage(14, configFileName);
					return false;
				}
				pos--;
			}
			
			//position of the first char after "default_wallet"
			pos = foundDef + 14 ;
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
					//print message like
					//error: no default wallet configured in 'moneytracker.config'
					printMessage(14, configFileName);
					return false ;
				}
			}
			//check if after the '=' some char is found
			pos = pos + 1;
			while(!valid && pos < lineRead.size())
			{
				
				if(lineRead[pos] == ' ' || lineRead[pos] == '\t')
				{	
					pos++;
				}
				else
				{
					valid = true;					
				}
			}
		}
		else
		{
			//print message like
			//error: no default wallet configured in 'moneytracker.config'
			printMessage(14, configFileName);
			valid = false;
		}
	}
	
	fileToOpen.close() ;
	
	return valid;
}

string readConfig(string configTag, string configFileName)
{
	ifstream configFile(configFileName.c_str());
	string line;
	string word = "";
	
	while(getline(configFile, line))
	{
		//if configTag wa found start storing default wallet name
		size_t foundTag = line.find(configTag);
		if(foundTag != std::string::npos)
		{
			foundTag = line.find("=");
			size_t pos = foundTag +1;
			while(pos < line.size())
			{
				if(line[pos] != ' ' && line[pos] != '\t')
				{
					while(pos < line.size() && line[pos] != ' ' && line[pos] != '\t')
					{
						word = word + line[pos];
						pos++;
					}
					break;
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


