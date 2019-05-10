OPTIONS=-g --std=c++11 -O0 # -Ofast

OPENSSL_PATH=src/core/crypto/openssl
CORE_PATH=src/core
LEDGER_PATH=src/ledger
SRC_PATH=src
PLUGINS_PATH=src/plugins

all: test cli
	@echo
	@echo "sucessfully built neopt-cli on build/ directory"

cli: # building neopt-cli
	g++   $(OPTIONS)  -Isrc/cli -I$(SRC_PATH) -Isrc/core -I$(PLUGINS_PATH)/ImportBlocks -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl  src/cli/Program.cpp  $(PLUGINS_PATH)/ImportBlocks/ImportBlocks.cpp $(PLUGINS_PATH)/ImportBlocks/ImportBlocksSettings.cpp $(LEDGER_PATH)/NeoSystem.cpp $(LEDGER_PATH)/plugin/PluginSystem.cpp  $(CORE_PATH)/system/printable.cpp $(LEDGER_PATH)/payloads/TransactionFactory.cpp -o bin/neopt-cli

test:
	cd tests && $(MAKE) test

test-coverage:
	cd tests && $(MAKE) test-coverage

run:
	./bin/neopt-cli

vendor: openssl cryptopp clang gtests

openssl:
	cd src/core && chmod +x linux_get_build_openssl.sh
	cd src/core && ./linux_get_build_openssl.sh

cryptopp:
	cd src/core && chmod +x linux_get_build_cryptopp.sh
	cd src/core && ./linux_get_build_cryptopp.sh

clang:
	sudo apt install clang clang-format clang-tidy

gtests:
	cd tests && ./linux_install_gtestlib.sh
	sudo apt install lcov
