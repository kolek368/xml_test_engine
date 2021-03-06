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
   for(auto& lib : this->m_pOpenedLibs) {
      dlclose(lib);
   }
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
   const std::string SHARED_LIB_EXTENSION(".so");
   if(!boost::filesystem::exists(this->m_LibsPath))
      return SLS_INVALID_PATH;
   boost::filesystem::recursive_directory_iterator it(this->m_LibsPath);
   boost::filesystem::recursive_directory_iterator itend;
   while(it != itend)
   {
      SlsLibApi tmpApi;
      if(it->path().filename().extension() == SHARED_LIB_EXTENSION)
      {
         void* handle = dlopen(it->path().c_str(), RTLD_LAZY);
         if(NULL != handle)
         {
            SLS_STATUS (*GetApiList)(SlsLibApi *api);
            GetApiList = (SLS_STATUS (*)(SlsLibApi *))dlsym(handle, "GetApiList");
            if(NULL == GetApiList) {
               std::cout << dlerror() << std::endl;
               dlclose(handle);
            }
            else
            {
               GetApiList(&tmpApi);
               this->m_pOpenedLibs.push_back(handle);
               this->m_LoadedLibs.insert(SlsLib(it->path().filename().c_str(), tmpApi));
            }
         }
      }
      it++;
   }
   return SLS_OK;
}
