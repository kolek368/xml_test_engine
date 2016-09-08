/*
 * SlsLibraryApi.h
 *
 *  Created on: Aug 27, 2016
 *      Author: ares
 */

#ifndef SLSLIBRARYAPI_HPP_
#define SLSLIBRARYAPI_HPP_
#include <exception>
#include <map>
#include <string>
#include "SlsStack.hpp"

typedef enum _SLS_STATUS
{
   SLS_OK = 0,
   SLS_ERROR = -1,
   SLS_INVALID_PATH = -2,
} SLS_STATUS;

typedef SLS_STATUS (*sls_lib_function)(SlsStack *stack);

typedef std::map<std::string, sls_lib_function> SlsLibApi;
typedef std::pair<std::string, sls_lib_function> SlsLibFun;

typedef std::map<std::string, SlsLibApi> SlsLibs;
typedef std::pair<std::string, SlsLibApi> SlsLib;

typedef std::pair<std::string, std::string> SlsFunParam;

#endif /* SLSLIBRARYAPI_HPP_ */
