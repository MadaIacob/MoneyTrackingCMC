///not used for the moment

#include <fstream>
#include <string>

#include "WalletEntity.h"
#include "CreateWalletTestHelper.h"

using namespace std;

//helper function
//calls createWallet method from WalletEntity class
void helperCreateWallet(const string walletName, const string amount)
{
	WalletEntity newWallet;
	newWallet.createWallet(walletName, amount);
}

//helper function
//reads from the file created and returns the content
string readWallet(const string walletName)
{
	
	ifstream wallet(walletName.c_str());
	
	string walletContent;
	
	//read from the given file
	getline(wallet,walletContent);
	
	return walletContent;
}

//helper function 
//check if the file has been created
bool walletCreated(const string walletName)
{
	bool isCreated = false;
	ifstream wallet(walletName.c_str());
	
	if(wallet.good())
	{
		wallet.close();
		isCreated = true;
	}
	else 
	{
		isCreated = false;
	}
	
	return isCreated;
}
