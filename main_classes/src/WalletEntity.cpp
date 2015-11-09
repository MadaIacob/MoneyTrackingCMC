//============================================================================
// Name        : WalletEntity.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Implementation for class WalletEntity, in C++
//============================================================================

#include <iostream>
#include <string>
#include "WalletEntity.h"
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
					
	time_t WalletEntity::getTimeStamp()
	{
		return timeStamp;
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
	
	void WalletEntity::setTimeStamp()
	{
		time_t now = time(NULL);
		timeStamp = now;
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

