#include "gtest/gtest.h"

#include "BalanceCmd.h"
#include "Command.h"
#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "Config.h"

#include <vector>
#include <string>

using namespace std;

TEST(ParseParams, ValidParams)
{
	//set-up
	BalanceCmd balance ;

	vector <string> params0 ;

	vector <string> params1 ;
	params1.push_back("-c") ;
	params1.push_back("two") ;

	vector <string> params2 ;
	params2.push_back("--category") ;
	params2.push_back("two") ;

	// test
	EXPECT_EQ(true, balance.parseParams(params0));
	EXPECT_EQ(true, balance.parseParams(params1));
	EXPECT_EQ(true, balance.parseParams(params2));
}

TEST(ParseParams, InvalidParams)
{
	//set-up
	BalanceCmd balance ;

	vector <string> params1 ;
	params1.push_back("one") ;

	vector <string> params2 ;
	params2.push_back("one") ;
	params2.push_back("two") ;

	vector <string> params3 ;
	params3.push_back("one") ;
	params3.push_back("two") ;
	params3.push_back("three") ;

	EXPECT_EQ(false, balance.parseParams(params1));
	EXPECT_EQ(false, balance.parseParams(params2));
	EXPECT_EQ(false, balance.parseParams(params3));
}

/*
TEST(ValidateParams, ValidParams)
{
	// moneytracker config can not be opened
	// set-up

	//EXPECT_EQ(COULD_NOT_OPEN_CONFIG_ERR, message.getMessageCode());

	// no default wallet configured

	// wallet file can not be opened

	// category found

	// category not found


}
*/
