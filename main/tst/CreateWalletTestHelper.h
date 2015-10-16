/*
File Description		helper methods used for testsing the  
						WalletEntity class' methods 
Author					madalina.iacob
Date					11.10.2015
*/

#ifndef CREATEWALLETTESTHELPER_H
#define CREATEWALLETTESTHELPER_H

#include <string>

void helperCreateWallet(const std::string walletName, const std::string amount = "+00.00");
std::string readWallet(const std::string walletName);
bool walletCreated(const std::string walletName);
bool helperAddWalletEntity(
	const time_t time,
	const std::string sign,
	const std::string amount,
	const std::string category,
	const std::string currency,
	const std::string walletName);
	std::string readLastLine(const std::string fileName);
void createFile(const string fileName,const string containt);
#endif