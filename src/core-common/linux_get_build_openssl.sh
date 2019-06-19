#!/bin/bash

set -euxo pipefail # safer script: will fail

OPENSSL_VER=openssl-1.1.1b

echo "# Building $OPENSSL_VER (for Linux)"
# ===============
# getting openssl
# ===============
wget -nc https://www.openssl.org/source/$OPENSSL_VER.tar.gz
rm -rf openssl_src
tar -zxf $OPENSSL_VER.tar.gz
rm -rf openssl_src
rm -rf crypto/openssl
mv $OPENSSL_VER openssl_src
# ================
# building openssl
# ================
mkdir tmp_build
cd tmp_build
../openssl_src/config
make && make test
cd ..
echo "# Finished building $OPENSSL_VER (for Linux)"

mkdir crypto/openssl
mv openssl_src/include crypto/openssl/   # include files
mv tmp_build/include/openssl/* crypto/openssl/include/openssl/
mv tmp_build/libcrypto.a crypto/openssl/liblinux-openssl-crypto-x86_64.a
rm -rf openssl_src
rm -rf tmp_build
