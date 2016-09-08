/*
 * sls_stack.hpp
 *
 *  Created on: Aug 26, 2016
 *      Author: ares
 */

#ifndef SLSSTACK_HPP_
#define SLSSTACK_HPP_

#include <cstdint>
#include <exception>

class SlsException : public std::exception
{
public:
   SlsException(std::string what = "SlsException")
   {
      this->m_What = what;
   };
   virtual const char* what() const throw()
   {
      return this->m_What.c_str();
   }
private:
   std::string m_What;
};

class SlsStack
{
public:
   SlsStack(int32_t size = 256)
   {
      if(this->m_MAX_SIZE < size)
      {
         SlsException exception("Stack size exceeds max stack size.");
         throw exception;
      }
      else
      {
         try
         {
            this->m_pStack = new uint8_t[size];
            this->m_iCurrentMaxSize = size;
            this->m_iStackIdx = -1;
         }
         catch(std::exception &e)
         {
            throw e;
         }
      }
   }
   ~SlsStack()
   {
      delete this->m_pStack;
   }

   void push(uint8_t byte) {
      return this->pushn(&byte, sizeof(uint8_t));
   };

   void pushw(uint16_t word) {
      return this->pushn((uint8_t *)&word, sizeof(word));
   };

   void pushd(uint32_t dword) {
      return this->pushn((uint8_t *)&dword, sizeof(dword));
   };

   void pushn(uint8_t *nbytes, int32_t nbr) {
      if( (int32_t)(this->m_iStackIdx + nbr) >= this->m_iCurrentMaxSize)
      {
         SlsException exception("Not enough memory left.");
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)nbytes;
      for(int32_t i = 0; i < nbr; i++, pTranslator++)
      {
         this->m_pStack[this->m_iStackIdx+1+i] = *pTranslator;
      }
      this->m_iStackIdx += nbr;
   };

   void pop(uint8_t* byte){
      return this->popn(byte, sizeof(uint8_t));
   };

   void popw(uint16_t* word)
   {
      return this->popn((uint8_t*)word, sizeof(uint16_t));
   }

   void popd(uint32_t* dword)
   {
      return this->popn((uint8_t*)dword, sizeof(uint32_t));
   }

   void popn(uint8_t* nbytes, int32_t nbr)
   {
      if(nullptr == nbytes)
      {
         SlsException exception("Invalid pointer.");
         throw exception;
      }
      if(this->m_iStackIdx < (nbr-1))
      {
         SlsException exception("Insufficient number of bytes on stack.");
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)nbytes;
      for(int32_t i = nbr; i > 0; i--, pTranslator++)
      {
         *pTranslator = this->m_pStack[this->m_iStackIdx+1-i];
      }
      this->m_iStackIdx -= nbr;
   }

private:
   const int32_t m_MAX_SIZE = 4096;
   int32_t m_iCurrentMaxSize;
   uint8_t* m_pStack = nullptr;
   int32_t m_iStackIdx = -1;
};



#endif /* SLSSTACK_HPP_ */
