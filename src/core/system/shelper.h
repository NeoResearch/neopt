#ifndef SHELPER_H
#define SHELPER_H

// String Helper: shelper

// system
#include<vector>
#include<algorithm>
#include<sstream>

// neo core
#include<system/types.h>

using namespace std; // TODO: avoid!

namespace neopt
{

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

   static vbyte HexToBytes(const string& v)
   {
      // TODO: implement
      NEOPT_EXCEPTION("Not implemented yet: HexToBytes");
      return vbyte(0);
   }


};

// TODO: define all operators here that are necessary

}

#endif
