#include "gtest/gtest.h"

#include "Wallet.h"
#include "CreateWalletCmd.h"

#include <vector>
#include <string>

using namespace std;

TEST(CreateWalletParseTest, parseParams)
{
  CreateWalletCmd command;
  vector<string> params;

  EXPECT_EQ(false, command.parseParams(params));
  EXPECT_EQ(INVALID_COM_ERR, command.getMessageCode());

  params.push_back("param1");
  params.push_back("param2");
  params.push_back("param3");
  params.push_back("param4");

  EXPECT_EQ(false, command.parseParams(params));
}
