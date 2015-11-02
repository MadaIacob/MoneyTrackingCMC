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
	string parameter4,
	string parameter5	
	)
{
	switch (messageCode)
	{
		case 0:
		{//error: unknown command !
			cout << "error: invalid command !" << endl;
			break;
		};
		case 1:
		{//error: at least filename should be specified.
			cout << "error: at least filename should be specified." << endl;
			break;
		};
		case 2:
		{//wref563r  is not a valid initial amount.
		 //Creating my.wallet aborted.
			cout << "error: '" << parameter2 
			<< "' is not a valid initial amount.\nCreating '"
			<< parameter1 <<"' aborted."
			<< endl;
			break;
		};
		case 3:
		{//error: could not create my.wallet
			cout << "error: could not create '" << parameter1 << "'."
			<< endl;
			break;
		};
		case 4:
		{//error: wallet my.wallet already exists!
			cout << "error: wallet '"<< parameter1 << "' already exists!\n";
			break;
		};
		case 5:
		{// writing file error! 
			cout <<" writing file error! " << endl;
			break;
		};
		case 6:
		{//my.wallet created with the initial amount of +55.00 RON
			cout << "'" << parameter1 << "' created with the initial amount of "
			<< parameter2 << " RON." << endl;
			break;
		};
		case 7://error: no amount specified for
		{
			cout << "error: no amount specified for '" << parameter1 << "'." 
			<< endl;
			break;
		};
		case 8://error: parameter for 'income' should be a positive number
		{
			cout << "error: invalid parameters for '" << parameter1 
			<< "'." << endl;
			break;
		};
		case 9://Spending 'other' in an amount of 145.12 RON was registered.
		{
			cout << parameter1 << " '" << parameter2
			<< "' in an amount of "<< parameter3 <<" "<<parameter4
			<<" was registered to '"<< parameter5<<"'."<<endl;
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
			<< "'" << parameter2 << "." << endl;
			break;
		};
		case 13: //error: could not open 'moneytracker.config'
		{
			cout << "error: could not open configuration '" << parameter1 
			<< "'." << endl;
			break;
		};
		case 14: //error: no default wallet configured in 'moneytracker.config'
		{
			cout << "error: no default wallet configured in '" 
			<< parameter1 << "'." << endl;
			break;
		};
		case 15: //Balance for clothes in my.wallet is +900.00 RON
		{
			if(parameter1 == "")
			{
				cout << "Balance for '"	<< parameter2 << "' is " << parameter3 
				<< " " << parameter4 << "." << endl;	
			}
			else
			{
				cout << "Balance for '"	<< parameter1 << "' in '"
				<< parameter2 << "' is " << parameter3 << " " << parameter4 << "." 
				<< endl;
			}			
			break;
		};
		case 16: ////print "error: default tag and value should be specified."
		{
			cout <<"error: default tag and value should be specified."
			<< endl;
			break;
		}
		case 17: //"parameter1 was configured as default.
		{
			cout << "'" << parameter1 << "' was configured as default." << endl;
			break;
		}
		case 18: //"parameter1 is not a valid configuration value."
		{
			cout << "'" << parameter1 << "' is not a valid configuration value."
			<< endl;
			break;
		}
		case 19: //error: invalid parameter for config.
		{
			cout << "error: invalid parameters for 'config'." << endl;
			break;
		}
		case 20: // No transaction with category salary is registered in wallet
		{
			cout << "No transaction with category '" << parameter1 
			<< "' is registered in '" << parameter2 << "'." << endl;
			break;
		}
		default: //unknown messageCode value
		{
			cout << "unknown" << endl;
			break;
		};
		
	};
}