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
#include "HelperFunctions.h"
#include <string>

using namespace std;

Config::Config(string configFileName)
{
    Config::configFileName  = configFileName;
    validTags.push_back("default_wallet");
    validTags.push_back("default_currency");
    validTags.push_back("default_income_category");
    validTags.push_back("default_spend_category");
}

string Config::validTagsToString()
{
    string result;
    //create the result string with all the tags from validTags
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
    //check if the file was created
    if (file.good())
    {
        fileOperation = true;
    }
    file.close();
    return fileOperation;
}

bool Config::readConfigFile()
{
    configContent.clear();
    bool fileOperation = false;
    ifstream file(configFileName.c_str());
    if (file.good())
    {
        size_t found;
        string line;
        while (getline(file, line))
        {
            //check if the line contains an "="
            found = line.find("=");
            if (found != std::string::npos) {
                //format a line that contains a "," so that it has a
                //  space after every comma
                for( size_t pos = 0; pos < line.length(); pos += 2)
                {
                    pos = line.find( ",", pos );
                    if( pos != string::npos )
                    {
                        unsigned int i = pos +1;
                        while(line [i] == ' ' && i < line.length()) {
                            i++;
                        }
                        line.erase( pos, i-pos );
                        line.insert( pos, ", " );
                    }
                    else break;
                }
                //get the position of the "="
                found = line.find("=");
                //separate the key val pairs
                string key = removeLRSpaces(line.substr(0, found));
                string value = removeLRSpaces(line.substr(found+1));
                
                KeyVal kV;
                kV.key = key;
                kV.value = value;
                configContent.push_back(kV);
            }
            //if the line doesn't have an "=" copy the line as it is in key
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
        //iterate trough the configContent
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            //check if the key->value pair has a value and if so,
            //  put both key and value in the line to be written to file

            line = configContent.at(i).key + " = " +
            configContent.at(i).value + "\n";

            //write the line to the file
            file << line;
        }
        //check if the operation of writing to the file was ok
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
    //check if there is something in the configContent
    if (!configContent.empty())
    {
        string line = "";
        //iterate trough the configContent and print the
        //  key->value pair to the console
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
    //check if there is something in the configContent
    if (!configContent.empty())
    {
        //iterate trough the configContent and check if the provided tag
        //  exists in the key->value pairs of the configContent
        //std::cout << "vasile mondialu" << std::endl;
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            string aux = configContent.at(i).key;
            size_t pos = aux.find("=");
            if ( pos != std::string::npos) {
                aux.erase(remove(aux.begin(), aux.end(), ' '), aux.end());
                aux.erase(remove(aux.begin(), aux.end(), '\t'), aux.end());
                string auxiliar = aux.substr(0, pos-1);
                aux = auxiliar;
            }
            if (aux == tag)
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
    //check if there is something in the validTag vector
    if (!validTags.empty())
    {
        //iterate trough the validTags and check if the provided tag
        //  exists in the validTags vector
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
    //check if there is something in the configContent
    if (!configContent.empty())
    {
        //check if the provided tag exists in the configContent vector
        if(existsTag(kv.key))
        {
            //iterate trough the configContent
            for (unsigned int i = 0; i < configContent.size(); i++)
            {
                //modify the key->value pair with the provided values
                string aux = configContent.at(i).key;
                size_t pos = aux.find("=");
                if ( pos != std::string::npos) {
                    aux.erase(remove(aux.begin(), aux.end(), ' '), aux.end());
                    aux.erase(remove(aux.begin(), aux.end(), '\t'), aux.end());
                    string auxiliar = aux.substr(0, pos-1);
                    aux = auxiliar;
                }
                if (aux == kv.key)
                {
                    configContent.at(i).key = aux;
                    configContent.at(i).value = kv.value;
                    contentModified = true;
                    break;
                }
            }
        }
        //if the provided tag doesen't exist in the configContent vector
        //  check if the tag is a valid tag and if so, add the key->value pair
        //  to the configContent
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
    //check if there is something in the configContent
    if (!configContent.empty())
    {
        //iterate trough the configContent and
        //  return the value for the provided key
        for (unsigned int i = 0; i < configContent.size(); i++)
        {
            if (configContent.at(i).key == key)
            {
                value = configContent.at(i).value;
                break;
            }
        }
    }
    return value;
}

string Config::getConfigFileName()
{
    return configFileName;
}


// string Config::removeLRSpaces(string stripString)
// {
//     while(std::isspace(*stripString.begin()))
//         stripString.erase(stripString.begin());
//
//     while(std::isspace(*stripString.rbegin()))
//         stripString.erase(stripString.length()-1);
//     return stripString;
// }



// int main(int argc, char const *argv[]) {
    // Config config("vasilica");
    // //config.createConfigFile();
    // //std::cout << "paramaterii valizi sunt : " << config.validTagsToString() << std::endl;
    // //std::cout << "crearea efectuata ? " << config.createConfigFile() << std::endl;
    // std::cout << "citirea efectuata ? " << config.readConfigFile() << std::endl;
    // vector<KeyVal> cont = config.getConfigContent();
    // std::cout << "scrierea efectuata ? " << config.writeConfigFile() << std::endl;
    // cout << "dimensiunea este : " << cont.size() << endl;
    // for (unsigned int i =0; i < cont.size(); i++)
    // {
    //     cout << "key is : " << cont.at(i).key << "-> value is : " << cont.at(i).value << std::endl;
    // }
    // config.printConfigContent();
    // cout << "exista tagul default_wallet ? : " << config.existsTag("default_wallet") << endl;
    // //cout << "este valid tagul  default_wallet ? : " << config.isValidTag("default_wallet") << endl;
    // std::cout << "XXXXXXXXXXXXXXXXXXXXXXXXXXXXX" << std::endl;
    // cout << "modificarea efectuata cu succes ? : " << config.modifyContent("leguma","carnea") << endl;
    // config.writeConfigFile();
    // cont = config.getConfigContent();
    // for (unsigned int i =0; i < cont.size(); i++)
    // {
    //     cout << "key is : " << cont.at(i).key << "-> value is : " << cont.at(i).value << std::endl;
    // }
    // std::cout << "value for default_wallet -> " << config.getTagValue("default_wallet") << std::endl;
    // std::cout << "configFileName : " << config.getConfigFileName() << std::endl;


    // Config config;
    // string aux = "    vas      ile     ";
    // std::cout << "stingul netransformat este : " << "//" << aux << "//" << std::endl;
    // std::cout << "stingul transformat este : " << "//" << config.removeLRSpaces(aux) << "//" << std::endl;
    //
    // return 0;
// }
