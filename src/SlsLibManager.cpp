/*
 * SlsLibManager.cpp
 *
 *  Created on: Aug 27, 2016
 *      Author: ares
 */

#include "SlsLibManager.h"

SlsLibManager::SlsLibManager() {
   // TODO Auto-generated constructor stub

}

SlsLibManager::~SlsLibManager() {
   // TODO Auto-generated destructor stub
}

SLS_STATUS SlsLibManager::setPath(const char* libsDirectoryPath)
{
   if(!boost::filesystem::exists(libsDirectoryPath))
      return SLS_INVALID_PATH;
   this->m_LibsPath = boost::filesystem::path(libsDirectoryPath);
   return SLS_OK;
}

SLS_STATUS SlsLibManager::loadLibs(void)
{
   if(!boost::filesystem::exists(this->m_LibsPath))
      return SLS_INVALID_PATH;
   return SLS_OK;
}
