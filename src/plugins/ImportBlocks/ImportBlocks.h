#ifndef PLUGIN_IMPORT_BLOCKS_H
#define PLUGIN_IMPORT_BLOCKS_H

// system includes
#include<vector>

// core includes
#include<core/plugin/IPlugin.h>

// WARNING: this .hpp include is very risky an may break plugin
#include<core/IBlockchain.hpp>
#include<core/PluginSettings.hpp>

// local includes
#include<BlockImporter.hpp>

namespace neopt
{

class ImportBlocks : public IPlugin
{
private:
   BlockImporter* _blockImporter;
   PluginSettings settings;

public:
   ImportBlocks();

   virtual ~ImportBlocks();

   std::string Name() const;

protected:

   bool OnMessage(const std::vector<std::string>& message);

   void OnPluginsLoaded();

private:
   void OnImportComplete(); // TODO: only use later as a callback after importer actor finishes

};

}

#endif
