all: libcrypto_openssl.a #simple testing
	g++ -Ofast --std=c++11 -I. -Iopenssl/include -L. main.cpp -o neopt-core-test libcrypto_openssl.a -llinux-openssl-crypto-x86_64 -ldl -lpthread -Lopenssl
	#g++ -Ofast --std=c++11 -I. -Iopenssl/include libcrypto/libcrypto.cpp -Lopenssl -llinux-openssl-crypto-x86_64 -lpthread -ldl main.cpp -o neopt-core-test

libcrypto_openssl.a:
	g++ -c -Ofast --std=c++11 -I. -Iopenssl/include libcrypto/libcrypto.cpp -Lopenssl -llinux-openssl-crypto-x86_64 -lpthread -ldl -static -o libcrypto_openssl.o
	ar rvs libcrypto_openssl.a libcrypto_openssl.o
