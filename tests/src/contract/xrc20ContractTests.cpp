#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "signer/signer.h"
#include "contract/xrc20Contract.h"

using namespace std;
using namespace testing;
using namespace iotex;
using namespace iotex::abi;

class Xrc20ContractTests : public Test
{
    public: 
        void SetUp() override 
        {
            signer.str2hex(addressStr, address, sizeof(address));
        }

        void TearDown() override {}

        char addressStr[ETH_ADDRESS_C_STRING_SIZE] = "19e7e376e7c213b7e7e7e46cc70a5dd086daff2a";
        uint8_t address[ETH_ADDRESS_SIZE] = {0};
};

// --------------------- parseInputOutput  ------------------------------

TEST_F(Xrc20ContractTests, generateCallDataForTotalSupply)
{
    uint8_t data[IOTEX_CONTRACT_ENCODED_FUNCTIONSELECTOR_SIZE] = {0};
    uint8_t expected[] = {0x18, 0x16, 0x0d, 0xdd};
    Xrc20Contract::generateCallDataForTotalSupply(data);
}

TEST_F(Xrc20ContractTests, generateCallDataForBalanceOf)
{
    char expected[] = "70a0823100000000000000000000000019e7e376e7c213b7e7e7e46cc70a5dd086daff2a";
    uint8_t data[IOTEX_CONTRACT_ENCODED_TOTALSUPPLY_SIZE] = {0};
    char dataStr[sizeof(expected)] = {0};
    Xrc20Contract::generateCallDataForBalanceOf(address, data);
    signer.hex2str(data, sizeof(data), dataStr, sizeof(dataStr));
    ASSERT_STREQ(expected, dataStr);
}

TEST_F(Xrc20ContractTests, generateCallDataForTransfer)
{
    char expected[] = "a9059cbb00000000000000000000000019e7e376e7c213b7e7e7e46cc70a5dd086daff2a0000000000000000000000000000000000000000000000000000000000000064";
    uint8_t data[IOTEX_CONTRACT_ENCODED_TRANSFER_SIZE] = {0};
    char dataStr[sizeof(expected)] = {0};
    Xrc20Contract::generateCallDataForTransfer(address, 100, data);
    signer.hex2str(data, sizeof(data), dataStr, sizeof(dataStr));
    ASSERT_STREQ(expected, dataStr);
}
