/*
File Description		Implementation of TransactionCmd class 
Author					calin-ciprian.popita
Date					10.11.2015
*/

#include <stdlib.h>
#include "TransactionCmd.h"

using namespace std;

//constructor - chooses between income/spend
TransactionCmd::TransactionCmd(const string& command)
{
	if(command == "income")
	{//"income" command 
		//set transaction sign to (+)
		walletEntity.setSign("+");
		//set transaction category to default value
		walletEntity.setCategory("salary");
	}
	else
	{//"spend" command 
		//set transaction sign to (-)
		walletEntity.setSign("-");
		//set transaction category to default value
		walletEntity.setCategory("other");
	}
	//set transaction time stamp
	walletEntity.setTimeStamp();
}

//performs syntactic analysis - sets error message if anything besides 
//tags and amount provided for 
//income/spend  
void TransactionCmd::parseParams(vector<string>& params) 
{
	//check how many parameters were provided for income/spend
	if (!params.empty()) 
	{//at least one argument provided for income/spend command
		//signalises the first category flag found;
		bool categoryFound = false;
		//signalises the first wallet flag found;
		bool walletFound = false;
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
			{
				//first category flag found
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
			{//unwanted parameter found - set error message
				ptrMessage->setMessageCode(INVALID_PARAM_ERR);
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
			}
			else
			{//unwanted parameter found on last position - set error message
				ptrMessage->setMessageCode(INVALID_PARAM_ERR);
			}
		}
		else
		{//no parameters left after search
		}
		
	}
	else
	{//no amount provided for income/spend command - set error message
		ptrMessage->setMessageCode(INVALID_PARAM_ERR);
	}
	
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
}

// validates the values provided for income/spend parameters
void TransactionCmd::validateParams(vector<string>& params) 
{
	//----------validate amount - mandatory parameter for transaction-----------
	
	//check if amount is valid
	if(!validateAmount(walletEntity.getAmount().c_str()))
	{//amount is not valid
		//set error message
		ptrMessage->setMessageCode(INVALID_AMOUNT_ERR);
		
		//rearrange params vector for message printing ?????   **********************************************************************************
		//empty the vector
		params.resize(0);
		//put amount in vector for INVALID_AMOUNT_ERR case
		params.push_back(walletEntity.getAmount());	
		//put amount in vector for INVALID_AMOUNT_ERR case
		params.push_back(wallet.getName());	
	}
	else 
	{//amount is valid
		//truncate amount to have only two decimals and no leading zeros
		string truncatedAmount=truncateAmount(walletEntity.getAmount().c_str());
		//check if validated sum is negative or zero
		if(atof(truncatedAmount.c_str()) <= 0.00)								
		{//amount is valid, but negative or zero 
			//set error message
			ptrMessage->setMessageCode(INCOME_SPEND_HIGHER_ERR);
			//params vector is already set by parseParams method
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
		}
	}
	else
	{//no walletName provided
		//check for default_wallet tag in config
		
		//default_wallet tag exists
			//check if default_wallet file exists
			
			//default_wallet file exists
				//set default_wallet as walletName 
				wallet.setName("my.wallet");
			//default_wallet file doesn't exist
				//set error message
		
		//default_wallet tag doesn't exist
			//set error message 		
	
	}
	
}

//executes income/spend without any validations
void TransactionCmd::executeCommand(vector<string>& params)
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
	}
} 









