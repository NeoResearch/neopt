#include<ImportBlocks.h>

using namespace std;
using namespace neopt;

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

    // TODO: use Actor system for message passing
    _blockImporter.Receive(BlockImporterAction::StartImport);
    IBlockchain* blockchain = this->pluginSystem->neoSystem->blockchain;

    cout << "ImportBlocks plugin loaded!" << endl;
}
