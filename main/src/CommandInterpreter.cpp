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
#include <time.h>

#include "WalletEntity.h"
#include "CommandInterpreter.h"
#include "PrintMessage.h"
#include "HelperFunctions.h"

using namespace std;

//validates and executes commands provided by user from console
//returns "true" if a valid command is provided
bool validateCommand(int argc, char* argv[])
{
	bool validCommand = false;
	//if command is "create"
	if(strcmp(argv[1], "create") == 0) 
	{
		//execute "create" command
		executeCreate(argc, argv[2], argv[3]);
		validCommand = true;
	}
	else if((strcmp(argv[1], "income") == 0) ||
			(strcmp(argv[1], "spend") == 0))
	{
		//execute "income" or "spend" command
		executeIncomeSpend(argc, argv[1], argv[3], argv[2]);
		validCommand = true;
	}
	else
	{
		// no valid command provided, keep validCommand = false
	}
	return validCommand;
}

//validates arguments for "create" command and executes it according to them
void executeCreate(
	const int argc, //number of arguments from command line
	const char fileName[], //new wallet name
	const char initialAmount[]) //initial amount for new wallet
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
			//check if fileName already exists
			if(validateFileName(fileName))
			{
				WalletEntity wallet;
				//create fileName wallet with "+0.00" initialAmount
				wallet.createWallet(fileName);
			}
			else
			{
				//fileName already exists
				//print "error: wallet "<< fileName << " already exists!\n"
				printMessage(4,fileName);
			}
			break;
		}
		default: //"create" command with at least fileName and amount
		{
			//check if fileName already exists
			//also check if initialAmount is valid
			if(validateFileName(fileName)) 
				if(validateAmount(initialAmount))
				{
					
					WalletEntity wallet;
					//create fileName wallet with given initialAmount
					wallet.createWallet(fileName, truncateAmount(initialAmount));
				}
				else
				{					
					//initialAmount is not a valid amount
					printMessage(2, fileName, initialAmount);
				}
			else
			{
				//fileName already exists
				//print "error: wallet "<< fileName << " already exists!\n"
				printMessage(4,fileName);
			}
			break;
		}
	}
}

//validates arguments for "income" or "spend" command and executes it 
//according to them
void executeIncomeSpend(
	const int argc, //number of arguments from command line
	string command, //"income" or "spend"
	const char amount[], //amount for new operation
	const char fileName[]) //wallet name
{
	//number of arguments for "income" or "spend" command
	switch (argc)
	{
		case 2:// "income/spend" command with no arguments
		{
			// print error: no ammount specified for 'income'.
			//or
			// print error: no ammount specified for 'spend'.
			printMessage(7, command);
			break;
		}
		default: //income/spend command with amount as first argument
		{
			
			//if(!validateAmount(amount))
			{	//amount is not valid
		
				//print error: parameter for 'income' should be a positive number
				//or
				//print error: parameter for 'spend' should be a positive number
				printMessage(8, command);
			}
			//else 
			{	//amount is valid
				
				//truncate amount to have only two decimals and no leading zeros
				string truncatedAmount=truncateAmount(amount);
				//check if validated sum is negative or zero
				if(atof(truncatedAmount.c_str()) <= 0.00)								
				{
					//amount is valid, but negative or zero 
					//print error: income should be higher than 0.
					//or
					//print error: spend should be higher than 0.
					printMessage(11, command);
				}
				else
				{
					//amount is valid and positive, execute "income/spend" command
					//in default wallet
					
					//check for "default_wallet" tag in config file
					if(existsConfigTag("default_wallet"))
					{
						//check if the file specified in "default_wallet" tag exists
						if(!validateFileName(readConfig("default_wallet")))
						{
							//prepare values for WalletEntity
							char sign = '+' ;
							string category = "salary" ;
							string messageFlag = "Income";// parameter for printMessage
							if (command == "spend") 
							{
								sign = '-' ;
								category = "other";
								messageFlag = "Spending";
							}
							else 
							{
								
							}
							//cut sign to amount
							string cutAmount = cutSign(truncatedAmount) ;
							//get current time
							time_t transactionTime = time(0) ;
							
							//create walletEntity with default values
							WalletEntity walletEntity(
								transactionTime, 
								sign, 
								cutAmount, 
								category,
								"RON");
								
							//if writing to file succesfull
							if(addWalletEntity(walletEntity))
							{
								//print a success message
								// like "Spending 'other' in an amount of 145.12 RON was registered."
								printMessage(
									9, 
									messageFlag, 
									category, 
									cutAmount, 
									"RON");
								// and one like "Transaction time: Thu, 08 Oct 2015 10:52:40 GMT"
								printMessage(
									10, 
									//convert transactionTime to string
									displayGMT(transactionTime));				
								
							} 
							else
							{
								//writing to file not succesfull
							}
						}
						else 
						{
							//file specified in "default_wallet" tag 
						}
					}	
					else
					{
						// tag "default_wallet" is not implemented in config
					}
				}
			}
		break;
		}
	}
}


//displays Help Menu - a list of valid commands and arguments
void printHelpMenu()
{
	cout << endl << "Accepted commands and arguments:" << endl;
	cout << " moneytracker[.exe] create  <file_name> <initial_amount>" << endl;
	cout << " moneytracker[.exe] income  <initial_amount>" << endl;
	cout << " moneytracker[.exe] spend   <initial_amount>" << endl;
}


// validates the amount input
bool validateAmount(const char word [])
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
					//printMessage(2, fileName, word);
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
					//error message
					//printMessage(2, fileName, word);
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
					//error message
					//printMessage(2, fileName, word);
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
					//error message
					//printMessage(2, fileName, word);
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
	/* NOT NEEDED IN SPRINT 2
	//check for not allowed characters in fileName
	string notAllowedChars = ":?\"*"; 
	//check all chars in notAllowedChars string
    for(unsigned int i = 0; i < notAllowedChars.length(); i++)
	{
		//save first position on which notAllowedChars[i] was found in fileName
		size_t firstFound = fileName.find(notAllowedChars[i]);
		//check if notAllowedChars[i] was found in fileName
		if(!firstFound)
		{	
			//print "error: characters  < > : \" | ? *  are not allowed for naming files!"
			printMessage(3);
			//invalidate fileName (fileName contains not allowed characters)
			return false;
		}
		
	}*/

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
string displayGMT(time_t myTime)
{
  struct tm * timeinfo;
  char buffer [100];//buffer for streaming time
  
  //calculate GMT format for myTime
  timeinfo = gmtime (&myTime);

  //stream GMT formatted time to buffer
  strftime (buffer,100,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

  return buffer;
  
}

