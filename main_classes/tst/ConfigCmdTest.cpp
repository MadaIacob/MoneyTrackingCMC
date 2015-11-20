/*
File Description		Implementation of TransactionCmd class
Author					calin-ciprian.popita
Date					17.11.2015
*/
#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <iostream>

#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "MessageCodes_E.h"
#include "ConfigCmd.h"
#include "TestHelper.h"

using namespace std;

TEST(ConfigParseTest, noParameters)
{
    //set-up
    ConfigCmd command;
    vector<string> params;
    MessageHandler mes;
    command.setMessageHandler(mes);

    //test
    EXPECT_EQ(true, command.parseParams(params));
    mes = command.getPtrMessage();

	//tear-down
}

TEST(ConfigParseTest, invalidParameters)
{
    //set-up
    ConfigCmd command1;
	MessageHandler mes1;
    command1.setMessageHandler(mes1);
    vector<string> params1;
	params1.push_back("-w");

    ConfigCmd command2;
	MessageHandler mes2;
    command2.setMessageHandler(mes2);
    vector<string> params2;
	params2.push_back("default");

    ConfigCmd command3;
	MessageHandler mes3;
    command3.setMessageHandler(mes3);
    vector<string> params3;
	params3.push_back("default_wallet");

	ConfigCmd command4;
 	MessageHandler mes4;
    command4.setMessageHandler(mes4);
    vector<string> params4;
	params4.push_back("default_wallet=");

	ConfigCmd command5;
	MessageHandler mes5;
    command5.setMessageHandler(mes5);
    vector<string> params5;
 	params5.push_back("default_wallet");
	params5.push_back("=");

	ConfigCmd command6;
	MessageHandler mes6;
    command6.setMessageHandler(mes6);
    vector<string> params6;
	params6.push_back("-w");
	params6.push_back("my.wallet");

	ConfigCmd command7;
	MessageHandler mes7;
    command7.setMessageHandler(mes7);
    vector<string> params7;
	params7.push_back("default_wallet= ");

	ConfigCmd command8;
	MessageHandler mes8;
    command8.setMessageHandler(mes8);
    vector<string> params8;
	params8.push_back("default_wallet");
	params8.push_back("default_wallet");

	ConfigCmd command9;
	MessageHandler mes9;
    command9.setMessageHandler(mes9);
    vector<string> params9;
	params9.push_back("default_wallet");
	params9.push_back("default_wallet= ");

	ConfigCmd command10;
	MessageHandler mes10;
    command10.setMessageHandler(mes10);
    vector<string> params10;
	params10.push_back("default_wallet");
	params10.push_back("default_wallet");
	params10.push_back("default_wallet=");

	ConfigCmd command11;
	MessageHandler mes11;
    command11.setMessageHandler(mes11);
    vector<string> params11;
	params11.push_back("a");
	params11.push_back("default_wallet=");

	ConfigCmd command12;
	MessageHandler mes12;
    command12.setMessageHandler(mes12);
    vector<string> params12;
	params12.push_back("a");
	params12.push_back("default_wallet=");
	params12.push_back("my.wallet");

	ConfigCmd command13;
	MessageHandler mes13;
    command13.setMessageHandler(mes13);
    vector<string> params13;
	params13.push_back("default_wallet=");
	params13.push_back("my.wallet");
	params13.push_back("a");

    //test
    EXPECT_EQ(false, command1.parseParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes1.getMessageCode());

    EXPECT_EQ(false, command2.parseParams(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes2.getMessageCode());

    EXPECT_EQ(false, command3.parseParams(params3));
    mes3 = command3.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes3.getMessageCode());

    EXPECT_EQ(false, command4.parseParams(params4));
    mes4 = command4.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes4.getMessageCode());

    EXPECT_EQ(false, command5.parseParams(params5));
    mes5 = command5.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes5.getMessageCode());

    EXPECT_EQ(false, command6.parseParams(params6));
    mes6 = command6.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes6.getMessageCode());

    EXPECT_EQ(false, command7.parseParams(params7));
    mes7 = command7.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes7.getMessageCode());

	EXPECT_EQ(false, command8.parseParams(params8));
    mes8 = command8.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes8.getMessageCode());

    EXPECT_EQ(false, command9.parseParams(params9));
    mes9 = command9.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes9.getMessageCode());

    EXPECT_EQ(false, command10.parseParams(params10));
    mes10 = command10.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes10.getMessageCode());

    EXPECT_EQ(false, command11.parseParams(params11));
    mes11 = command11.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes11.getMessageCode());

    EXPECT_EQ(false, command12.parseParams(params12));
    mes12 = command12.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes12.getMessageCode());

    EXPECT_EQ(false, command13.parseParams(params13));
    mes13 = command13.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes13.getMessageCode());

	//tear-down
}

TEST(ConfigExecuteTest, invalidTags)
{
    //set-up
    ConfigCmd command1;
	MessageHandler mes1;
    command1.setMessageHandler(mes1);
    vector<string> params1;
	params1.push_back("-w");
	params1.push_back("wallet");

    ConfigCmd command2;
	MessageHandler mes2;
    command2.setMessageHandler(mes2);
    vector<string> params2;
	params2.push_back("default=");
	params2.push_back("wallet");

    ConfigCmd command3;
	MessageHandler mes3;
    command3.setMessageHandler(mes3);
    vector<string> params3;
	params3.push_back("default");
	params3.push_back("=wallet");

	ConfigCmd command4;
 	MessageHandler mes4;
    command4.setMessageHandler(mes4);
    vector<string> params4;
	params4.push_back("default= ");
	params4.push_back("wallet");

	ConfigCmd command5;
	MessageHandler mes5;
    command5.setMessageHandler(mes5);
    vector<string> params5;
	params5.push_back("default");
	params5.push_back(" =wallet");


    //test
    EXPECT_EQ(true, command1.executeCommand(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(NO_VALID_CONFIG_VALUE_ERR, mes1.getMessageCode());

    EXPECT_EQ(true, command2.executeCommand(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(NO_VALID_CONFIG_VALUE_ERR, mes2.getMessageCode());

    EXPECT_EQ(true, command3.executeCommand(params3));
    mes3 = command3.getPtrMessage();
    EXPECT_EQ(NO_VALID_CONFIG_VALUE_ERR, mes3.getMessageCode());

    EXPECT_EQ(true, command4.executeCommand(params4));
    mes4 = command4.getPtrMessage();
    EXPECT_EQ(NO_VALID_CONFIG_VALUE_ERR, mes4.getMessageCode());

    EXPECT_EQ(true, command5.executeCommand(params5));
    mes5 = command5.getPtrMessage();
    EXPECT_EQ(NO_VALID_CONFIG_VALUE_ERR, mes5.getMessageCode());

	//tear-down
}

 TEST(ConfigExecuteTest, validParams)
{
//set-up
	createFile("test.config", "default_wallet = my.wallet\ndefault_currency = RON");

    ConfigCmd command1("test.config");
	MessageHandler mes1;
    command1.setMessageHandler(mes1);
    vector<string> params1;
	params1.push_back("default_wallet");
	params1.push_back("wallet");

	ConfigCmd command2;
	MessageHandler mes2;
    command2.setMessageHandler(mes2);
    vector<string> params2;
	params2.push_back("default_currency");
	params2.push_back("EUR");

//test

	//test function executeCommand
	EXPECT_TRUE(command1.executeCommand(params1));
    mes1 = command1.getPtrMessage();
	//check for success message
    EXPECT_EQ(TAG_CONFIGURED_MSG, mes1.getMessageCode());
	//copy content to string
	string modifiedConfigContent = fileToString("test.config");
	//compare string with expected content
	EXPECT_TRUE(modifiedConfigContent.find("default_wallet = wallet",0) <
				modifiedConfigContent.length());

	//test function executeCommand
	EXPECT_TRUE(command2.executeCommand(params2));
    mes2 = command2.getPtrMessage();
	//check for success message
    EXPECT_EQ(TAG_CONFIGURED_MSG, mes2.getMessageCode());
	//search for the modified content within config file
	modifiedConfigContent = fileToString("test.config");
	//compare string with expected content
	EXPECT_TRUE(modifiedConfigContent.find("default_currency = EUR",0) <
				modifiedConfigContent.length());
//tear-down

	//delete modified file
	//remove("test.config");

}

 TEST(ConfigExecuteTest, clearTagValueParse)
 {
     //set-up
    createFile("test.config", "default_wallet = wallet\ndefault_income_category = category");

    ConfigCmd command1("test.config");
    ConfigCmd command2("test.config");

    MessageHandler mes1;
    command1.setMessageHandler(mes1);
    vector<string> params1;
    params1.push_back("default_wallet");
    params1.push_back("=");
    params1.push_back("");

    MessageHandler mes2;
    command2.setMessageHandler(mes2);
    vector<string> params2;
    params2.push_back("default_income_category");
    params2.push_back("=");
    params2.push_back("");

    //test
    EXPECT_EQ(false, command1.parseParams(params1));
    EXPECT_EQ(true, command2.parseParams(params2));

    //tear-down
    //remove("test.config");
 }

 TEST(ConfigExecuteTest, clearTagValueExecute)
 {
     //set-up
    createFile("test.config", "default_wallet = wallet\ndefault_income_category = category");

    ConfigCmd command1("test.config");
    ConfigCmd command2("test.config");

    MessageHandler mes1;
    command1.setMessageHandler(mes1);
    vector<string> params1;
    params1.push_back("default_wallet");
    params1.push_back("=");
    params1.push_back("");

    MessageHandler mes2;
    command2.setMessageHandler(mes2);
    vector<string> params2;
    params2.push_back("default_income_category");
    params2.push_back("=");
    params2.push_back("");

    //test
    EXPECT_EQ(false, command1.parseParams(params1));
    EXPECT_EQ(true, command2.parseParams(params2));
    if(!mes1.isSetMessageCode())
    {
        EXPECT_EQ(false, command1.executeCommand(params1));
    }

    if(!mes2.isSetMessageCode())
    {
        EXPECT_EQ(true, command2.executeCommand(params2));
    }

    //tear-down
    //remove("test.config");
 }
