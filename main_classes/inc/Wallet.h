//============================================================================
// Name        : Wallet.h
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Header for class Wallet, in C++
//============================================================================

#ifndef WALLET_H
#define WALLET_H
#include <vector>
#include "WalletEntity.h"

class Wallet {
	private:
		std::string walletName;
		std::vector<WalletEntity> walletContent;
		
	public:
		Wallet(const std::string walletName = "", 
				const std::string sign = "+", 
				const std::string amount = "00.00", 
				const std::string currency = "RON");
		std::string getName();
		bool readWalletFile();
		bool createWalletFile();
		bool appendWalletFile(WalletEntity walletEntity);
		bool existsWalletFile();
		WalletEntity getWalletEntityFromLine(const std::string line);
		std::vector<WalletEntity> getWalletContent();
};

#endif

