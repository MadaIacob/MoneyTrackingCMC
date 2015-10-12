///not used for the moment

#include <fstream>
#include <string>

#include "WalletEntity.h"
#include "CreateWalletTestHelper.h"

using namespace std;

void createWallet(const string walletName, const string amount)
{
	WalletEntity newWallet;
	newWallet.createWallet(walletName, amount);
}

string readWallet(const string walletName){
	
	ifstream wallet(walletName.c_str());
	
	string walletContent;
	
	//read from the given file
	getline(wallet,walletContent);
	
	return walletContent;
}
