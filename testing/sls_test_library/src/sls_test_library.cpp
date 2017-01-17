/*
 * sls_test_library.cpp
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "SlsLibraryApi.hpp"

#define LibraryNamespace   "SLS_TEST_LIB"

using namespace std;

extern "C" SLS_STATUS TestFunPrintMsg(SlsStack *stack)
{
   uint16_t msgSize;
   SLS_STATUS Status = SLS_OK;
   stack->popw(&msgSize);
   uint8_t *msg = new uint8_t[msgSize];
   stack->popn(msg, msgSize);
   for(int i = 0; i < msgSize; i++)
   {
      cout << msg[i];
   }
   cout << endl;
   delete [] msg;
   return Status;
}

extern "C" SLS_STATUS TestFunPrintAdd(SlsStack *stack)
{
   uint32_t a;
   uint32_t b;
   uint32_t result;
   SLS_STATUS Status = SLS_OK;
   stack->popd(&a);
   stack->popd(&b);
   result = a + b;
   stack->pushd(result);
   cout << "a + b = " << result << endl;
   return Status;
}

extern "C" SLS_STATUS TestFunFillArray(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   uint8_t *arrayPtr;
   uint8_t size;
   stack->popn((uint8_t *)&arrayPtr, sizeof(arrayPtr));
   stack->pop(&size);
   printf("Array pointer: %lX \r\n", (unsigned long int)arrayPtr);
   for(uint8_t i = 0; i < size; i++)
   {
      arrayPtr[i] = i;
   }
   return Status;
}

extern "C" SLS_STATUS TestFunReadArray(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   uint8_t *arrayPtr;
   uint8_t size;
   stack->popn((uint8_t *)&arrayPtr, sizeof(arrayPtr));
   stack->pop(&size);
   for(uint8_t i = 0; i < size; i++)
   {
      std::cout << "Element[" << i << "] = " << arrayPtr[i] << std::endl;
   }
   return Status;
}

extern "C" SLS_STATUS TestFunFactorial(SlsStack *stack)
{
   SLS_STATUS Status = SLS_OK;
   uint32_t value;
   uint32_t result = 1;
   stack->popd(&value);
   while(value > 1) {
      result *= value;
      value -= 1;
   }
   stack->pushd(result);
   return Status;
}

extern "C" std::string GetLibraryNamespace(void)
{
   return std::string(LibraryNamespace);
}

extern "C" SLS_STATUS GetApiList(SlsLibApi *api)
{
   SLS_STATUS Status = SLS_OK;
   api->clear();
   api->insert(SlsLibFun("TestFunPrintMsg", TestFunPrintMsg));
   api->insert(SlsLibFun("TestFunPrintAdd", TestFunPrintAdd));
   api->insert(SlsLibFun("TestFunFillArray", TestFunFillArray));
   api->insert(SlsLibFun("TestFunReadArray", TestFunReadArray));
   api->insert(SlsLibFun("TestFunFactorial", TestFunFactorial));
   return Status;
}

