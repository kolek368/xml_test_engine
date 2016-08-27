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


class SlsStack
{
public:
   SlsStack(int32_t size = 0)
   {
      if(this->m_MAX_SIZE < size)
      {
         std::bad_alloc exception;
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
      if( (int32_t)(this->m_iStackIdx + sizeof(uint8_t)) >= this->m_iCurrentMaxSize)
      {
         std::bad_alloc exception;
         throw exception;
      }
      this->m_pStack[this->m_iStackIdx+1] = byte;
      this->m_iStackIdx += sizeof(uint8_t);
   };

   void pushw(uint16_t word) {
      if( (int32_t)(this->m_iStackIdx + sizeof(uint16_t)) >= this->m_iCurrentMaxSize)
      {
         std::bad_alloc exception;
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)&word;
      this->m_pStack[this->m_iStackIdx+1] = *pTranslator;
      this->m_pStack[this->m_iStackIdx+2] = *(pTranslator+1);
      this->m_iStackIdx += sizeof(uint16_t);
   };

   void pushd(uint32_t dword) {
      if( (int32_t)(this->m_iStackIdx + sizeof(uint32_t)) >= this->m_iCurrentMaxSize)
      {
         std::bad_alloc exception;
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)&dword;
      this->m_pStack[this->m_iStackIdx+1] = *pTranslator;
      this->m_pStack[this->m_iStackIdx+2] = *(pTranslator+1);
      this->m_pStack[this->m_iStackIdx+3] = *(pTranslator+2);
      this->m_pStack[this->m_iStackIdx+4] = *(pTranslator+3);
      this->m_iStackIdx += sizeof(uint32_t);
   };

   void pushn(uint8_t *nbytes, int32_t nbr) {
      if( (int32_t)(this->m_iStackIdx + nbr) >= this->m_iCurrentMaxSize)
      {
         std::bad_alloc exception;
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
      if(nullptr == byte)
      {
         std::bad_exception exception;
         throw exception;
      }
      if(this->m_iStackIdx < ((int32_t)sizeof(uint8_t)-1))
      {
         std::bad_exception exception;
         throw exception;
      }
      *byte = this->m_pStack[this->m_iStackIdx];
      this->m_iStackIdx -= sizeof(uint8_t);
   };

   void popw(uint16_t* word)
   {
      if(nullptr == word)
      {
         std::bad_exception exception;
         throw exception;
      }
      if(this->m_iStackIdx < ((int32_t)sizeof(uint16_t)-1))
      {
         std::bad_exception exception;
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)word;
      *pTranslator = this->m_pStack[this->m_iStackIdx-1];
      *(pTranslator+1) = this->m_pStack[this->m_iStackIdx];
      this->m_iStackIdx -= sizeof(uint16_t);
   }

   void popd(uint32_t* dword)
   {
      if(nullptr == dword)
      {
         std::bad_exception exception;
         throw exception;
      }
      if(this->m_iStackIdx < ((int32_t)sizeof(uint16_t)-1))
      {
         std::bad_exception exception;
         throw exception;
      }
      uint8_t* pTranslator = (uint8_t *)dword;
      *pTranslator = this->m_pStack[this->m_iStackIdx-3];
      *(pTranslator+1) = this->m_pStack[this->m_iStackIdx-2];
      *(pTranslator+2) = this->m_pStack[this->m_iStackIdx-1];
      *(pTranslator+3) = this->m_pStack[this->m_iStackIdx];
      this->m_iStackIdx -= sizeof(uint32_t);
   }

   void popn(uint8_t* nbytes, int32_t nbr)
   {
      if(nullptr == nbytes)
      {
         std::bad_exception exception;
         throw exception;
      }
      if(this->m_iStackIdx < (nbr-1))
      {
         std::bad_exception exception;
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
