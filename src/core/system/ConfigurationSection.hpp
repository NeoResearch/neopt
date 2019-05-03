#ifndef CONFIGURATION_SECTION_HPP
#define CONFIGURATION_SECTION_HPP

// system includes
#include <iostream>
#include <sstream>

namespace neopt {

class ConfigurationSection
{
public:
   static ConfigurationSection AddJsonBuild(std::string path, bool optional = false)
   {
      // TODO: implement
      std::cout << "TODO static: Empty configuration!" << std::endl;
      return ConfigurationSection();
   }

   std::string Value() const
   {
      std::cout << "EMPTY VALUE! (TODO)" << std::endl;
      return "";
   }

   //virtual std::string GetSection(std::string key) = 0;
   virtual ConfigurationSection GetSection(std::string key) const
   {
      std::cout << "TODO: Empty configuration!" << std::endl;
      return ConfigurationSection();
   }
};

}

#endif
