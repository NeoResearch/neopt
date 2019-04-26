OPTIONS=-O0 -g # -Ofast

OPENSSL_PATH=src/core/crypto/openssl
CORE_PATH=src/core
PLUGINS_PATH=src/plugins

all: test cli
	@echo
	@echo "sucessfully built neopt-cli on build/ directory"

cli: # building neopt-cli
	g++   $(OPTIONS) --std=c++11 -Isrc/cli -Isrc -Isrc/core -I$(PLUGINS_PATH)/ImportBlocks -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl  src/cli/Program.cpp  $(PLUGINS_PATH)/ImportBlocks/ImportBlocks.cpp $(PLUGINS_PATH)/ImportBlocks/ImportBlocksSettings.cpp $(CORE_PATH)/NeoSystem.cpp $(CORE_PATH)/plugin/PluginSystem.cpp  $(CORE_PATH)/system/printable.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -o build/neopt-cli

test:
	cd tests && $(MAKE) tests

openssl:
	cd src/core && ./linux_get_build_openssl.sh

run:
	./build/neopt-cli
