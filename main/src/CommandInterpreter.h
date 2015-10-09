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
std::string validateAmount(const char word[]);
bool validateFileName(std::string fileName);

#endif // COMMANDINTREPRETER_H