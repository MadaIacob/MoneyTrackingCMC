#include <iostream>
#include <string.h>

using namespace std;

void printHelpMenu();

int main(int argc, char* argv[])
{
	
	char arg1[100]; 			//how long?
	strcpy(arg1, argv[1]);
	
	if(strcmp(arg1, "create")) 	//atentie strcmp return 0
	{
		cout << "Unknown command!" << endl;
		printHelpMenu();
	}
	else
	{
		cout << "create file initialized!" <<endl;
		// create;
	}
	
	return 0;
}