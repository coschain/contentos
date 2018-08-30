CONTENTOS_BUILD_TYPE=Debug
CONTENTOS_TESTNET=ON
CONTENTOS_XCODE="-G Xcode"

if [[ $@ == *'makefile'* ]]
then
    CONTENTOS_XCODE=""
fi
if [[ $@ == *'release'* ]]
then
    CONTENTOS_BUILD_TYPE=Release
fi
if [[ $@ == *'mainnet'* ]]
then
    CONTENTOS_TESTNET=OFF
fi

cmake $CONTENTOS_XCODE -DBOOST_ROOT="/usr/local/Cellar/boost/1.67.0_1" -DCMAKE_BUILD_TYPE=$CONTENTOS_BUILD_TYPE -DBUILD_CONTENTOS_TESTNET=$CONTENTOS_TESTNET ..
