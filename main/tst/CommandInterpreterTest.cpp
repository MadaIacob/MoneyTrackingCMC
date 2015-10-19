/*
File Description		Tests for the CommandInterpreter functions 
Author					cosmin.farcau, calin-ciprian.popita
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include "CommandInterpreter.h"

TEST(validateCommand, outOfRangeValues)
{
	//set-up
	char* argv1[2]={(char*) "unknown", (char*) "unknown"};
	char* argv2[2]={(char*) "moneytracker.exe", (char*) "unknown"};
			
	//test
	EXPECT_FALSE(validateCommand(0,&argv1[0]));
	EXPECT_FALSE(validateCommand(1,&argv1[0]));
	EXPECT_FALSE(validateCommand(2,&argv1[0]));
	EXPECT_FALSE(validateCommand(3,&argv1[0]));
	EXPECT_FALSE(validateCommand(0,&argv2[0]));
	EXPECT_FALSE(validateCommand(1,&argv2[0]));
	EXPECT_FALSE(validateCommand(2,&argv2[0]));
	EXPECT_FALSE(validateCommand(3,&argv2[0]));
	
	//tear-down		

}

TEST(validateCommand, inRangeValues)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe",(char*) "create"};
	char* argv2[3]={(char*) "moneytracker.exe",(char*) "income"};
	char* argv3[3]={(char*) "moneytracker.exe",(char*) "spend"};
			
	//test
	EXPECT_TRUE(validateCommand(2,&argv1[0]));
	EXPECT_TRUE(validateCommand(2,&argv2[0]));
	EXPECT_TRUE(validateCommand(2,&argv3[0]));
	
	//tear-down		

}
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
	EXPECT_EQ("+0.00", truncateAmount("+000"));
	EXPECT_EQ("+0.00", truncateAmount("-0"));
	EXPECT_EQ("+0.00", truncateAmount("-000"));
	EXPECT_EQ("+0.00", truncateAmount("+0.00"));
	EXPECT_EQ("+0.00", truncateAmount("-000.000"));
	EXPECT_EQ("+0.00", truncateAmount("-0.00"));

}
