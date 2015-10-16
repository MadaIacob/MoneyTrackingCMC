/*
File Description	Error messages list
Functions			
Author				calin-ciprian.popita
Date				09.10.2015
*/ 

#ifndef PRINTMESSAGE_H
#define PRINTMESSAGE_H

void printMessage( const char errorCode = -1,
	std::string parameter1 = "",
	std::string parameter2 = "",
	std::string parameter3 = "",
	std::string parameter4 = "");

#endif //PRINTMESSAGE_H
