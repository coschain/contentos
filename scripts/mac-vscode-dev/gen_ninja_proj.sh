#!/bin/sh

basepath=$(cd `dirname $0`; pwd)
bninja=$basepath/../../../bninja


mkdir $bninja
cd $bninja

export OPENSSL_ROOT_DIR=/usr/local/opt/openssl/
cmake -G Ninja -DBOOST_ROOT="/usr/local/Cellar/boost/1.67.0_1" -DCMAKE_BUILD_TYPE=Debug -DENABLE_MAC_SHARED_LIB=1 -DBUILD_CONTENTOS_TESTNET=ON -DCMAKE_CXX_COMPILER="$HOME/quickcc/quickcc.sh" -DCMAKE_C_COMPILER="$HOME/quickcc/quickc.sh"  ../contentos/
cd ../contentos/