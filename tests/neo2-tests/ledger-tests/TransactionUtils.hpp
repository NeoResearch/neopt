#ifndef TESTS_TRANSACTION_UTILS_HPP
#define TESTS_TRANSACTION_UTILS_HPP

#include <gtest/gtest.h>

#include <gmock/gmock.h> // will need mocking here for Tx


// core includes
#include <ledger/payloads/Transaction.hpp>

#include <system/shelper.h>
#include <system/vhelper.hpp>

using namespace std;
using namespace neopt;

using ::testing::Return; // testing

// must move this to Utils in the future
class MockInvokeHashTx : public Transaction
{
public:
   MockInvokeHashTx()
     : Transaction(TT_InvocationTransaction)
   {
   }

   MOCK_METHOD0(getHash, UInt256());

   MOCK_METHOD1(DeserializeExclusiveData, void(IBinaryReader&));
};

   //EXPECT_CALL(mockTx1, getHash())
   //  .WillOnce(Return(UInt256(htx1)));
     //.WillOnce(Return(UInt256(htx1)));


 
#endif 