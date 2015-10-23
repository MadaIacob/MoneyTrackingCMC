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
	const int argc, //number of arguments from command line
	char* argv[], //arguments from the command line
	const std::string configFileName = "moneytracker.config");
bool executeBalance(
	const int argc,
	const std::string configFileName = "moneytracker.config", 
	const char fileName[] = "");

#endif // COMMANDINTREPRETER_H