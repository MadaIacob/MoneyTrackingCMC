/*
File Description	Prints error messages
Functions			prints error messages 	
Author				calin-ciprian.popita
Date				09.10.2015
*/ 

#include <iostream>
#include <string.h>
#include "PrintMessage.h"

using namespace std;
//prints messages
void printMessage( const char messageCode,
	string fileName,
	string initialAmount
	)
{
	switch (messageCode)
	{
		case 0:
		{
			cout << "error: unknown command !" << endl;
			break;
		};
		case 1:
		{
			cout << "error: at least filename should be specified." << endl;
			break;
		};
		case 2:
		{
			cout << "error: " << initialAmount 
			<< " is not a valid initial ammount.\nCreating "
			<< fileName <<" aborted."
			<< endl;
			break;
		};
		case 3:
		{
			cout << "error: characters  < > : \" / \\ | ? *  are not allowed !"
			<< endl;
			break;
		};
		case 4:
		{
			cout << "error: wallet "<< fileName << " already exists!\n";
			break;
		};
		case 5:
		{
			cout <<" writing file error! " << endl;
			break;
		};
		case 6:
		{
			cout << fileName << " created with the initial amount of "
			<< initialAmount << " RON" << endl;
			break;
		};
		default: //unknown messageCode value
		{
			cout << "unknown" << endl;
			
		};
		
	};
}