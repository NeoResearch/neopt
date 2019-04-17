// Welcome to neopt project
// this main.cpp file should be deleted as soon as basic testing is fully configured on project
// for the final version, the "main" will in fact become some CLI tool (just like neo-cli),
//    that executes commands compatible to neo-cli standard
// now, this main is just for simple testing

// system includes
#include<iostream>
#include<vector>

// neopt core includes
#include<system/IEquatable.h>
#include<numbers/UIntBase.hpp>
#include<numbers/UInt160.hpp>
#include<IScriptContainer.h>
#include<IVerifiable.h>
#include<IInventory.h>
#include<Transaction.hpp>
#include<crypto/ICrypto.h>
#include<crypto/CryptoNeoOpenSSL.h>

using namespace std;
using namespace neopt;

int main()
{
   IEquatable<int>* ieq = nullptr;
   UIntBase* uint = nullptr;
   UInt160 uint160;
   IScriptContainer* iscript = nullptr;
   IVerifiable* iverifiable = nullptr;
   IInventory* iinventory = nullptr;
   Transaction* tx = nullptr;

   CryptoNeoOpenSSL lib;
   vbyte v;
   v = lib.Hash160(v);
   cout << "v:" << v << endl;
   // 0xb472a266d0bd89c13706a4132ccfb16f7c3b9fcb

   v = lib.Hash160(vbyte(1, 0));
   cout << "v:" << v << endl;
   // 0x9f7fd096d37ed2c0e3f7f0cfc924beef4ffceb68

   cout << lib.Hash256(vbyte()) << endl;
   // 0x5df6e0e2761359d30a8275058e299fcc0381534545f55cf43e41983f5d4c9456

   cout << lib.SHA256(vbyte()) << endl;
   // 0xe3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855


   cout << "Finished sucessfully" << endl;

   return 0;
}
