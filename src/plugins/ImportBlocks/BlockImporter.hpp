#ifndef BLOCK_IMPORTER_HPP
#define BLOCK_IMPORTER_HPP

// TODO: transform into actor with OnReceive (on non-portable version)

// system includes
// ...

// core includes
#include<core/IBlockchain.hpp>
#include<core/Block.hpp>

// local includes
#include<ImportBlocksSettings.h>

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

   ///ImportBlocksSettings& settings;

public:
   BlockImporter(IBlockchain& _blockchain) :
      blockchain(_blockchain)
   {
   }

private:
   static bool CheckMaxOnImportHeight(uint currentImportBlockHeight)
   {
       if (ImportBlocksSettings::Default().MaxOnImportHeight == 0 || ImportBlocksSettings::Default().MaxOnImportHeight >= currentImportBlockHeight)
           return true;
       return false;
   }

public:
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
