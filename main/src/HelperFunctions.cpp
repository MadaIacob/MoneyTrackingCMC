/*
File Description		Smaller functions used accross the application 
Author					cosmin.farcau, madalina.iacob
Date					15.10.2015
*/
#include <iostream>
#include <string>
#include <fstream>
#include <time.h>
#include <algorithm>

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
	size_t foundTag;
	size_t foundEqual;
	while(getline(configFile, line))
	{
		//remove spaces and tags from current line
		line.erase(remove(line.begin(), line.end(), ' '), line.end());
		line.erase(remove(line.begin(), line.end(), '\t'), line.end());
			
		//if configTag was found start storing default wallet name
		foundTag = line.find(configTag);
		if(foundTag != std::string::npos)
		{	
			foundEqual = line.find("=");
			size_t pos = foundEqual +1;
			
			//check if the configTag is correct and save the file name
			if(foundTag == 0 &&
			   line[foundTag + configTag.size()] == '=')
			{
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


