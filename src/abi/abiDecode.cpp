#include "abi/abiDecode.h"

#include "signer/signer.h"
#include "helpers/client_helper.h"
#include <stdint.h>
#include <string.h>

using namespace iotex;
using namespace std;
using namespace iotex::abi;

ResultCode iotex::abi::decode::decodeUintGeneric(const char* pData, size_t uintSize, uint64_t* out)
{
	uint8_t bytes[8] = {0};
	ResultCode res = signer.str2hex(pData, bytes + sizeof(bytes) - uintSize, uintSize);

    if (res != ResultCode::SUCCESS) { return res; }
    IotexHelpers.endianSwap(bytes, 8);
	*out = *((uint64_t*) bytes);

    return ResultCode::SUCCESS;
}

ResultCode iotex::abi::decode::decodeIntGeneric(const char* pData, size_t uintSize, int64_t* out)
{
	uint8_t bytes[8];
	memset(bytes, 0xFF, sizeof(bytes));
	ResultCode res = signer.str2hex(pData, bytes + sizeof(bytes) - uintSize, uintSize);

    if (res != ResultCode::SUCCESS) { return res; }
    IotexHelpers.endianSwap(bytes, 8);
	*out = *((int64_t*) bytes);

    return ResultCode::SUCCESS;
}