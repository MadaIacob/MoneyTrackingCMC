#include "gtest/gtest.h"

#include "BalanceCmd.h"
#include "Command.h"
#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "Config.h"

#include <vector>
#include <string>

#include <iostream>

using namespace std;

TEST(ParseParams, Valid0And2Params)
{
	//set-up
	BalanceCmd balance ;

	vector <string> params0 ;

	vector <string> params2a ;
	params2a.push_back("-c") ;
	params2a.push_back("two") ;

	vector <string> params2b ;
	params2b.push_back("--category") ;
	params2b.push_back("two") ;

	vector <string> params2c;
	params2c.push_back("-w") ;
	params2c.push_back("two") ;

	vector <string> params2d ;
	params2d.push_back("--wallet") ;
	params2d.push_back("two") ;
	
	// test
	EXPECT_EQ(true, balance.parseParams(params0)) ;
	EXPECT_EQ(true, balance.parseParams(params2a)) ;
	EXPECT_EQ(true, balance.parseParams(params2b)) ;
	EXPECT_EQ(true, balance.parseParams(params2c)) ;
	EXPECT_EQ(true, balance.parseParams(params2d)) ;	
}


TEST(ParseParams, Valid4Params_c)
{
	//set-up
	BalanceCmd balance1 ;

	vector <string> params4a ;
	params4a.push_back("-c") ;
	params4a.push_back("category") ;
	params4a.push_back("-w") ;
	params4a.push_back("walet_wal") ;

	vector <string> params4c ;
	params4c.push_back("-c") ;
	params4c.push_back("cat-)") ;
	params4c.push_back("--wallet") ;
	params4c.push_back("was12=3al") ;
	
	vector <string> params4b ;
	params4b.push_back("-c") ;
	params4b.push_back("category") ;
	params4b.push_back("-w") ;
	params4b.push_back("walet_wal") ;

	vector <string> params4d ;
	params4d.push_back("-c") ;
	params4d.push_back("cat-)") ;
	params4d.push_back("--wallet") ;
	params4d.push_back("was12=3al") ;
	
	// test
	EXPECT_EQ(true, balance1.parseParams(params4a)) ;
	EXPECT_EQ(true, balance1.parseParams(params4c)) ;
	EXPECT_EQ(true, balance1.parseParams(params4b)) ;
	EXPECT_EQ(true, balance1.parseParams(params4d)) ;	
}

TEST(ParseParams, Valid4Params_cat)
{
	//set-up
	BalanceCmd balance1 ;

	vector <string> params4a ;
	params4a.push_back("--category") ;
	params4a.push_back("cate gory") ;
	params4a.push_back("-w") ;
	params4a.push_back("walet_wal") ;

	vector <string> params4b ;
	params4b.push_back("--category") ;
	params4b.push_back("0-123bc") ;
	params4b.push_back("--wallet") ;
	params4b.push_back("0000-wal-23c") ;
	
	// test
	EXPECT_EQ(true, balance1.parseParams(params4a)) ;
	EXPECT_EQ(true, balance1.parseParams(params4b)) ;
}

TEST(ParseParams, Valid4Params_w)
{
	//set-up
	BalanceCmd balance1 ;

	vector <string> params4a ;
	params4a.push_back("-w") ;
	params4a.push_back("walet_wal") ;	
	params4a.push_back("-c") ;
	params4a.push_back("0.123 -gory") ;

	vector <string> params4b ;
	params4b.push_back("-w") ;
	params4b.push_back("0-123bc") ;
	params4b.push_back("--category") ;
	params4b.push_back("  00.0023c") ;
	
	// test
	EXPECT_EQ(true, balance1.parseParams(params4a)) ;
	EXPECT_EQ(true, balance1.parseParams(params4b)) ;
}

TEST(ParseParams, Valid4Params_wal)
{
	//set-up
	BalanceCmd balance1 ;

	vector <string> params4a ;
	params4a.push_back("--wallet") ;
	params4a.push_back("walet_wal") ;	
	params4a.push_back("-c") ;
	params4a.push_back("0.123 -gory") ;

	vector <string> params4b ;
	params4b.push_back("--wallet") ;
	params4b.push_back("0-123.23") ;
	params4b.push_back("--category") ;
	params4b.push_back("  00.0023 c 	") ;
	
	// test
	EXPECT_EQ(true, balance1.parseParams(params4a)) ;
	EXPECT_EQ(true, balance1.parseParams(params4b)) ;
}

/*
TEST(ParseParams, InvalidParams)
{
	//set-up
	BalanceCmd balance2 ;

	vector <string> params1 ;
	params1.push_back("one") ;

	vector <string> params2 ;
	params2.push_back("one") ;
	params2.push_back("two") ;

	vector <string> params3 ;
	params3.push_back("one") ;
	params3.push_back("two") ;
	params3.push_back("three") ;

	EXPECT_EQ(false, balance2.parseParams(params1));
	EXPECT_EQ(false, balance2.parseParams(params2));
	EXPECT_EQ(false, balance2.parseParams(params3));

}
*/


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

