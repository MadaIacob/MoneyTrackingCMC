#ifndef FILEHELPER_H
#define FILEHELPER_H

#include <string>

//converts windows path to c++ accepted path 
//(replaces all '\' characters with '/')
std::string convertPath(std::string givenPath);
//checks if the file fileName already exists. 
//Returns true if fileName is not already in use and false otherwise
bool validateFileName(std::string fileName);

#endif