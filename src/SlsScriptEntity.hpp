/*
 * SlsScriptEntity.h
 *
 *  Created on: Sep 1, 2016
 *      Author: ares
 */

#ifndef SLSSCRIPTENTITY_HPP_
#define SLSSCRIPTENTITY_HPP_
#include <vector>
#include "SlsLibraryApi.hpp"

#define MAX_SLS_SCRIPT_STACK_SIZE   256

class SlsScriptEntity {
public:
   SlsScriptEntity() {

   };
   virtual ~SlsScriptEntity(){

   };
   virtual SLS_STATUS init(void) {
      return SLS_OK;
   };
   virtual void addParams(void) {};
   virtual void execute(void) {};
};

class SlsCallEntity : public SlsScriptEntity {
public:
   ~SlsCallEntity() {
      if(NULL != this->m_Stack)
      {
         delete this->m_Stack;
      }
   }

   SLS_STATUS init(void)
   {
      SLS_STATUS status = SLS_OK;
      this->m_Stack = new SlsStack(MAX_SLS_SCRIPT_STACK_SIZE);
      if(NULL == this->m_Stack)
      {
         status = SLS_ERROR;
      }
      for(auto const& value: this->m_Params)
      {
         if("string" == value.first)
         {
            try
            {
               uint16_t stringLen = (uint16_t)value.second.length();
               this->m_Stack->pushn((uint8_t *)value.second.c_str(), value.second.length());
               this->m_Stack->pushw(stringLen);
            }
            catch(SlsException& e)
            {
               return SLS_ERROR;
            }
         }
      }
      return status;
   }

   void addParam(SlsFunParam &param) {
      this->m_Params.push_back(param);
   }

   void addParam(sls_lib_function fun) {
      this->m_Fun = fun;
   }

   void execute(void) {
      this->m_Fun(this->m_Stack);
   };
private:
   std::vector<SlsFunParam> m_Params;
   SlsStack *m_Stack = NULL;
   sls_lib_function m_Fun = NULL;
};

#endif /* SLSSCRIPTENTITY_HPP_ */
