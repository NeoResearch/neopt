#ifndef NEOPT_NVM_EXECUTIONENGINELIMITS_HPP
#define NEOPT_NVM_EXECUTIONENGINELIMITS_HPP

// c++ standard part
#include <vector>

// neopt core part
#include <crypto/Crypto.h>
#include <numbers/BigInteger.h>
#include <numbers/UInt256.hpp>
#include <system/IEquatable.h>
#include <system/printable.h>
#include <system/vhelper.hpp>

namespace neopt {
namespace nvm {

class ExecutionEngineLimits
{
public:
   // TODO:
   static int MaxSizeForBigInteger()
   {
      return 0;
   }
};

} // namespace nvm
} // namespace neopt

#endif // NEOPT_NVM_ExecutionEngineLimits_HPP