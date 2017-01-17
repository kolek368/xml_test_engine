/*
 * SlsProgram.h
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */

#ifndef SLSPROGRAM_H_
#define SLSPROGRAM_H_

#include <exception>
#include <string>
#include <vector>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "SlsLibraryApi.hpp"
#include "SlsLibManager.h"
#include "SlsScriptEntity.hpp"
#include "SlsVariable.hpp"

class SlsProgram
{
public:
   SlsProgram(const char* libPath);
   ~SlsProgram();
   bool build(const char* path);
   void run(void);
private:
   bool load(const char* path);
   bool compile(void);
   bool parseLine(boost::property_tree::ptree::value_type &line);
   bool parseCall(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog);
   bool parseSet(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog);
   bool parseIf(boost::property_tree::ptree::value_type &line, std::vector<SlsScriptEntity *> &prog);
   SLS_STATUS createVariable(std::string Name, std::string Type, std::string Value);
   boost::property_tree::ptree m_RawProgram;
   bool m_ProgramReady;
   SlsStack* m_Stack;
   SlsLibManager m_Libs;
   std::vector<SlsScriptEntity *> m_Program;
   SlsVariables m_Variables;
};

#endif /* SLSPROGRAM_H_ */
