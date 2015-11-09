/*
File Description		application
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "../inc/Command.h"
#include "../inc/CommandFactory.h"
#include "../inc/MessageHandler.h"
#include <vector>
#include <string>

using namespace std;

int main(int argc, char* argv[]) 
{
	CommandFactory factory;
	MessageHandler message;
	
	//check if any command provided after the application name
	if ( argc > 1 ) 
	{//command provided
		Command* command = factory.makeCommand(argv[1]);
		//check if the provided command is valid
		if ( command == 0 ) 
		{//no valid command provided in command line
			//print error message
			message.unknownCommand(argv[1]);
			//exit
			return 0;
		}
		else
		{//valid command provided
		}
		
		//set message for command
		command->setMessageHandler(message);
		
		//check for parameters after the command
		if ( argc > 2 ) 
		{//valid command with parameters
			//put all parameters into vector
			vector<string> params(&argv[2], &argv[2] + argc - 2);
			//check syntax
			command->parseParams(params);
		} 
		else 
		{//valid command without parameters
			command->parseParams();
		}

		//check if any error so far
		if (message.isSetMessageCode()) 
		{//invalid syntax for command
			//print error message
			message.printMessage(command);
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
			message.printMessage(command);
			//exit
			return 0;
		}
		else
		{}

		//execute command
		command->executeCommand();
		
		//check message
		if (message.isSetMessageCode()) 
		{//error or success in executing the command
			//print error/success message
			message.printMessage(command);
			//exit
			return 0;
		}
		else
		{}
	}
	else
	{//no command provided after the application name
		message.unknownCommand();
	}

	return 0;
}
