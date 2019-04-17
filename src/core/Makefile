all: #simple testing
	g++    -Ofast --std=c++11 -I. -Ilibneocrypto/openssl/include libneocrypto/CryptoNeoOpenSSL.cpp -Llibneocrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl main.cpp -o neopt-core-test

# no need to build external lib for now
withlib: libneocrypto_openssl.a
	g++    -Ofast --std=c++11 -I. -Ilibneocrypto/openssl/include  main.cpp -o neopt-core-test libneocrypto_openssl.a -llinux-openssl-crypto-x86_64 -ldl -lpthread -Llibneocrypto/openssl
libneocrypto_openssl.a:
	g++ -c -Ofast --std=c++11 -I. -Ilibneocrypto/openssl/include libneocrypto/CryptoNeoOpenSSL.cpp -Llibneocrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl -static -o libneocrypto_openssl.o
	ar rvs libneocrypto_openssl.a libneocrypto_openssl.o
