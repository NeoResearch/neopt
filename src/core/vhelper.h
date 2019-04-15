#ifndef VHELPER_H
#define VHELPER_H

// Vector Helper: vhelper

// system
#include<vector>
#include<algorithm>
#include<sstream>

// neo core
#include<Types.h>

namespace neopt
{

// vector helper class
class vhelper
{
public:

   template<class T>
   static vector<T> Reverse(const vector<T>& v)
   {
      vector<T> rev(v);
      std::reverse(rev.begin(), rev.end());
      return std::move(rev);
   }

   // TODO: replace by operator<< ?
   template<class T>
   static string ToHexString(const vector<T>& v)
   {
      stringstream ss;
      // TODO: check if format is this
      for(unsigned i=0; i<v.size(); i++) // TODO: use foreach
         ss << v[i];
      return ss.str();
   }
};

// TODO: define all operators here that are necessary

}

#endif
