#ifndef KHELPER_H
#define KHELPER_H

// cli helper

// TODO: move things to a String Helper

// system includes
#include<string>
#include<algorithm>
#include <cctype>
#include <locale>

// core includes

namespace neopt
{

class khelper
{
public:

   static std::string ToLower(const std::string& s)
   {
      std::string data(s);
      std::transform(data.begin(), data.end(), data.begin(), ::tolower);
      return std::move(data);
   }

   static void ltrim(std::string &s) {
      s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
      }));
   }

   static void rtrim(std::string &s)
   {
      s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
      }).base(), s.end());
   }

   static void trim(std::string &s) {
      ltrim(s);
      rtrim(s);
   }

   static std::string ltrim_copy(std::string s)
   {
      ltrim(s);
      return s;
   }

   static inline std::string rtrim_copy(std::string s)
   {
      rtrim(s);
      return s;
   }

   static inline std::string trim_copy(std::string s)
   {
      trim(s);
      return s;
   }

};

}

#endif
