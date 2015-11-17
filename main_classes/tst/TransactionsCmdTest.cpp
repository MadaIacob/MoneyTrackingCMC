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

TEST(TransactionExecuteTest, addIncomeSpend)
{
    //set-up
    TransactionCmd command1(INCOME);
    TransactionCmd command2(SPEND);

    createFile("mada.wallet", "+100.00 RON\n");

    vector<string> params1;
    params1.push_back("123.25");
    params1.push_back("-w");
    params1.push_back("mada.wallet");

    vector<string> params2;
    params2.push_back("123.25");
    params2.push_back("-w");
    params2.push_back("mada.wallet");
    params2.push_back("-c");
    params2.push_back("clothes");

    MessageHandler mes1;
    MessageHandler mes2;

    command1.setMessageHandler(mes1);
    command2.setMessageHandler(mes2);

    //test
    command1.parseParams(params1);
    EXPECT_EQ(true, command1.validateParams(params1));
    EXPECT_EQ(true, command1.executeCommand(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes1.getMessageCode());

    command2.parseParams(params2);
    EXPECT_EQ(true, command2.validateParams(params2));
    EXPECT_EQ(true, command2.executeCommand(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(SPEND_INCOME_REGISTERED_MSG, mes2.getMessageCode());

    //tear-down
    remove("mada.wallet");
}
