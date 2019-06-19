#ifndef TRANSACTION_ATTRIBUTE_HPP
#define TRANSACTION_ATTRIBUTE_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <ledger/payloads/TransactionAttributeUsage.hpp>
#include <system/IBinaryReader.h>
#include <system/IBinaryWriter.h>
#include <system/ISerializable.h>
#include <system/types.h>

namespace neopt {

class TransactionAttribute : public ISerializable
{
public:
   TransactionAttributeUsage Usage;
   vbyte Data;

   virtual void Serialize(IBinaryWriter& writer) const
   {
      writer.Write((byte)Usage);
      if (Usage == TransactionAttributeUsage::TAU_DescriptionUrl)
         writer.Write((byte)Data.size());
      else if (Usage == TransactionAttributeUsage::TAU_Description || Usage >= TransactionAttributeUsage::TAU_Remark)
         writer.WriteVarInt(Data.size());
      if (Usage == TransactionAttributeUsage::TAU_ECDH02 || Usage == TransactionAttributeUsage::TAU_ECDH03)
         writer.Write(Data, 1, 32);
      else
         writer.Write(Data);
   }

   virtual void Deserialize(IBinaryReader& reader)
   {
      Usage = (TransactionAttributeUsage)reader.ReadByte();
      if (Usage == TransactionAttributeUsage::TAU_ContractHash || Usage == TransactionAttributeUsage::TAU_Vote || (Usage >= TransactionAttributeUsage::TAU_Hash1 && Usage <= TransactionAttributeUsage::TAU_Hash15))
         Data = reader.ReadBytes(32);
      else if (Usage == TransactionAttributeUsage::TAU_ECDH02 || Usage == TransactionAttributeUsage::TAU_ECDH03)
         Data = vhelper::Concat(vbyte(1, (byte)Usage), reader.ReadBytes(32));
      else if (Usage == TransactionAttributeUsage::TAU_Script)
         Data = reader.ReadBytes(20);
      else if (Usage == TransactionAttributeUsage::TAU_DescriptionUrl)
         Data = reader.ReadBytes(reader.ReadByte());
      else if (Usage == TransactionAttributeUsage::TAU_Description || Usage >= TransactionAttributeUsage::TAU_Remark)
         Data = reader.ReadVarBytes(types::MaxValue<ushort>());
      else
         NEOPT_EXCEPTION("TransactionAttribute Deserialize FormatException");
      //throw new FormatException();
   }
};

}

#endif
