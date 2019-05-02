OPTIONS=-O0 -g # -Ofast

OPENSSL_PATH=crypto/openssl

all: lint neopt-core-test #simple testing


neopt-core-test:
	g++   $(OPTIONS) --std=c++11 -I. -I$(OPENSSL_PATH)/include crypto/CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl main.cpp system/printable.cpp payloads/TransactionFactory.cpp plugin/PluginSystem.cpp -o neopt-core-test

# no need to build external lib for now
withlib: libneocrypto_openssl.a
	g++   $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include  main.cpp -o neopt-core-test libneocrypto_openssl.a -llinux-openssl-crypto-x86_64 -ldl -lpthread -L$(OPENSSL_PATH)
libneocrypto_openssl.a:
	g++ -c $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include crypto/CryptoNeoOpenSSL.cpp -Lcrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl -static -o libneocrypto_openssl.o
	ar rvs libneocrypto_openssl.a libneocrypto_openssl.o

lint:
	clang-format -i main.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	clang-tidy main.cpp -checks=*,-fuchsia-default-arguments -- -std=c++11 -I.
	clang-tidy *.hpp -checks=*,-fuchsia-default-arguments,-llvm-header-guard,-google-runtime-references -- -I. -std=c++11
