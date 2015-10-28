/*
File Description		Tests for the helperFunctions 
Author					cosmin.farcau, madalina.iacob
Date					14.10.2015
*/

#include "gtest/gtest.h"
#include "HelperFunctions.h"
#include "CreateWalletTestHelper.h"

#include <string>
#include <time.h>

TEST(cutSignTest, cutMinus)
{
	EXPECT_EQ("4d3.5", cutSign("-4d3.5"));
	EXPECT_EQ("-4d3.5", cutSign("--4d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("-#k0.634d3.5"));
	EXPECT_EQ("+343.565", cutSign("-+343.565"));
	EXPECT_EQ("0003435", cutSign("-0003435"));
	EXPECT_EQ("0.34365", cutSign("-0.34365"));
	EXPECT_EQ("0000.0123", cutSign("-0000.0123"));
	EXPECT_EQ("896123", cutSign("-896123"));
}

TEST(cutSignTest, cutPlus)
{
	EXPECT_EQ("4d3.5", cutSign("+4d3.5"));
	EXPECT_EQ("00003654d3.5", cutSign("+00003654d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("+#k0.634d3.5"));
	EXPECT_EQ("3435", cutSign("+3435"));
	EXPECT_EQ("0.3435", cutSign("+0.3435"));
	EXPECT_EQ("0000.3435", cutSign("+0000.3435"));
}

TEST(validateFileNameTest, existingFileName)
{
	//set-up
	helperCreateWallet("some.wallet","0.23");
	
	//test
	EXPECT_EQ(false, validateFileName("some.wallet"));
	EXPECT_EQ(true, validateFileName("not.wallet"));
	
	//tear-down		
	remove("some.wallet");

}

TEST(displayGMTTest, inRangeTime)
{
	//set-up
	time_t epochTime1 = 1445244094;
	time_t epochTime2 = 0;
	
	std::string expectedTime1 = "Mon, 19 Oct 2015 08:41:34 GMT";
	std::string expectedTime2 = "Thu, 01 Jan 1970 00:00:00 GMT";
	
	std::string actualTime1 = displayGMT(epochTime1);
	std::string actualTime2 = displayGMT(epochTime2);
	
	//test
	EXPECT_EQ(expectedTime1, actualTime1);
	EXPECT_EQ(expectedTime2, actualTime2);
		
}

TEST(displayGMTTest, outOfRangeTime)
{
	//set-up
	time_t epochTime = -1445244094;
	std::string expectedTime = "";
	std::string actualTime = displayGMT(epochTime);
	
	//test
	EXPECT_EQ(expectedTime, actualTime);
		
}
/*
TEST(GetBalanceTest, SingleEntryBalance)
{
	//set-up
	helperCreateWallet("test.wallet","+00.00");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance("test.wallet"));
	
	//tear-down		
	remove("test.wallet");
}

TEST(GetBalanceTest, NegativeBalance)
{
	//set-up
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "+", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "700", "other", "RON", "wallet");
	std::string balance = "-100.00";
	//test
	EXPECT_EQ(balance, getBalance("wallet"));
	
	//tear-down		
	remove("wallet");
}

TEST(GetBalanceTest, PositiveBalance)
{
	//set-up
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "-", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "700", "other", "RON", "wallet");
	std::string balance = "+300.00";
	//test
	EXPECT_EQ(balance, getBalance("wallet"));
	
	//tear-down		
	remove("wallet");
}

TEST(GetBalanceTest, ZeroBalance)
{
	//set-up
	helperCreateWallet("wallet", "+100.55");
	helperAddWalletEntity(125467, "-", "200", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "99.45", "other", "RON", "wallet");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance("wallet"));
	
	//tear-down		
	remove("wallet");
}
*/
TEST(GetAmountTest, validAmount)
{
	EXPECT_EQ(-0.01, getAmount("1445286465;-;0.01;other;RON"));
	EXPECT_EQ(-999.00, getAmount("1445324005;-;999.00;salary;RON"));
	EXPECT_EQ(0.01, getAmount("1445286465;+;0.01;other;RON"));
	EXPECT_EQ(9999.00, getAmount("1445324005;+;9999.00;salary;RON"));
}