OPTIONS=-g --std=c++11 -O0 # -Ofast

# openssl
OPENSSL_PATH=build/openssl
# common
COMMON_PATH=src/common
# src
SRC_PATH=src
# neo2
CLI_PATH=src/cli2
NEO2_PATH=src/neo2

all: test neopt-common cli2
	@echo
	@echo "sucessfully built neopt-cli2 on bin/ directory"

cli2: # building neopt-cli
	g++   $(OPTIONS)  -I$(CLI_PATH) -I$(SRC_PATH) -I$(NEO2_PATH) -I$(COMMON_PATH) -I$(NEO2_PATH)/plugins/ImportBlocks -I$(OPENSSL_PATH)/include $(COMMON_PATH)/crypto/CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $(CLI_PATH)/Program.cpp  $(NEO2_PATH)/plugins/ImportBlocks/ImportBlocks.cpp $(NEO2_PATH)/plugins/ImportBlocks/ImportBlocksSettings.cpp $(NEO2_PATH)/ledger/NeoSystem.cpp $(NEO2_PATH)/ledger/plugin/PluginSystem.cpp  $(COMMON_PATH)/system/printable.cpp $(COMMON_PATH)/system/ISerializable.cpp $(NEO2_PATH)/ledger/payloads/TransactionFactory.cpp -o bin/neopt-cli2

neopt-common:
	(cd src/common && make)

test:
	cd tests && $(MAKE) test

test-coverage:
	cd tests && $(MAKE) test-coverage

run:
	./bin/neopt-cli2

vendor: openssl cryptopp clang gtests

openssl:
	#cd src/core && chmod +x linux_get_build_openssl.sh
	#cd src/core && ./linux_get_build_openssl.sh
	mkdir -p build/openssl
	(cd build/openssl && ../../libopenssl/config && make && make test)
	cp -r libopenssl/include build/openssl/   # include files
	cp build/openssl/libcrypto.a build/openssl/liblinux-openssl-crypto-x86_64.a
	#cp -r build/openssl/include/openssl/* build/openssl/include/openssl/
	#mv tmp_build/libcrypto.a crypto/openssl/liblinux-openssl-crypto-x86_64.a


cryptopp:
	cd src/core && chmod +x linux_get_build_cryptopp.sh
	cd src/core && ./linux_get_build_cryptopp.sh

clang:
	sudo apt install clang clang-format clang-tidy

gtests:
	cd tests && ./linux_install_gtestlib.sh
	sudo apt install lcov
