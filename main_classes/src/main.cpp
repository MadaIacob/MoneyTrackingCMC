/*
File Description		application
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "Command.h"
#include "CommandFactory.h"
#include "MessageHandler.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char* argv[]) 
{
	//create message object
	MessageHandler message;
	//prepare a vector to keep parameters
	vector<string> params;
		
	
	//check if any command provided after the application name
	if ( argc > 1 ) 
	{//command provided
		//create the factory to handle the Command object
		CommandFactory factory;
		//create the proper Command object
		Command* command = factory.makeCommand(argv[1]);
		
		//check if the provided command is valid
		if ( command == 0 ) 
		{//no valid command provided in command line
			//set error message
			message.setMessageCode(INVALID_COM_ERR);
			//print error message
			message.printMessage(params);
			//exit
			return 0;
		}
		else
		{//valid command provided
		}
		
		// associate message object to command
		command->setMessageHandler(message);
		
		//check for parameters after the command
		if ( argc > 2 ) 
		{//valid command with parameters
			//put all parameters into vector
			for (int i = 2; i < argc; i++)
			{
				params.push_back(argv[i]);
			}
		} 
		else 
		{//valid command without parameters
		}
		//check syntax		
		command->parseParams(params);
		//check if any error so far
		if (message.isSetMessageCode()) 
		{//invalid syntax for command
			//print error message
			message.printMessage(params);
			//exit
			return 0;
		}
		else
		{}
	
		//check parameters for valid values
		command->validateParams(params);
		//check if any error so far
		if (message.isSetMessageCode()) 
		{//invalid values for parameters
			//print error message
			message.printMessage(params);
			//exit
			return 0;
		}
		else
		{}

		//execute command
		command->executeCommand(params);
		//check message
		if (message.isSetMessageCode()) 
		{//error or success in executing the command
			//print error/success message
			message.printMessage(params);
			//exit
			return 0;
		}
		else
		{}
	}
	else
	{//no command provided after the application name
		//set error message
		message.setMessageCode(INVALID_COM_ERR);
		//print error message
		message.printMessage(params);
	}

	return 0;
}
