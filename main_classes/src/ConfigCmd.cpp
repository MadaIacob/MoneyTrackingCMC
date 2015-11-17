#include "ConfigCmd.h"
#include "Command.h"
#include "MessageHandler.h"
#include "FileHelper.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

ConfigCmd::ConfigCmd()
{

}

bool ConfigCmd::parseParams(vector<string>& params)
{
	if(params.size() > 3)
	{
		//cout << "nu trebuie sa fiu aici" << endl;
		params.clear();
		params.push_back("config");
		ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
		return false;
	}
	else if(params.size() == 0)
	{
		//cout << "nu trebuie sa fiu aici 2" << endl;
		return true;
	}
	else
	{
	vector<string> auxParams;
	for(size_t i = 0; i< params.size(); i++)
	{
		auxParams.push_back(params.at(i));
	}
	params.clear();
	size_t paramsSize;

	paramsSize = auxParams.size();
	if(paramsSize >= 1)
	{
		cout << "aici0" << endl;
		size_t i = 0;
		for (; i <= paramsSize-1 ; i++)
		{
			string aux = auxParams.at(i);
			aux.erase(remove(aux.begin(), aux.end(), ' '), aux.end());
			aux.erase(remove(aux.begin(), aux.end(), '\t'), aux.end());
			size_t foundStr = aux.find("=");
			if(foundStr != std::string::npos)
			{
				cout << "nu trebuie sa fiu aici 3" << endl;
				if(!(foundStr >= aux.length()-1))
				{
					cout << "nici aici nu trebuie" << endl;
					//cazul in care "=" este in mijlocul primului argument
					//exemplu "default_wallet=mywallet"
					params.push_back(aux.substr(0,foundStr));
					params.push_back(aux.substr(foundStr+1));
				}
				else
				{
					//cazul in care "=" este in capatul primului argument
					//exemplu "default_wallet= mywallet"
					cout << "nici aici nu trebuie2" << endl;
					i++;
					if(i <= paramsSize -1)
					{
						params.push_back(aux.substr(0,foundStr));
						params.push_back(auxParams.at(i));
					}
				}
			}
			else if((i+1 <= paramsSize-1) && (strcmp(auxParams.at(i+1).c_str(),"=") == 0))
			{
				cout << "nu trebuie sa fiu aici 4" << endl;
				//cazul in care "=" este un argument separat
				//exemplu "default_wallet = mywallet"
				i +=2;
				if(i <= paramsSize - 1)
				{
					params.push_back(auxParams.at(i-2));
					params.push_back(auxParams.at(i));
				}
			}
			else if((i + 2) <= paramsSize)
			{
				//cazul in care "=" este la inceputul argumentului doi
				//exemplu "default_wallet =mywallet"
				i++;

				aux = auxParams.at(i);
				aux.erase(remove(aux.begin(), aux.end(), ' '), aux.end());
				aux.erase(remove(aux.begin(), aux.end(), '\t'), aux.end());
				if(aux.find("=") != string::npos)
				{
					cout << "nu trebuie sa fiu aici 5" << endl;
					params.push_back(auxParams.at(i-1));
					params.push_back(aux.substr(1));
				}
				else
				{
					cout << "aici 1" << endl;
					params.clear();
					params.push_back("config");
					ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
					return false;
				}
			}
			if((i+1) != paramsSize)
			{
				cout << "aici 2" << endl;
				params.clear();
				params.push_back("config");
				ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
				return false;
			}
		}
		cout << "PARAMS " << params.at(0) << " -" << params.at(1) << "-"<< endl;
		if(params.at(0) == "" || params.at(1) == "")
		{
			cout << "aici 3" << endl;
			params.clear();
			params.push_back("config");
			ptrMessage->setMessageCode(INVALID_PARAM_ERR) ;
			return false;
		}
	}
	}

	return true;
}

bool ConfigCmd::validateParams(vector<string>& params)
{
	//cout << "in validate" << endl;
	return true;
}

bool ConfigCmd::executeCommand(vector<string>& params)
{
	//cout << "in execute command" << endl;
	params.push_back(config.getConfigFileName());
	if(!validateFileName(config.getConfigFileName()))
	{
		config.readConfigFile();
		if(params.size() == 1)
		{

			config.readConfigFile();
			config.printConfigContent();
		}
		else
		{
			if(config.existsTag(params.at(0)))
			{
				config.modifyContent(params.at(0), params.at(1));
				config.writeConfigFile();
				ptrMessage->setMessageCode(TAG_CONFIGURED_MSG);
			}
			else if(config.isValidTag(params.at(0)))
			{
				config.readConfigFile();
				config.printConfigContent();
				config.modifyContent(params.at(0), params.at(1));
				config.writeConfigFile();
				ptrMessage->setMessageCode(TAG_CONFIGURED_MSG);
				config.readConfigFile();
				config.printConfigContent();
			}
			else
			{
				ptrMessage->setMessageCode(NO_VALID_CONFIG_VALUE_ERR);
			}

		}
	}
	else
	{
		ptrMessage->setMessageCode(NO_DEFAULT_WALLET_ERR);
	}

	return true;

}

ConfigCmd::~ConfigCmd()
{

}
