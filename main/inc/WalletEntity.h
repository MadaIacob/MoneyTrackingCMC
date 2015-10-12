/*
File Description		Header file representing WalletEntity class interface
Author					Mada Iacob
Date					8.10.2015
*/


#ifndef WALLETENTITY_H
#define WALLETENTITY_H

#include <string>

class WalletEntity
{
	public:
		//default constructor
		WalletEntity();
		//creates a wallet with a given name and a given amount
		//if amount is not specified then it is by default 00.00
		void createWallet(
			const std::string walletName, 
			const std::string initialAmount = "+00.00");
};

#endif // WALLETENTITY_H