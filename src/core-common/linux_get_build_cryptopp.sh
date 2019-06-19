#!/bin/bash

set -euxo pipefail # safer script: will fail

wget -nc https://github.com/weidai11/cryptopp/archive/CRYPTOPP_8_2_0.zip
unzip CRYPTOPP_8_2_0.zip
rm -rf crypto/cryptopp
mv cryptopp-CRYPTOPP_8_2_0 crypto/cryptopp
(cd crypto/cryptopp && make)
