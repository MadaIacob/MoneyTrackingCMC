/*
File Description		Tests for the CommandInterpreter functions 
Author					cosmin.farcau, calin-ciprian.popita
Date					11.10.2015
*/

#include "gtest/gtest.h"

#include "CommandInterpreter.h"
#include "CreateWalletTestHelper.h"

#include <string>
#include <stdio.h>

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

TEST(validateCommand, boundaryValues)
{
	char* argv1[2]={(char*) "moneytracker.exe", (char*) "reate"};
	char* argv2[2]={(char*) "moneytracker.exe", (char*) "creat"};
	char* argv3[2]={(char*) "moneytracker.exe", (char*) "cr eate"};
	char* argv4[2]={(char*) "moneytracker.exe", (char*) "incom"};
	char* argv5[2]={(char*) "moneytracker.exe", (char*) "ncome"};
	char* argv6[2]={(char*) "moneytracker.exe", (char*) "spen"};
	char* argv7[2]={(char*) "moneytracker.exe", (char*) "pend"};
	char* argv8[2]={(char*) "moneytracker.exe", (char*) "balanc"};
	char* argv9[2]={(char*) "moneytracker.exe", (char*) "alance"};
	
	EXPECT_FALSE(validateCommand(2,&argv1[0]));
	EXPECT_FALSE(validateCommand(2,&argv2[0]));
	EXPECT_FALSE(validateCommand(2,&argv3[0]));
	EXPECT_FALSE(validateCommand(2,&argv4[0]));
	EXPECT_FALSE(validateCommand(2,&argv5[0]));	
	EXPECT_FALSE(validateCommand(2,&argv6[0]));
	EXPECT_FALSE(validateCommand(2,&argv7[0]));
	EXPECT_FALSE(validateCommand(2,&argv8[0]));
	EXPECT_FALSE(validateCommand(2,&argv9[0]));	
	
}

TEST(validateCommand, inRangeValues)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe",(char*) "create"};
	char* argv2[3]={(char*) "moneytracker.exe",(char*) "income"};
	char* argv3[3]={(char*) "moneytracker.exe",(char*) "spend"};
	char* argv4[3]={(char*) "moneytracker.exe",(char*) "balance"};
			
	//test
	EXPECT_TRUE(validateCommand(2,&argv1[0]));
	EXPECT_TRUE(validateCommand(2,&argv2[0]));
	EXPECT_TRUE(validateCommand(2,&argv3[0]));
	EXPECT_TRUE(validateCommand(2,&argv4[0]));
	
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

TEST(executeCreateTest, validParameters)
{
	//set-up
	int noOfArguments1 = 3;
	char fileName1[] = "validParametersFileTest1";
	
	int noOfArguments2 = 4;
	char fileName2[] = "validParametersFileTest2";
	char initialAmount2[] = "36.459";
	
	int noOfArguments3 = 2;
	char fileName3[] = "validParametersFileTest1";
	
	//test
	EXPECT_EQ(true,executeCreate(noOfArguments1, fileName1));
	EXPECT_EQ(true,executeCreate(noOfArguments2, fileName2, initialAmount2));
	EXPECT_EQ(false,executeCreate(noOfArguments3, fileName3));
	
	//tear-down
	remove(fileName1);
	remove(fileName2);
}

TEST(executeCreateTest, invalidParameters)
{
	//set-up
	int noOfArguments1 = 3;
	char fileName1[] = "invalidParametersFileTest1";
	
	int noOfArguments2 = 4;
	char fileName2[] = "invalidParametersFileTest2";
	char initialAmount2[] = "36,459";
	
	int noOfArguments3 = 4;
	char fileName3[] = "invalidParametersFileTest3";
	char initialAmount3[] = "36.45sd9";
	
	int noOfArguments4 = 2;
	char fileName4[] = "invalidParametersFileTest4";
	
	//test
	EXPECT_EQ(true,executeCreate(noOfArguments1, fileName1));
	EXPECT_EQ(false,executeCreate(noOfArguments1, fileName1));
	EXPECT_EQ(false,executeCreate(noOfArguments2, fileName2,initialAmount2));
	EXPECT_EQ(false,executeCreate(noOfArguments3, fileName3,initialAmount3));
	EXPECT_EQ(false,executeCreate(noOfArguments4, fileName4));
	
	//tear-down
	remove(fileName1);
	remove(fileName2);
	remove(fileName3);
	remove(fileName4);
}

TEST(executeIncomeSpendTest, validParameters)
{
	//set-up
	std::string command1 = "income";
	char amount1[] = "10.23";

	std::string command2 = "spend";
	char amount2[] = "10.23";
	
	char fileName[] = "executeIncomeSpendTest.txt";
	helperCreateWallet(fileName);
	
	int noOfArguments = 3;
	
	
	std::string configName("configFile");
	std::string configContaint("default_wallet = executeIncomeSpendTest.txt");
	createFile(configName, configContaint);
	
	//test
	EXPECT_EQ(true, executeIncomeSpend(noOfArguments,
						command1,
						amount1,
						configName,
						fileName));
	EXPECT_EQ(true, executeIncomeSpend(noOfArguments,
						command2,
						amount2,
						configName,
						fileName));
						
	//tear-down
	remove(fileName);	
	remove(configName.c_str());
} 

TEST(executeIncomeSpendTest, invalidParameters)
{
	//set-up
	
	int noOfArguments1 = 2;
	char amount1[] = "10.23";

	char amount2[] = "10,23";

	char amount3[] = "10.23ds464";
	
	char amount4[] = "-10.23464";
	
	char fileName[] = "executeIncomeSpendTest";
	char nonExistentFileName[] = "nonExistent";
	helperCreateWallet(fileName);
	helperCreateWallet(nonExistentFileName);
	std::string command = "income";
	int noOfArguments = 3;
	
	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments1,
						command,
						amount1,
						fileName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						command,
						amount2,
						fileName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						command,
						amount3,
						fileName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						command,
						amount4,
						fileName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						command,
						amount4,
						nonExistentFileName));
						
	//tear-down
	remove(fileName);	
	remove(nonExistentFileName);
}