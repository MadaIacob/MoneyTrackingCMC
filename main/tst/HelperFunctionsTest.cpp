/*
File Description		Tests for the helperFunctions 
Author					cosmin.farcau, 
Date					14.10.2015
*/

#include "gtest/gtest.h"
#include "HelperFunctions.h"
#include "CreateWalletTestHelper.h"


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
