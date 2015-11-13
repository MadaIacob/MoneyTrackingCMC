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
