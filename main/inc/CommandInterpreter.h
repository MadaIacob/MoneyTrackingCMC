/*
File Description		Function prototypes for CommandInterpreter.cpp
Author					calin-ciprian.popita , cosmin.farcau
Date					09.10.2015
*/ 

#ifndef COMMANDINTREPRETER_H
#define COMMANDINTREPRETER_H
#include <string>

void printHelpMenu();
void validateCreate(int argc, const char fileName[], const char initialAmount[]);
bool validateCommand(int argc, char* argv[]);
bool validateFileName(std::string fileName);
//std::string validateAmount(const char word[]);
bool validateAmount(const char [], const std::string );
std::string truncateAmount(const char []);

#endif // COMMANDINTREPRETER_H