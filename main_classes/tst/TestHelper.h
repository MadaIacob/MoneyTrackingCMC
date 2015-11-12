#ifndef TESTHELPER_H
#define TESTHELPER_H

#include <string>

void createFile(const std::string fileName,const std::string content);
std::string readLastLine(const std::string fileName);
std::string convertPath(std::string givenPath);
bool validateFileName(std::string fileName);
#endif
