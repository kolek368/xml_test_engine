/*
 * sls_test_library.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */

#include <string>
#include <vector>
#include "SlsLibraryApi.hpp"

#define LibraryNamespace   "SLS_TEST_LIB"

using namespace std;

SLS_STATUS TestFunPrintMsg(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   return Status;
}

SLS_STATUS TestFunPrintAdd(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   return Status;
}

SLS_STATUS TestFunFillArray(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   return Status;
}

SLS_STATUS TestFunReadArray(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   return Status;
}

std::string GetLibraryNamespace(void)
{
   return std::string(LibraryNamespace);
}

SLS_STATUS GetApiList(SlsLibApi *api)
{
   SLS_STATUS Status = SLS_OK;
   api->clear();
   api->insert(SlsLibFun("TestFunPrintMsg", TestFunPrintMsg));
   api->insert(SlsLibFun("TestFunPrintAdd", TestFunPrintAdd));
   api->insert(SlsLibFun("TestFunFillArray", TestFunFillArray));
   api->insert(SlsLibFun("TestFunReadArray", TestFunReadArray));
   return Status;
}

