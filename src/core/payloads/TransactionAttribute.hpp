#ifndef TRANSACTION_ATTRIBUTE_HPP
#define TRANSACTION_ATTRIBUTE_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/types.h>
#include<system/ISerializable.h>
#include<system/IBinaryWriter.h>
#include<system/IBinaryReader.h>
#include<payloads/TransactionAttributeUsage.hpp>


namespace neopt
{

// WARNING: escaping from the "Diamond of Death"
// making ISerializable a virtual inheritance
class TransactionAttribute //: public ISerializable
{
public:

   TransactionAttributeUsage Usage;
   vbyte Data;


   virtual void Serialize(IBinaryWriter& writer) const
   {
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
