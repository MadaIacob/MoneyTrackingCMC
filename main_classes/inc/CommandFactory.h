/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#ifndef COMMANDFACTORY_H
#define COMMANDFACTORY_H

#include "Command.h"
#include "CreateWalletCmd.h"
#include "TransactionCmd.h"
#include "BalanceCmd.h"
#include <vector>
#include <string>

class CommandFactory {
private:
        Command* ptrCmd;
public:
        CommandFactory() : ptrCmd(0) {}

        Command* makeCommand(const std::string& command);

        ~CommandFactory();
};

#endif // COMMANDFACTORY_H