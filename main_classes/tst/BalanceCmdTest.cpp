#include "gtest/gtest.h"

#include "BalanceCmd.h"
#include "Command.h"
#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "Config.h"
#include "TestHelper.h"

#include <vector>
#include <string>

#include <iostream>

using namespace std;

TEST(BalanceParseParams, Valid0And2Params)
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


TEST(BalanceParseParams, Valid4Params_c)
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

TEST(BalanceParseParams, Valid4Params_cat)
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

TEST(BalanceParseParams, Valid4Params_w)
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

TEST(BalanceParseParams, Valid4Params_wal)
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


TEST(BalanceParseParams, InvalidParamsNoTags)
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

	vector <string> params4 ;
	params4.push_back("one") ;
	params4.push_back("two") ;
	params4.push_back("three") ;
	params4.push_back("four") ;

	EXPECT_EQ(false, balance2.parseParams(params1)) ;
	EXPECT_EQ(false, balance2.parseParams(params2)) ;
	EXPECT_EQ(false, balance2.parseParams(params3)) ;
	EXPECT_EQ(false, balance2.parseParams(params4)) ;
}

TEST(BalanceParseParams, InvalidParamsTags)
{
	//set-up
	BalanceCmd balance2 ;

	vector <string> params1 ;
	params1.push_back("--category") ;

	vector <string> params2 ;
	params2.push_back("one") ;
	params2.push_back("-w") ;

	vector <string> params3 ;
	params3.push_back("-c") ;
	params3.push_back("two") ;
	params3.push_back("three") ;

	vector <string> params4 ;
	params4.push_back("-w") ;
	params4.push_back("two") ;
	params4.push_back("-w") ;
	params4.push_back("four") ;

	vector <string> params5 ;
	params5.push_back("-w") ;
	params5.push_back("two") ;
	params5.push_back("--category") ;
	params5.push_back("four") ;
	params5.push_back("five") ;

	EXPECT_EQ(false, balance2.parseParams(params1)) ;
	EXPECT_EQ(false, balance2.parseParams(params2)) ;
	EXPECT_EQ(false, balance2.parseParams(params3)) ;
	EXPECT_EQ(false, balance2.parseParams(params4)) ;
	EXPECT_EQ(false, balance2.parseParams(params5)) ;
}


TEST(BalanceValidateParams, NoConfigFile)
{
	// moneytracker config can not be opened

	// set-up
	BalanceCmd balance("noConfigFile") ;

	vector <string> params0 ;

	MessageHandler message ;
	balance.setMessageHandler(message) ;

	balance.validateParams(params0) ;

	EXPECT_EQ(false, balance.validateParams(params0)) ;
	EXPECT_EQ(COULD_NOT_OPEN_CONFIG_ERR, message.getMessageCode());

}

TEST(BalanceValidateParams, NoDefaultWallet)
{
	// default_wallet is not configured

	// set-up
	BalanceCmd balance("testConfigFile") ;
	createFile("testConfigFile" , "default_wallet = ");
	vector <string> params0 ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;

	balance.validateParams(params0) ;

	EXPECT_EQ(false, balance.validateParams(params0)) ;
	EXPECT_EQ(NO_DEFAULT_WALLET_ERR, message.getMessageCode());

}

TEST(BalanceValidateParams, CannotOpenDefaultWallet)
{
	// default_wallet can not be opened

	// set-up
	BalanceCmd balance("testConfigFile") ;
	createFile("testConfigFile" , "default_wallet = bambamparam");
	vector <string> params0 ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;
	balance.validateParams(params0) ;

	// test
	EXPECT_EQ(false, balance.validateParams(params0)) ;
	EXPECT_EQ(COULD_NOT_OPEN_FILE_BAL_ERR, message.getMessageCode());

	remove("testConfigFile") ;
}

TEST(BalanceValidateParams, CannotOpenSpecifiedWallet)
{
	// wallet specified by '-w' can not be opened

	// set-up 1
	BalanceCmd balance ;
	vector <string> params ;
	params.push_back("-w") ;
	params.push_back("inexistent_wallet") ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;
	// test
	EXPECT_EQ(false, balance.validateParams(params)) ;
	EXPECT_EQ(COULD_NOT_OPEN_FILE_BAL_ERR, message.getMessageCode());

	// set-up 2
	params.clear() ;
	params.push_back("--wallet") ;
	params.push_back("nonexistent_wallet") ;
	// test
	EXPECT_EQ(false, balance.validateParams(params)) ;
	EXPECT_EQ(COULD_NOT_OPEN_FILE_BAL_ERR, message.getMessageCode());

}

TEST(BalanceValidateParams, CategoryNotDefined)
{
	// category specified by '-c' is not found
	createFile("testWalletFile" ,
	"1447245226;-;564.00;other;RON\n"
	"1448011815;+;20.00;salary;RON\n");
	createFile("batchTestFile", "default_wallet = testWalletFile");

	// set-up 1
	BalanceCmd balance("batchTestFile") ;
	vector <string> params ;
	params.push_back("-c") ;
	params.push_back("inexistent_category") ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;
	// test
	EXPECT_EQ(false, balance.validateParams(params)) ;
	EXPECT_EQ(NO_TRANSACTION_REG_ERR, message.getMessageCode());

	// set-up 2
	BalanceCmd balance2("batchTestFile") ;
	MessageHandler message2 ;
	params.clear() ;
	params.push_back("--category") ;
	params.push_back("nonexistent_category") ;
	balance2.setMessageHandler(message2);
	// test
	EXPECT_EQ(false, balance2.validateParams(params)) ;
	EXPECT_EQ(NO_TRANSACTION_REG_ERR, message2.getMessageCode());

	// set-up 3
	BalanceCmd balance3("batchTestFile") ;
	MessageHandler message3 ;
	params.clear() ;
	params.push_back("--category") ;
	params.push_back("nonexistent_category") ;
	params.push_back("-w") ;
	params.push_back("testWalletFile") ;
	balance3.setMessageHandler(message3);
	// test
	EXPECT_EQ(false, balance3.validateParams(params)) ;
	EXPECT_EQ(NO_TRANSACTION_REG_ERR, message3.getMessageCode());

	//tear-down
	remove("testWalletFile") ;
	remove("batchTestFile");
}

TEST(BalanceValidateParams, ValidCategory)
{
	// category specified by '-c' is not found

	// set-up 1
	createFile("testWalletFile" ,
	"1447245226;-;564.00;categ;RON\n"
	"1448011815;+;20.00;salaros;RON\n");

	BalanceCmd balance ;
	vector <string> params ;
	params.push_back("-c") ;
	params.push_back("salaros") ;
	params.push_back("-w") ;
	params.push_back("testWalletFile") ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;
	// test
	EXPECT_EQ(true, balance.validateParams(params)) ;

	// tear-down
	//remove("testWalletFile") ;
}

TEST(BalanceExecuteCommand, ByCategoryAndWallet)
{
	// category specified by '-c' is not found

	// set-up 1
	createFile("testWalletFile" ,
	"1447245226;-;500.00;categ;RON\n"
	"1447245226;-;500.00;bam;RON\n"
	"1447245226;-;500.00;categ;RON\n"
	"1447245226;+;100.00;bam;RON\n"
	"1448011815;+;20.00;salaros;RON\n");

	BalanceCmd balance ;
	vector <string> params ;
	params.push_back("-c") ;
	params.push_back("bam") ;
	params.push_back("-w") ;
	params.push_back("testWalletFile") ;
	MessageHandler message ;
	balance.setMessageHandler(message) ;
	// test
	EXPECT_EQ(true, balance.validateParams(params)) ;
	EXPECT_EQ(true, balance.executeCommand(params)) ;
	EXPECT_EQ(BALANCE_IS_MSG, message.getMessageCode()) ;
	EXPECT_EQ("-400.00", params.at(0)) ;
	// tear-down
	remove("testWalletFile") ;
}
