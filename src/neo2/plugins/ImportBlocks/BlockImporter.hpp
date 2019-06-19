#ifndef BLOCK_IMPORTER_HPP
#define BLOCK_IMPORTER_HPP

// TODO: transform into actor with OnReceive (on non-portable version)

// system includes
// ...

// core includes
#include<ledger/IBlockchain.hpp>
#include<ledger/payloads/Block.hpp>
#include<common/system/BinaryReader.hpp>
#include<ledger/Blockchain.hpp>
#include<common/system/vhelper.hpp>
#include<common/system/printable.h>

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
       //std::cout << "ImportBlocksSettings::Default().MaxOnImportHeight = " << ImportBlocksSettings::Default().MaxOnImportHeight  << std::endl;
       if (ImportBlocksSettings::Default().MaxOnImportHeight == 0 || ImportBlocksSettings::Default().MaxOnImportHeight >= currentImportBlockHeight)
           return true;
       return false;
   }

   // this plugin is not meant to be fully portable (so it should be seen as optional, for x86/64 only)
   // it depends on binary reading large chunks of binary files, what may not be feasible for browsers and microcontrollers
   // TODO: non-static to avoid Blockchain singleton (for now)
   std::vector<Block> GetBlocks(std::istream& stream, bool read_start = false)
   {
      vector<Block> blocks;
      // reading from binary stream
      BinaryReader r(stream);
      uint start = read_start ? r.ReadUInt32() : 0;
      uint count = r.ReadUInt32();
      std::cout << "BlockImporter::Import from height " << start << " to height " << count << std::endl;
      uint end = start + count - 1;
      if (end <= blockchain.Height())
      //if (end <= Blockchain::Singleton().Height)
         return std::move(blocks);
      for (uint height = start; height <= end; height++)
      {
         std::cout << "Will read bytes for height = " << height << std::endl;
         int size = r.ReadInt32();
         std::cout << "block size = " << size << "(reading these and storing on array)" << std::endl;
         vbyte array = r.ReadBytes(size);
         std::cout << "array size = " << array.size() << array << std::endl;
         if (!CheckMaxOnImportHeight(height))
            break;
         std::cout << "may import" << std::endl;
         if (height > blockchain.Height())
         //if (height > Blockchain::Singleton().Height)
         {
            std::cout << "needs to load block!" << std::endl;
            //Block block = array.AsSerializable<Block>();
            Block block = vhelper::AsSerializable<Block>(array);
            blocks.push_back(std::move(block));
         }
         else
            std::cout << "skipping block.." << std::endl;
      }
      return std::move(blocks);
   }

   // this methods depends on disk read/write, so it's not fully portable
   // this plugin is not meant to be fully portable anyway, mostly for x86/64
   std::vector<Block> GetBlocksFromFile()
   {
      std::vector<Block> blocks;
      const string pathAcc = "chain.acc";

      if (BinaryReader::FileExists(pathAcc))
      {
         std::cout << "File 'chain.acc' found! Will import it!" << std::endl;
         std::ifstream fs(pathAcc, std::ios::binary);
         return GetBlocks(fs);
      }
      else
         std::cout << "File 'chain.acc' not found!" << std::endl;

// TODO: allow .zip
/*
       const string pathAccZip = pathAcc + ".zip";
       if (BinaryReader::FileExists(pathAccZip))
       {
           using (FileStream fs = new FileStream(pathAccZip, FileMode.Open, FileAccess.Read, FileShare.Read))
           using (ZipArchive zip = new ZipArchive(fs, ZipArchiveMode.Read))
           using (Stream zs = zip.GetEntry(pathAcc).Open())
               foreach (var block in GetBlocks(zs))
                   yield return block;
       }
*/

// TODO: allow split files
/*
       var paths = Directory.EnumerateFiles(".", "chain.*.acc", SearchOption.TopDirectoryOnly).Concat(Directory.EnumerateFiles(".", "chain.*.acc.zip", SearchOption.TopDirectoryOnly)).Select(p => new
       {
           FileName = Path.GetFileName(p),
           Start = uint.Parse(Regex.Match(p, @"\d+").Value),
           IsCompressed = p.EndsWith(".zip")
       }).OrderBy(p => p.Start);

       foreach (var path in paths)
       {
           if (path.Start > Blockchain.Singleton.Height + 1) break;
           if (path.IsCompressed)
               using (FileStream fs = new FileStream(path.FileName, FileMode.Open, FileAccess.Read, FileShare.Read))
               using (ZipArchive zip = new ZipArchive(fs, ZipArchiveMode.Read))
               using (Stream zs = zip.GetEntry(Path.GetFileNameWithoutExtension(path.FileName)).Open())
                   foreach (var block in GetBlocks(zs, true))
                       yield return block;
           else
               using (FileStream fs = new FileStream(path.FileName, FileMode.Open, FileAccess.Read, FileShare.Read))
                   foreach (var block in GetBlocks(fs, true))
                       yield return block;
       }
       */
       return blocks;
    }


public:
   void Receive(BlockImporterAction action) // TODO: transform into protected OnReceive with Actor system
   {
      switch(action)
      {
         case StartImport:
         {
            std::cout << "starting to import blocks..." << std::endl;

            //bool b = CheckMaxOnImportHeight(10);

            blocksBeingImported = this->GetBlocksFromFile();

            this->Receive(BlockImporterAction::ImportCompleted); // TODO: use actor message for this
            break;
         }
         case ImportCompleted:
         {
            std::cout << "import blocks finished..." << std::endl;

            std::vector<Block> blocksToImport = blocksBeingImported;
            blocksBeingImported.clear();

            if(blocksToImport.size() > 0)
            {
               blockchain.OnImport(blocksToImport);
               //Blockchain::Singleton().OnImport(blocksToImport);
                //_blockchainActorRef.Tell(new Blockchain.Import { Blocks = blocksToImport });
            }
            else
            {
                blocksBeingImported.clear();//Dispose();
                //_doneAction(); // should call ImportBlocks::OnImportCompleted
                std::cout << "Should call ImportBlocks::OnImportCompleted. TODO" << std::endl;
            }

            break;
         }
      }
   }

};

}

#endif
