/*
File Description	small functions used in moneytracker
Functions			
Author				cosmin.farcau
Date				15.10.2015
*/ 

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>

std::string cutSign(std::string validAmount);
bool existsConfigTag(
	std::string configTag = "default_wallet", 
	std::string configFileName = "moneytracker.config");
std::string readConfig(
	std::string configTag = "default_wallet" , 
	std::string configFileName = "moneytracker.config");
bool validateFileName(std::string fileName);
std::string convertPath(std::string givenPath);
std::string displayGMT(const time_t myTime);
std::string getBalance(const std::string walletName);
double getAmount(const std::string line);
std::string* getArgumentsForIncomeSpend(int argNumber, char* argv[]);

#endif
