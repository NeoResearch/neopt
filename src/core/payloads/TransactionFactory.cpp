#include <payloads/TransactionFactory.h>

// forward definitions

#include <payloads/ContractTransaction.hpp>
#include <payloads/MinerTransaction.hpp>
#include <payloads/Transaction.hpp>
#include <payloads/TransactionType.h>

using namespace std;
using namespace neopt;

Transaction*
TransactionFactory::Create(TransactionType type) const
{
   cout << "TX FACTORY WILL GENERATE FOR TYPE: " << type << endl;
   switch (type) {
      case TransactionType::TT_MinerTransaction:
         return new MinerTransaction();
      case TransactionType::TT_ContractTransaction:
         return new ContractTransaction();
      case TransactionType::TT_IssueTransaction:
      case TransactionType::TT_ClaimTransaction:
      case TransactionType::TT_EnrollmentTransaction:
      case TransactionType::TT_RegisterTransaction:
      case TransactionType::TT_StateTransaction:
      case TransactionType::TT_PublishTransaction:
      case TransactionType::TT_InvocationTransaction: {
         std::cout << "Transaction type is " << type << std::endl;
         NEOPT_EXCEPTION("NOT IMPLEMENTED TX TYPE CreateInstance Factory yet!");
         return nullptr;
         break;
      }
      default:
         return nullptr;
   }
   return nullptr;
}
