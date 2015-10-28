/*
File Description		Function prototypes for CommandInterpreter.cpp
Author					calin-ciprian.popita , cosmin.farcau
Date					09.10.2015
*/ 

#ifndef COMMANDINTREPRETER_H
#define COMMANDINTREPRETER_H
#include <string>

void printHelpMenu();
bool executeCreate(int argc, const char fileName[], const char initialAmount[] = "0.00");
bool validateCommand(int argc, char* argv[]);
bool validateAmount(const char []);
std::string truncateAmount(const char []);
bool executeIncomeSpend(
	const int argc, 
	char* argv[], 
	const std::string configFileName = "moneytracker.config");
bool executeBalance(
	const int argc, 
	char* argv[], 
	const std::string configFileName = "moneytracker.config");
bool incomeSpend(
	const std::string command = "", 
	const std::string truncatedAmount = "", 
	const std::string walletFile = "", 
	const std::string category = "", 
	const std::string currency = "RON");

#endif // COMMANDINTREPRETER_H