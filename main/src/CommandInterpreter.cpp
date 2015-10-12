/*
File Description	User interface
Functions			interprets commands provided by user from console 	
Author				calin-ciprian.popita, cosmin.farcau, madalina.iacob
Date				09.10.2015
*/ 

#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <sstream>

#include "WalletEntity.h"
#include "CommandInterpreter.h"
#include "PrintMessage.h"

using namespace std;

//validates and executes commands provided by user from console
bool validateCommand(int argc, char* argv[])
{
	bool validCommand = false;
	if(strcmp(argv[1], "create") == 0) 
	{
		validateCreate(argc, argv[2], argv[3]);
		validCommand = true;
	}
	else
	{
	}
	return validCommand;
}

//validates "create" command arguments

const char fileName[]=""; 	// is this ok? 


void validateCreate(
	const int argc, 
	const char fileName[], 
	const char initialAmount[])
{
	switch (argc)
	{
		case 2:
		{
			// print " error: wallet name required !"
			printMessage(1);
			break;
		}
		case 3:
		{
			//check if fileName already exists and for valid characters
			if(validateFileName(fileName))
			{
				WalletEntity wallet;
				wallet.createWallet(fileName);
			}
			else
			{
			}
			break;
		}
		default:
		{
			//check if fileName already exists and for valid characters
			if(validateFileName(fileName) && validateAmount(initialAmount))
			{
				
				WalletEntity wallet;
				wallet.createWallet(fileName, truncateAmount(initialAmount));
			}
			else
			{
			}
			break;
		}
	}
}


//displays the list of valid commands and arguments
void printHelpMenu()
{
	cout << endl << "Accepted commands and arguments:" << endl;
	cout << "	mt create <file_name> <initial_amount>" << endl;
}



// validates the amount input
bool validateAmount(const char word [])
{
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	
	int len = strlen(word);
	int pos = 0;
	E_ReadState state = INIT;
	string validWord = "";
	
	bool valid = true;
	for (pos = 0; pos < len; pos++)
	{
		switch (state)
		{
			case INIT:
			{
				if((word[pos] == '+') || 
					(word[pos] == '-') )
				{
					state = EXPECT_NUM;
				}
				else if ('0' <= word[pos] && word[pos] <= '9')  
				{
					state = EXPECT_NUM_SEP;
				}
				else
				{
					printMessage(2, fileName, word); //error message
					valid = false;
					return false;
				}
			break;
			}
			case EXPECT_NUM:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					state = EXPECT_NUM_SEP;
				}
				else
				{
					printMessage(2, fileName, word);
					valid = false;
					return false;
				}
			break;
			}
			case EXPECT_NUM_SEP:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					state = EXPECT_NUM_SEP;
				}
				else if (word[pos] == '.')
				{
					state = EXPECT_DEC;
				}
				else
				{
					printMessage(2, fileName, word);
					valid = false;
					return false;
				}
			break;	
			}
			case EXPECT_DEC:
			{
				if ('0' <= word[pos] && word[pos] <= '9' ) 
				{
					state = EXPECT_DEC;
				}
				else
				{
					printMessage(2, fileName, word);
					valid = false;
					return false;
				}
			break;
			}
			default:
			{
			break;
			}
		}
	}
	
	return valid;
}

// get rid of leading zeros, round to second decimal, get rif of extra decimals
string truncateAmount(const char word[])
{
	string validAmount(word); 
	
	int len = strlen(word);
	// find the position of '.' separator
	int separatPos = 0;
	for(int i = 0; i < len; i++)
	{
		if (word[i] == '.')
		{
			separatPos = i;
		}
		else 
		{
		}
	}
	// keep maximum three decimals
	if (separatPos != 0)
	{
		validAmount.resize(separatPos+3);
	}
	
	// delete leading zeros (if any)
	double validValue = atof(validAmount.c_str()); 
	
	// round the second decimal, and get rid of others (if any)
	if(validValue >= 0)
	{
	int aux = validValue*100 + 0.5;
	validValue = aux / 100.00;
	}
	 else
	{
	int aux = validValue*100 - 0.4;
	validValue = aux / 100.00;
	} 
	
	// convert to string the validated amount
	string amountConverted;
	ostringstream sstream;
	sstream << validValue;
	amountConverted = sstream.str();

	return amountConverted;
}

// madalina


//helper function. Converts windows path to c++ accepted path
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

//validates file name introducesd by user and checks if the file already exists. 
//Returns true if the fileName is a valid one and false otherwise
bool validateFileName(string fileName)
{
	bool isValidFileName = false;
	
	size_t found = fileName.find("\\");
	
	//validate syntactically the file name
	if(found != std::string::npos)
	{
		fileName = convertPath(fileName);
		isValidFileName = true;
	}
	else
	{
		isValidFileName = true;
	}
	
	//checks if the file already exists
	if(isValidFileName)
	{
		ifstream fileChecking(fileName.c_str());
		if(fileChecking.good())
		{
			fileChecking.close();
			isValidFileName = false;
			printMessage(4,fileName);
		}
		else
		{
			
		}
	}
	return isValidFileName;
	
} 

