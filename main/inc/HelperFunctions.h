/*
File Description	small functions used in moneytracker
Functions			
Author				cosmin.farcau
Date				15.10.2015
*/ 

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

#include <string>

std::string cutSign(std::string validAmount);

bool existsConfigTag(std::string configTag, std::string configFileName = "moneytracker.config");

std::string readConfig(std::string configTag , std::string configFileName = "moneytracker.config");

#endif
