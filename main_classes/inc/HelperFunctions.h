#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include <string>

bool validateFileName(std::string fileName) ;
std::string convertPath(std::string givenPath) ;
bool validateAmount(const char word []) ;
std::string truncateAmount(const char word[]) ;

#endif