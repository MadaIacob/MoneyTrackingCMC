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
	if ((argc == 1) || (!validateCommand(argc, &argv[0])))
	{
		printMessage(0);
		printHelpMenu();
	}

	return 0;
}