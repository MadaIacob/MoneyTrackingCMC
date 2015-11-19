#ifndef CONFIGCMD_H
#define CONFIGCMD_H

#include "Command.h"
#include "Config.h"
#include <vector>
#include <string>

class ConfigCmd : public Command {
	private:
		Config config;
	public:
		ConfigCmd();
		ConfigCmd(std::string configFileName);
		bool parseParams(std::vector<std::string>& params);
		bool validateParams(std::vector<std::string>& params);
		bool executeCommand(std::vector<std::string>& params);
		~ConfigCmd();
};

#endif
