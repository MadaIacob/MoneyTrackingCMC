
#include "HelperFunctions.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include <cmath>

using namespace std ;


// validates the amount input
bool validateAmount(string word)
{
	// valid = true means the input amount is correctly written by the user
	// and gets validated; this will be returned by 'validateAmount'
	bool valid = true;
	// states in which the 'switch' below can get during the 'for':
	enum E_ReadState { INIT, EXPECT_NUM, EXPECT_NUM_SEP, EXPECT_DEC };
	E_ReadState state = INIT;

	// move through each char of the 'word' (initial amount)
	int len = word.length() ;
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
				if((word.at(pos) == '+') ||
					(word.at(pos) == '-') )
				{
				// if first char is + or - the next is expected to be a number
					state = EXPECT_NUM;
				}
				else if ('0' <= word.at(pos) && word.at(pos) <= '9')
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
				if ('0' <= word.at(pos) && word.at(pos) <= '9')
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
				if ('0' <= word.at(pos) && word.at(pos) <= '9')
				{
					//after getting into EXPECT_NUM_SEP state, if char is num
					//the next expected is again num or sep
					state = EXPECT_NUM_SEP;
				}
				else if (word.at(pos) == '.')
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
				if ('0' <= word.at(pos) && word.at(pos) <= '9' )
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

string cutSign(string validAmount)
{
	string cutAmount = "" ;
	int len = validAmount.length();
	for(int i = 1; i < len; i++)
		{
			cutAmount += validAmount[i] ;
		}
	return cutAmount;
}


string truncateAmount(string word)
{
	int len = word.length();
	// find the position of '.' separator
	int separatPos = 0;
	for(int i = 0; i < len; i++)
	{
		if (word.at(i) == '.')
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
		word.resize(separatPos+4);
	}

	// delete leading zeros (if any) by converting string to double
	double validValue = atof(word.c_str());

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
	if(validValue >0 )
	{
		amountConverted = '+' + amountConverted;
	}
	else if(validValue == 0)
	{
		amountConverted = "+00.00";
	}

	return amountConverted;
}

string removeLRSpaces(string stripString)
{
    while(std::isspace(*stripString.begin()))
        stripString.erase(stripString.begin());

    while(std::isspace(*stripString.rbegin()))
        stripString.erase(stripString.length()-1);
    return stripString;
}

//converts string to int
//returns 0 if at least one character from string is not a digit
int stoi(const string stringNumber)
{
	//returned value
	int res = 0;
	//parse string one by one character
	for (unsigned int i = 0; i < stringNumber.length(); i++)
	{
		//check if digit
		if((stringNumber[i] >= '0') && (stringNumber[i] <= '9'))
		{//digit
			//iteratively calculate result using powers of 10
			//48 is ASCII value for '0'
			res += (stringNumber[i]-48)*pow(10, stringNumber.length() - i - 1);
		}
		else
		{//not digit 
			//force exit
			return 0;
		}
	}
	return res;
}

//Gets reference to a string containing GMT calculated time, formatted like:
//"DD-MM-YYYY HH:MM" (also accepts day, month and hour as one digit number)
//If input string respects format,it formattes the string like:
//"DD-MM-YYYY HH:MM" (adding zeros where needed, removing separators)
//and checks if all characters are digits
//Returns true if the string respects input format 
//and if all chars except separators are digits
bool parseDateTime(string& dateTime)
{
	//save original content
	string originalDateTime = dateTime;
	//value to return
	bool isValid = true;
	
	//check if length of string is within valid boundaries
	if((dateTime.length() <= 16) && (dateTime.length() >= 13))
	{//length of string within valid boundaries
	 //parse string
	 
	 //parse day
		//find position for separator between day and month
		int i = dateTime.find_first_of('-');
		//check if day is only one character by checking if '-' is on position 1  
		if (i == 1)
		{//day is one character
			//add "0" in front of day
			dateTime.insert(0, "0");
		}
		else if (i == 2)
		{//day is two characters
		}
		else
		{//day is not valid (more than 3 characters)
			isValid = false;
		}
		
	//parse month
		//find position for separator between month and year
		i = dateTime.find_first_of('-',3);
		//check if month is only one character by checking if '-' is on position 3
		if (i == 4)
		{//month is one character
			//add "0" in front of month
			dateTime.insert(3, "0");
		}
		else if (i == 5)
		{//month is two characters
		}
		else
		{
			isValid = false;
		}
		
	//parse year
		//find position for separator between year and hour
		i = dateTime.find_first_of(' ');
		//check if year is four characters by checking if ' ' is on position 8
		if (i == 10)
		{//year is four characters
		}
		else
		{//year is not four characters
			isValid = false;
		}
		
	//parse hour
		//find position for separator between hour and minute
		i = dateTime.find_first_of(':');
		//check if hour is only one character by checking if '-' is on position 3
		if (i == 12)
		{//hour is one character
			//add "0" in front of hour
			dateTime.insert(11, "0");
		}
		else if (i == 13)
		{//hour is two characters
		}
		else
		{
			isValid = false;
		}
		//erase hour/minute separator from string
		//dateTime.erase(10, 1);
	//parse minute
		//check if minute is written as two characters - mandatory
		//by checking if the string without separators is complete 
		if(dateTime.length() == 16)
		{//minute is written as two characters (string is complete)
			//check if all characters but the separators are digits
			for (int j = 0; j < 16; j++)
			{//loop through string one character by one
				//if separator, jump one position
				switch (j)
				{
					case 2:
					case 5:
					case 10:
					case 13: j++;
				}
				//check if not digit
				if((dateTime[j] > '9') || (dateTime[j] < '0')) 
				{//not digit
					isValid = false;	
					break;//exit for
				}
				else
				{//digit
				}
			}
			//isValid = true;
		}
		else
		{//minute is not written as two characters
			isValid = false;
		}
	}
	else
	{//string length is outof range
		isValid = false;
	}
	if (!isValid)
		dateTime = originalDateTime;
	return isValid;
}

//Gets reference to a string containing GMT calculated time, formatted like:
//"DD-MM-YYYY HH:MM" and checks it
//Returns true if the string represents a valid date/time
bool validateDateTime(string& dateTime)
{
	//value to return
	bool isValid = false;
	
	//check minute
	int minute = stoi(dateTime.substr(14, 2));
	if(minute >= 60)
	{//out of range
		return false;
	}
	else
	{}
	
	//check hour
	int hour = stoi(dateTime.substr(11, 2));
	if(hour >= 24)
	{//out of range
		return false;
	}
	else
	{}
	
	//check month
	int month = stoi(dateTime.substr(3, 2));
	if((month >= 13) || (month == 0))
	{//out of range
		return false;
	}
	else
	{}

	//check year and day if month is february
	int day = stoi(dateTime.substr(0, 2));
	int year = stoi(dateTime.substr(6, 4));
	//check year if valid leap year
	if (year >= 1970) 
	{//valid year
		//check if february and leap year
		if ((((year - 1968) % 4) == 0) && (month == 2))
		{//valid leap year and february
			if((day > 0) && (day < 30))
			{//valid day
				isValid = true;
			}
			else
			{//day out of range
			}				
		}
		else
		{//valid non-leap year
			//check month
			switch(month)
			{
				case 2:
				{//check day if february
					if((day > 0) && (day < 29))
					{//valid day
						isValid = true;
					}
					else
					{//day out of range						
					}
					break;	
				}
				case 4://april
				case 6://june
				case 9://september
				case 11://november
				{//check day
					if((day > 0) && (day < 31))
					{//valid day
						isValid = true;
					}
					else
					{//day out of range						
					}
					break;	
				}
				default: //january,march,may,july,august,october,december
				{
					if((day > 0) && (day < 32))
					{
						isValid = true;
					}
					else
					{//day out of range
						
					}
					break;	
				}
			}			
		}
	}
	else
	{//not valid year		
	}
	
	return isValid;
}

//gets reference to a string containing GMT time, formatted like:
//"DD-MM-YYYY HH:MM" 
//returns unix timestamp format 
time_t stringToUnixTime(string& dateTime)
{
	//value to return
	time_t rawtime = 0;
	//time/date pointer for easy element access 
	struct tm * timeinfo;

	
	//convert a time_t value to local struct tm value
	timeinfo = localtime(&rawtime);
	//retain hour value
	int diff = timeinfo->tm_hour;
	//convert the same time_t value to GMT struct tm value
	timeinfo = gmtime(&rawtime);
	//calculate difference between local time and GMT
	diff = diff - timeinfo->tm_hour;
	
	//calculate time/date values from string
	timeinfo->tm_year = stoi(dateTime.substr(6, 4)) - 1900;
	timeinfo->tm_mon = stoi(dateTime.substr(3, 2)) - 1;
	timeinfo->tm_mday = stoi(dateTime.substr(0, 2));
	timeinfo->tm_hour = stoi(dateTime.substr(11, 2)) + diff;//add diff to compensate
	timeinfo->tm_min = stoi(dateTime.substr(14, 2));
	timeinfo->tm_sec = 0;

	//convert to time_t
	rawtime = mktime(timeinfo);
	
	return rawtime;
}