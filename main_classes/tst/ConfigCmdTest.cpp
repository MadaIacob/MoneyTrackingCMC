#include "gtest/gtest.h"

#include <string>
#include <vector>

#include "Wallet.h"
#include "WalletEntity.h"
#include "MessageHandler.h"
#include "MessageCodes_E.h"
#include "ConfigCmd.h"

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
/*
TEST(ConfigParseTest, invalidParameters)
{
    //set-up
    ConfigCmd command;
	MessageHandler mes;
    command.setMessageHandler(mes);
    vector<string> params1;
	params1.push_back("-w");
    vector<string> params2;
	params2.push_back("default");
    vector<string> params3;
	params3.push_back("default_wallet");
    vector<string> params4;
	params4.push_back("default_wallet=");
    vector<string> params5;
 	params5.push_back("default_wallet");
	params5.push_back("=");
	vector<string> params6;
 	params6.push_back("default_wallet");
	params6.push_back("==");
    vector<string> params7;
	params7.push_back("default_wallet= ");

    //test
    //EXPECT_EQ(false, command.parseParams(params1));
    mes = command.getPtrMessage();
    //EXPECT_EQ(INVALID_PARAM_ERR, mes.getMessageCode());

	//tear-down
}*/
