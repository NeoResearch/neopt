#ifndef CONTRACT_TRANSACTION_HPP
#define CONTRACT_TRANSACTION_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <ledger/payloads/Transaction.hpp>
#include <ledger/payloads/TransactionType.h>

namespace neopt {

class ContractTransaction : public Transaction
{
public:
   ContractTransaction()
     : Transaction(TT_ContractTransaction)
   {
   }

protected:
   virtual void DeserializeExclusiveData(IBinaryReader& reader)
   {
      std::cout << "ContractTX::DeserializeExclusiveData" << std::endl;
      if (Transaction::Version != 0)
         NEOPT_EXCEPTION("ContractTx FormatException");
   }

   void OnDeserialized()
   {
      Transaction::OnDeserialized();
   }

protected:
   virtual void SerializeExclusiveData(IBinaryWriter& writer) const
   {
   }
};
}

#endif
