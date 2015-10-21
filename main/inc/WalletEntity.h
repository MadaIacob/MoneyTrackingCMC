/*
File Description		Header file representing WalletEntity class interface
Author					Mada Iacob
Date					8.10.2015
*/


#ifndef WALLETENTITY_H
#define WALLETENTITY_H

#include <string>
#include <ctime>

class WalletEntity
{
	private:
		std::time_t timeEntity;
		std::string signEntity;
		std::string amountEntity;
		std::string categoryEntity;
		std::string currencyEntity;
	public:
		//default constructor
		WalletEntity();
		
		//connstructor. Creates WalletEntity object
		WalletEntity(
			const std::time_t timeEntity,
			const std::string signEntity,
			const std::string amountEntity,
			const std::string categoryEntity,
			const std::string currencyEntity = "RON");
			
		//creates a wallet with a given name and a given amount
		//if amount is not specified then it is by default 00.00
		void createWallet(
			const std::string walletName, 
			const std::string initialAmount = "+00.00");
			
		//adds new wallet entity
		bool addWalletEntity(const std::string walletName);
		double getAmount(const std::string line);
};

#endif // WALLETENTITY_H