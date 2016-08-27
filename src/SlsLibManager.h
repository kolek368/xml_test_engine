/*
 * SlsLibManager.h
 *
 *  Created on: Aug 27, 2016
 *      Author: ares
 */

#ifndef SLSLIBMANAGER_H_
#define SLSLIBMANAGER_H_

#include <boost/filesystem.hpp>
#include "SlsLibraryApi.hpp"

class SlsLibManager {
public:
   SlsLibManager();
   ~SlsLibManager();
   SLS_STATUS setPath(const char* libsDirectoryPath);
   SLS_STATUS loadLibs(void);
   SlsLibs m_LoadedLibs;
private:
   boost::filesystem::path m_LibsPath;
};

#endif /* SLSLIBMANAGER_H_ */
