//============================================================================
// Name        : WalletEntity.h
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Header for class WalletEntity, in C++
//============================================================================

#ifndef WALLETENTITY_H
#define WALLETENTITY_H

#include <string>
#include <ctime>

class WalletEntity {
	private:
		time_t timeStamp;
		std::string sign;
		double amount;
		std::string category;
		std::string currency;
		
	public:
		WalletEntity(const std::string sign = "+", const double amount = 0, 
						const std::string currency = "RON");
		time_t getTimeStamp();
		std::string getSign();
		double getAmount();
		std::string getCategory();
		std::string getCurrency();
		
		void setTimeStamp();
		void setSign(const std::string sign);
		void setAmount(const double amount);
		void setCategory(const std::string category);
		void setCurrency(const std::string currency);
};

#endif