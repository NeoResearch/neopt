#ifndef ICONFIGURATION_SECTION_H
#define ICONFIGURATION_SECTION_H


namespace neopt
{

class IConfigurationSection
{
public:

   std::string Value() = 0;

   //virtual std::string GetSection(std::string key) = 0;
   virtual IConfigurationSection& GetSection(std::string key) = 0;

};


}

#endif
