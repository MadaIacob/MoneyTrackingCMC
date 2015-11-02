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

using namespace std;

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

TEST(getBalanceTest, singleEntryBalance_NoCategory)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "test.wallet";
	arguments[1] = "";
	helperCreateWallet("test.wallet","+00.00");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down	
	delete[] arguments;
	remove("test.wallet");
}

TEST(getBalanceTest, negativeBalance_NoCategory)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "";
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "+", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "700", "other", "RON", "wallet");
	std::string balance = "-100.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getBalanceTest, positiveBalance_NoCategory)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "";
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "-", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "700", "other", "RON", "wallet");
	std::string balance = "+300.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getBalanceTest, zeroBalance_NoCategory)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "";
	helperCreateWallet("wallet", "+100.55");
	helperAddWalletEntity(125467, "-", "200", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "99.45", "other", "RON", "wallet");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getBalanceTest, singleLineWallet_Category)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "test.wallet";
	arguments[1] = "other";
	helperCreateWallet("test.wallet","+600.00");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down	
	delete[] arguments;
	remove("test.wallet");
}

TEST(getBalanceTest, negativeBalance_Category)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "spaga";
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "+", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "100", "spaga", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "700", "other", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "200", "spaga", "RON", "wallet");
	helperAddWalletEntity(132457, "-", "300", "spaga", "RON", "wallet");
	std::string balance = "-600.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getBalanceTest, positiveBalance_Category)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "salary";
	helperCreateWallet("wallet", "+100.00");
	helperAddWalletEntity(125467, "+", "500", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "700", "other", "RON", "wallet");
	helperAddWalletEntity(125467, "+", "100", "salary", "RON", "wallet");
	helperAddWalletEntity(125467, "+", "305.62", "salary", "RON", "wallet");
	std::string balance = "+905.62";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getBalanceTest, noMatchingCategory)
{
	//set-up
	std::string* arguments = new std::string[2];
	arguments[0] = "wallet";
	arguments[1] = "food";
	helperCreateWallet("wallet", "+1000.55");
	helperAddWalletEntity(125467, "-", "100", "salary", "RON", "wallet");
	helperAddWalletEntity(132457, "+", "99.45", "other", "RON", "wallet");
	std::string balance = "+0.00";
	//test
	EXPECT_EQ(balance, getBalance(&arguments[0]));
	
	//tear-down		
	delete[] arguments;
	remove("wallet");
}

TEST(getAmountTest, validAmount)
{
	EXPECT_EQ(-0.01, getAmount("1445286465;-;0.01;other;RON"));
	EXPECT_EQ(-999.00, getAmount("1445324005;-;999.00;salary;RON"));
	EXPECT_EQ(0.01, getAmount("1445286465;+;0.01;other;RON"));
	EXPECT_EQ(9999.00, getAmount("1445324005;+;9999.00;salary;RON"));
	EXPECT_EQ(999.50, getAmount("+999.50"));
	EXPECT_EQ(-1453.78, getAmount("-1453.78"));
	
}

TEST(getArgumentsForIncomeSpendTest, outOfRangeArguments)
{
	//set-up
	char* arguments[4]={(char*) "--c", (char*) "--w", 
						 (char*) "-category", (char*) "-wallet"};
	std::string* result1 = new std::string[3];
	result1 = getArgumentsForIncomeSpend(0,&arguments[0]);
	
	std::string* result2 = new std::string[3];
	result2 = getArgumentsForIncomeSpend(1,&arguments[3]);
	
	std::string* result3 = new std::string[3];
	result3 = getArgumentsForIncomeSpend(4,&arguments[0]);
	
	//test
	EXPECT_EQ("", result1[0]);
	EXPECT_EQ("", result1[1]);
	EXPECT_EQ("", result1[2]);

	EXPECT_EQ("-wallet", result2[0]);
	EXPECT_EQ("", result2[1]);
	EXPECT_EQ("", result2[2]);

	EXPECT_EQ("", result3[0]);
	EXPECT_EQ("", result3[1]);
	EXPECT_EQ("", result3[2]);
	
	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
}

TEST(getArgumentsForIncomeSpendTest, categoryOnly)
{
	//set-up
	char* arguments1[4]={(char*) "-c", (char*) "food", 
						 (char*) "--category", (char*) "drinks"};
	std::string* result1 = new std::string[3];
	result1 = getArgumentsForIncomeSpend(4,&arguments1[0]);

	char* arguments2[4]={(char*) "--category", (char*) "drinks", 
						 (char*) "-c", (char*) "food"};
	std::string* result2 = new std::string[3];
	result2 = getArgumentsForIncomeSpend(4,&arguments2[0]);
	
	char* arguments3[4]={(char*) "-c", (char*) "--category",
						 (char*) "--category", (char*) "-c"};
	std::string* result3 = new std::string[3];
	result3 = getArgumentsForIncomeSpend(4,&arguments3[0]);

	char* arguments4[4]={(char*) "-category", (char*) "drinks",
						 (char*) "-c", (char*) "food"};
	std::string* result4 = new std::string[3];
	result4 = getArgumentsForIncomeSpend(4,&arguments4[0]);

	std::string* result5 = new std::string[3];
	result5 = getArgumentsForIncomeSpend(2,&arguments4[2]);

	//test
	EXPECT_EQ("", result1[0]);
	EXPECT_EQ("food", result1[1]);
	EXPECT_EQ("", result1[2]);

	EXPECT_EQ("", result2[0]);
	EXPECT_EQ("drinks", result2[1]);
	EXPECT_EQ("", result2[2]);

	EXPECT_EQ("", result3[0]);
	EXPECT_EQ("--category", result3[1]);
	EXPECT_EQ("", result3[2]);

	EXPECT_EQ("", result4[0]);
	EXPECT_EQ("food", result4[1]);
	EXPECT_EQ("", result4[2]);
	
	EXPECT_EQ("", result5[0]);
	EXPECT_EQ("food", result5[1]);
	EXPECT_EQ("", result5[2]);

	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
	delete[] result5;
}

TEST(getArgumentsForIncomeSpendTest, walletNameOnly)
{
	//set-up
	char* arguments1[4]={(char*) "-w", (char*) "food", 
						 (char*) "--wallet", (char*) "drinks"};
	std::string* result1 = new std::string[3];
	result1 = getArgumentsForIncomeSpend(4,&arguments1[0]);

	char* arguments2[4]={(char*) "--wallet", (char*) "drinks", 
						 (char*) "-w", (char*) "food"};
	std::string* result2 = new std::string[3];
	result2 = getArgumentsForIncomeSpend(4,&arguments2[0]);
	
	char* arguments3[4]={(char*) "-w", (char*) "--wallet",
						 (char*) "--wallet", (char*) "-c"};
	std::string* result3 = new std::string[3];
	result3 = getArgumentsForIncomeSpend(4,&arguments3[0]);

	char* arguments4[4]={(char*) "-wallet", (char*) "drinks",
						 (char*) "-w", (char*) "food"};
	std::string* result4 = new std::string[3];
	result4 = getArgumentsForIncomeSpend(4,&arguments4[0]);

	std::string* result5 = new std::string[3];
	result5 = getArgumentsForIncomeSpend(2,&arguments4[2]);

	//test
	EXPECT_EQ("", result1[0]);
	EXPECT_EQ("", result1[1]);
	EXPECT_EQ("food", result1[2]);

	EXPECT_EQ("", result2[0]);
	EXPECT_EQ("", result2[1]);
	EXPECT_EQ("drinks", result2[2]);

	EXPECT_EQ("", result3[0]);
	EXPECT_EQ("", result3[1]);
	EXPECT_EQ("--wallet", result3[2]);

	EXPECT_EQ("", result4[0]);
	EXPECT_EQ("", result4[1]);
	EXPECT_EQ("food", result4[2]);
	
	EXPECT_EQ("", result5[0]);
	EXPECT_EQ("", result5[1]);
	EXPECT_EQ("food", result5[2]);

	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
	delete[] result5;
} 

TEST(getArgumentsForIncomeSpendTest, categoryAndWalletName)
{
	//set-up
	
	//no amount
	char* arguments1[4]={(char*) "-w", (char*) "wallet", 
						 (char*) "--category", (char*) "drinks"};
	std::string* result1 = new std::string[3];
	result1 = getArgumentsForIncomeSpend(4,&arguments1[0]);

	char* arguments2[4]={(char*) "--wallet", (char*) "-w", 
						 (char*) "-c", (char*) "--category"};
	std::string* result2 = new std::string[3];
	result2 = getArgumentsForIncomeSpend(4,&arguments2[0]);
	
	char* arguments3[4]={(char*) "-c", (char*) "--wallet",
						 (char*) "--wallet", (char*) "-c"};
	std::string* result3 = new std::string[3];
	result3 = getArgumentsForIncomeSpend(4,&arguments3[0]);

	char* arguments4[4]={(char*) "--wallet", (char*) "-c",
						 (char*) "--category", (char*) "-w"};
	std::string* result4 = new std::string[3];
	result4 = getArgumentsForIncomeSpend(4,&arguments4[0]);
	
	//amount
	char* arguments01[5]={(char*) "w", 
						  (char*) "-w", (char*) "wallet", 
						  (char*) "--category", (char*) "drinks"};
	std::string* result01 = new std::string[3];
	result01 = getArgumentsForIncomeSpend(5,&arguments01[0]);

	char* arguments02[5]={(char*) "w", (char*) "--wallet",
						  (char*) "-w", 
						  (char*) "-c", (char*) "--category"};
	std::string* result02 = new std::string[3];
	result02 = getArgumentsForIncomeSpend(5,&arguments02[0]);
	
	char* arguments03[5]={(char*) "-c", (char*) "--wallet",
						  (char*) "--category", 
						  (char*) "--wallet", (char*) "-c"};
	std::string* result03 = new std::string[3];
	result03 = getArgumentsForIncomeSpend(5,&arguments03[0]);

	char* arguments04[5]={(char*) "--wallet", (char*) "-c",
						  (char*) "--category", (char*) "-w",
						  (char*) "--wallet"};
	std::string* result04 = new std::string[3];
	result04 = getArgumentsForIncomeSpend(5,&arguments04[0]);

	//test
	EXPECT_EQ("", result1[0]);
	EXPECT_EQ("drinks", result1[1]);
	EXPECT_EQ("wallet", result1[2]);

	EXPECT_EQ("", result2[0]);
	EXPECT_EQ("--category", result2[1]);
	EXPECT_EQ("-w", result2[2]);

	EXPECT_EQ("", result3[0]);
	EXPECT_EQ("--wallet", result3[1]);
	EXPECT_EQ("-c", result3[2]);

	EXPECT_EQ("", result4[0]);
	EXPECT_EQ("-w", result4[1]);
	EXPECT_EQ("-c", result4[2]);
	
	EXPECT_EQ("w", result01[0]);
	EXPECT_EQ("drinks", result01[1]);
	EXPECT_EQ("wallet", result01[2]);

	EXPECT_EQ("w", result02[0]);
	EXPECT_EQ("--category", result02[1]);
	EXPECT_EQ("-w", result02[2]);

	EXPECT_EQ("--category", result03[0]);
	EXPECT_EQ("--wallet", result03[1]);
	EXPECT_EQ("-c", result03[2]);

	EXPECT_EQ("--wallet", result04[0]);
	EXPECT_EQ("-w", result04[1]);
	EXPECT_EQ("-c", result04[2]);
	
	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
	delete[] result01;
	delete[] result02;
	delete[] result03;
	delete[] result04;
} 

TEST(getArgumentsForBalanceTest, outOfRangeArguments)
{
	//set-up
	char* arguments[4]={(char*) "--c", (char*) "--w", 
						 (char*) "-category", (char*) "-wallet"};
	std::string* result1 = new std::string[3];
	result1 = getArgumentsForBalance(0,&arguments[0]);
	
	std::string* result2 = new std::string[3];
	result2 = getArgumentsForBalance(1,&arguments[0]);
	
	std::string* result3 = new std::string[3];
	result3 = getArgumentsForBalance(4,&arguments[0]);
	
	//test
	EXPECT_EQ("", result1[0]);
	EXPECT_EQ("", result1[1]);
	EXPECT_EQ("", result1[2]);

	EXPECT_EQ("invalid", result2[0]);
	EXPECT_EQ("", result2[1]);
	EXPECT_EQ("", result2[2]);

	EXPECT_EQ("invalid", result3[0]);
	EXPECT_EQ("", result3[1]);
	EXPECT_EQ("", result3[2]);
	
	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
}
TEST(getArgumentsForBalanceTest, categoryOnly)
{
	//set-up
	char* arguments1[4]={(char*) "-c", (char*) "food", 
						 (char*) "--category", (char*) "drinks"};
	std::string* result1 = new std::string[2];
	result1 = getArgumentsForBalance(4,&arguments1[0]);

	char* arguments2[4]={(char*) "--category", (char*) "drinks", 
						 (char*) "-c", (char*) "food"};
	std::string* result2 = new std::string[2];
	result2 = getArgumentsForBalance(4,&arguments2[0]);
	
	char* arguments3[4]={(char*) "-c", (char*) "--category",
						 (char*) "--category", (char*) "-c"};
	std::string* result3 = new std::string[2];
	result3 = getArgumentsForBalance(4,&arguments3[0]);

	char* arguments4[4]={(char*) "-category", (char*) "drinks",
						 (char*) "-c", (char*) "food"};
	std::string* result4 = new std::string[2];
	result4 = getArgumentsForBalance(4,&arguments4[0]);

	std::string* result5 = new std::string[2];
	result5 = getArgumentsForBalance(2,&arguments4[2]);
	
	std::string* result6 = new std::string[2];
	result6 = getArgumentsForBalance(2,&arguments3[2]);

	//test
	EXPECT_EQ("invalid", result1[0]);
	EXPECT_EQ("", result1[1]);
	EXPECT_EQ("food", result1[2]);

	EXPECT_EQ("invalid", result2[0]);
	EXPECT_EQ("", result2[1]);
	EXPECT_EQ("drinks", result2[2]);

	EXPECT_EQ("invalid", result3[0]);
	EXPECT_EQ("", result3[1]);
	EXPECT_EQ("--category", result3[2]);

	EXPECT_EQ("invalid", result4[0]);
	EXPECT_EQ("", result4[1]);
	EXPECT_EQ("food", result4[2]);
	
	EXPECT_EQ("", result5[0]);
	EXPECT_EQ("", result5[1]);
	EXPECT_EQ("food", result5[2]);

	EXPECT_EQ("", result6[0]);
	EXPECT_EQ("", result6[1]);
	EXPECT_EQ("-c", result6[2]);

	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
	delete[] result5;
	delete[] result6;
}
/* do not erase
TEST(getArgumentsForBalanceTest, walletNameOnly)
{
	//set-up
	char* arguments1[4]={(char*) "-w", (char*) "food", (char*) "--wallet", (char*) "drinks"};
	std::string* result1 = new std::string[2];
	result1 = getArgumentsForBalance(4,&arguments1[0]);

	char* arguments2[4]={(char*) "--wallet", (char*) "drinks", (char*) "-w", (char*) "food"};
	std::string* result2 = new std::string[2];
	result2 = getArgumentsForBalance(4,&arguments2[0]);
	
	char* arguments3[4]={(char*) "-w", (char*) "-c", (char*) "--wallet", (char*) "drinks"};
	std::string* result3 = new std::string[2];
	result3 = getArgumentsForBalance(4,&arguments3[0]);

	char* arguments4[4]={(char*) "-wallet", (char*) "drinks", (char*) "-w", (char*) "-w"};
	std::string* result4 = new std::string[2];
	result4 = getArgumentsForBalance(4,&arguments4[0]);

	//test
	EXPECT_EQ("food", result1[0]);
	EXPECT_EQ("", result1[1]);

	EXPECT_EQ("drinks", result2[0]);
	EXPECT_EQ("", result2[1]);

	EXPECT_EQ("-c", result3[0]);
	EXPECT_EQ("", result3[1]);

	EXPECT_EQ("-w", result4[0]);
	EXPECT_EQ("", result4[1]);
	
	//tear-down
	delete[] result1;
	delete[] result2;
	delete[] result3;
	delete[] result4;
}*/

TEST(writeConfigTest, defaultWalletTagOK) 
{
	//set-up	
	string testOkConfigFile1("okConfig1");
	string containtOkConfig1("default_wallet = my.wallet \n default_wallet = other.wallet\n default_wallet2 =other.wallet2");
	createFile(testOkConfigFile1 , containtOkConfig1);
	
	//pre-test
	EXPECT_EQ("my.wallet", readConfig("default_wallet", testOkConfigFile1));
	EXPECT_EQ("other.wallet2", readConfig("default_wallet2", testOkConfigFile1));
	//test
	writeConfig("default_wallet",
				"mytest.wallet",
				testOkConfigFile1) ;
	EXPECT_EQ("mytest.wallet", readConfig("default_wallet", testOkConfigFile1));
	writeConfig("default_wallet2",
				"mytest.wallet2",
				testOkConfigFile1) ;
				
	EXPECT_EQ(true, writeConfig("default_wallet",
				"mytest.wallet",
				testOkConfigFile1) ) ;
	EXPECT_EQ(true, writeConfig("default_wallet2",
				"mytest.wallet2",
				testOkConfigFile1) ) ;				
	EXPECT_EQ("mytest.wallet", readConfig("default_wallet", testOkConfigFile1));
	EXPECT_EQ("mytest.wallet2", readConfig("default_wallet2", testOkConfigFile1));
	
	//tear-down
	remove("okConfig1");
	
}

TEST(writeConfigTest, defaultWalletOKNoValue) 
{
	//set-up	
	string testOkConfigFile2("okConfig3");
	string containtOkConfig1("default_wallet =  \n default_wallet = other.wallet\n default_wallet2 =other.wallet2");
	createFile(testOkConfigFile2 , containtOkConfig1);
	
	//pre-test
	EXPECT_EQ("", readConfig("default_wallet", testOkConfigFile2));
	//test
	writeConfig("default_wallet",
				"mytest.wallet",
				testOkConfigFile2) ;
	EXPECT_EQ("mytest.wallet", readConfig("default_wallet", testOkConfigFile2));
	writeConfig("default_wallet2",
				"mytest.wallet2",
				testOkConfigFile2) ;
				
	EXPECT_EQ(true, writeConfig("default_wallet",
				"mytest.wallet",
				testOkConfigFile2) ) ;
	EXPECT_EQ(true, writeConfig("default_wallet2",
				"mytest.wallet2",
				testOkConfigFile2) ) ;				
	EXPECT_EQ("mytest.wallet", readConfig("default_wallet", testOkConfigFile2));
	EXPECT_EQ("mytest.wallet2", readConfig("default_wallet2", testOkConfigFile2));
	
	//tear-down
	remove("okConfig3");
	
}

TEST(writeConfigTest, writeToNonexistingFile) 
{
	//set-up	
	string testOkConfigFile1("okConfig2");
	string containtOkConfig1("default_wallet = my.wallet \n default_wallet = other.wallet\n default_wallet2 =other.wallet2");
	createFile(testOkConfigFile1 , containtOkConfig1);
	
	//pre-test
	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig2"));
	EXPECT_EQ("other.wallet2", readConfig("default_wallet2", "okConfig2"));
	
	writeConfig("default_wallet", "mytest.wallet", "testNoConfigFile") ;
	//test
	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig2"));
	EXPECT_EQ(false, writeConfig("default_wallet", 
				"mytest.wallet",
				"testNoConfigFile") ) ;
	
	writeConfig("default_wallet2", "mytest.wallet2", "testNoConfigFile") ;
				
	EXPECT_EQ(false, writeConfig("default_wallet2",
				"mytest.wallet2",
				"testNoConfigFile") ) ;
			
	//tear-down
	remove("okConfig2");
	
}


