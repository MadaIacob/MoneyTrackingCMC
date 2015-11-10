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
	MessageHandler message;
	
	//check if any command provided after the application name
	if ( argc > 1 ) 
	{//command provided
		//create the factory to handle the Command object
		CommandFactory factory;
		//create the proper Command object
		Command* command = factory.makeCommand(argv[1]);
		
		// associate message to command
		command->ptrMessage = &message ;
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
		
		//associate a message to command
		command->setMessageHandler(message);
		
		//prepare a vector to keep parameters
		vector<string> params;
		
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
		cout << "here ok 3 " << message.isSetMessageCode() << endl ;
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
		cout << "here ok 4 " << message.isSetMessageCode() << endl ;
		//check message
		if (message.isSetMessageCode()) 
		{//error or success in executing the command
			//print error/success message
			cout << "here ok 5 " << params.size() << endl 
			<< message.getMessageCode() << endl;
			for(unsigned int i = 0; i< params.size(); i++)
			{
				cout << "params. " << i << " = " << params.at(i) << endl;
			}
			
			message.printMessage(params);
			cout << "here ok 6 " << params.size() << endl ;
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
