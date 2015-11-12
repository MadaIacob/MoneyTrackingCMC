

#include "gtest/gtest.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include "Config.h"
using namespace std;

void createFile(const string fileName,const string containt)
{
	ofstream testFileConfig(fileName.c_str());

	testFileConfig << containt << '\n';
}

TEST(ExistsConfigTagTest, defaultWalletTagOK)
{

	//set-up
	string testOkConfigFile1("okConfig1");
	string containtOkConfig1("default_wallet = my.wallet");

	string testOkConfigFile2("okConfig2");
	string containtOkConfig2("		default_wallet 		=		 my.wallet");

	string testOkConfigFile3("okConfig3");
	string containtOkConfig3("default_wallet = 					my.wallet");

	string testOkConfigFile4("okConfig4");
	string containtOkConfig4("default_wallet = my.wallet anything else");

	// createFile(testOkConfigFile1 , containtOkConfig1);
	// createFile(testOkConfigFile2 , containtOkConfig2);
	// createFile(testOkConfigFile3 , containtOkConfig3);
	// createFile(testOkConfigFile4 , containtOkConfig4);
	Config okConfig1();

	//test
	EXPECT_EQ(true, existsConfigTag("default_wallet", "okConfig1"));
	EXPECT_EQ(true, existsConfigTag("default_wallet", "okConfig2"));
	EXPECT_EQ(true, existsConfigTag("default_wallet", "okConfig3"));
	EXPECT_EQ(true, existsConfigTag("default_wallet", "okConfig4"));

	//tear-down
	remove("okConfig1");
	remove("okConfig2");
	remove("okConfig3");
	remove("okConfig4");
}

// TEST(ExistsConfigTagTest, defaultWalletTagNotOK)
// {
// 	//set-up
// 	string testOkConfigFile1("okConfig1");
// 	string containtOkConfig1("default_wallet bad = my.wallet");
//
// 	string testOkConfigFile2("okConfig2");
// 	string containtOkConfig2("		default_wallet 	= ");
//
// 	string testOkConfigFile3("okConfig3");
// 	string containtOkConfig3("not_ default_wallet = my.wallet");
//
// 	string testOkConfigFile4("okConfig4");
// 	string containtOkConfig4("somethig_default_wallet = my.wallet");
//
// 	string testOkConfigFile5("okConfig5");
// 	string containtOkConfig5("def ault_walle t = my.wallet");
//
// 	createFile(testOkConfigFile1 , containtOkConfig1);
// 	createFile(testOkConfigFile2 , containtOkConfig2);
// 	createFile(testOkConfigFile3 , containtOkConfig3);
// 	createFile(testOkConfigFile4 , containtOkConfig4);
//
// 	//test
// 	EXPECT_EQ(false, existsConfigTag("default_wallet", "okConfig1"));
// 	EXPECT_EQ(false, existsConfigTag("default_wallet", "okConfig2"));
// 	EXPECT_EQ(false, existsConfigTag("default_wallet", "okConfig3"));
// 	EXPECT_EQ(false, existsConfigTag("default_wallet", "okConfig4"));
// 	EXPECT_EQ(false, existsConfigTag("default_wallet", "okConfig5"));
//
// 	//tear-down
// 	remove("okConfig1");
// 	remove("okConfig2");
// 	remove("okConfig3");
// 	remove("okConfig4");
// 	remove("okConfig5");
// }
//
// TEST(ReadConfigTagTest, defaultWalletTagOK)
// {
// 	//set-up
// 	string testOkConfigFile1("okConfig1");
// 	string containtOkConfig1("default_wallet = my.wallet \n default_wallet = other.wallet");
//
// 	string testOkConfigFile2("okConfig2");
// 	string containtOkConfig2("		default_wallet 	=  my.wallet");
//
//
// 	string testOkConfigFile3("okConfig3");
// 	string containtOkConfig3("default_wallet 		=			 my.wallet	\t");
//
// 	string testOkConfigFile4("okConfig4");
// 	string containtOkConfig4("def ault_w allet = your.wallet \n default_wallet = my.wallet");
//
// 	createFile(testOkConfigFile1 , containtOkConfig1);
// 	createFile(testOkConfigFile2 , containtOkConfig2);
// 	createFile(testOkConfigFile3 , containtOkConfig3);
// 	createFile(testOkConfigFile4 , containtOkConfig4);
//
// 	//test
// 	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig1"));
// 	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig2"));
// 	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig3"));
// 	EXPECT_EQ("my.wallet", readConfig("default_wallet", "okConfig4"));
//
// 	//tear-down
// 	remove("okConfig1");
// 	remove("okConfig2");
// 	remove("okConfig3");
// 	remove("okConfig4");
// }
