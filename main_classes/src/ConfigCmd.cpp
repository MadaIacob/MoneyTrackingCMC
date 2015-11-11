#include "ConfigCmd.h"
#include "Command.h"
#include "MessageHandler.h"
#include "FileHelper.h"

#include <vector>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

ConfigCmd::ConfigCmd()
{
	
}

void ConfigCmd::parseParams(vector<string>& params)
{
	if(params.empty())
	{
		if ( params.size() > 2)
		{
			ptrMessage->setMessageCode(INVALID_COM_ERR) ;
		}
		else {}
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
		size_t i = 0;
		for (; i <= paramsSize-1 ; i++)
		{
			string aux = auxParams.at(i);
			size_t foundStr = aux.find("=");
			if(foundStr != std::string::npos)
			{
				if(!(foundStr >= aux.length()-1))
				{
					//cazul in care "=" este in mijlocul primului argument
					//exemplu "default_wallet=mywallet"
					params.push_back(aux.substr(0,foundStr));
					params.push_back(aux.substr(foundStr+1));
				}
				else
				{
					//cazul in care "=" este in capatul primului argument
					//exemplu "default_wallet= mywallet"
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
				//cazul in care "=" este un argument separat
				//exemplu "default_wallet = mywallet"
				i +=2;
				if(i <= paramsSize - 1)
				{
					params.push_back(auxParams.at(i-2));
					params.push_back(auxParams.at(i));
				}
			}
			else if(i <= paramsSize - 2)
			{
				//cazul in care "=" este la inceputul argumentului doi
				//exemplu "default_wallet =mywallet"
				i++;
				
				aux = auxParams.at(i);
				if(aux.find("=") != string::npos)
				{
					params.push_back(auxParams.at(i-1));
					params.push_back(aux.substr(1));
				}
				else
				{
					params.clear();
					break;
				}
			}
			if((i+1) != paramsSize)
			{
				params.clear();
				break;
			}
		}
		if(params.at(0) == "" || params.at(1) == "")
		{
			params.clear();
		}
	}
	else
	{
		
	}
		
	}
}

void ConfigCmd::validateParams(vector<string>& params)
{
	
}

void ConfigCmd::executeCommand(vector<string>& params)
{
	params.push_back(config.getConfigFileName());
	
	if(validateFileName(config.getConfigFileName())
	{
		config.readConfigFile();
		if(params.size() == 0)
		{
			config.printConfigContent();
		}
		else 
		{
			if(config.existsTag(params.at(0))
			{
				config.modifyContent(params.at(0), params.at(1));
				ptrMessage->setMessageCode(TAG_CONFIGURED_MSG);
			}
			else if(config.isValidTag(params.at(0))
			{
				config.modifyContent(params.at(0), params.at(1));
				ptrMessage->setMessageCode(TAG_CONFIGURED_MSG);
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
	
}

ConfigCmd::~ConfigCmd()
{
	
}

/* int main()
{
	ConfigCmd cmd;
	vector<string> params;
	params.push_back("default_wallet=");
	//params.push_back("=");
	params.push_back("mada.wallet");
	
	cout << "params size 1: " << params.size() << endl;
	cmd.parseParams(params);
	cout << "params size 2: " << params.size() << endl;
	for(size_t i = 0; i < params.size(); i++)
	{
		cout << "elementul : " << i << params.at(i) << endl;
	}
} */