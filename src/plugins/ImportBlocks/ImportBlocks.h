#ifndef PLUGIN_IMPORT_BLOCKS_H
#define PLUGIN_IMPORT_BLOCKS_H

// system includes
#include<vector>

// core includes
#include<core/plugin/IPlugin.h>

namespace neopt
{

class ImportBlocks : public IPlugin
{
public:
   // what to put here?

protected:

   bool OnMessage(const std::vector<std::string>& message);

   std::string Name() const;

};

}

#endif
