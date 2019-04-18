FILENAME :=  $(patsubst %.Test.cpp,%.core.test,$(wildcard core.tests/*.Test.cpp))

all:
	@echo "please type 'make tests'"

tests: $(FILENAME)
	@echo "Executing core test for: $(FILENAME)"
	export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:gtestlib/googlemock:gtestlib/googlemock/gtest && ./$(FILENAME)

# compiling core tests
%.core.test : %.Test.cpp
	g++ --coverage -O0 -I../src/core --std=c++11 -Igtestlib/googletest/include -Lgtestlib/googlemock/gtest -Lgtestlib/googlemock -lgtest -lgtest_main $< -o $@

coverage:
	mkdir -p reports
	lcov --directory . --capture --output-file reports/app.info
	(cd reports && genhtml app.info)

# cleaning tests
clean:
	rm -f *.test
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.info
