/*
File Description		Implementation of TransactionCmd class
Author					calin-ciprian.popita
Date					10.11.2015

18.11.2015 - added default category taken from config file or hardcoded
*/

#include <stdlib.h>
#include "TransactionCmd.h"
#include "HelperFunctions.h"
#include "FileHelper.h"
#include "Command.h"
#include "Config.h"
#include <iostream>
using namespace std;

//constructor - chooses between income/spend
TransactionCmd::TransactionCmd(Transaction_E transaction)
{
	if(transaction == INCOME)
	{//"income" command
		//set transaction sign to (+)
		walletEntity.setSign("+");
	}
	else
	{//"spend" command
		//set transaction sign to (-)
		walletEntity.setSign("-");
	}
	//set transaction time stamp
	walletEntity.setTimeStamp();
}

//performs syntactic analysis - sets error message if anything besides
//tags and amount provided for income/spend
//returns true if amount and only flagged parameters are found
bool TransactionCmd::parseParams(vector<string>& params)
{
	//returned value
	bool isParseOK = true;
	//check how many parameters were provided for income/spend
	switch(params.size())
	{
		case 0:
		{//no parameter provided for income/spend command
			//set error message
			ptrMessage->setMessageCode(INVALID_PARAM_ERR);
			isParseOK = false;
			break;
		}
		case 1:
		{//one parameter that represents the amount
			//put command line argument into WalletEntity.amount
			walletEntity.setAmount(params.at(0));
			break;
		}
		default:
		{//at least two arguments provided for income/spend command
			//signalises the first category flag found;
			bool categoryFound = false;
			//signalises the first wallet flag found;
			bool walletFound = false;
			//signalises the first time flag found;
			bool timeFound = false;
			//signalises the first amount found;
			bool amountFound = false;

			unsigned int i = 0;
			//go through command line params
			for(; i < params.size() - 1; i++)
			{
				//check for the first "-c" or "--category" flag among parameters
				if(((params.at(i) == "-c") ||
					(params.at(i) == "--category")) &&
					 categoryFound == false)
				{//first category flag found
					categoryFound = true;
					//jump over "-c" or "--category" flag
					i++;
					//put the next command line argument into WalletEntity.category
					walletEntity.setCategory(params.at(i));
				}
				//check for the first "-w" or "--wallet" flag among parameters
				else if(((params.at(i) == "-w") ||
					(params.at(i) == "--wallet")) &&
					 walletFound == false)
				{//first wallet flag found
					walletFound = true;
					//jump over "-w" or "--wallet" flag
					i++;
					//put the next command line argument into Wallet.walletName
					wallet.setName(params.at(i));
				}
				//check for the first "-t" or "--time" flag among parameters
				else if(((params.at(i) == "-t") ||
					(params.at(i) == "--time")) &&
					 timeFound == false)
				{//first time flag found
					timeFound = true;
					//jump over "-t" or "--time" flag
					i++;
					//put the next command line argument into WalletEntity.timeStamp
					walletEntity.setTimeStamp(params.at(i));
				}
				//check for the first amount among parameters
				else if(!amountFound)
				{//first unflagged parameter represents the amount
					//amount found
					amountFound = true;
					//put command line argument into WalletEntity.amount
					walletEntity.setAmount(params.at(i));
				}
				//check for unwanted parameters (not flagged params, not amount)
				else
				{//unwanted parameter found
					//set error message
					ptrMessage->setMessageCode(INVALID_PARAM_ERR);
					isParseOK = false;
					break;
				}
			}
			// check if there's one more parameter left after search
			// this is the case where the last but one parameter is not a flag
			if(i == (params.size() - 1))
			{//one parameter left after search

				//check if amount was found so far
				if(!amountFound)
				{//the last parameter represents the amount
					amountFound = true;
					//put command line argument into WalletEntity.amount
					walletEntity.setAmount(params.at(i));
					break;
				}
				else
				{//unwanted parameter found on last position
					//set error message
					ptrMessage->setMessageCode(INVALID_PARAM_ERR);
					break;
				}
			}
			else
			{//no parameters left after search
			}
			if (!amountFound)
			{//amount not found after parse
				isParseOK = false;
				ptrMessage->setMessageCode(INVALID_PARAM_ERR);
			}
			else
			{//amount found
			}
			break;
		}

	}//end switch

	//rearrange params vector for message printing ?????   **********************************************************************************
	//empty the vector
	params.resize(0);
	//check whether the command is "income" or "spend"
	if(walletEntity.getSign() == "+")
	{//the command is "income"
		//put command name in vector for INVALID_PARAM_ERR case
		params.push_back("income");
	}
	else
	{//the command is "spend"
		//put command name in vector for INVALID_PARAM_ERR case
		params.push_back("spend");
	}

	return isParseOK;
}

// validates the values provided for income/spend parameters
//returns true if all parameters have valid values
bool TransactionCmd::validateParams(vector<string>& params)
{
	//----------validate amount - mandatory parameter for transaction-----------
	//check if amount is valid
	if(!validateAmount(walletEntity.getAmount().c_str()))
	{//amount is not valid
		//set error message
		ptrMessage->setMessageCode(INVALID_PARAM_ERR);
		//params vector already arranged by parseParams
		//no other validation needed -> exit validateParams
		return false;
	}
	else
	{//amount is valid
		//truncate amount to have only two decimals and no leading zeros
		string truncatedAmount=truncateAmount(walletEntity.getAmount());
		//check if validated sum is negative or zero
		if(atof(truncatedAmount.c_str()) <= 0.00)
		{//amount is valid, but negative or zero
			//set error message
			ptrMessage->setMessageCode(INCOME_SPEND_HIGHER_ERR);
			//params vector already arranged by parseParams

			//no other validation needed -> exit validateParams
			return false;
		}
		else
		{//amount is valid and positive
			//cut the sign and set walletEntity.amount
			walletEntity.setAmount(cutSign(truncatedAmount));
		}
	}

	//------------validate walletName if provided for transaction---------------

	//check if walletName was provided
	if(wallet.getName() != "")
	{//walletName provided
		//check if walletName file exists
		if(!validateFileName(wallet.getName()))
		{//walletName file exists

		}
		else
		{//walletName file doesn't exist - display error message

			//rearrange params vector for message printing ?????   **********************************************************************************
			//empty the vector
			params.resize(0);
			//put wallet name in vector
			params.push_back(wallet.getName());

			//set error message
			ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_ERR);

			return false;
		}
	}
	else
	{//no walletName provided
		//check for config file
		if(!validateFileName("moneytracker.config"))
		{//config file exists

			//create config object
			Config configFile;
			configFile = Config("moneytracker.config");

			//put config file content into config object
			if(configFile.readConfigFile())
			{//no error reading config file
				//check for default_wallet tag in config
				if(configFile.existsTag("default_wallet") &&
				   (configFile.getTagValue("default_wallet") != ""))
				{//default_wallet tag exists
					//check if default_wallet file exists
					if(!validateFileName(configFile.getTagValue("default_wallet")))
					{//default_wallet file exists
						//set default_wallet as walletName
						wallet.setName(configFile.getTagValue("default_wallet"));
					}
					else
					{//default_wallet file doesn't exist

						//rearrange params vector for message printing ?????   **********************************************************************************
						//empty the vector
						params.resize(0);
						//put wallet name in vector
						params.push_back(configFile.getTagValue("default_wallet"));

						//set error message
						ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_ERR);

						return false;
					}
				}
				else
				{//default_wallet tag doesn't exist or is empty

					//rearrange params vector for message printing ?????   **********************************************************************************
					//empty the vector
					params.resize(0);
					//put config file name in vector
					params.push_back("moneytracker.config");

					//set error message
					ptrMessage->setMessageCode(NO_DEFAULT_WALLET_ERR);

					return false;
				}
			}
			else
			{//error reading config file
				return false;
			}
		}
		else
		{//config file doesn't exist

			//rearrange params vector for message printing ?????   **********************************************************************************
			//empty the vector
			params.resize(0);
			//put config file name in vector
			params.push_back("moneytracker.config");

			//set error message
			ptrMessage->setMessageCode(COULD_NOT_OPEN_CONFIG_ERR);

			return false;
		}
	}


	//---------------  validate category for transaction  ----------------------

	//check if category was provided
	if(walletEntity.getCategory().find(";") != std::string::npos)
	   {
		   ptrMessage->setMessageCode(NOT_ALLOWED_CHARACTER);
		   return false;
	   }
	if(walletEntity.getCategory() == "")
	{//no category provided
		//check for config file
		if(!validateFileName("moneytracker.config"))
		{//config file exists

			//create config object
			Config configFile;
			configFile = Config("moneytracker.config");

			//put config file content into config object
			if(configFile.readConfigFile())
			{//no error reading config file
				//check whether the command is "income" or "spend"
				if(walletEntity.getSign() == "+")
				{//the command is "income"
					//check for default_income_category tag in config
					if(configFile.existsTag("default_income_category") &&
					   (configFile.getTagValue("default_income_category") != ""))
					{//default_income_category tag exists
						//set default_income_category as category
						walletEntity.setCategory(configFile.getTagValue("default_income_category"));
					}
					else
					{//default_income_category tag doesn't exist or is empty
					 	//set "salary" as category
						walletEntity.setCategory("salary");
					}
				}
				else
				{//the command is "spend"
					//check for default_spending_category tag in config
					if(configFile.existsTag("default_spending_category") &&
					   (configFile.getTagValue("default_spending_category") != ""))
					{//default_spending_category tag exists
						//set default_spending_category as category
						walletEntity.setCategory(configFile.getTagValue("default_spending_category"));
					}
					else
					{//default_spending_category tag doesn't exist or is empty
						//set "other" as category
						walletEntity.setCategory("other");
					}
				}

			}
			else
			{//error reading config file
				return false;
			}
		}
		else
		{//config file doesn't exist

			//rearrange params vector for message printing ?????   **********************************************************************************
			//empty the vector
			params.resize(0);
			//put config file name in vector
			params.push_back("moneytracker.config");

			//set error message
			ptrMessage->setMessageCode(COULD_NOT_OPEN_CONFIG_ERR);

			return false;
		}
	}
	else
	{//category provided
	}


	return true;
}

//executes income/spend without any validations
//returns true if execution is successfull
bool TransactionCmd::executeCommand(vector<string>& params)
{
	//append a line in walletName file and check if successfull
	if(wallet.appendWalletFile(walletEntity))
	{//line appended - display success message

		//rearrange params vector for message printing ?????   **********************************************************************************
		//empty the vector
		params.resize(0);
		//check whether the command is "income" or "spend"
		if(walletEntity.getSign() == "+")
		{//the command is "income"
			//put command name in vector for SPEND_INCOME_REGISTERED_MSG
			params.push_back("income");
		}
		else
		{//the command is "spend"
			//put command name in vector for SPEND_INCOME_REGISTERED_MSG
			params.push_back("spend");
		}
		//put category in vector
		params.push_back(walletEntity.getCategory());
		//put amount in vector
		params.push_back(walletEntity.getAmount());
		//put currency in vector
		params.push_back(walletEntity.getCurrency());
		//put wallet name in vector
		params.push_back(wallet.getName());
		//put GMT format timestamp in vector
		params.push_back(walletEntity.getTimeStampGMT());

		//set success message
		ptrMessage->setMessageCode(SPEND_INCOME_REGISTERED_MSG);
	}
	else
	{//line not appended - display error message

		//rearrange params vector for message printing ?????   **********************************************************************************
		//empty the vector
		params.resize(0);
		//put wallet name in vector
		params.push_back(wallet.getName());

		//set error message
		ptrMessage->setMessageCode(COULD_NOT_OPEN_FILE_ERR);

		return false;
	}
	return true;
}
