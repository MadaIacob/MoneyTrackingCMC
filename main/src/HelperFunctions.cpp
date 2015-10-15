/*
File Description		Smaller functions used accross the application 
Author					cosmin.farcau 
Date					15.10.2015
*/

#include <string>
#include "HelperFunctions.h"

using namespace std;

// function that checks if the first character of a string is a '-'
bool isFirstMinus (string amount)
{
	if (amount[0] == '-')
	{
		return true ;
	}
	else
	{
		return false ;
	}
}

// this cut the first char if '-'; this function is called after truncateAmount
string cutSign(string validAmount)
{
	string cutAmount = "" ;
	int len = validAmount.length();
	for(int i = 0; i < len; i++)
	{
		if ( !( (i == 0)&&(validAmount[i] == '-') ) )
		{
			cutAmount += validAmount[i] ;
		}
		else 
		{
		}
	}
	
	return cutAmount;
}
