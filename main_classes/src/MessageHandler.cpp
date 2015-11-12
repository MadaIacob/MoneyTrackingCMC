#include <string>
#include <vector>
#include <iostream>
#include "MessageCodes_E.h"
#include "MessageHandler.h"

using namespace std;

MessageHandler::MessageHandler() : messageCode(NO_MESSAGE)
{

}

void MessageHandler::setMessageCode(MessageCodes_E messageCode)
{
	if(MessageHandler::messageCode == NO_MESSAGE)
	{
		MessageHandler::messageCode = messageCode;
	}
}

bool MessageHandler::isSetMessageCode()
{
	bool isSetMessage = false;
	if(messageCode != NO_MESSAGE)
	{
		isSetMessage = true;
	}

	return isSetMessage;
}

void MessageHandler::printMessage(vector<string>& parameters)
{
	switch(messageCode)
	{
		case INVALID_COM_ERR:
		{
			cout << "error: invalid command !" << endl;
			break;
		}
		case FILENAME_NOT_SPEC_ERR:
		{
			cout << "error: at least filename should be specified." << endl;
			break;
		}
		case INVALID_AMOUNT_ERR:
		{
			//parameters[0] = amount
			//parameters[1] = walletName
			cout << "error: '" << parameters.at(1) << "' is not a valid "
			<<"initial amount." << endl << "Creating '" << parameters.at(0)
			<<"' aborted." << endl;
			break;
		}
		case COULD_NOT_CREATE_ERR:
		{
			//parameters[0] = walletName
			cout << "error: could not create '" << parameters.at(0) << "'."
			<<endl;
			break;
		}
		case WALLET_EXISTS_ERR:
		{
			//parameters[0] = walletName
			cout << "error: wallet '" << parameters.at(0) << "' already exists!"
			<< endl;
			break;
		}
		case INVALID_PARAM_ERR:
		{
			//parameters[0] = command name
			cout << "error: invalid parameters for '" << parameters.at(0) << "'."
			<< endl;
			break;
		}
		case INCOME_SPEND_HIGHER_ERR:
		{
			//parameters[0] = income or spend
			string commandName = "income";

			if(parameters.at(0) == "spend")
			{
				commandName = "spending";
			}

			cout << "error: " << commandName
			<< " should be higher than 0." << endl;

			break;
		}
		case COULD_NOT_OPEN_FILE_ERR:
		{
			//parameters[0] = fileName
			cout << "error: could not open '" << parameters.at(0)
			<< "' to register transaction." << endl;
			break;
		}
		case COULD_NOT_OPEN_CONFIG_ERR:
		{
			//parameters[0] = config file name
			cout << "error: could not open configuration '" << parameters.at(0)
			<< "'." << endl;
			break;
		}
		case NO_DEFAULT_WALLET_ERR:
		{
			//parameters[3] = config file name
			cout << "error: no default wallet configured in '"
			<< parameters.at(3) << "'." << endl;
			break;
		}
		case NO_TRANSACTION_REG_ERR:
		{
			//parameters[0] = category
			//parameters[1] = walletName
			cout << "No transaction with category '" << parameters.at(0)
			<< "' is registered in '" << parameters.at(1) << "'." << endl;
			break;
		}
		case NO_VALID_CONFIG_VALUE_ERR:
		{
			//parameters[0] = config tag
			cout << "'" << parameters.at(0) << "' is not a valid configuration"
			<< " value." << endl;
			break;
		}
		case WALLET_CRETED_MSG:
		{
			//parameters[0] = wallet name
			//parameters[1] = sign
			//parameters[2] = amount
			//parameters[3] = currency
			cout << "'" << parameters.at(0)
			<< "' created with the initial amount of "
			<< parameters.at(1)<<parameters.at(2) << " " << parameters.at(3) << endl;
			break;
		}
		case SPEND_INCOME_REGISTERED_MSG:
		{
			//parameters[0] = income or spend
			//parameters[1] = category
			//parameters[2] = amount
			//parameters[3] = currency
			//parameters[4] = walletName
			//parameters[5] = GMT time
			string commandName = "income";

			if(parameters.at(0) == "spend")
			{
				commandName = "spending";
			}

			cout << commandName << " '" << parameters.at(1)
			<< "' in an amount of "<< parameters.at(2) <<" "<<parameters.at(3)
			<<" was registered to '"<< parameters.at(4)<<"'."<<endl;
			cout << "Transaction time: " << parameters.at(5) << endl;
			break;
		}
		case BALANCE_IS_MSG:
		{
			//parameters[0] = ballance
			//parameters[1] = currency
			//parameters[2] = file name
			//parameters[3] = category
			if(parameters.size() == 4)
			{
				cout << "Balance for '"	<< parameters.at(3)<< "' in '"
				<< parameters.at(2) << "' is " << parameters.at(0) << " "
				<< parameters.at(1) << "." << endl;
			}
			else
			{
				cout << "Balance for '"	<< parameters.at(2) << "' is "
				<< parameters.at(0) << " " << parameters.at(1)
				<< "." << endl;
			}
		}
		case TAG_CONFIGURED_MSG:
		{
			//parameters[1] = tag value
			cout << "'" << parameters.at(1)
			<< "' was configured as default." << endl;
			break;
		}
		case HELP_MSG:
		{
			cout << endl << "Accepted commands and arguments:" << endl;
			cout << " ------------------------------------"
			<< "---------------------------------" << endl;
			cout << " moneytracker[.exe] create <file_name> <initial_amount>"
			<< endl;
			cout << " ------------------------------------"
			<< "---------------------------------" << endl;
			cout << " moneytracker[.exe] income [-c/--category]"
			<< " <category> [-w/--wallet] <walletName>"
			<< " <initial_amount> " << endl;
			cout << " moneytracker[.exe] income <initial_amount>"
			<< " [-c/--category] <category>"
			<< " [-w/--wallet] <walletName>" << endl;
			cout << " ------------------------------------"
			<< "---------------------------------" << endl;
			cout << " moneytracker[.exe] spend [-c/--category]"
			<< " <category> <initial_amount> " << endl;
			cout << " moneytracker[.exe] spend <initial_amount>"
			<< " [-c/--category] <category>" << endl;
			cout << " ------------------------------------"
			<< "---------------------------------" << endl;
			cout << " moneytracker[.exe] balance [-c/--category] <category>"
			<< endl;
			cout << " ------------------------------------"
			<< "---------------------------------" << endl;
			cout << " moneytracker[.exe] config default_wallet[ ]=[ ] <new_tag_value> "
			<< endl;
			break;
		}
		default:
		{
			break;
		}

	}

}

MessageCodes_E MessageHandler::getMessageCode()
{
	return messageCode;
}

//displayes an error message when no Command object was created
void MessageHandler::unknownCommand(string command)
{
	if(command != "")
	{//an unknown command was provided in command line
		cout << "error: unknown command '" << command << "'!" << endl;
	}
	else
	{//no command provided in command line
		cout << "error: no command provided!" << command << endl;
	}
}
/*
 int main()
{
	MessageHandler message;
	vector<string> parameters;

	cout << "Message is set?" << message.isSetMessageCode() << endl;
	message.setMessageCode(NO_VALID_CONFIG_VALUE_ERR);
	parameters.push_back("dsffdsf");
	cout << "Message is set?" << message.isSetMessageCode() << endl;
	message.printMessage(parameters);
	cout << "Message is: " << message.getMessageCode() <<endl;
	message.unknownCommand();
	message.unknownCommand("gaina");
	} */
