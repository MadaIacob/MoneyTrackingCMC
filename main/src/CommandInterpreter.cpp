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
#include <iomanip>

#include "WalletEntity.h"
#include "CommandInterpreter.h"
#include "PrintMessage.h"

using namespace std;

//validates and executes commands provided by user from console
bool validateCommand(int argc, char* argv[])
{
	bool validCommand = false;
	//if command is "create"
	if(strcmp(argv[1], "create") == 0) 
	{
		//check and execute "create" with provided arguments
		validateCreate(argc, argv[2], argv[3]);
		validCommand = true;
	}
	else
	{
	}
	return validCommand;
}

//validates and executes "create" command arguments
void validateCreate(
	const int argc, 
	const char fileName[], 
	const char initialAmount[])
{
	//number of arguments for "create" command
	switch (argc)
	{
		case 2:// "create" command with no arguments
		{
			// print "error: at least filename should be specified."
			printMessage(1);
			break;
		}
		case 3: //"create" command with fileName only
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
		default: //"create" command with at least fileName and amount
		{
			//check if fileName already exists
			//also check if initialAmount is valid
			if(validateFileName(fileName) && 
				validateAmount(initialAmount, fileName))
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
bool validateAmount(const char word [], const string fileName)
{
	// valid = true means the input amount is correctly written by the user
	// and gets validated; this will be returned by 'validateAmount'
	bool valid = true;

	// states in which the 'switch' below can get during the 'for': INITial,
	// EXPECT NUMber, EXPECT NUMber or SEParator, EXPECT DECimal
	// e.g. in the INIT state, if the first char is + or - we then expect a num
	// if it is a num, then we expect the next to be a num or separator
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	E_ReadState state = INIT;
	
	// move through each char of the 'word' (initial amount)
	int len = strlen(word);
	for (int pos = 0; pos < len; pos++)
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
					// error message
					printMessage(2, fileName, word);
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
		validAmount.resize(separatPos+4);
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
	sstream << fixed << setprecision(2) << validValue;
	amountConverted = sstream.str();
	if(validValue >=0 ) amountConverted = '+' + amountConverted;

	return amountConverted;
}


//converts windows path to c++ accepted path
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
	bool isValidFileName = true;
	
	size_t found = fileName.find("\\");
	
	//replace "\" with "/" in fileName
	if(found != std::string::npos)
	{
		fileName = convertPath(fileName);
	}
	else
	{
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

