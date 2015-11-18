//============================================================================
// Name        : WalletEntity.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Implementation for class WalletEntity, in C++
//============================================================================

#include <iostream>
#include <string>
#include <cstdlib>
#include "WalletEntity.h"
#include "HelperFunctions.h"
using namespace std;
	WalletEntity::WalletEntity(const string lhSign, 
					const string lhAmount, 
					const string lhCurrency) : 
					sign(lhSign), 
					amount(lhAmount), 
					currency(lhCurrency) {}
					
	WalletEntity::WalletEntity(const string lhSign, 
					const string lhAmount, 
					const string lhCategory,
					const string lhCurrency) : 
					sign(lhSign), 
					amount(lhAmount), 
					category(lhCategory),
					currency(lhCurrency) 
	{
		setTimeStamp();
	}
	WalletEntity::WalletEntity(const string lhTimestamp,
					const string lhSign, 
					const string lhAmount, 
					const string lhCategory,
					const string lhCurrency) : 
					sign(lhSign), 
					amount(lhAmount), 
					category(lhCategory),
					currency(lhCurrency) 
	{
		timeStamp = atol(lhTimestamp.c_str());
	}
					
	time_t WalletEntity::getTimeStamp()
	{
		return timeStamp;
	}
	
	//returns unix timestamp format 
	//returns a string containing GMT calculated time, formatted like:
	//"Thu, 08 Oct 2015 10:52:40 GMT"
	string WalletEntity::getTimeStampGMT()
	{
	  struct tm * timeinfo;
	  char buffer [100];//buffer for streaming time
	  
	  //calculate GMT format for myTime
	  timeinfo = gmtime (&timeStamp);

	  //stream GMT formatted time to buffer
	  strftime (buffer,100,"%a, %d %b %Y %H:%M:%S GMT",timeinfo);

	  return buffer;
	}
	
	string WalletEntity::getSign()
	{
		return sign;;
	}
	string WalletEntity::getAmount() 
	{
		return amount;
	}
	string WalletEntity::getCategory() 
	{
		return category;
	}
	string WalletEntity::getCurrency()
	{
		return currency;;
	}
	
	void WalletEntity::setTimeStamp(const string timeValue)
	{
		if(timeValue != "")
		{
			timeStamp = stringToUnixTime(timeValue);
		}
		else
		{
			timeStamp = time(NULL);
		}
		 
	}
	void WalletEntity::setSign(const string sign)
	{
		WalletEntity::sign = sign;
	}
	void WalletEntity::setAmount(const string amount) 
	{
		WalletEntity::amount = amount;
	}
	void WalletEntity::setCategory(const string category)
	{
		WalletEntity::category = category;
	}
	void WalletEntity::setCurrency(const string currency)
	{
		WalletEntity::currency = currency;
	}


/* int main () 
{
	WalletEntity walletEntity("+", "20.0", "other", "RON");
	//WalletEntity walletEntity("+", "200", "EUR");
	//WalletEntity walletEntity;
	cout<<"walletEntity.timeStamp = "<<walletEntity.getTimeStamp()<<endl;
	cout<<"walletEntity.sign = "<<walletEntity.getSign()<<endl;
	cout<<"walletEntity.amount = "<<walletEntity.getAmount()<<endl;
	cout<<"walletEntity.category = "<<walletEntity.getCategory()<<endl;
	cout<<"walletEntity.currency = "<<walletEntity.getCurrency()<<endl;
} 
 */

