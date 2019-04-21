#ifndef CONFIGURATION_SECTION_HPP
#define CONFIGURATION_SECTION_HPP

// system includes
#include<iostream>
#include<sstream>

namespace neopt
{

class ConfigurationSection
{
public:

   static ConfigurationSection AddJsonBuild(std::string path, bool optional = false)
   {
      // TODO: implement
      return ConfigurationSection();
   }

   std::string Value() const
   {
   }

   //virtual std::string GetSection(std::string key) = 0;
   virtual ConfigurationSection GetSection(std::string key) const
   {
   }

};


}

#endif
