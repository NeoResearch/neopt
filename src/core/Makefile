OPTIONS=-O0 -g # -Ofast

all: #simple testing
	g++   $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include crypto/CryptoNeoOpenSSL.cpp -Lcrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl main.cpp -o neopt-core-test

# no need to build external lib for now
withlib: libneocrypto_openssl.a
	g++   $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include  main.cpp -o neopt-core-test libneocrypto_openssl.a -llinux-openssl-crypto-x86_64 -ldl -lpthread -Lcrypto/openssl
libneocrypto_openssl.a:
	g++ -c $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include crypto/CryptoNeoOpenSSL.cpp -Lcrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl -static -o libneocrypto_openssl.o
	ar rvs libneocrypto_openssl.a libneocrypto_openssl.o
