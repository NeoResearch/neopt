#ifndef TRANSACTION_FACTORY_HPP
#define TRANSACTION_FACTORY_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <system/types.h>
//#include<payloads/Transaction.hpp> // forward declaration
#include <ledger/payloads/TransactionType.h>
//#include<payloads/MinerTransaction.hpp>

namespace neopt {
// forward declaration
class Transaction;

// requires a singleton to provide static methods
class TransactionFactory
{
private:
   friend struct MakeStatic<TransactionFactory>;

   // this ensures no one will create instances for this (except me and my friends...)
   TransactionFactory()
   {
   }

public:
   // factory: use static public method
   static Transaction* CreateInstance(TransactionType type)
   {
      return MakeStatic<TransactionFactory>().object().Create(type);
   }

   // another option to invoke method
   // must be implemented externally (to resolve forward-dec. dependencies)
   Transaction* Create(TransactionType type) const;
};

} // namespace neopt

// forward declarations
#include <ledger/payloads/Transaction.hpp>

#endif
