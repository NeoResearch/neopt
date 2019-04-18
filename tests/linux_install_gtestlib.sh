#!/bin/bash

wget https://github.com/google/googletest/archive/release-1.8.0.tar.gz
mkdir gtestlib
tar xf release-1.8.0.tar.gz -C gtestlib --strip-components=1
cd gtestlib
cmake -DBUILD_SHARED_LIBS=ON .
make
