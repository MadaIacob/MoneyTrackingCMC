#ifndef CONFIGCMD_H
#define CONFIGCMD_H

#include "Command.h"
#include "Config.h"
#include <vector>
#include <string>

class ConfigCmd : public Command {
	private:
		Command command;
		Config config;
	public:
		ConfigCmd();
		bool parseParams(std::vector<std::string>& params);
		bool validateParams(std::vector<std::string>& params);
		bool executeCommand(std::vector<std::string>& params);
		~ConfigCmd();
};

#endif