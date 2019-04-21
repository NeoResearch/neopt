#ifndef IMPORT_BLOCKS_SETTINGS_H
#define IMPORT_BLOCKS_SETTINGS_H

// system includes
#include <functional>

// core includes
#include<core/plugin/PluginSettings.hpp> // TODO: risky include
#include<core/system/types.h>
#include<system/ConfigurationSection.hpp> // TODO: risky include

namespace neopt
{

class ImportBlocksSettings : public PluginSettings
{
public:
   uint MaxOnImportHeight;

   // TODO: singleton pattern
private:
   static ImportBlocksSettings* _default;

public:
   //static ImportBlocksSettings& Default();
   static ImportBlocksSettings& Default()
   {
      return *_default;
   }

private:

   //static uint parse_uint(std::string s);
   static uint parse_uint(std::string s)
   {
       return 0;
   }


   ImportBlocksSettings(const ConfigurationSection& section);



public:

   template<class T>
   T GetValueOrDefault(const ConfigurationSection& section, T defaultValue, std::function<T(string)> selector)
   {
       if (section.Value() == "") return defaultValue;
       //if (section.Value == nullptr) return defaultValue;
       return selector(section.Value());
   }

   static void Load(const ConfigurationSection& section)
   {
       _default = new ImportBlocksSettings(section);
   }

};

}

#endif
