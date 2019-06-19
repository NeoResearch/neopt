#ifndef IMPORT_BLOCKS_SETTINGS_H
#define IMPORT_BLOCKS_SETTINGS_H

// system includes
#include <functional>

// core includes
#include<ledger/plugin/PluginSettings.hpp> // TODO: risky include
#include<common/system/types.h>
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

   static ImportBlocksSettings& Default()
   {
      if(!_default)
         _default = new ImportBlocksSettings(ConfigurationSection()); // empty configuration
      return *_default;
   }

   static void FreeSettings()
   {
      if(_default)
         delete _default;
      _default = nullptr;
   }

private:

   //static uint parse_uint(std::string s);
   static uint parse_uint(std::string s)
   {
      std::cout << "TODO: must parse_uint" << std::endl;
      return 0;
   }

   ImportBlocksSettings(const ConfigurationSection& section);

public:

   template<class T>
   T GetValueOrDefault(const ConfigurationSection& section, T defaultValue, std::function<T(string)> selector)
   {
      if (section.Value() == "") return defaultValue;
      return selector(section.Value());
   }

   static void Load(const ConfigurationSection& section)
   {
       _default = new ImportBlocksSettings(section);
   }

};

}

#endif
