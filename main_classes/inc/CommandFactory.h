/*
File Description		factory pattern for Command, handles all commands
Author					calin-ciprian.popita
Date					09.11.2015
*/ 

#include "Command.h"
#include "CreateWallet.h"

class CommandFactory {
private:
        Command* ptrCmd;
public:
        CommandFactory() : ptrCmd(0) {}

        Command* makeCommand(const string& command);

        ~CommandFactory();
};
