#include "gtest/gtest.h"

#include "BalanceCmd.h"
#include "Wallet.h"
#include "WalletEntity.h"


TEST(ParseParams, NumberOfParams)
{
	//set-up
	
	WalletEntity entity1("+","100","RON");
	Wallet wallet1("testWallet", entity1);
	
	vector <string> params0 {} ;
	vector <string> params1 {"one"} ;
	vector <string> params2 {"one", "two"} ;
	vector <string> params3 {"one", "two", "three"} ;
	
	EXPECT_EQ(true, parseParams(params0));


}