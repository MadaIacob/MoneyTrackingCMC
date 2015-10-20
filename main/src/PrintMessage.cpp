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
	string parameter1,
	string parameter2,
	string parameter3,
	string parameter4
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
			cout << "error: " << parameter2 
			<< " is not a valid initial ammount.\nCreating "
			<< parameter1 <<" aborted."
			<< endl;
			break;
		};
		case 3:
		{
			cout << "error: characters  < > : \" | ? *  are not allowed for naming files!"
			<< endl;
			break;
		};
		case 4:
		{
			cout << "error: wallet "<< parameter1 << " already exists!\n";
			break;
		};
		case 5:
		{
			cout <<" writing file error! " << endl;
			break;
		};
		case 6:
		{
			cout << parameter1 << " created with the initial amount of "
			<< parameter2 << " RON" << endl;
			break;
		};
		case 7://error: no ammount specified for 'spend'.
		{
			cout << "error: no ammount specified for '" << parameter1 << "'." 
			<< endl;
			break;
		};
		case 8://error: parameter for 'income' should be a positive number
		{
			cout << "error: parameter for '" << parameter1 
			<< "' should be a positive number" 	<< endl;
			break;
		};
		case 9://Spending 'other' in an amount of 145.12 RON was registered.
		{
			cout << parameter1 << " '" << parameter2
			<< "' in an amount of "<< parameter3 <<" "<<parameter4
			<<" was registered." << endl;
			break;
		};
		case 10://Transaction time: Thu, 08 Oct 2015 10:52:40 GMT
		{
			cout << "Transaction time: " << parameter1 << endl;
			break;
		};
		case 11: //error: income should be higher than 0.
		{
			if(parameter1 == "spend")
			{
				parameter1 = "spending";
			}
			cout << "error: " << parameter1
			<< " should be higher than 0." << endl;
			break;
		};
		case 12: //error: could not open 'C:\path\some.wallet' to register transaction
		{
			cout << "error: could not open '" << parameter1
			<< "' to register transaction" << endl;
			break;
		};
		case 13: //error: could not open 'moneytracker.config'
		{
			cout << "error: could not open configuration '" << parameter1	<< "'" << endl;
			break;
		};
		case 14: //error: no default wallet configured in 'moneytracker.config'
		{
			cout << "error: no default wallet configured in '" 
			<< parameter1 << "'" << endl;
			break;
		};
		
		default: //unknown messageCode value
		{
			cout << "unknown" << endl;
			
		};
		
	};
}