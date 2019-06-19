#FILENAME :=  $(patsubst %.Test.cpp,%.core.test,$(wildcard core.tests/*.Test.cpp))

# openssl
OPENSSL_PATH=../build/openssl
# common
COMMON_PATH=../src/common
# neo2
NEO2_PATH=../src/neo2
# gtest
GTEST_PATH=../libgtest/build/googletest
GMOCK_PATH=../libgtest/build/googlemock
GTEST_INCLUDE=../libgtest/googletest/include
GMOCK_INCLUDE=../libgtest/googlemock/include

all:
	@echo "please type 'make test'"

#all: $(FILENAME)
#	@echo "Executing core test for: $(FILENAME)"

# todo: not too great structure... cleaning every time to ensure tests are updated.
#test: clean core.test ledger.test #$(FILENAME)
#	@echo "Executed tests"
#	./core.test
#	./ledger.test
test: clean neo2.test #$(FILENAME)
	@echo "Executed tests"
	./neo2.test

neo2.test : neo2.Test.cpp
	g++ --coverage -g -O0 --std=c++11 -I$(COMMON_PATH) -I$(NEO2_PATH) -I$(GTEST_INCLUDE) -I$(GMOCK_INCLUDE) -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(COMMON_PATH)/crypto/CryptoNeoOpenSSL.cpp $(NEO2_PATH)/ledger/payloads/TransactionFactory.cpp $(COMMON_PATH)/system/printable.cpp $(COMMON_PATH)/system/ISerializable.cpp $(COMMON_PATH)/crypto/CryptoExtra.cpp $(COMMON_PATH)/crypto/cryptopp/libcryptopp.a  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

core.test : core.Test.cpp
	#g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	g++ --coverage -g -O0 --std=c++11 -I$(CORE_PATH) -I$(GTEST_PATH)/include -I$(GMOCK_PATH)/include -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

ledger.test : ledger.Test.cpp
	#g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	g++ --coverage -g -O0 --std=c++11 -I$(CORE_PATH) -I$(SRC_PATH) -I$(GTEST_PATH)/include -I$(GMOCK_PATH)/include -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(LEDGER_PATH)/payloads/TransactionFactory.cpp $(CORE_PATH)/system/printable.cpp $(CORE_PATH)/system/ISerializable.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

# compiling core tests
#%.core.test : %.Test.cpp
#	g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
#	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(GMOCK_PATH):$(GMOCK_PATH)/gtest && ./$@

test-coverage:
	mkdir -p reports
	lcov --directory . --capture --output-file reports/app.info
	(cd reports && genhtml app.info)

# cleaning tests
clean:
	rm -f *.test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
