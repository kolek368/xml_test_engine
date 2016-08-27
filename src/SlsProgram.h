/*
 * SlsProgram.h
 *
 *  Created on: Aug 23, 2016
 *      Author: ares
 */

#ifndef SLSPROGRAM_H_
#define SLSPROGRAM_H_

#include <string>
#include <exception>
#include <boost/foreach.hpp>
#include <boost/filesystem.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/ptree.hpp>

class SlsProgram
{
public:
   SlsProgram();
   ~SlsProgram();
   bool build(const char* path);
private:
   bool load(const char* path);
   bool compile(void);
   boost::property_tree::ptree m_RawProgram;
};

#endif /* SLSPROGRAM_H_ */
