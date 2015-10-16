/*
File Description		Function prototypes for CommandInterpreter.cpp
Author					calin-ciprian.popita , cosmin.farcau
Date					09.10.2015
*/ 

#ifndef COMMANDINTREPRETER_H
#define COMMANDINTREPRETER_H
#include <string>

void printHelpMenu();
void executeCreate(int argc, const char fileName[], const char initialAmount[]);
bool validateCommand(int argc, char* argv[]);
bool validateFileName(std::string fileName);
bool validateAmount(const char [], const std::string );
std::string truncateAmount(const char []);
void executeIncomeSpend(
	const int argc, 
	std::string command, 
	const char amount[],
	const char fileName[]);
std::string displayGMT(time_t myTime);

#endif // COMMANDINTREPRETER_H