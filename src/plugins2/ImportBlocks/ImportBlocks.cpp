#include "ImportBlocks.h"

using namespace std;
using namespace neopt;

void ImportBlocks::Configure()
{
   cout << "Configuring ImportBlocks plugin" << endl;
   ImportBlocksSettings::Load(this->GetConfiguration());
}

ImportBlocks::ImportBlocks()
{
   _blockImporter = nullptr;
}

ImportBlocks::~ImportBlocks()
{
   if(_blockImporter)
      delete _blockImporter;
}


bool ImportBlocks::OnMessage(const vector<string>& message)
{
   return false;
}

string ImportBlocks::Name() const
{
   return "ImportBlocks";
}

void ImportBlocks::OnPluginsLoaded()
{
    //SuspendNodeStartup();
    //_blockImporter = System.ActorSystem.ActorOf(BlockImporter.Props());
    //_blockImporter.Tell(new BlockImporter.StartImport { BlockchainActorRef = System.Blockchain, OnComplete = OnImportComplete });

    IBlockchain& blockchain = this->pluginSystem->neoSystem->blockchain;

    _blockImporter = new BlockImporter(blockchain);

    // TODO: use Actor system for message passing
    //_blockImporter->Receive(BlockImporterAction::StartImport);


    cout << "ImportBlocks plugin loaded!" << endl;
}
