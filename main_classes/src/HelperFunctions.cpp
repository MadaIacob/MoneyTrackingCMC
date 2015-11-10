
#include "HelperFunctions.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>

using namespace std ;


// validates the amount input
bool validateAmount(const char word [])
{
	// valid = true means the input amount is correctly written by the user
	// and gets validated; this will be returned by 'validateAmount'
	bool valid = true;
	// states in which the 'switch' below can get during the 'for': 
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	E_ReadState state = INIT;
	
	// move through each char of the 'word' (initial amount)
	int len = strlen(word);
	// void amount case
	if(len == 0) 
	{
		return false;
	}
	else
	{}
	for (int pos = 0; pos < len; pos++)
	{
		switch (state)
		{
			//INITial state, when the 'for' starts, first char in word 
			case INIT:
			{
				if((word[pos] == '+') || 
					(word[pos] == '-') )
				{
				// if first char is + or - the next is expected to be a number
					state = EXPECT_NUM;
				}
				else if ('0' <= word[pos] && word[pos] <= '9')  
				{
				// if char is a number, then we expect the next to be a num or separator
					state = EXPECT_NUM_SEP;
				}
				else
				{
					valid = false;
					return false;
				}
			break;
			}
			//you get in this state when a number was expected
			case EXPECT_NUM:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					state = EXPECT_NUM_SEP;
				}
				else
				{
					valid = false;
					return false;
				}
			break;
			}
			//you get in this state when a number or the '.' separator was expected
			case EXPECT_NUM_SEP:
			{
				if ('0' <= word[pos] && word[pos] <= '9') 
				{
					//after getting into EXPECT_NUM_SEP state, if char is num
					//the next expected is again num or sep
					state = EXPECT_NUM_SEP;
				}
				else if (word[pos] == '.')
				{
					//after hte separator you only expect numbers (decimals)
					state = EXPECT_DEC;
				}
				else
				{
					valid = false;
					return false;
				}
			break;	
			}
			//you get in this state when a number is expected, but after the '.'
			case EXPECT_DEC:
			{
				if ('0' <= word[pos] && word[pos] <= '9' ) 
				{
					//if char is decimal, the next is expected to be also decimal
					state = EXPECT_DEC;
				}
				else
				{
					valid = false;
					return false;
				}
			break;
			}
			default:
			{
			break;
			}
		}
	}
	
	return valid;
}


string truncateAmount(const char word[])
{
	//keep word as a string
	string validAmount(word); 
	
	int len = strlen(word);
	// find the position of '.' separator
	int separatPos = 0;
	for(int i = 0; i < len; i++)
	{
		if (word[i] == '.')
		{
			separatPos = i;
		}
		else 
		{
		}
	}
	// keep maximum three decimals
	if (separatPos != 0)
	{
		validAmount.resize(separatPos+4);
	}
	
	// delete leading zeros (if any) by converting string to double
	double validValue = atof(validAmount.c_str()); 
	
	// round the second decimal, and get rid of third (if there is)
	if(validValue >= 0)
	{
	int aux = validValue*100 + 0.5;
	validValue = aux / 100.00;
	}
	 else
	{
	int aux = validValue*100 - 0.4;
	validValue = aux / 100.00;
	} 

	// convert to string the validated amount
	string amountConverted;
	ostringstream sstream;
	sstream << fixed << setprecision(2) << validValue;
	amountConverted = sstream.str();
	if(validValue >=0 ) amountConverted = '+' + amountConverted;

	return amountConverted;
}



