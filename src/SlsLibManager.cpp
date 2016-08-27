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
   boost::filesystem::recursive_directory_iterator it(this->m_LibsPath);
   boost::filesystem::recursive_directory_iterator itend;
   while(it != itend)
   {
      SlsLibApi tmpApi;
      std::cout << it->path().filename().c_str() << std::endl;
      this->m_LoadedLibs.insert(SlsLib(it->path().filename().c_str(), tmpApi));
      it++;
   }
   return SLS_OK;
}
