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
