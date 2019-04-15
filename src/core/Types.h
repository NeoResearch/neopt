#ifndef TYPES_H
#define TYPES_H

// system includes
#include<vector>

// core includes
// ... none

namespace neopt
{
// basic types for Neo core

// the simplest chunk of information
typedef unsigned char byte;

// byte array definition
typedef std::vector<byte> vbyte;

#define NEOPT_EXCEPTION(str) { printf("neopt error: %s\n", str); exit(1); }

}

#endif
