#ifndef TYPES_H
#define TYPES_H

// system includes
#include<vector>

// core includes
#include<vhelper.h> // TODO: verify if it's nice here or not

namespace neopt
{
// basic types for Neo core

// the simplest chunk of information
typedef unsigned char byte;

// byte array definition
typedef vector<byte> vbyte;

#define NEOPT_EXCEPTION(str) { printf("neopt error: %s\n", str); exit(1); }

}

#endif
