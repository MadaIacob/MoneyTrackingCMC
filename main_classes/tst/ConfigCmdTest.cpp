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

    //test
    cout << "t1" << endl;
    EXPECT_EQ(false, command1.parseParams(params1));
    mes1 = command1.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes1.getMessageCode());

    cout << "t2" << endl;
    EXPECT_EQ(false, command2.parseParams(params2));
    mes2 = command2.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes2.getMessageCode());

    cout << "t3" << endl;
    EXPECT_EQ(false, command3.parseParams(params3));
    mes3 = command3.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes3.getMessageCode());

    cout << "t4" << endl;
    EXPECT_EQ(false, command4.parseParams(params4));
    mes4 = command4.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes4.getMessageCode());

    cout << "t5" << endl;
    EXPECT_EQ(false, command5.parseParams(params5));
    mes5 = command5.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes5.getMessageCode());

    cout << "t6" << endl;
    EXPECT_EQ(false, command6.parseParams(params6));
    mes6 = command6.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes6.getMessageCode());

    cout << "t7" << endl;
    EXPECT_EQ(false, command7.parseParams(params7));
    mes7 = command7.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes7.getMessageCode());

    cout << "t8" << endl;
	EXPECT_EQ(false, command8.parseParams(params8));
    mes8 = command8.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes8.getMessageCode());

    cout << "t9" << endl;
    EXPECT_EQ(false, command9.parseParams(params9));
    mes9 = command9.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes9.getMessageCode());

    cout << "t10" << endl;
    EXPECT_EQ(false, command10.parseParams(params10));
    mes10 = command10.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes10.getMessageCode());

    cout << "t11" << endl;
    EXPECT_EQ(false, command11.parseParams(params11));
    mes11 = command11.getPtrMessage();
    EXPECT_EQ(INVALID_PARAM_ERR, mes11.getMessageCode());

	//tear-down
}
