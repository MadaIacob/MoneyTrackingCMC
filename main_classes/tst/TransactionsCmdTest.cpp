#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "MessageCodes_E.h"
#include "TransactionCmd.h"

using namespace std;

TEST(TransactionParseTest, noParameters)
{
    //set-up
    TransactionCmd commandI("income");
    TransactionCmd commandS("spent");

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
    TransactionCmd commandI("income");
    TransactionCmd commandS("spent");

    vector<string> paramsI;
    paramsI.push_back("123.369");
    vector<string> paramsI2;
    paramsI2.push_back("-w");
    paramsI2.push_back("myWallet");
    paramsI2.push_back("123.369");
    vector<string> paramsS;
    paramsS.push_back("123.369");
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
    EXPECT_EQ(true, commandI.parseParams(paramsI));
    EXPECT_EQ(true, commandI.parseParams(paramsI2));
    EXPECT_EQ(true, commandS.parseParams(paramsS));
    EXPECT_EQ(true, commandS.parseParams(paramsS2));
    EXPECT_EQ(false, commandS.parseParams(paramsS3));
}
