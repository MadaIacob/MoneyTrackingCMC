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
#include <string>

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
	vector <std::string> validTags;*/


class Config
{
    private :
        std::string configFileName;
        std::vector<std::string> validTags;
        std::vector<KeyVal> configContent;
    public :
        //constructor for class Config with default fileName set to
        // "moneytracker.config" if no parameter is specified
        Config(std::string configFileName = "moneytracker.config");

        //returns all the valid default tags from the config file
        std::string validTagsToString();

        //returns the content of the config file as a vector of
        //  key->value pairs of strings
		std::vector<KeyVal> getConfigContent();

        //creates a config file with the name set to configFileName field
        //returns true in case of success and false otherwise
        bool createConfigFile();

        //reads the content of the config file and saves into a vector of
        //  key->value pairs of strings
        //returns true in case of success and false otherwise
		bool readConfigFile();

        //writes the content ot the vector of key->value pairs of strings
        //  to the the config file
        //returns true in case of success and false otherwise
		bool writeConfigFile();

        //prints the content of the vector of key->value pairs of strings
        //  to the console
		void printConfigContent();

        //checks if a tag exists and returns true if the tag exists
        //  and false otherwise
        bool existsTag(const std::string tag );

        //checks if a tag one of the default tags and returns true if
        //  the tag is a default tag and false otherwise
        bool isValidTag(const std::string tag);

        //modifies a key->value pair or adds a key->value pair if the key
        //  does not exist
        bool modifyContent(const std::string key, const std::string value);

        //returns the value for a given key or "" if key is not found
        std::string getTagValue(const std::string);

        //returns the configFileName
        std::string getConfigFileName();

};

#endif // CONFIG_H
