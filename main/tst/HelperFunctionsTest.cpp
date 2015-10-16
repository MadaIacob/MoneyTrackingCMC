/*
File Description		Tests for the helperFunctions 
Author					cosmin.farcau, 
Date					14.10.2015
*/

#include "gtest/gtest.h"
#include "HelperFunctions.h"

TEST(isFirstMinusTest, isMinus)
{
	EXPECT_EQ(true, isFirstMinus("-s34d3.5"));
	EXPECT_EQ(true, isFirstMinus("-00043"));
	EXPECT_EQ(true, isFirstMinus("--s34d3.5"));
	EXPECT_EQ(true, isFirstMinus("-@#$.s34d3.5"));
	EXPECT_EQ(true, isFirstMinus("-+,/s34d3.5"));
}

TEST(isFirstMinusTest, isNotMinus)
{
	EXPECT_EQ(false, isFirstMinus("+-4d3.5"));
	EXPECT_EQ(false, isFirstMinus("000000.5"));
	EXPECT_EQ(false, isFirstMinus("s-+9/8.34d3.5"));
	EXPECT_EQ(false, isFirstMinus("&^@kdd58es34d3"));
	EXPECT_EQ(false, isFirstMinus("123483703"));
}

TEST(cutSignTest, cutMinus)
{
	EXPECT_EQ("4d3.5", cutSign("-4d3.5"));
	EXPECT_EQ("-4d3.5", cutSign("--4d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("-#k0.634d3.5"));
	EXPECT_EQ("0003435", cutSign("-0003435"));
	EXPECT_EQ("+343.565", cutSign("-+343.565"));
}

TEST(cutSignTest, noMinus)
{
	EXPECT_EQ("4d3.5", cutSign("4d3.5"));
	EXPECT_EQ("+00003654d3.5", cutSign("+00003654d3.5"));
	EXPECT_EQ("#k0.634d3.5", cutSign("#k0.634d3.5"));
	EXPECT_EQ("0003435", cutSign("0003435"));
}
