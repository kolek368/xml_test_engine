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
   for(std::vector<void *>::iterator it = this->m_pOpenedLibs.begin(); it != this->m_pOpenedLibs.end(); it++)
   {
      dlclose(*it);
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
         /* on Linux, use "./myclass.so" */
         void* handle = dlopen(it->path().c_str(), RTLD_LAZY);
         if(NULL != handle)
         {
            SLS_STATUS (*GetApiList)(SlsLibApi *api);
            GetApiList = (SLS_STATUS (*)(SlsLibApi *))dlsym(handle, "GetApiList");
            if(NULL == GetApiList) {
               printf("%s\n", dlerror());
               dlclose(handle);
            }
            else
            {
               GetApiList(&tmpApi);
               for(std::map<std::string, sls_lib_function>::iterator it2 = tmpApi.begin(); it2 != tmpApi.end(); it2++)
               {
                  std::cout << it2->first << std::endl;
                  sls_lib_function tmpFunPtr = (sls_lib_function)dlsym(handle, it2->first.c_str());
                  std::cout << it2->first << " " << std::hex << GetApiList << std::endl;
                  tmpApi[it2->first] = tmpFunPtr;
               }
               this->m_pOpenedLibs.push_back(handle);
               this->m_LoadedLibs.insert(SlsLib(it->path().filename().c_str(), tmpApi));
            }
         }
      }
      it++;
   }
   return SLS_OK;
}
