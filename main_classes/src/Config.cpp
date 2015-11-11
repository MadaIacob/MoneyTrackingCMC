//============================================================================
// Name        : Config.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Implementatiom for class Config, in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Config.h"

using namespace std;

Config::Config(string configFileName)
{
    Config::configFileName  = configFileName;
    validTags.push_back("default_wallet");
    validTags.push_back("default_currency");
    validTags.push_back("default_income_currency");
    validTags.push_back("default_spend_currency");
}
string Config::validTagsToString()
{
    string result;
    for (unsigned int i = 0; i < validTags.size(); i++)
    {
        result += validTags.at(i) + " ";
    }
    return result;
}

vector<KeyVal> Config::getConfigContent()
{
    return configContent;
}

bool Config::createConfigFile()
{
    bool fileOperation = false;
    ofstream file(configFileName.c_str());
    if (file.good())
    {
        file << "ceapa" << '\n' << "cartofi" << '\n';
        fileOperation = true;
    }
    file.close();
    return fileOperation;
}

bool Config::readConfigFile()
{
    bool fileOperation = false;
    ifstream file(configFileName.c_str());
    if (file.good())
    {
        size_t found;
        string line;
        while (getline(file, line))
        {
            found = line.find("=");
            if (found != std::string::npos) {
                line.erase(remove(line.begin(), line.end(), ' '), line.end());
                line.erase(remove(line.begin(), line.end(), '\t'), line.end());
                found = line.find("=");
                string key = line.substr(0, found);
                string value = line.substr(found+1);
                KeyVal kV;
                kV.key = key;
                kV.value = value;
                configContent.push_back(kV);
            }
            else
            {
                KeyVal kv;
                kv.key = line;
                kv.value = "";
                configContent.push_back(kv);
            }
            //std::cout << "linia este :" << line << std::endl;
        }
        fileOperation = true;
    }
    file.close();
    return fileOperation;
}


bool Config::writeConfigFile()
{
    bool fileOperation = false;
    string line = "";
    ofstream file(configFileName.c_str());
    if (!configContent.empty())
    {
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            if (configContent.at(i).value != "")
            {
                line = configContent.at(i).key + " = " +
                configContent.at(i).value + "\n";
            }
            else
            {
                line = configContent.at(i).key + "\n";
            }
            for( size_t pos = 0; pos < line.length(); pos += 2)
            {
                pos = line.find( ",", pos );
                if( pos == string::npos ) break;

                line.erase( pos, 1 );
                line.insert( pos, ", " );
            }
            file << line;
        }
        if (file.good())
        {
            fileOperation = true;
        }
    }
    file.close();
    return fileOperation;
}

void Config::printConfigContent()
{
    if (!configContent.empty())
    {
        string line = "";
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            if (configContent.at(i).value != "")
            {
                line = configContent.at(i).key + " = " +
                configContent.at(i).value + "\n";
            }
            else
            {
                line = configContent.at(i).key + "\n";
            }
            cout <<line;
        }
    }
}
bool Config::existsTag(const string tag){
    bool tagExists = false;
    if (!configContent.empty())
    {
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            if (configContent.at(i).key == tag)
            {
                tagExists = true;
            }
        }
    }
    return tagExists;
}

bool Config::isValidTag(const string tag)
{
    bool validTag = false;
    if (!validTags.empty())
    {
        for (unsigned int i = 0; i < validTags.size(); i++)
        {
            if (validTags.at(i) == tag)
            {
                validTag = true;
            }
        }
    }
    return validTag;
}
bool Config::modifyContent(const std::string key, const std::string value)
{
    KeyVal kv;
    kv.key = key;
    kv.value = value;
    bool contentModified = false;

    if (!configContent.empty())
    {
        if(existsTag(kv.key))
        {
            for (unsigned int i = 0; i < configContent.size(); i++)
            {
                if (configContent.at(i).key == kv.key)
                {
                    configContent.at(i).value = kv.value;
                    contentModified = true;
                }
            }
        }
        else if (isValidTag(kv.key))
        {
            configContent.push_back(kv);
            contentModified = true;
        }
    }
    return contentModified;
}

std::string Config::getTagValue(const std::string key)
{
    string value = "";
    if (!configContent.empty())
    {
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            if (configContent.at(i).key == key)
            {
                value = configContent.at(i).value;
            }
        }
    }
    return value;
}

// int main(int argc, char const *argv[]) {
//     Config config("vasilica");
//     //config.createConfigFile();
//     std::cout << "paramaterii valizi sunt : " << config.validTagsToString() << std::endl;
//     //std::cout << "crearea efectuata ? " << config.createConfigFile() << std::endl;
//     std::cout << "citirea efectuata ? " << config.readConfigFile() << std::endl;
//     vector<KeyVal> cont = config.getConfigContent();
//     std::cout << "scrierea efectuata ? " << config.writeConfigFile() << std::endl;
//     cout << "dimensiunea este : " << cont.size() << endl;
//     for (unsigned int i =0; i < cont.size(); i++)
//     {
//         cout << "key is : " << cont.at(i).key << "-> value is : " << cont.at(i).value << std::endl;
//     }
//     config.printConfigContent();
//     cout << "exista tagul default_wallet ? : " << config.existsTag("default_wallet") << endl;
//     cout << "este valid tagul  default_wallet ? : " << config.isValidTag("default_wallet") << endl;
//     std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
//     cout << "modificarea efectuata cu succes ? : " << config.modifyContent("gatu_masiii","ceapa_pulii") << endl;
//     config.writeConfigFile();
//     cont = config.getConfigContent();
//     for (unsigned int i =0; i < cont.size(); i++)
//     {
//         cout << "key is : " << cont.at(i).key << "-> value is : " << cont.at(i).value << std::endl;
//     }
//     std::cout << "value for default_wallet -> " << config.getTagValue("default_wallet") << std::endl;
//
//     return 0;
// }
