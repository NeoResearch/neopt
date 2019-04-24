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
         DeserializeExclusiveData(reader);
         Attributes = reader.ReadSerializableArray<TransactionAttribute>(MaxTransactionAttributes);
         Inputs = reader.ReadSerializableArray<CoinReference>();
         Outputs = reader.ReadSerializableArray<TransactionOutput>(types::MaxValue<ushort>() + 1);
      }

protected:
      virtual void OnDeserialized()
      {
      }

   };
}

#endif
