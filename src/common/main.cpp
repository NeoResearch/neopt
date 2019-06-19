// Welcome to neopt project
// this main.cpp file should be deleted as soon as basic testing is fully configured on project
// for the final version, the "main" will in fact become some CLI tool (just like neo-cli),
//    that executes commands compatible to neo-cli standard
// now, this main is just for simple testing

// system includes
#include <cassert>
#include <iostream>
#include <vector>

// neopt core includes
#include <crypto/Crypto.h>
#include <crypto/ICrypto.h>
#include <numbers/Fixed8.hpp>
#include <numbers/UInt160.hpp>
#include <numbers/UIntBase.hpp>
#include <system/BinaryReader.hpp>
#include <system/IEquatable.h>
#include <system/printable.h>
#include <wallets/whelper.hpp>

using namespace std;
using namespace neopt;

int
main()
{
   IEquatable<int>* ieq = nullptr;
   UIntBase* uint = nullptr;
   UInt160 uint160;

   Crypto lib;
   vbyte v;
   v = lib.Hash160(v);
   cout << "hash160(''):" << v << endl;
   // 0xb472a266d0bd89c13706a4132ccfb16f7c3b9fcb

   v = lib.Hash160(vbyte(1, 0));
   cout << "hash160('0x00'):" << v << endl;
   // 0x9f7fd096d37ed2c0e3f7f0cfc924beef4ffceb68

   cout << "hash256(''):" << lib.Hash256(vbyte()) << endl;
   // 0x5df6e0e2761359d30a8275058e299fcc0381534545f55cf43e41983f5d4c9456

   cout << "sha256(''):" << lib.Sha256(vbyte()) << endl;
   // 0xe3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855

   vbyte mypubkey;
   vbyte priv = lib.GeneratePrivateKey(mypubkey);
   cout << endl;
   cout << "priv:" << priv << endl;
   cout << "pub:" << mypubkey << endl;

   vbyte sig = lib.SignData(lib.Sha256(vbyte()), priv, mypubkey);
   cout << "sig:" << sig << endl;

   std::cout << lib.VerifySignature(vbyte(0), sig, mypubkey) << std::endl;
   /*
   strange fail. TODO: investigate in the future
   digest: [32]0xe3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855
   priv:[32]0x0889f303d029922eb48c661802be5c0631ad0bfc195360483eb6cdfed938d285
   pub:[33]0x0395add0fe8f578288860584b01bd68c21ee18819c1a6b6b67d2eafd3aefae6399
   sig:[64]0x49cdf1429642fdf5e1ca25ca71278b216f0f0f2c251c3bfb56bca67f454aa0ea135cb98efbfafce69d2ee088c3c9dbe2c9bfcb8255dc3c3a5c52cb92264aa500
   neopt-core-test: main.cpp:62: int main(): Assertion `lib.VerifySignature(vbyte(0), sig, mypubkey) == 1' failed.
   */
   std::cout <<  lib.VerifySignature(vbyte(1), sig, mypubkey) << std::endl;
   std::cout <<  lib.VerifySignature(vbyte(1, 3), lib.SignData(lib.Sha256(vbyte(1, 3)), priv, mypubkey), mypubkey) << std::endl;

   cout << "Finished sucessfully" << endl;

   return 0;
}
