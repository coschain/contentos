eosiocpp -o eosio.token.wast eosio.token.cpp
eosiocpp -g eosio.token.abi  eosio.token.cpp

echo "const char* const eosio_token_wast = R\"=====(" >eosio.token.wast.hpp
cat eosio.token.wast >>eosio.token.wast.hpp
echo "" >>eosio.token.wast.hpp
echo ")=====\";" >>eosio.token.wast.hpp

echo "const char* const eosio_token_abi = R\"=====(" >eosio.token.abi.hpp
cat eosio.token.abi >>eosio.token.abi.hpp
echo "" >>eosio.token.abi.hpp
echo ")=====\";" >>eosio.token.abi.hpp

