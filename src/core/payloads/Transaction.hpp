#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/ISerializable.h>
#include<system/IEquatable.h>
#include<IInventory.hpp>
#include<system/IComparable.h>
#include<numbers/UIntBase.hpp>
#include<numbers/BigInteger.h>
#include<numbers/Fixed8.hpp>
#include<system/shelper.h>
#include<Witness.hpp>
#include<payloads/TransactionType.h>
#include<payloads/TransactionAttribute.hpp>
#include<payloads/CoinReference.hpp>
#include<payloads/TransactionOutput.hpp>


namespace neopt
{

   class Transaction : public IEquatable<Transaction>, public IInventory
   {
   public:
      const int MaxTransactionSize = 102400;
      /// <summary>
      /// Maximum number of attributes that can be contained within a transaction
      /// </summary>
      const int MaxTransactionAttributes = 16;

      const TransactionType Type;
      byte Version;
      std::vector<TransactionAttribute> Attributes;
      std::vector<CoinReference> Inputs;
      std::vector<TransactionOutput> Outputs;
      std::vector<Witness> Witnesses;

   private:
      Fixed8 _feePerByte;
   public:
      /// <summary>
      /// The <c>NetworkFee</c> for the transaction divided by its <c>Size</c>.
      /// <para>Note that this property must be used with care. Getting the value of this property multiple times will return the same result. The value of this property can only be obtained after the transaction has been completely built (no longer modified).</para>
      /// </summary>
      Fixed8 getFeePerByte()
      {
         if (_feePerByte == -Fixed8::Satoshi())
             _feePerByte = NetworkFee() / Size();
         return _feePerByte;
      }

   private:
      UInt256* _hash;
   public:
      UInt256 getHash()
      {
          if (_hash == nullptr)
               _hash = new UInt256(Crypto::Default().Hash256(this->GetHashData()));
          return *_hash; // do not move this
      }

      InventoryType getInventoryType()
      {
         return InventoryType::IT_TX;
      }

      bool IsLowPriority()
      {
         return true; // TODO: fix
         //return NetworkFee < ProtocolSettings.Default.LowPriorityThreshold;
      }


   private:
      Fixed8 _network_fee;

   public:
      virtual Fixed8 NetworkFee()
      {
          if (_network_fee == -Fixed8::Satoshi())
          {
              // TODO: make this part
              //Fixed8 input = References.Values.Where(p => p.AssetId.Equals(Blockchain.UtilityToken.Hash)).Sum(p => p.Value);
              //Fixed8 output = Outputs.Where(p => p.AssetId.Equals(Blockchain.UtilityToken.Hash)).Sum(p => p.Value);
              //_network_fee = input - output - SystemFee;
          }
          return _network_fee;
      }

// TODO:
/*
      private IReadOnlyDictionary<CoinReference, TransactionOutput> _references;
        public IReadOnlyDictionary<CoinReference, TransactionOutput> References
        {
            get
            {
                if (_references == null)
                {
                    Dictionary<CoinReference, TransactionOutput> dictionary = new Dictionary<CoinReference, TransactionOutput>();
                    foreach (var group in Inputs.GroupBy(p => p.PrevHash))
                    {
                        Transaction tx = Blockchain.Singleton.Store.GetTransaction(group.Key);
                        if (tx == null) return null;
                        foreach (var reference in group.Select(p => new
                        {
                            Input = p,
                            Output = tx.Outputs[p.PrevIndex]
                        }))
                        {
                            dictionary.Add(reference.Input, reference.Output);
                        }
                    }
                    _references = dictionary;
                }
                return _references;
            }
        }
*/
      virtual int Size()
      {
         // TODO: calculate this
         return 0;//sizeof(TransactionType) + sizeof(byte) + Attributes.GetVarSize() + Inputs.GetVarSize() + Outputs.GetVarSize() + Witnesses.GetVarSize();
      }

      virtual Fixed8 SystemFee()
      {
         //TODO:  make this
         //return ProtocolSettings.Default.SystemFee.TryGetValue(Type, out Fixed8 fee) ? fee : Fixed8.Zero;
         return Fixed8::Zero();
      }


      // IVerifiable
      virtual std::vector<Witness> getWitnesses()
      {
         return Witnesses;
      }

      // IVerifiable
      virtual vbyte GetMessage()
      {
          return this->GetHashData();
      }

      // IVerifiable
      virtual std::vector<UInt160> GetScriptHashesForVerifying(ISnapshot& snapshot)
      {
         /*
         if (References == null) throw new InvalidOperationException();
         HashSet<UInt160> hashes = new HashSet<UInt160>(Inputs.Select(p => References[p].ScriptHash));
         hashes.UnionWith(Attributes.Where(p => p.Usage == TransactionAttributeUsage.Script).Select(p => new UInt160(p.Data)));
         foreach (var group in Outputs.GroupBy(p => p.AssetId))
         {
             AssetState asset = snapshot.Assets.TryGet(group.Key);
             if (asset == null) throw new InvalidOperationException();
             if (asset.AssetType.HasFlag(AssetType.DutyFlag))
             {
                  hashes.UnionWith(group.Select(p => p.ScriptHash));
             }
         }
         return hashes.OrderBy(p => p).ToArray();
         */
         return std::vector<UInt160>(0);
      }

   public:
      Transaction() : // TODO: remove
         Type(TransactionType::TT_MinerTransaction) // TODO: remove
      {
      }

   protected:
      Transaction(TransactionType _type) :
         Type(_type),_feePerByte(-Fixed8::Satoshi()), _hash(nullptr), _network_fee(-Fixed8::Satoshi())
      {
      }

   public:
      virtual ~Transaction()
      {
         if(_hash)
            delete _hash;
         _hash = nullptr;
      }

      bool Equals(const Transaction* other)
      {
         if(other == nullptr)
            return false;
         // (other == nullptr ? false : CompareTo(*other) == 0) // TODO: make shorter?
         return false;//CompareTo(*other) == 0;
      }

   protected:
      virtual void DeserializeExclusiveData(IBinaryReader& reader)
      {
      }

   public:

      void Deserialize(IBinaryReader& reader)
      {
         this->DeserializeUnsigned(reader);
         Witnesses = reader.ReadSerializableArray<Witness>();
         OnDeserialized();
      }

      void DeserializeUnsigned(IBinaryReader& reader)
      {
         if ((TransactionType)reader.ReadByte() != Type)
            NEOPT_EXCEPTION("Transaction::DeserializeUnsigned FormatException");
         DeserializeUnsignedWithoutType(reader);
      }

private:
      void DeserializeUnsignedWithoutType(IBinaryReader& reader)
      {
         Version = reader.ReadByte();
         std::cout << "Transaction:: will read exclusive data" << std::endl;
         DeserializeExclusiveData(reader);
         std::cout << "Transaction:: will read arrays" << std::endl;
         std::cout << "Transaction:: will read array 1" << std::endl;
         Attributes = reader.ReadSerializableArray<TransactionAttribute>(MaxTransactionAttributes);
         std::cout << "Transaction:: will read array 2" << std::endl;
         Inputs = reader.ReadSerializableArray<CoinReference>();
         std::cout << "Transaction:: will read array 3" << std::endl;
         Outputs = reader.ReadSerializableArray<TransactionOutput>(types::MaxValue<ushort>() + 1);
      }

protected:
      virtual void OnDeserialized()
      {
      }


public:
       virtual bool Verify(ISnapshot& snapshot)
       {
          std::vector<Transaction> mempool(0);
          return Verify(snapshot, mempool);
       }

       virtual bool Verify(ISnapshot& snapshot, std::vector<Transaction>& mempool)
       {
          /*
            if (Size > MaxTransactionSize) return false;
            for (int i = 1; i < Inputs.Length; i++)
                for (int j = 0; j < i; j++)
                    if (Inputs[i].PrevHash == Inputs[j].PrevHash && Inputs[i].PrevIndex == Inputs[j].PrevIndex)
                        return false;
            if (mempool.Where(p => p != this).SelectMany(p => p.Inputs).Intersect(Inputs).Count() > 0)
                return false;
            if (snapshot.IsDoubleSpend(this))
                return false;
            foreach (var group in Outputs.GroupBy(p => p.AssetId))
            {
                AssetState asset = snapshot.Assets.TryGet(group.Key);
                if (asset == null) return false;
                if (asset.Expiration <= snapshot.Height + 1 && asset.AssetType != AssetType.GoverningToken && asset.AssetType != AssetType.UtilityToken)
                    return false;
                foreach (TransactionOutput output in group)
                    if (output.Value.GetData() % (long)Math.Pow(10, 8 - asset.Precision) != 0)
                        return false;
            }
            TransactionResult[] results = GetTransactionResults()?.ToArray();
            if (results == null) return false;
            TransactionResult[] results_destroy = results.Where(p => p.Amount > Fixed8.Zero).ToArray();
            if (results_destroy.Length > 1) return false;
            if (results_destroy.Length == 1 && results_destroy[0].AssetId != Blockchain.UtilityToken.Hash)
                return false;
            if (SystemFee > Fixed8.Zero && (results_destroy.Length == 0 || results_destroy[0].Amount < SystemFee))
                return false;
            TransactionResult[] results_issue = results.Where(p => p.Amount < Fixed8.Zero).ToArray();
            switch (Type)
            {
                case TransactionType.MinerTransaction:
                case TransactionType.ClaimTransaction:
                    if (results_issue.Any(p => p.AssetId != Blockchain.UtilityToken.Hash))
                        return false;
                    break;
                case TransactionType.IssueTransaction:
                    if (results_issue.Any(p => p.AssetId == Blockchain.UtilityToken.Hash))
                        return false;
                    break;
                default:
                    if (results_issue.Length > 0)
                        return false;
                    break;
            }
            if (Attributes.Count(p => p.Usage == TransactionAttributeUsage.ECDH02 || p.Usage == TransactionAttributeUsage.ECDH03) > 1)
                return false;
            if (!VerifyReceivingScripts()) return false;
            return this.VerifyWitnesses(snapshot);
            */
       }

    private:
       bool VerifyReceivingScripts()
       {
            //TODO: run ApplicationEngine
            //foreach (UInt160 hash in Outputs.Select(p => p.ScriptHash).Distinct())
            //{
            //    ContractState contract = Blockchain.Default.GetContract(hash);
            //    if (contract == null) continue;
            //    if (!contract.Payable) return false;
            //    using (StateReader service = new StateReader())
            //    {
            //        ApplicationEngine engine = new ApplicationEngine(TriggerType.VerificationR, this, Blockchain.Default, service, Fixed8.Zero);
            //        engine.LoadScript(contract.Script, false);
            //        using (ScriptBuilder sb = new ScriptBuilder())
            //        {
            //            sb.EmitPush(0);
            //            sb.Emit(OpCode.PACK);
            //            sb.EmitPush("receiving");
            //            engine.LoadScript(sb.ToArray(), false);
            //        }
            //        if (!engine.Execute()) return false;
            //        if (engine.EvaluationStack.Count != 1 || !engine.EvaluationStack.Pop().GetBoolean()) return false;
            //    }
            //}
            return true;
       }



      // serialization

public:
      void Serialize(IBinaryWriter& writer)
      {
         this->SerializeUnsigned(writer);
         IBinaryWriter::WriteArray<Witness>(writer, Witnesses);
      }

protected:
      virtual void SerializeExclusiveData(IBinaryWriter& writer) const
      {
      }

public:
      void SerializeUnsigned(IBinaryWriter& writer) const
      {
         writer.Write((byte)Type);
         writer.Write(Version);
         SerializeExclusiveData(writer);
         IBinaryWriter::WriteArray<TransactionAttribute>(writer, Attributes);
         //writer.Write(Attributes);
         IBinaryWriter::WriteArray<CoinReference>(writer, Inputs);
         //writer.Write(Inputs);
         IBinaryWriter::WriteArray<TransactionOutput>(writer, Outputs);
         //writer.Write(Outputs);
      }

      // strange static methods (could be elsewhere?)
public:

      static Transaction* DeserializeFrom(IBinaryReader& reader)
      {
         std::cout << "Transaction::DeserializeFrom" << std::endl;
          // Looking for type in reflection cache
          Transaction* transaction = new Transaction((TransactionType)reader.ReadByte());//ReflectionCache.CreateInstance<Transaction>(reader.ReadByte());
          //if (transaction == null) throw new FormatException();

          std::cout << "Transaction:: will deserialize unsigned" << std::endl;
          transaction->DeserializeUnsignedWithoutType(reader);
          std::cout << "Transaction:: will read witness" << std::endl;
          transaction->Witnesses = reader.ReadSerializableArray<Witness>();
          std::cout << "Transaction:: on deserialized" << std::endl;
          transaction->OnDeserialized();
          return transaction;
      }


   };
}

#endif
