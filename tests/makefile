FILENAME :=  $(patsubst %.Test.cpp,%.core.test,$(wildcard core.tests/*.Test.cpp))

OPENSSL_PATH=../src/core/crypto/openssl
CORE_PATH=../src/core
GTEST_PATH=gtestlib/googletest
GMOCK_PATH=gtestlib/googlemock

all:
	@echo "please type 'make tests'"

#all: $(FILENAME)
#	@echo "Executing core test for: $(FILENAME)"

# todo: not too great structure... cleaning every time to ensure tests are updated.
tests: clean $(FILENAME)
	@echo "Executed core test for: $(FILENAME)"

# compiling core tests
%.core.test : %.Test.cpp
	g++ --coverage -O0 -I../src/core --std=c++11 -I$(OPENSSL_PATH)/include $(OPENSSL_PATH)/../CryptoNeoOpenSSL.cpp $(CORE_PATH)/payloads/TransactionFactory.cpp -I$(GTEST_PATH)/include -L$(GMOCK_PATH)/gtest -L$(GMOCK_PATH) -lgtest -lgtest_main  -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl $< -o $@
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:$(GMOCK_PATH):$(GMOCK_PATH)/gtest && ./$@

coverage:
	mkdir -p reports
	lcov --directory . --capture --output-file reports/app.info
	(cd reports && genhtml app.info)

# cleaning tests
clean:
	rm -f *.test
	rm -f core.tests/*.test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
