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
	ResultCode res = signer.str2hex(pData, bytes + sizeof(bytes) - uintSize, uintSize, uintSize*2);
    if (res != ResultCode::SUCCESS) { return res; }

    IotexHelpers.endianSwap(bytes, 8);
	*out = *((uint64_t*) bytes);
    return ResultCode::SUCCESS;
}

ResultCode iotex::abi::decode::decodeIntGeneric(const char* pData, size_t uintSize, int64_t* out)
{
	uint8_t bytes[8];
	memset(bytes, 0xFF, sizeof(bytes));
	ResultCode res = signer.str2hex(pData, bytes + sizeof(bytes) - uintSize, uintSize, uintSize*2);
    if (res != ResultCode::SUCCESS) { return res; }

    IotexHelpers.endianSwap(bytes, 8);
	*out = *((int64_t*) bytes);
    return ResultCode::SUCCESS;
}

ResultCode iotex::abi::decode::decodeString(const char* pData, size_t size, IotexString& out)
{
	// A string has n 32 byte words where n>=3.
	// Word 1: header (offset to the data area)
	// Word 2: size of the string, encoded as uint
	// Words 3-n: the string contents.
	const uint wordSize = 64;
	if (size < 3*wordSize) { return ResultCode::ERROR_BAD_PARAMETER; }

	// Parse the string size to get the string size.
	// We only parse the last 8 bytpDataes from the size word. The size will never overflow a 64b uint.
	const char* pStringLenStart = pData + (wordSize*2) - 16;
	uint64_t stringLength = 0;
	ResultCode res = decodeUintGeneric(pStringLenStart, 8, &stringLength);
	if (res != ResultCode::SUCCESS) { return res; }
	// Check the size of the passed data is enough to contain the string size
	if ((size-64) < stringLength) { return ResultCode::ERROR_BAD_PARAMETER; }

	// Create a buffer of string size. Add 1 extra byte for the null terminator.
	out.reserve(stringLength);
	const char* pString = pData + wordSize*2;
	char buf[stringLength+1] = {0};
	signer.str2hex(pString, (uint8_t*) buf, sizeof(buf), stringLength*2);
	out = buf;
	
	return ResultCode::SUCCESS;
}
