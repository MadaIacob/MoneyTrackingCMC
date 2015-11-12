#include "gtest/gtest.h"
#include <cstring>
#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "Config.h"
#include "TestHelper.h"
using namespace std;


TEST(ReadWriteConfigFileTest, ValidContent)
{
	//set-up
	string testOkConfigFile1("okConfig1");
	KeyVal kv1, kv2, kv3, kv4;
	vector <KeyVal> vect;

	kv1.key = "default_wallet";
	kv1.value = "my.wallet";
	vect.push_back(kv1);

	kv2.key = "default_currency";
	kv2.value = "RON";
	vect.push_back(kv2);

	kv3.key = "default_income_category";
	kv3.value = "salary";
	vect.push_back(kv3);

	kv4.key = "default_spend_category";
	kv4.value = "other";
	vect.push_back(kv4);

	Config okConfig1(testOkConfigFile1);
	createFile(testOkConfigFile1 , "");
	okConfig1.readConfigFile();
	//okConfig1.createConfigFile();
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		okConfig1.modifyContent(vect.at(i).key, vect.at(i).value);
	}
	okConfig1.writeConfigFile();
	okConfig1.readConfigFile();

	//test
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		EXPECT_EQ(true, okConfig1.existsTag(vect.at(i).key));
		EXPECT_EQ(vect.at(i).value, okConfig1.getTagValue(vect.at(i).key));
	}

	//tear-down
	remove("okConfig1");
}

TEST(ReadWriteConfigFileTest, InvalidContent)
{
	//set-up
	string testOkConfigFile1("okConfig1");
	KeyVal kv1, kv2, kv3, kv4;
	vector <KeyVal> vect;

	kv1.key = "default_wallett";
	kv1.value = "my.wallet";
	vect.push_back(kv1);

	kv2.key = "default_currencyy";
	kv2.value = "RON";
	vect.push_back(kv2);

	kv3.key = "default_income_categoryy";
	kv3.value = "salary";
	vect.push_back(kv3);

	kv4.key = "default_spend_categoryy";
	kv4.value = "other";
	vect.push_back(kv4);

	Config okConfig1(testOkConfigFile1);
	createFile(testOkConfigFile1 , "");
	okConfig1.readConfigFile();
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		okConfig1.modifyContent(vect.at(i).key, vect.at(i).value);
	}
	okConfig1.writeConfigFile();
	okConfig1.readConfigFile();

	//test
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		EXPECT_EQ(false, okConfig1.existsTag(vect.at(i).key));
		EXPECT_EQ("", okConfig1.getTagValue(vect.at(i).key));
	}

	//tear-down
	remove("okConfig1");
}

TEST(IsValidTagTest, InvalidTags)
{
	//set-up
	string testOkConfigFile1("okConfig1");
	KeyVal kv1, kv2, kv3, kv4;
	vector <KeyVal> vect;

	kv1.key = "default_wallett";
	vect.push_back(kv1);

	kv2.key = "default_currencyy";
	vect.push_back(kv2);

	kv3.key = "default_income_categoryy";
	vect.push_back(kv3);

	kv4.key = "default_spend_categoryy";
	vect.push_back(kv4);

	Config okConfig1(testOkConfigFile1);

	for (unsigned int i = 0; i < vect.size(); i++)
	{
		okConfig1.modifyContent(vect.at(i).key, "");
	}

	//test
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		EXPECT_EQ(false, okConfig1.isValidTag(vect.at(i).key));
	}

	//tear-down
	remove("okConfig1");
}

TEST(IsValidTagTest, ValidTags)
{
	//set-up
	string testOkConfigFile1("okConfig1");
	KeyVal kv1, kv2, kv3, kv4;
	vector <KeyVal> vect;

	kv1.key = "default_wallet";
	vect.push_back(kv1);

	kv2.key = "default_currency";
	vect.push_back(kv2);

	kv3.key = "default_income_category";
	vect.push_back(kv3);

	kv4.key = "default_spend_category";
	vect.push_back(kv4);

	Config okConfig1(testOkConfigFile1);

	for (unsigned int i = 0; i < vect.size(); i++)
	{
		okConfig1.modifyContent(vect.at(i).key, "");
	}

	//test
	for (unsigned int i = 0; i < vect.size(); i++)
	{
		EXPECT_EQ(true, okConfig1.isValidTag(vect.at(i).key));
	}

	//tear-down
	remove("okConfig1");
}

TEST(CreateConfigFileTest, ValidTags)
{
	//set-up
	string testOkConfigFile1("testConfig");

	Config config("testConfig");
	config.createConfigFile();
	//test

	EXPECT_NE(true, validateFileName(testOkConfigFile1));

	//tear-down
	remove(testOkConfigFile1.c_str());
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

	string testOkConfigFile5("okConfig5");
	string containtOkConfig5("default_wallet = ");

	createFile(testOkConfigFile1 , containtOkConfig1);
	createFile(testOkConfigFile2 , containtOkConfig2);
	createFile(testOkConfigFile3 , containtOkConfig3);
	createFile(testOkConfigFile4 , containtOkConfig4);
	createFile(testOkConfigFile5 , containtOkConfig5);

	Config okConfig1(testOkConfigFile1);
	Config okConfig2(testOkConfigFile2);
	Config okConfig3(testOkConfigFile3);
	Config okConfig4(testOkConfigFile4);
	Config okConfig5(testOkConfigFile5);

	okConfig1.readConfigFile();
	okConfig2.readConfigFile();
	okConfig3.readConfigFile();
	okConfig4.readConfigFile();
	okConfig5.readConfigFile();

	//test
	EXPECT_EQ(true, okConfig1.existsTag("default_wallet"));
	EXPECT_EQ(true, okConfig2.existsTag("default_wallet"));
	EXPECT_EQ(true, okConfig3.existsTag("default_wallet"));
	EXPECT_EQ(true, okConfig4.existsTag("default_wallet"));
	EXPECT_EQ(true, okConfig5.existsTag("default_wallet"));

	//tear-down
	remove("okConfig1");
	remove("okConfig2");
	remove("okConfig3");
	remove("okConfig4");
	remove("okConfig5");
}

TEST(ExistsConfigTagTest, defaultWalletTagNotOK)
{
	//set-up
	string testOkConfigFile1("okConfig1");
	string containtOkConfig1("default_wallet bad = my.wallet");

	string testOkConfigFile2("okConfig2");
	string containtOkConfig2("		default_wallet 	= ");

	string testOkConfigFile3("okConfig3");
	string containtOkConfig3("not_ default_wallet = my.wallet");

	string testOkConfigFile4("okConfig4");
	string containtOkConfig4("somethig_default_wallet = my.wallet");

	string testOkConfigFile5("okConfig5");
	string containtOkConfig5("default walle t = my.wallet");

	createFile(testOkConfigFile1 , containtOkConfig1);
	createFile(testOkConfigFile2 , containtOkConfig2);
	createFile(testOkConfigFile3 , containtOkConfig3);
	createFile(testOkConfigFile4 , containtOkConfig4);
	createFile(testOkConfigFile5 , containtOkConfig5);

	Config okConfig1(testOkConfigFile1);
	Config okConfig2(testOkConfigFile2);
	Config okConfig3(testOkConfigFile3);
	Config okConfig4(testOkConfigFile4);
	Config okConfig5(testOkConfigFile5);

	okConfig1.readConfigFile();
	okConfig2.readConfigFile();
	okConfig3.readConfigFile();
	okConfig4.readConfigFile();
	okConfig5.readConfigFile();

	//test
	EXPECT_EQ(false, okConfig1.existsTag("default_wallet"));
	EXPECT_EQ(true, okConfig2.existsTag("default_wallet"));
	EXPECT_EQ(false, okConfig3.existsTag("default_wallet"));
	EXPECT_EQ(false, okConfig4.existsTag("default_wallet"));
	EXPECT_EQ(false, okConfig5.existsTag("default_wallet"));

	//tear-down
	remove("okConfig1");
	remove("okConfig2");
	remove("okConfig3");
	remove("okConfig4");
	remove("okConfig5");
}
