#include "gtest/gtest.h"

#include "Wallet.h"
#include "CreateWalletCmd.h"
#include "MessageHandler.h"
#include "Command.h"
#include "MessageCodes_E.h"
#include "TestHelper.h"

#include <vector>
#include <string>
#include <fstream>

using namespace std;

TEST(CreateWalletParseTest, noParameters)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params;
  MessageHandler mes;
  command.setMessageHandler(mes);

  //test
  EXPECT_EQ(false, command.parseParams(params));
  mes = command.getPtrMessage();
  EXPECT_EQ(FILENAME_NOT_SPEC_ERR, mes.getMessageCode());

}

TEST(CreateWalletParseTest, tooManyParameres)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params;
  MessageHandler mes;
  command.setMessageHandler(mes);

  params.push_back("param1");
  params.push_back("param2");
  params.push_back("param3");
  params.push_back("param4");

  bool isOk = command.parseParams(params);

  //test
  EXPECT_EQ(false, isOk);
  mes = command.getPtrMessage();
  EXPECT_EQ(INVALID_COM_ERR, mes.getMessageCode());
}

TEST(CreateWalletParseTest, okParameters)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params;
  params.push_back("myWallet");
  params.push_back("256.36");

  //test
  EXPECT_EQ(true, command.parseParams(params));
}

TEST(CreateWalletValidateTest, walletAlreadyExists)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params;
  string content = "wallet content";
  createFile("myWallet",content);

  MessageHandler mes;
  command.setMessageHandler(mes);

  params.push_back("myWallet");
  params.push_back("256.36");

  bool isOk = command.validateParams(params);
  mes = command.getPtrMessage();

  //test
  EXPECT_EQ(false, isOk);
  EXPECT_EQ(WALLET_EXISTS_ERR, mes.getMessageCode());

  //tear-down
  remove("myWallet");
}

TEST(CreateWalletValidateTest, invalidAmount)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params1;
  vector<string> params2;
  vector<string> params3;

  MessageHandler mes;
  command.setMessageHandler(mes);

  params1.push_back("wallet");
  params1.push_back("00,236");

  params2.push_back("wallet2");
  params2.push_back("abc.1213");

  params3.push_back("wallet2");
  params3.push_back("231b");


  //test
  bool isOk = command.validateParams(params1);
  mes = command.getPtrMessage();
  EXPECT_EQ(false, isOk);
  EXPECT_EQ(INVALID_AMOUNT_ERR, mes.getMessageCode());

  isOk = command.validateParams(params2);
  mes = command.getPtrMessage();
  EXPECT_EQ(false, isOk);
  EXPECT_EQ(INVALID_AMOUNT_ERR, mes.getMessageCode());

  isOk = command.validateParams(params3);
  mes = command.getPtrMessage();
  EXPECT_EQ(false, isOk);
  EXPECT_EQ(INVALID_AMOUNT_ERR, mes.getMessageCode());
}

TEST(CreateWalletValidateTest, validAmount)
{
  //set-up
  CreateWalletCmd command;
  vector<string> params1;
  vector<string> params2;
  vector<string> params3;


  params1.push_back("wallet1");
  params1.push_back("00.236");

  params2.push_back("wallet2");
  params2.push_back("+12.78");

  params3.push_back("wallet3");
  params3.push_back("-156");

  //test
  bool isOk = command.validateParams(params1);
  EXPECT_EQ(true, isOk);

  isOk = command.validateParams(params2);
  EXPECT_EQ(true, isOk);

  isOk = command.validateParams(params3);
  EXPECT_EQ(true, isOk);
}

TEST(CreateWalletExecuteTest, createWallet)
{
  CreateWalletCmd command;
  vector<string> params1;
  vector<string> params2;
  vector<string> params3;
  vector<string> params4;

  params1.push_back("wallet1");
  params1.push_back("00.232");

  params2.push_back("wallet2");
  params2.push_back("+12.789");

  params3.push_back("wallet3");
  params3.push_back("-156");

  params4.push_back("wallet4");

  //test
  bool isOk = command.executeCommand(params1);
  EXPECT_EQ(true, isOk);
  EXPECT_EQ("+0.23 RON", readLastLine("wallet1"));

  isOk = command.executeCommand(params2);
  EXPECT_EQ(true, isOk);
  EXPECT_EQ("+12.79 RON", readLastLine("wallet2"));

  isOk = command.executeCommand(params3);
  EXPECT_EQ(true, isOk);
  EXPECT_EQ("-156.00 RON", readLastLine("wallet3"));

  isOk = command.executeCommand(params4);
  EXPECT_EQ(true, isOk);
  EXPECT_EQ("+00.00 RON", readLastLine("wallet4"));

  //tear-down
  remove("wallet1");
  remove("wallet2");
  remove("wallet3");
  remove("wallet4");

}
