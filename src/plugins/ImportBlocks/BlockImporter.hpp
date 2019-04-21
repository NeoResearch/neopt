#ifndef BLOCK_IMPORTER_HPP
#define BLOCK_IMPORTER_HPP

// TODO: transform into actor with OnReceive (on non-portable version)

// system includes
// ...

// core includes
#include<core/IBlockchain.hpp>
#include<core/Block.hpp>
#include<core/PluginSettings.hpp>

namespace neopt
{

enum BlockImporterAction
{
   StartImport, ImportCompleted
};

class BlockImporter // TODO: public Actor (to have OnReceive)
{
private:

   static const int BlocksPerBatch = 10;
   IBlockchain& blockchain;
   bool isImporting;
   vector<Block> blocksBeingImported;
   ////private Action _doneAction; // TODO: callback

   PluginSettings& settings;

public:
   BlockImporter(PluginSettings& _settings, IBlockchain& _blockchain) :
      settings(_settings), blockchain(_blockchain)
   {
   }

   void Receive(BlockImporterAction action) // TODO: transform into OnReceive with Actor system
   {
      switch(action)
      {
         case StartImport:
            std::cout << "starting to import blocks..." << std::endl;


            this->Receive(BlockImporterAction::ImportCompleted); // TODO: use actor message for this
            break;
         case ImportCompleted:

            std::cout << "import blocks finished..." << std::endl;

            break;
      }
   }

};

}

#endif
