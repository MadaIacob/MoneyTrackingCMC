#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>
#include <ctime>

bool validateFileName(std::string fileName) ;
std::string convertPath(std::string givenPath) ;
bool validateAmount(std::string word) ;
std::string truncateAmount(std::string word) ;
std::string cutSign(std::string validAmount) ;
std::string removeLRSpaces(std::string stripString) ;
bool parseDateTime(std::string& dateTime) ;
bool validateDateTime(std::string& dateTime) ;
time_t stringToUnixTime(std::string& dateTime) ;
int stoi(const std::string stringNumber);

#endif
