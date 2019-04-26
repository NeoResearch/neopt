#ifndef TRANSACTION_FACTORY_HPP
#define TRANSACTION_FACTORY_HPP

// c++ standard part
#include<vector>

// neopt core part
#include<system/types.h>
//#include<payloads/Transaction.hpp> // forward declaration
#include<payloads/TransactionType.h>
//#include<payloads/MinerTransaction.hpp>

namespace neopt
{
    // forward declaration
    class Transaction;

    // requires a singleton to provide static methods
    class TransactionFactory 
    {
    private:
        // singleton
        static TransactionFactory* _factory;

    private:
        TransactionFactory() 
        {
        }

    public:
        static const TransactionFactory& Default()
        {
            if(!_factory)
                _factory = new TransactionFactory();
            return *_factory;
        }

        // use singleton on static public method
        static Transaction* CreateInstance(TransactionType type)
        {
            Default().CreateInstance(type);
        }

    private:
        // must be implemented externally
        Transaction* FactoryCreateInstance(TransactionType type);
    };

} // namespace neopt

// forward declarations 
#include<payloads/Transaction.hpp>

#endif

