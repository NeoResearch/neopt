#FILENAME :=  $(patsubst %.Test.cpp,%.core.test,$(wildcard core.tests/*.Test.cpp))

OPENSSL_PATH=../src/core/crypto/openssl
CORE_PATH=../src/core
LEDGER_PATH=../src/ledger
SRC_PATH=../src
GTEST_PATH=gtestlib/googletest
GMOCK_PATH=gtestlib/googlemock

all:
	@echo "please type 'make test'"

#all: $(FILENAME)
#	@echo "Executing core test for: $(FILENAME)"

# todo: not too great structure... cleaning every time to ensure tests are updated.
#test: clean core.test ledger.test #$(FILENAME)
#	@echo "Executed tests"
#	./core.test
#	./ledger.test
test: clean all.test #$(FILENAME)
	@echo "Executed tests"
	./all.test

all.test : all.Test.cpp
	#g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	g++ --coverage -g -O0 --std=c++11 -I$(CORE_PATH) -I$(SRC_PATH) -I$(GTEST_PATH)/include -I$(GMOCK_PATH)/include -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(LEDGER_PATH)/payloads/TransactionFactory.cpp $(CORE_PATH)/system/printable.cpp  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

core.test : core.Test.cpp
	#g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	g++ --coverage -g -O0 --std=c++11 -I$(CORE_PATH) -I$(GTEST_PATH)/include -I$(GMOCK_PATH)/include -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

ledger.test : ledger.Test.cpp
	#g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	g++ --coverage -g -O0 --std=c++11 -I$(CORE_PATH) -I$(SRC_PATH) -I$(GTEST_PATH)/include -I$(GMOCK_PATH)/include -I$(OPENSSL_PATH)/include -pthread $< -o $@ $(GMOCK_PATH)/gtest/libgtest_main.a $(GMOCK_PATH)/gtest/libgtest.a $(GMOCK_PATH)/libgmock.a $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(LEDGER_PATH)/payloads/TransactionFactory.cpp $(CORE_PATH)/system/printable.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl

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
