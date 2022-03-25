#ifndef IOTEX_ABI_DECODE_H
#define IOTEX_ABI_DECODE_H

#include "helpers/client_helper.h"
#include "IoTeXConstants.h"
#include "IoTeXResultCodes.h"

#include <stddef.h>
#include <stdint.h>

namespace
{
const uint8_t prefixSize = 2;
void skip0xPrefix(const char** pData, size_t* size)
{
	if((*pData)[0] == '0' && ((*pData)[1] == 'x' || (*pData)[1] == 'X'))
	{
		(*pData) += 2;
		*size -= 2;
	}
}
} // namespace

namespace iotex
{
namespace abi
{
namespace decode
{
iotex::ResultCode decodeUintGeneric(const char* pData, size_t uintSize, uint64_t* out);
iotex::ResultCode decodeIntGeneric(const char* pData, size_t uintSize, int64_t* out);
iotex::ResultCode decodeString(const char* pData, size_t size, IotexString& out);

template<uint8_t size>
ResultCode decodeUint(const char* pData, size_t dataSize, uint64_t* out)
{
	// The caller can pass the whole word (32 bytes) or more, but this funciton only decodes up to a
	// <size> byte int.
	if(size > sizeof(uint64_t))
		return ResultCode::ERROR_BAD_PARAMETER;
	size_t dataSizeWoPrefix = dataSize;
	if(dataSize >= prefixSize + size)
	{
		skip0xPrefix(&pData, &dataSizeWoPrefix);
	}
	// Move the pointer to the end of data minus the integer size
	pData = pData + (dataSizeWoPrefix) - (size * 2);
	return decodeUintGeneric(pData, size, (uint64_t*)out);
}

template<uint8_t size>
ResultCode decodeInt(const char* pData, size_t dataSize, int64_t* out)
{
	// The caller can pass the whole word (32 bytes) or more, but this funciton only decodes up to a
	// <size> byte int.
	if(size > sizeof(uint64_t))
		return ResultCode::ERROR_BAD_PARAMETER;
	size_t dataSizeWoPrefix = dataSize;
	if(dataSize >= prefixSize + size)
	{
		skip0xPrefix(&pData, &dataSizeWoPrefix);
	}
	// Move the pointer to the end of data minus the integer size
	pData = pData + (dataSizeWoPrefix) - (size * 2);
	return decodeIntGeneric(pData, size, (int64_t*)out);
}
} // namespace decode
} // namespace abi
} // namespace iotex

#endif