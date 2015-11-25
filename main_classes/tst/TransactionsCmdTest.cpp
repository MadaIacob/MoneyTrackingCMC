#include "gtest/gtest.h"

#include <string>
#include <vector>
#include <iostream>

#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "MessageCodes_E.h"
#include "TransactionCmd.h"
#include "TestHelper.h"
#include "TransactionType.h"

using namespace std;

TEST(TransactionParseTest, noParameters)
{
    //set-up
    TransactionCmd commandI(INCOME);
    TransactionCmd commandS(SPEND);

    vector<string> paramsI;
    vector<string> paramsS;

    MessageHandler mesI;
    MessageHandler mesS;

    commandI.setMessageHandler(mesI);
    commandS.setMessageHandler(mesS);

    //test
    EXPECT_EQ(false, commandI.parseParams(paramsI));
    mesI = commandI.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mesI.getMessageCode());

    EXPECT_EQ(false, commandS.parseParams(paramsS));
    mesS = commandS.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mesS.getMessageCode());
}

TEST(TransactionParseTest, oneParameter)
{
    //set-up
    TransactionCmd commandI(INCOME);
    TransactionCmd commandS(SPEND);

    vector<string> paramsI;
    paramsI.push_back("123.369");
    vector<string> paramsS;
    paramsS.push_back("123.369");

    MessageHandler mesI;
    MessageHandler mesS;

    commandI.setMessageHandler(mesI);
    commandS.setMessageHandler(mesS);

    //test
    EXPECT_EQ(true, commandI.parseParams(paramsI));
    EXPECT_EQ(true, commandS.parseParams(paramsS));
}

TEST(TransactionParseTest, moreParameters)
{
    //set-up
    TransactionCmd commandI(INCOME);
    TransactionCmd commandS(SPEND);

    vector<string> paramsI2;
    paramsI2.push_back("-w");
    paramsI2.push_back("myWallet");
    paramsI2.push_back("123.369");
    vector<string> paramsS2;
    paramsS2.push_back("123.369");
    paramsS2.push_back("-c");
    paramsS2.push_back("category");
    vector<string> paramsS3;
    paramsS3.push_back("-c");
    paramsS3.push_back("category");

    MessageHandler mesI;
    MessageHandler mesS;

    commandI.setMessageHandler(mesI);
    commandS.setMessageHandler(mesS);

    //test
    EXPECT_EQ(true, commandI.parseParams(paramsI2));
    EXPECT_EQ(true, commandS.parseParams(paramsS2));
    EXPECT_EQ(false, commandS.parseParams(paramsS3));
}

TEST(TransactionValidateTest, invalidAmount)
{
    //set-up
    TransactionCmd command1(INCOME);
    TransactionCmd command2(INCOME);

    vector<string> params1;
    params1.push_back("123,25");
    vector<string> params2;
    params2.push_back("2ab36");

    MessageHandler mes1;
    MessageHandler mes2;

    command1.setMessageHandler(mes1);
    command2.setMessageHandler(mes2);

    //test
    command1.parseParams(params1);
    EXPECT_EQ(false, command1.validateParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes1.getMessageCode());

    command2.parseParams(params2);
    EXPECT_EQ(false, command2.validateParams(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes2.getMessageCode());
}

TEST(TransactionValidateTest, negativeAmount)
{
    //set-up
    TransactionCmd command1(INCOME);

    vector<string> params1;
    params1.push_back("-123.25");

    MessageHandler mes1;

    command1.setMessageHandler(mes1);

    //test
    command1.parseParams(params1);
    EXPECT_EQ(false, command1.validateParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(INCOME_SPEND_HIGHER_ERR, mes1.getMessageCode());
}

TEST(TransactionValidateTest, missingWallet)
{
    //set-up
    TransactionCmd command1(INCOME);

    vector<string> params1;
    params1.push_back("123.25");
    params1.push_back("-w");
    params1.push_back("mada.wallet");

    MessageHandler mes1;

    command1.setMessageHandler(mes1);

    //test
    command1.parseParams(params1);
    EXPECT_EQ(false, command1.validateParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(COULD_NOT_OPEN_FILE_ERR, mes1.getMessageCode());
}

TEST(TransactionParseParamsTest, timeStampNotValid)
{
    //set-up
    TransactionCmd command1(SPEND), command2(SPEND), command3(INCOME);

    createFile("3645wallet2756", "+100.00 RON\n");

    vector<string> params1;
    params1.push_back("123.25");
    params1.push_back("-w");
    params1.push_back("3645wallet2756");
    params1.push_back("-t");
    params1.push_back(" 22-09-2012 23:45");

    vector<string> params2;
    params2.push_back("123.25");
    params2.push_back("--time");
    params2.push_back("22-09-1969 23:45");
    params2.push_back("-w");
    params2.push_back("3645wallet2756");

    vector<string> params3;
    params3.push_back("1400");
    params3.push_back("-c");
    params3.push_back("spaga");
    params3.push_back("--time");
    params3.push_back("29-02-1970 23:45");
    params3.push_back("-w");
    params3.push_back("3645wallet2756");

    MessageHandler mes1, mes2, mes3;

    command1.setMessageHandler(mes1);
    command2.setMessageHandler(mes2);
    command3.setMessageHandler(mes3);

    //test
    EXPECT_FALSE(command1.parseParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(TIME_NOT_VALID_ERR, mes1.getMessageCode());

    EXPECT_FALSE(command2.parseParams(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(TIME_NOT_VALID_ERR, mes2.getMessageCode());

    EXPECT_FALSE(command3.parseParams(params3));
    mes3 = command3.getPtrMessage();
    EXPECT_EQ(TIME_NOT_VALID_ERR, mes3.getMessageCode());
    //tear-down
    remove("3645wallet2756");
}

TEST(TransactionParseParamsTest, timeStampValid)
{
    //set-up
    TransactionCmd command1(SPEND), command2(SPEND), command3(INCOME);

    createFile("3645wallet2756", "+100.00 RON\n");

    vector<string> params1;
    params1.push_back("123.25");
    params1.push_back("-w");
    params1.push_back("3645wallet2756");
    params1.push_back("-t");
    params1.push_back("22-09-2012 23:45");

    vector<string> params2;
    params2.push_back("123.25");
    params2.push_back("--time");
    params2.push_back("22-09-1970 23:45");
    params2.push_back("-w");
    params2.push_back("3645wallet2756");

    vector<string> params3;
    params3.push_back("1400");
    params3.push_back("-c");
    params3.push_back("spaga");
    params3.push_back("--time");
    params3.push_back("29-02-2004 23:45");
    params3.push_back("-w");
    params3.push_back("3645wallet2756");

    //test
	EXPECT_TRUE(command1.parseParams(params1));
	EXPECT_TRUE(command2.parseParams(params2));
	EXPECT_TRUE(command3.parseParams(params3));
	
    //tear-down
    remove("3645wallet2756");
}

TEST(TransactionExecuteTest, addIncomeSpend)
{
    //set-up
    TransactionCmd command1(INCOME);
    TransactionCmd command2(SPEND);
    TransactionCmd command3(SPEND);
    TransactionCmd command4(INCOME);
    TransactionCmd command5(SPEND);
    TransactionCmd command6(INCOME);

	createFile("3645wallet2756", "+100.00 RON\n");

	vector<string> params1;
	params1.push_back("123.25");
	params1.push_back("-w");
	params1.push_back("3645wallet2756");

	vector<string> params2;
	params2.push_back("-w");
	params2.push_back("3645wallet2756");
	params2.push_back("123.2567");
	params2.push_back("-c");
	params2.push_back("bribe");

	vector<string> params3;
	params3.push_back("-w");
	params3.push_back("3645wallet2756");
	params3.push_back("-t");
	params3.push_back("29-2-2012 23:59");
	params3.push_back("123.25");

	vector<string> params4;
	params4.push_back("-w");
	params4.push_back("3645wallet2756");
	params4.push_back("--time");
	params4.push_back("29-2-2012 23:59");
	params4.push_back("123.25");
	params4.push_back("--category");
	params4.push_back("spaga");

	vector<string> params5;
	params5.push_back("123.25");
	params5.push_back("-t");
	params5.push_back("28-2-2015 1:59");
	params5.push_back("--category");
	params5.push_back("spaga");
	params5.push_back("-w");
	params5.push_back("3645wallet2756");

	vector<string> params6;
	params6.push_back("--time");
	params6.push_back("28-2-2015 1:59");
	params6.push_back("--wallet");
	params6.push_back("3645wallet2756");
	params6.push_back("-c");
	params6.push_back("spaga");
	params6.push_back("1234");

    MessageHandler mes1, mes2 , mes3, mes4, mes5, mes6;

    command1.setMessageHandler(mes1);
    command2.setMessageHandler(mes2);
    command3.setMessageHandler(mes3);
    command4.setMessageHandler(mes4);
    command5.setMessageHandler(mes5);
    command6.setMessageHandler(mes6);

    //test
    EXPECT_TRUE(command1.parseParams(params1));
    EXPECT_TRUE(command1.validateParams(params1));
    EXPECT_TRUE(command1.executeCommand(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes1.getMessageCode());

    EXPECT_TRUE(command2.parseParams(params2));
    EXPECT_TRUE(command2.validateParams(params2));
    EXPECT_TRUE(command2.executeCommand(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes2.getMessageCode());

    EXPECT_TRUE(command3.parseParams(params3));
    EXPECT_TRUE(command3.validateParams(params3));
    EXPECT_TRUE(command3.executeCommand(params3));
    mes3 = command3.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes3.getMessageCode());

    EXPECT_TRUE(command4.parseParams(params4));
    EXPECT_TRUE(command4.validateParams(params4));
    EXPECT_TRUE(command4.executeCommand(params4));
    mes4 = command4.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes4.getMessageCode());

    EXPECT_TRUE(command5.parseParams(params5));
    EXPECT_TRUE(command5.validateParams(params5));
    EXPECT_TRUE(command5.executeCommand(params5));
    mes5 = command5.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes5.getMessageCode());

    EXPECT_TRUE(command6.parseParams(params6));
    EXPECT_TRUE(command6.validateParams(params6));
    EXPECT_TRUE(command6.executeCommand(params6));
    mes6 = command6.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes6.getMessageCode());

    //tear-down
    remove("3645wallet2756");
}

