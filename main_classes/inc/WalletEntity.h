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
		std::string amount;
		std::string category;
		std::string currency;
		
	public:
		WalletEntity(const std::string sign = "+", 
					const std::string amount = "00.00", 
					const std::string currency = "RON");
		WalletEntity(const std::string sign, 
					const std::string amount, 
					const std::string category,
					const std::string currency);
		WalletEntity(const std::string lhTimestamp,
					const std::string lhSign, 
					const std::string lhAmount, 
					const std::string lhCategory,
					const std::string lhCurrency);
		time_t getTimeStamp();
		std::string getTimeStampGMT();
		std::string getSign();
		std::string getAmount();
		std::string getCategory();
		std::string getCurrency();
		
		void setTimeStamp(std::string dateTime = "");
		void setSign(const std::string sign);
		void setAmount(const std::string amount);
		void setCategory(const std::string category);
		void setCurrency(const std::string currency);
};

#endif