#ifndef NEOPT_SHELPER_H
#define NEOPT_SHELPER_H

// String Helper: shelper

// system
#include <algorithm>
#include <sstream>
#include <vector>

// neo core
#include "types.h"

using namespace std; // TODO: avoid!

namespace neopt {

// string helper class
class shelper
{
public:
   static bool StartsWith(const string& v, string value)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented yet: StartsWith");
      return false;
   }

   static string Substring(const string& v, int from)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented yet: Substring");
      return "";
   }

   static vbyte HexToBytes(const string& hex)
   {
      // TODO: implement (begin 0x)
      //NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      vbyte bytes(hex.length() / 2);

      for (uint i = 0; i < hex.length(); i += 2) {
         std::string byteString = hex.substr(i, 2);
         byte b = (byte)strtol(byteString.c_str(), NULL, 16);
         bytes[i / 2] = b;
      }
      return bytes;
   }
};

// TODO: define all operators here that are necessary

}

#endif
