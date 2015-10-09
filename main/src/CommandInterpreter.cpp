/*
File Description	User interface
Functions			interprets commands provided by user from console 	
Author				calin-ciprian.popita, cosmin.farcau
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
			if(validateFileName(fileName))
			{
				WalletEntity wallet;
				string aux = validateAmount(initialAmount);
				if (aux != "") wallet.createWallet(fileName,aux);
			}
			else
			{
			}
		}
	}
}


//displays the list of valid commands and arguments
void printHelpMenu()
{
	cout << endl << "Accepted commands and arguments:" << endl;
	cout << "	mt create <file_name> <initial_amount>" << endl;
}

//

// validates the input, raounds the amount to two decimals
string validateAmount(const char word[])
{
	// validate the input argv[3], and retain only three decimals
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	
	int len = 0;
	for(;word[len] != '\0';len++);
	int pos = 0;
	E_ReadState state = INIT;
	string validWord = "";
	int countDec = 0;
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
					validWord += word[pos];
				}
				else if ('0' <= word[pos] && word[pos] <= '9')  
				{
					state = EXPECT_NUM_SEP;
					validWord += word[pos];
				}
				else
				{
					printMessage(2, "",word);	//invalid format for number
					return "";
				}
			break;
			}
			case EXPECT_NUM:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					state = EXPECT_NUM_SEP;
					validWord += word[pos];
				}
				else
				{
					printMessage(2, "", word);
					return "";
				}
			break;
			}
			case EXPECT_NUM_SEP:
			{
				if ('0' <= word[pos] && word[pos] <= '9')  //
				{
					state = EXPECT_NUM_SEP;
					validWord += word[pos];
				}
				else if (word[pos] == '.')
				{
					state = EXPECT_DEC;
					validWord += word[pos];
				}
				else
				{
					printMessage(2, "", word);
					return "";
				}
			break;	
			}
			case EXPECT_DEC:
			{
				if ('0' <= word[pos] && word[pos] <= '9' ) 
				{
					state = EXPECT_DEC;
					if(countDec <= 2)
					{
						validWord += word[pos];
					}
					countDec++;
				}
				else
				{
					printMessage(2, "", word);
					return "";
				}
			break;
			}
			default:
			{
				break;
			break;
			}
		}
	}
	
	// delete leading zeros
	double validValue = atof(validWord.c_str()); //value = 45 
	
	// round the second decimal, and get rid of third
	double aux = validValue*1000;
	int n3dec = abs(((int)aux)% 10);

	if(validValue >= 0)
	{
		if(n3dec >= 5)
		{
			validValue = validValue + 0.01 - (n3dec/1000.00);
		}
		else
		{
			validValue = validValue - (n3dec/1000.00);
		}
	}
	else
	{
		if(n3dec >= 5)
		{
			validValue = validValue - 0.01 + (n3dec/1000.00);
		}
		else
		{
			validValue = validValue + (n3dec/1000.00);
		}
	}
	
	// convert to string the valid amount
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

