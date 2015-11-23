//============================================================================
// Name        : HelperFunctionsTest.cpp
// Author      : AmadeusCPPL
// Version     : 0.1
// Copyright   : Your copyright notice
// Description : Test implementation for HelperFunctions, in C++
//============================================================================

#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "HelperFunctions.h"
#include "TestHelper.h"
using namespace std;

TEST(validateAmountTest, notAllowedCharacters)
{
	//test
	EXPECT_EQ(false, validateAmount("-s34d3.5"));
	EXPECT_EQ(true, validateAmount("+0.000"));
	EXPECT_EQ(true, validateAmount("0"));
	EXPECT_EQ(true, validateAmount("-0.000"));
	EXPECT_EQ(false, validateAmount("3ddd4.5"));
	EXPECT_EQ(false, validateAmount("f633.5"));
	EXPECT_EQ(false, validateAmount("+343.000d35"));
	EXPECT_EQ(false, validateAmount("+34*3.00035"));
	EXPECT_EQ(false, validateAmount("+3^43.00035"));
	EXPECT_EQ(false, validateAmount("-3^43.0/0*.35"));
	EXPECT_EQ(false, validateAmount("+3^43.00<>\?035"));
	EXPECT_EQ(false, validateAmount("-3^43.00:\"?035"));
	EXPECT_EQ(false, validateAmount("+-456"));
	EXPECT_EQ(false, validateAmount("-+32.5456"));

}

TEST(validateAmountTest, leadingZeros)
{
	//test
	EXPECT_EQ(true, validateAmount("+0000.000"));
	EXPECT_EQ(true, validateAmount("00000"));
	EXPECT_EQ(true, validateAmount("-00.000"));
	EXPECT_EQ(true, validateAmount("-00003493.47895"));
	EXPECT_EQ(false, validateAmount("-0003d4.3695"));
	EXPECT_EQ(true, validateAmount("+000000006.00005"));
	EXPECT_EQ(true, validateAmount("000039998.00035"));
	EXPECT_EQ(true, validateAmount("+65"));
	EXPECT_EQ(true, validateAmount("39998"));
	EXPECT_EQ(true, validateAmount("-5"));
	EXPECT_EQ(true, validateAmount("-35987"));

}

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


TEST(truncateAmountTest, allowedCharacters)
{
	//test
	EXPECT_EQ("-3493.48", truncateAmount("-00003493.47895"));
	EXPECT_EQ("-34.37", truncateAmount("-00034.3695"));
	EXPECT_EQ("+6.00", truncateAmount("+000000006.00005"));
	EXPECT_EQ("+39998.00", truncateAmount("000039998.00035"));
	EXPECT_EQ("+349348.00", truncateAmount("349348"));
	EXPECT_EQ("-3437.00", truncateAmount("-3437"));
	EXPECT_EQ("+6.00", truncateAmount("+6"));
	EXPECT_EQ("+39998.00", truncateAmount("000039998.00035"));
	EXPECT_EQ("+00.00", truncateAmount("+000"));
	EXPECT_EQ("+00.00", truncateAmount("-0"));
	EXPECT_EQ("+00.00", truncateAmount("-000"));
	EXPECT_EQ("+00.00", truncateAmount("+0.00"));
	EXPECT_EQ("+00.00", truncateAmount("-000.000"));
	EXPECT_EQ("+00.00", truncateAmount("-0.00"));

}

TEST(stoiTest, valid)
{
	//test
	EXPECT_EQ(0, stoi("0"));
	EXPECT_EQ(0, stoi("00"));
	EXPECT_EQ(0, stoi("00000000000000"));
	EXPECT_EQ(1, stoi("1"));
	EXPECT_EQ(1, stoi("01"));
	EXPECT_EQ(20004, stoi("00000000020004"));
	EXPECT_EQ(30005, stoi("00030005"));
	EXPECT_EQ(700004, stoi("00000000000700004"));
	EXPECT_EQ(123456789, stoi("00000000000123456789"));
}

TEST(stoiTest, notValid)
{
	//test
	EXPECT_EQ(-1, stoi("+0"));
	EXPECT_EQ(-1, stoi("0.0"));
	EXPECT_EQ(-1, stoi("00000000000-000"));
	EXPECT_EQ(-1, stoi("-1"));
	EXPECT_EQ(-1, stoi("00030 005"));
	EXPECT_EQ(-1, stoi("00000000000123456789+"));
}

TEST(parseDateTimeTest, valid)
{
	//set-up
	string dateTime1 = "0-0-0000 0:00";
	string dateTime2 = "00-0-0100 0:05";
	string dateTime3 = "0-00-0000 0:10";
	string dateTime4 = "9-0-8000 00:00";
	string dateTime5 = "00-00-0080 0:00";
	string dateTime6 = "00-00-0000 00:04";	
	
	//test
	EXPECT_TRUE(parseDateTime(dateTime1));
	EXPECT_TRUE(parseDateTime(dateTime2));
	EXPECT_TRUE(parseDateTime(dateTime3));
	EXPECT_TRUE(parseDateTime(dateTime4));
	EXPECT_TRUE(parseDateTime(dateTime5));
	EXPECT_TRUE(parseDateTime(dateTime6));	
	
	//tear-down
}

TEST(parseDateTimeTest, notValid)
{
	//set-up
	string dateTime1 = "0 0-0000 0:00";
	string dateTime2 = "00-0-0100 0:005";
	string dateTime3 = "0-00-000 0:10";
	string dateTime4 = "9-0 8000 00:00";
	string dateTime5 = "00-00-0080 0-00";
	string dateTime6 = "00-00-0000 0004";	
	string dateTime7 = "0 0-0000 0:00";
	string dateTime8 = "300-0-0100 0:005";
	string dateTime9 = "G0-00-000 0:10";
	string dateTime10 = "9-0i-8000 00:00";
	string dateTime11 = "00-00-0r80 0:00";
	string dateTime12 = "00/00-0000 09:04";	
	
	//test
	EXPECT_FALSE(parseDateTime(dateTime1));
	EXPECT_FALSE(parseDateTime(dateTime2));
	EXPECT_FALSE(parseDateTime(dateTime3));
	EXPECT_FALSE(parseDateTime(dateTime4));
	EXPECT_FALSE(parseDateTime(dateTime5));
	EXPECT_FALSE(parseDateTime(dateTime6));	
	EXPECT_FALSE(parseDateTime(dateTime7));
	EXPECT_FALSE(parseDateTime(dateTime8));
	EXPECT_FALSE(parseDateTime(dateTime9));
	EXPECT_FALSE(parseDateTime(dateTime10));
	EXPECT_FALSE(parseDateTime(dateTime11));
	EXPECT_FALSE(parseDateTime(dateTime12));	
	
	//tear-down
}