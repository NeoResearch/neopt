OPTIONS=-O0 -g # -Ofast

OPENSSL_PATH=../core/crypto/openssl
CORE_PATH=../core
PLUGINS_PATH=../plugins

all: #simple testing
	g++   $(OPTIONS) --std=c++11 -I. -I.. -I../core -I$(PLUGINS_PATH)/ImportBlocks -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl  Program.cpp  $(PLUGINS_PATH)/ImportBlocks/ImportBlocks.cpp $(PLUGINS_PATH)/ImportBlocks/ImportBlocksSettings.cpp $(CORE_PATH)/NeoSystem.cpp $(CORE_PATH)/plugin/PluginSystem.cpp  -o neopt-cli
