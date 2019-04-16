#ifndef CHELPER_H
#define CHELPER_H

// Crypto Helper: chelper

// system
#include<vector>
#include<sstream>

// neo core
#include<system/types.h>
#include<numbers/UInt160.hpp>

using namespace std; // TODO: avoid!

namespace neopt
{

// crypto helper class
class chelper
{
public:

   static UInt160 ToScriptHash(const vbyte& v)
   {
      NEOPT_EXCEPTION("Not implemented: ToScriptHash");
      return UInt160();
   }

};

// TODO: define all operators here that are necessary

}

#endif
