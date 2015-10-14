/*
File Description		application
Author					calin-ciprian.popita, cosmin.farcau
Date					09.10.2015
*/ 

#include <iostream>
#include "CommandInterpreter.h"
#include "PrintMessage.h"

using namespace std;

int main(int argc, char* argv[])
{
	// if no command or command not valid
	//(if no command supplied, validateCommand doesn't execute)
	if ((argc == 1) || (!validateCommand(argc, &argv[0])))
	{
		//print error message "error: unknown command !"
		printMessage(0);
		//display help menu (possible command syntaxes)
		printHelpMenu();
	}

	return 0;
}