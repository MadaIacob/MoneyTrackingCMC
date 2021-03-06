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
	char* argv1[2]={(char*) "moneytracker.exe",(char*) "create"};
	char* argv2[2]={(char*) "moneytracker.exe",(char*) "income"};
	char* argv3[2]={(char*) "moneytracker.exe",(char*) "spend"};
	char* argv4[2]={(char*) "moneytracker.exe",(char*) "balance"};
	char* argv5[2]={(char*) "moneytracker.exe",(char*) "config"};
			
	//test
	EXPECT_TRUE(validateCommand(2,&argv1[0]));
	EXPECT_TRUE(validateCommand(2,&argv2[0]));
	EXPECT_TRUE(validateCommand(2,&argv3[0]));
	EXPECT_TRUE(validateCommand(2,&argv4[0]));
	EXPECT_TRUE(validateCommand(2,&argv5[0]));
	
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
	char* argv1[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "80",
					(char*) "-c", (char*) "-c"} ;
	char* argv1b[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "800",
					(char*) "-c", (char*) "--category"} ;
	char* argv2[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "-c",
					(char*) "-w", (char*) "123"} ;
	char* argv2b[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "-c",
					(char*) "--category", (char*) "55"} ;
	char* argv3[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "--category",
					(char*) "--wallet", (char*) "999.99"} ;
	char* argv4[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category",
					(char*) "--category", (char*) "100"} ;
	char fileName[] = "executeIncomeSpendTest" ;
	helperCreateWallet(fileName) ;
	std::string configName1("configFile1") ;
	std::string configContent("sdrsrfs\n\trfsdrf\ndefault_wallet\t = \t \t\texecuteIncomeSpendTest\t\n default_wallet = some.wallet");
	createFile(configName1, configContent) ;
	
	//test
	EXPECT_EQ(true, executeIncomeSpend(3, &argv1[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv1[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(3, &argv1b[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv1b[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv2[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv2b[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv3[0], configName1)) ;
	EXPECT_EQ(true, executeIncomeSpend(5, &argv4[0], configName1)) ;
	
	//tear-down
	remove(fileName);	
	remove(configName1.c_str());
}

TEST(executeIncomeSpendTest, amountNotValid)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "-80"};
	char* argv2[3]={(char*) "moneytracker.exe", (char*) "spend", (char*) "080,555"};
	char* argv3[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "6fd80"};

	char* argv4[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "-c",(char*) "scholarship", (char*) "-80"};
	char* argv5[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "080,555", (char*) "-c", (char*) "food"};
	char* argv6[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category",(char*) "scholarship", (char*) "-80"};
	char* argv7[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "080,555", (char*) "--category", (char*) "food"};
	char* argv8[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "-c", (char*) "80", (char*) "scholarship"};
	
	char fileName[] = "executeIncomeSpendTest";
	helperCreateWallet(fileName);
	std::string configName("configFile");
	std::string configContaint("default_wallet = executeIncomeSpendTest");
	createFile(configName, configContaint);
	int noOfArguments = 3;
	
	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv1[0], configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv2[0], configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv3[0], configName));
	noOfArguments = 5;	
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv4[0], configName));	
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv5[0], configName));	
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv6[0], configName));		
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv7[0], configName));							
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments, &argv8[0], configName));	
	
	
	//tear-down
	remove(fileName);	
	remove(configName.c_str());
}

TEST(executeIncomeSpendTest, defaultWalletDoesNotExist)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "23.4"};
	char* argv2[5]={(char*) "moneytracker.exe", (char*) "spend", (char*) "23.4", (char*) "-c", (char*) "food" };
	char* argv3[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category", (char*) "food" ,(char*) "23.4"};
	
	std::string configName("configFile");
	std::string configContaint("default_wallet = executeIncomeSpendTest");
	createFile(configName, configContaint);
	int noOfArguments = 3;
	
	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv1[0],
						configName));
	noOfArguments = 5;	
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv2[0],
						configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv3[0],
						configName));					
	//tear-down
	remove(configName.c_str());
}

TEST(executeIncomeSpendTest, defaultWalletTagDoesNotExistInConfigFile)
{
	//set-up
	char fileName[] = "executeIncomeSpendTest";
	helperCreateWallet(fileName);
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "23.4"};
	char* argv2[5]={(char*) "moneytracker.exe",  (char*) "spend", (char*) "23.4", (char*) "-c", (char*) "food"};
	char* argv3[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category", (char*) "food" ,(char*) "23.4"};
	int noOfArguments = 3;
	
	std::string configName5("configFile5");
	std::string configContaint("sdrsrfs\n\trfsdrf\n default_w allet\t = \t\t\texecuteIncomeSpendTest\ndfgdfgd");
	createFile(configName5, configContaint);

	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv1[0],
						configName5));
	noOfArguments = 5;
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv2[0],
						configName5));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv3[0],
						configName5));
											
	//tear-down
	remove(fileName);	
	remove(configName5.c_str());

}

TEST(executeIncomeSpendTest, configFileDoesNotExist)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "23.4"};
	char* argv2[5]={(char*) "moneytracker.exe",  (char*) "spend", (char*) "23.4", (char*) "-c", (char*) "food"};
	char* argv3[5]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category", (char*) "food" ,(char*) "23.4"};
	std::string configName("configFile");
	int noOfArguments = 3;
	
	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv1[0],
						configName));
	noOfArguments = 5;						
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv2[0],
						configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv3[0],
						configName));
						
	//tear-down
}

TEST(executeIncomeSpendTest, amountNotSpecified)
{
	//set-up
	int noOfArguments = 2;
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "23.4"};
	
	char* argv2[3]={(char*) "moneytracker.exe", (char*) "spend", (char*) "-c"};
	char* argv3[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "--category"};
	
	char* argv4[4]={(char*) "moneytracker.exe", (char*) "spend", (char*) "-c", (char*) "food"};
	char* argv5[4]={(char*) "moneytracker.exe", (char*) "spend", (char*) "--category", (char*) "200"};
	char fileName[] = "executeIncomeSpendTest";
	
	helperCreateWallet(fileName);
	std::string configName("configFile");
	std::string configContaint("default_wallet = executeIncomeSpendTest");
	createFile(configName, configContaint);
	
	//test
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv1[0],
						configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv2[0],
						configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv3[0],
						configName));
	noOfArguments = 4;					
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv4[0],
						configName));
	EXPECT_EQ(false, executeIncomeSpend(noOfArguments,
						&argv5[0],
						configName));
						
	//tear-down
	remove(fileName);	
	remove(configName.c_str());
}

TEST(executeBalanceTest, defaultWallet_TagOK_WalletExists)
{
	//set-up
	int noOfArguments = 2;
	char* argv[2]={(char*) "moneytracker.exe", (char*) "balance"};
	std::string configName1("configFile1");
	std::string configContent("sdrsrfs\n\trfsdrf\ndefault_wallet\t = \t \t\texecuteBalance1\t\n default_wallet = some.wallet");
	createFile(configName1, configContent);
	std::string fileName1("executeBalance1");
	std::string fileContent("+1000.00");
	createFile(fileName1, fileContent);
	
	std::string configName2("configFile2");
	configContent = "default_wallet\t =executeBalance2\t\n";
	createFile(configName2, configContent);
	std::string fileName2("executeBalance2");
	fileContent = "+1000.00 RON\n1445429653;-;200.00;other;RON\n1445429660;-;200.00;other;RON\n1445429679;+;100.00;salary;RON\n1445430767;-;300.00;other;RON";
	createFile(fileName2, fileContent);
	//test
	EXPECT_EQ(true, executeBalance(noOfArguments, &argv[0], configName1));
	EXPECT_EQ(true, executeBalance(noOfArguments, &argv[0], configName2));
						
	//tear-down
	remove(fileName1.c_str());	
	remove(configName1.c_str());
	remove(fileName2.c_str());	
	remove(configName2.c_str());
} 

TEST(executeBalanceTest, defaultWallet_TagNotOK)
{
	//set-up
	int noOfArguments = 2;
	char* argv[2]={(char*) "moneytracker.exe", (char*) "balance"};
	std::string configName1("configFile1");
	std::string configContent("sdrsrfs\n\trfsdrf\nde fault_wallet\t = \t \t\texecuteBalance1\t\n default_wal let = some.wallet");
	createFile(configName1, configContent);
	std::string fileName1("executeBalance1");
	std::string fileContent("+1000.00");
	createFile(fileName1, fileContent);
	
	std::string configName2("configFile2");
	configContent = "default_wallett =executeBalance2\t\n";
	createFile(configName2, configContent);
	std::string fileName2("executeBalance2");
	fileContent = "+1000.00 RON\n1445429653;-;200.00;other;RON\n1445429660;-;200.00;other;RON\n1445429679;+;100.00;salary;RON\n1445430767;-;300.00;other;RON";
	createFile(fileName2, fileContent);

	//test
	EXPECT_EQ(false, executeBalance(noOfArguments, &argv[0], configName1));
	EXPECT_EQ(false, executeBalance(noOfArguments, &argv[0], configName2));
						
	//tear-down
	remove(fileName1.c_str());	
	remove(configName1.c_str());
	remove(fileName2.c_str());	
	remove(configName2.c_str());
}

TEST(executeBalanceTest, defaultWallet_WalletDoesNotExists)
{
	//set-up
	int noOfArguments = 2;
	char* argv[2]={(char*) "moneytracker.exe", (char*) "balance"};
	std::string configName1("configFile1");
	std::string configContent("default_wallet= executeBalance1");
	createFile(configName1, configContent);
	
	//test
	EXPECT_EQ(false, executeBalance(noOfArguments, &argv[0], configName1));
						
	//tear-down
	remove(configName1.c_str());
} 

TEST(executeBalanceTest, defaultWallet_ConfigFileDoesNotExists)
{
	//set-up
	int noOfArguments = 2;
	char* argv[2]={(char*) "moneytracker.exe", (char*) "balance"};
	std::string configName1("configFile1");
	
	//test
	EXPECT_EQ(false, executeBalance(noOfArguments, &argv[0], configName1));
						
	//tear-down
}

TEST(executeIncomeSpend_CategoryTest, validParameters)
{
	//set-up
	char* argv1[3]={(char*) "moneytracker.exe", (char*) "income", (char*) "80"};
	char* argv2[3]={(char*) "moneytracker.exe", (char*) "spend", (char*) "+0080.01234"};
	char fileName[] = "executeIncomeSpendTest";
	helperCreateWallet(fileName);
	int noOfArguments = 3;
	std::string configName1("configFile1");
	std::string configContaint("sdrsrfs\n\trfsdrf\ndefault_wallet\t = \t \t\texecuteIncomeSpendTest\t\n default_wallet = some.wallet");
	createFile(configName1, configContaint);
	
	//test
	EXPECT_EQ(true, executeIncomeSpend(noOfArguments,
						&argv1[0],
						configName1));
	EXPECT_EQ(true, executeIncomeSpend(noOfArguments,
						&argv2[0],
						configName1));
						
	//tear-down
	remove(fileName);	
	remove(configName1.c_str());
} 

TEST(executeConfigTest, validParameters)
{
	//set-up
	char * argv1[3] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest"};
	char * argv2[5] = {(char*) "moneytracker.exe",
					  (char*) "config",
					  (char*) "default_wallet",
					  (char*) "=",
					  (char*) "secondTest"};
	char * argv3[4] = {(char*) "moneytracker.exe",
					  (char*) "config",
					  (char*) "default_wallet=",
					  (char*) "thirdTest"};
	char * argv4[4] = {(char*) "moneytracker.exe",
					  (char*) "config",
					  (char*) "default_wallet",
					  (char*) "=forthTest"};
	char * argv5[4] = {(char*) "moneytracker.exe",
					  (char*) "config",
					  (char*) "default_wallet",
					  (char*) "==fifthTest"};	
					  
	std::string configFileName = "testConfig";
	std::string configContaint = "default_wallet=my.wallet\ncurrency = ";
	configContaint += "RON,EUR\ndefault_tag = something\n";
	
	createFile(configFileName.c_str(), configContaint);
	
	//test
	EXPECT_EQ(true,executeConfig(3, &argv1[0], configFileName));
	EXPECT_EQ("firstTest", getConfigValue("default_wallet", configFileName));
	EXPECT_EQ(true,executeConfig(5, &argv2[0], configFileName));
	EXPECT_EQ("secondTest", getConfigValue("default_wallet", configFileName));
	EXPECT_EQ(true,executeConfig(4, &argv3[0], configFileName));
	EXPECT_EQ("thirdTest", getConfigValue("default_wallet", configFileName));
	EXPECT_EQ(true,executeConfig(4, &argv4[0], configFileName));
	EXPECT_EQ("forthTest", getConfigValue("default_wallet", configFileName));
	EXPECT_EQ(true,executeConfig(4, &argv5[0], configFileName));
	EXPECT_EQ("=fifthTest", getConfigValue("default_wallet", configFileName));
	
	//tear-down
	remove(configFileName.c_str());
}

TEST(executeConfigTest, invalidParameters)
{
	//set-up
	char * argv1[4] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest",
					   (char*) "currency"};
	char * argv2[4] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest",
					   (char*) "currency="};
	char * argv3[5] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest",
					   (char*) "currency=",
					   (char*) "RON"};
	char * argv4[5] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest",
					   (char*) "currency",
					   (char*) "RON"};
	char * argv5[6] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet=firstTest",
					   (char*) "currency",
					   (char*) "=",
					   (char*) "RON"};
	char * argv6[4] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet",
					   (char*) "firstTest"};
	char * argv7[4] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallettt=",
					   (char*) "firstTest"};
	char * argv8[3] = {(char*) "moneytracker.exe", 
					   (char*) "config" , 
					   (char*) "default_wallet="};
					   
	std::string configFileName = "test.config";				   
	std::string configContaint = 
	"default_wallet=my.wallet\ncurrency = RON,EUR\ndefault_tag = something\n";
	createFile(configFileName, configContaint);
	
	//test
	EXPECT_EQ(false,executeConfig(4, &argv1[0], configFileName));
	EXPECT_EQ(false,executeConfig(4, &argv2[0], configFileName));
	EXPECT_EQ(false,executeConfig(5, &argv3[0], configFileName));
	EXPECT_EQ(false,executeConfig(5, &argv4[0], configFileName));
	EXPECT_EQ(false,executeConfig(6, &argv5[0], configFileName));
	EXPECT_EQ(false,executeConfig(4, &argv6[0], configFileName));
	EXPECT_EQ(false,executeConfig(4, &argv7[0], configFileName));
	EXPECT_EQ(false,executeConfig(3, &argv8[0], configFileName));
	
	//tear-down
	remove(configFileName.c_str());
}


