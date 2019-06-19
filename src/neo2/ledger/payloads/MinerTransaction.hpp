#ifndef MINER_TRANSACTION_HPP
#define MINER_TRANSACTION_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <core/IInventory.hpp>
#include <Witness.hpp>
#include <numbers/BigInteger.h>
#include <numbers/Fixed8.hpp>
#include <numbers/UIntBase.hpp>
#include <ledger/payloads/CoinReference.hpp>
#include <ledger/payloads/Transaction.hpp>
#include <ledger/payloads/TransactionAttribute.hpp>
#include <ledger/payloads/TransactionOutput.hpp>
#include <ledger/payloads/TransactionType.h>
#include <system/IComparable.h>
#include <system/IEquatable.h>
#include <system/ISerializable.h>
#include <system/shelper.h>

namespace neopt {

class MinerTransaction : public Transaction
{
public:
   uint Nonce;

   virtual Fixed8 getNetworkFee()
   {
      return Fixed8::Zero();
   }

   virtual int Size()
   {
      return Transaction::Size() + sizeof(uint);
   }

public:
   MinerTransaction()
     : Transaction(TT_MinerTransaction)
   {
   }

protected:
   virtual void DeserializeExclusiveData(IBinaryReader& reader)
   {
      std::cout << "MinerTX::DeserializeExclusiveData" << std::endl;
      if (Transaction::Version != 0)
         NEOPT_EXCEPTION("MinerTx FormatException");
      this->Nonce = reader.ReadUInt32();
   }

   void OnDeserialized()
   {
      Transaction::OnDeserialized();
      // TODO:
      /*
            if (Transaction::Inputs.Length != 0)
                throw new FormatException();
            if (Transaction::Outputs.Any(p => p.AssetId != Blockchain.UtilityToken.Hash))
                throw new FormatException();
            */
   }

protected:
   virtual void SerializeExclusiveData(IBinaryWriter& writer) const
   {
      writer.Write(Nonce);
   }
};
}

#endif
