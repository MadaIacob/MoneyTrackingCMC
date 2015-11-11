//============================================================================
// Name        : Config.h
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Header for class Config, in C++
//============================================================================

#ifndef CONFIG_H
#define CONFIG_H
#include <vector>

struct KeyVal {
    std::string key;
    std::string value;
};

	/*string default_wallet; // = my.wallet
	string default_currency; // = RON
	string default_income_category; // = salary
	string default_spending_category; // = other
	string currencies; // = RON, EUR, USD
	string rate_EUR_RON; // = 4.42
	string rate_RON_EUR; // = 0.23
	string rate_USD_RON; // = 3.92
	string rate_EUR_USD; // = 1.13
	vector <std::string> validTags;
	validTags.push_back("default_wallet");
	validTags.push_back("default_currency");
	validTags.push_back("default_income_category");
	validTags.push_back("default_spending_category");
	validTags.push_back("currencies");
	validTags.push_back("rate_EUR_RON");
	validTags.push_back("rate_RON_EUR");
	validTags.push_back("rate_USD_RON");
	validTags.push_back("rate_EUR_USD");*/


class Config
{
    private :
        std::string configFileName;
        std::vector<std::string> validTags;
        std::vector<KeyVal> configContent;
    public :
        Config(std::string configFileName = "moneytracker.config");
        std::string validTagsToString();
		std::vector<KeyVal> getConfigContent();
        bool createConfigFile();
		bool readConfigFile();
		bool writeConfigFile();
		void printConfigContent();
        bool existsTag(const std::string tag );
        bool isValidTag(const std::string tag);
        bool modifyContent(const std::string key, const std::string value);
        std::string getTagValue(const std::string);
        std::string getConfigFileName();

};

#endif // CONFIG_H
