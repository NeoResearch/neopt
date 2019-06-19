OPTIONS=-O0 -g # -Ofast

OPENSSL_PATH=../../build/openssl/

all: lint neopt-core-test #simple testing


neopt-core-test:
	g++   $(OPTIONS) --std=c++11 -I. -I$(OPENSSL_PATH)/include crypto/CryptoNeoOpenSSL.cpp -L$(OPENSSL_PATH) -llinux-openssl-crypto-x86_64 -lpthread -ldl main.cpp system/printable.cpp system/ISerializable.cpp -o neopt-core-test

# no need to build external lib for now
withlib: libneocrypto_openssl.a
	g++   $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include  main.cpp -o neopt-core-test libneocrypto_openssl.a -llinux-openssl-crypto-x86_64 -ldl -lpthread -L$(OPENSSL_PATH)
libneocrypto_openssl.a:
	g++ -c $(OPTIONS) --std=c++11 -I. -Icrypto/openssl/include crypto/CryptoNeoOpenSSL.cpp -Lcrypto/openssl -llinux-openssl-crypto-x86_64 -lpthread -ldl -static -o libneocrypto_openssl.o
	ar rvs libneocrypto_openssl.a libneocrypto_openssl.o

lint:
	clang-tidy main.cpp -checks=*,-fuchsia-default-arguments -- -std=c++11 -x c++ -I.
	clang-tidy *.hpp -checks=*,-fuchsia-default-arguments,-llvm-header-guard,-google-runtime-references -- -I. -std=c++11 -x c++
	#clang-tidy *.h -checks=*,-fuchsia-default-arguments,-llvm-header-guard,-google-runtime-references -- -I. -std=c++11 -x c++
	clang-tidy *.cpp -checks=*,-fuchsia-default-arguments,-llvm-header-guard,-google-runtime-references -- -I. -std=c++11 -x c++

fmt:
	clang-format -i *.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd adt && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd crypto && clang-format -i *.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd crypto && clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd crypto && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd payloads && clang-format -i *.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd payloads && clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd payloads && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd wallets && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd system && clang-format -i *.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd system && clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd system && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd plugin && clang-format -i *.cpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd plugin && clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd plugin && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd numbers && clang-format -i *.h -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd numbers && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
	cd json && clang-format -i *.hpp -style='{ BasedOnStyle : Mozilla , ColumnLimit : 0, IndentWidth: 3, AccessModifierOffset: -3}'
