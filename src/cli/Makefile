OPTIONS=-O0 -g # -Ofast

OPENSSL_PATH=../core/crypto/openssl

all: #simple testing
	g++   $(OPTIONS) --std=c++11 -I. -I.. -I../core -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl Program.cpp -o neopt-cli
