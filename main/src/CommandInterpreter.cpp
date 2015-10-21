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
		executeIncomeSpend(argc, argv[1], argv[2], argv[3]);
		validCommand = true;
	}
	else if(strcmp(argv[1], "balance") == 0) 
	{
		//execute "balance" command
		//executeBalance(argc, argv[2], argv[3]);
		validCommand = true;
	}
	else
	{
		// no valid command provided, keep validCommand = false
	}
	return validCommand;
}

//validates arguments for "create" command and executes it according to them
//returns true if new wallet was successfully created
bool executeCreate(
	const int argc, //number of arguments from command line
	const char fileName[], //new wallet name
	const char initialAmount[]) //initial amount for new wallet
{
	bool validArguments = false;
	
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
				validArguments = true;
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
					validArguments = true;
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
	return validArguments;
}

//validates arguments for "income" or "spend" command and executes it 
//according to them
//returns true if income/spend was successfully executed
bool executeIncomeSpend(
	const int argc, //number of arguments from command line
	const string command, //"income" or "spend"
	const char amount[], //amount for new operation
	const string configFileName, //config file for default values
	const char fileName[]) //wallet name
{
	bool validArguments = false;
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
			if(!validateAmount(amount))
			{	//amount is not valid
				//print error: parameter for 'income' should be a positive number
				//or
				//print error: parameter for 'spend' should be a positive number
				printMessage(8, command);
			}
			else 
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
					if(existsConfigTag("default_wallet", configFileName))
					{				
						//check if the file specified in "default_wallet" tag exists
						if(!validateFileName(
							readConfig("default_wallet", 
							configFileName)))
						{	//the file specified in "default_wallet" tag exists
							
							//prepare values for WalletEntity
							string sign = "+" ;
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
								
							//if writing to file successful
							if(walletEntity.addWalletEntity(readConfig(
								"default_wallet", 
								configFileName)))
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
								validArguments = true;		
								
							} 
							else
							{
								//writing to file not succesfull
							}
						}
						else 
						{
							//file specified in "default_wallet" tag doesn't exist
							//print error: could not open 'C:\path\some.wallet' to register transaction
							printMessage(12, readConfig("default_wallet"));
						}
					}	
					else
					{
						// could not open moneytracker.config or
						// tag "default_wallet" is incorrect or 
						// tag "default_wallet" is not implemented at all 
					}
				}
			}
		break;
		}
	}
	return validArguments;
}


//displays Help Menu - a list of valid commands and arguments
void printHelpMenu()
{
	cout << endl << "Accepted commands and arguments:" << endl;
	cout << " ------------------------------------" 
	<< "---------------------------------" << endl;
	cout << " moneytracker[.exe] create <file_name> <initial_amount>" << endl;
	cout << " ------------------------------------" 
	<< "---------------------------------" << endl;
	cout << " moneytracker[.exe] income [-c/--category]" 
	<< " <category> <initial_amount> " << endl;
	cout << " moneytracker[.exe] income <initial_amount>" 
	<< " [-c/--category] <category>" << endl;
	cout << " ------------------------------------" 
	<< "---------------------------------" << endl;
	cout << " moneytracker[.exe] spend [-c/--category]" 
	<< " <category> <initial_amount> " << endl;
	cout << " moneytracker[.exe] spend <initial_amount>" 
	<< " [-c/--category] <category>" << endl;
	cout << " ------------------------------------" 
	<< "---------------------------------" << endl;
	cout << " moneytracker[.exe] balance" << endl;
}


// validates the amount input
bool validateAmount(const char word [])
{
	// valid = true means the input amount is correctly written by the user
	// and gets validated; this will be returned by 'validateAmount'
	bool valid = true;

	// states in which the 'switch' below can get during the 'for': 
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	E_ReadState state = INIT;
	
	// move through each char of the 'word' (initial amount)
	int len = strlen(word);
	for (int pos = 0; pos < len; pos++)
	{
		switch (state)
		{
			//INITial state, when the 'for' starts, first char in word 
			case INIT:
			{
				if((word[pos] == '+') || 
					(word[pos] == '-') )
				{
				// if first char is + or - the next is expected to be a number
					state = EXPECT_NUM;
				}
				else if ('0' <= word[pos] && word[pos] <= '9')  
				{
				// if char is a number, then we expect the next to be a num or separator
					state = EXPECT_NUM_SEP;
				}
				else
				{
					valid = false;
					return false;
				}
			break;
			}
			//you get in this state when a number was expected
			case EXPECT_NUM:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					state = EXPECT_NUM_SEP;
				}
				else
				{
					valid = false;
					return false;
				}
			break;
			}
			//you get in this state when a number or the '.' separator was expected
			case EXPECT_NUM_SEP:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					//after getting into EXPECT_NUM_SEP state, if char is num
					//the next expected is again num or sep
					state = EXPECT_NUM_SEP;
				}
				else if (word[pos] == '.')
				{
					//after hte separator you only expect numbers (decimals)
					state = EXPECT_DEC;
				}
				else
				{
					valid = false;
					return false;
				}
			break;	
			}
			//you get in this state when a number is expected, but after the '.'
			case EXPECT_DEC:
			{
				if ('0' <= word[pos] && word[pos] <= '9' ) 
				{
					//if char is decimal, the next is expected to be also decimal
					state = EXPECT_DEC;
				}
				else
				{
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
// and return the modified string
string truncateAmount(const char word[])
{
	//keep word as a string
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
	
	// delete leading zeros (if any) by converting string to double
	double validValue = atof(validAmount.c_str()); 
	
	// round the second decimal, and get rid of third (if there is)
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


