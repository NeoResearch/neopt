#!/bin/bash

OPENSSL_VER=openssl-1.1.1b

echo "# Building $OPENSSL_VER (for Linux)"
# ===============
# getting openssl
# ===============
wget -nc https://www.openssl.org/source/$OPENSSL_VER.tar.gz
rm -rf openssl_src
tar -zxf $OPENSSL_VER.tar.gz
rm -rf openssl_src
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

mkdir libneocrypto/openssl
mv openssl_src/include libneocrypto/openssl/   # include files
mv tmp_build/include/openssl/* libneocrypto/openssl/include/openssl/
mv tmp_build/libcrypto.a libneocrypto/openssl/liblinux-openssl-crypto-x86_64.a
rm -rf openssl_src
rm -rf tmp_build
