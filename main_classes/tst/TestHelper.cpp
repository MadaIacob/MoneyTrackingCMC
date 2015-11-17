#include <fstream>
#include <string>
#include <cstring>

#include "TestHelper.h"

using namespace std;

//helper function
//creates a new file with given name and containt
void createFile(const string fileName,const string content)
{
	ofstream testFileConfig(fileName.c_str());

	testFileConfig << content << '\n';
}

//helper function
//returns the last line from the file
string readLastLine(const string fileName)
{
	ifstream file(fileName.c_str());
	string lastLine;
	string line;
	if(file.is_open())
	{
		while(getline(file,line))
		{
			bool isEmpty = true;
			for(unsigned int i = 0; i< line.size(); i++)
			{
				char ch = line[i];
				isEmpty = isEmpty && isspace(ch);
			}
			if(!isEmpty)
			{
				lastLine = line;
			}
		}

		file.close();
	}
	return lastLine;
}

//converts windows path to c++ accepted path
//(replaces all '\' characters with '/')
string convertPath(string givenPath)
{
	for(unsigned int i = 0; i < givenPath.length(); i++)
	{
		if(givenPath[i] == '\\')
		{
			givenPath[i] = '/';
		}
	}

	return givenPath;
}

//checks if the file fileName already exists.
//Returns true if fileName is not already in use and false otherwise
bool validateFileName(string fileName)
{
	//save first position on which '\' was found in fileName
	size_t firstFound = fileName.find("\\");
	//if at least one '\' found
	if(!firstFound)
	{
		//replace all '\' with '/' in fileName
		fileName = convertPath(fileName);
	}
	else
	{
		//keep fileName unchanged
	}

	bool isValidFileName = true;

	ifstream fileChecking(fileName.c_str());

	//check if fileName already exists
	if(fileChecking.good())
	{
		fileChecking.close();
		isValidFileName = false;
	}
	else
	{
		//valid fileName, so keep isValidFileName=true
	}

	return isValidFileName;

}

//helper function
//reads all content from a file to a string
//returns the string
string fileToString(const string fileName)
{
	//value to return
	string content = "";
	//open file and create stream object
	ifstream fileStream(fileName.c_str());
	//put file content to string
	if (fileStream.good())
    {//file ok
        string line = "";
		//read file content line by line
        while (getline(fileStream, line))
        {//append line to content string
			content = content + line + "\n";
 		}
		//cut last "\n"
		content.resize(content.length()-1);
	}
	else
	{// file not ok		
	}
	//close file
	fileStream.close();
	
	return content;
}
