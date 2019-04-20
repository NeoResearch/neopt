#ifndef BLOCK_IMPORTER_HPP
#define BLOCK_IMPORTER_HPP

// TODO: transform into actor with OnReceive


namespace neopt
{

enum BlockImporterAction
{
   StartImport, ImportCompleted
};

class BlockImporter // TODO: public Actor (to have OnReceive)
{
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
