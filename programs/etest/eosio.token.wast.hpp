const char* const eosio_token_wast = R"=====(
(module
 (type $FUNCSIG$viji (func (param i32 i64 i32)))
 (type $FUNCSIG$vij (func (param i32 i64)))
 (type $FUNCSIG$vijjii (func (param i32 i64 i64 i32 i32)))
 (type $FUNCSIG$vijii (func (param i32 i64 i32 i32)))
 (type $FUNCSIG$v (func))
 (type $FUNCSIG$j (func (result i64)))
 (type $FUNCSIG$vjj (func (param i64 i64)))
 (type $FUNCSIG$vj (func (param i64)))
 (type $FUNCSIG$ij (func (param i64) (result i32)))
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$ijjjj (func (param i64 i64 i64 i64) (result i32)))
 (type $FUNCSIG$ijjjjii (func (param i64 i64 i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$jjj (func (param i64 i64) (result i64)))
 (type $FUNCSIG$jj (func (param i64) (result i64)))
 (type $FUNCSIG$iiii (func (param i32 i32 i32) (result i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$vijji (func (param i32 i64 i64 i32)))
 (type $FUNCSIG$vijjjj (func (param i32 i64 i64 i64 i64)))
 (type $FUNCSIG$vijj (func (param i32 i64 i64)))
 (type $FUNCSIG$djj (func (param i64 i64) (result f64)))
 (type $FUNCSIG$di (func (param i32) (result f64)))
 (type $FUNCSIG$vif (func (param i32 f32)))
 (type $FUNCSIG$vid (func (param i32 f64)))
 (type $FUNCSIG$ijj (func (param i64 i64) (result i32)))
 (type $FUNCSIG$fjj (func (param i64 i64) (result f32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (type $FUNCSIG$viii (func (param i32 i32 i32)))
 (type $FUNCSIG$iiiiii (func (param i32 i32 i32 i32 i32) (result i32)))
 (type $FUNCSIG$viiiii (func (param i32 i32 i32 i32 i32)))
 (type $FUNCSIG$vf (func (param f32)))
 (type $FUNCSIG$vd (func (param f64)))
 (type $FUNCSIG$ijjjij (func (param i64 i64 i64 i32 i64) (result i32)))
 (type $FUNCSIG$ijjjii (func (param i64 i64 i64 i32 i32) (result i32)))
 (type $FUNCSIG$ijjjiij (func (param i64 i64 i64 i32 i32 i64) (result i32)))
 (type $FUNCSIG$ijjjiii (func (param i64 i64 i64 i32 i32 i32) (result i32)))
 (type $FUNCSIG$ijjj (func (param i64 i64 i64) (result i32)))
 (type $FUNCSIG$ijjjji (func (param i64 i64 i64 i64 i32) (result i32)))
 (type $FUNCSIG$i (func (result i32)))
 (import "env" "__addtf3" (func $__addtf3 (param i32 i64 i64 i64 i64)))
 (import "env" "__ashlti3" (func $__ashlti3 (param i32 i64 i64 i32)))
 (import "env" "__ashrti3" (func $__ashrti3 (param i32 i64 i64 i32)))
 (import "env" "__cmptf2" (func $__cmptf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__divtf3" (func $__divtf3 (param i32 i64 i64 i64 i64)))
 (import "env" "__divti3" (func $__divti3 (param i32 i64 i64 i64 i64)))
 (import "env" "__eqtf2" (func $__eqtf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__extenddftf2" (func $__extenddftf2 (param i32 f64)))
 (import "env" "__extendsftf2" (func $__extendsftf2 (param i32 f32)))
 (import "env" "__fixdfti" (func $__fixdfti (param i32 f64)))
 (import "env" "__fixsfti" (func $__fixsfti (param i32 f32)))
 (import "env" "__fixtfdi" (func $__fixtfdi (param i64 i64) (result i64)))
 (import "env" "__fixtfsi" (func $__fixtfsi (param i64 i64) (result i32)))
 (import "env" "__fixtfti" (func $__fixtfti (param i32 i64 i64)))
 (import "env" "__fixunsdfti" (func $__fixunsdfti (param i32 f64)))
 (import "env" "__fixunssfti" (func $__fixunssfti (param i32 f32)))
 (import "env" "__fixunstfdi" (func $__fixunstfdi (param i64 i64) (result i64)))
 (import "env" "__fixunstfsi" (func $__fixunstfsi (param i64 i64) (result i32)))
 (import "env" "__fixunstfti" (func $__fixunstfti (param i32 i64 i64)))
 (import "env" "__floatditf" (func $__floatditf (param i32 i64)))
 (import "env" "__floatsidf" (func $__floatsidf (param i32) (result f64)))
 (import "env" "__floatsitf" (func $__floatsitf (param i32 i32)))
 (import "env" "__floattidf" (func $__floattidf (param i64 i64) (result f64)))
 (import "env" "__floatunditf" (func $__floatunditf (param i32 i64)))
 (import "env" "__floatunsitf" (func $__floatunsitf (param i32 i32)))
 (import "env" "__floatuntidf" (func $__floatuntidf (param i64 i64) (result f64)))
 (import "env" "__getf2" (func $__getf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__gttf2" (func $__gttf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__letf2" (func $__letf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__lshlti3" (func $__lshlti3 (param i32 i64 i64 i32)))
 (import "env" "__lshrti3" (func $__lshrti3 (param i32 i64 i64 i32)))
 (import "env" "__lttf2" (func $__lttf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__modti3" (func $__modti3 (param i32 i64 i64 i64 i64)))
 (import "env" "__multf3" (func $__multf3 (param i32 i64 i64 i64 i64)))
 (import "env" "__multi3" (func $__multi3 (param i32 i64 i64 i64 i64)))
 (import "env" "__negtf2" (func $__negtf2 (param i32 i64 i64)))
 (import "env" "__netf2" (func $__netf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "__subtf3" (func $__subtf3 (param i32 i64 i64 i64 i64)))
 (import "env" "__trunctfdf2" (func $__trunctfdf2 (param i64 i64) (result f64)))
 (import "env" "__trunctfsf2" (func $__trunctfsf2 (param i64 i64) (result f32)))
 (import "env" "__udivti3" (func $__udivti3 (param i32 i64 i64 i64 i64)))
 (import "env" "__umodti3" (func $__umodti3 (param i32 i64 i64 i64 i64)))
 (import "env" "__unordtf2" (func $__unordtf2 (param i64 i64 i64 i64) (result i32)))
 (import "env" "abort" (func $abort))
 (import "env" "action_data_size" (func $action_data_size (result i32)))
 (import "env" "assert_recover_key" (func $assert_recover_key (param i32 i32 i32 i32 i32)))
 (import "env" "assert_ripemd160" (func $assert_ripemd160 (param i32 i32 i32)))
 (import "env" "assert_sha1" (func $assert_sha1 (param i32 i32 i32)))
 (import "env" "assert_sha256" (func $assert_sha256 (param i32 i32 i32)))
 (import "env" "assert_sha512" (func $assert_sha512 (param i32 i32 i32)))
 (import "env" "current_receiver" (func $current_receiver (result i64)))
 (import "env" "current_time" (func $current_time (result i64)))
 (import "env" "db_end_i64" (func $db_end_i64 (param i64 i64 i64) (result i32)))
 (import "env" "db_find_i64" (func $db_find_i64 (param i64 i64 i64 i64) (result i32)))
 (import "env" "db_get_i64" (func $db_get_i64 (param i32 i32 i32) (result i32)))
 (import "env" "db_idx128_end" (func $db_idx128_end (param i64 i64 i64) (result i32)))
 (import "env" "db_idx128_find_primary" (func $db_idx128_find_primary (param i64 i64 i64 i32 i64) (result i32)))
 (import "env" "db_idx128_find_secondary" (func $db_idx128_find_secondary (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx128_lowerbound" (func $db_idx128_lowerbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx128_next" (func $db_idx128_next (param i32 i32) (result i32)))
 (import "env" "db_idx128_previous" (func $db_idx128_previous (param i32 i32) (result i32)))
 (import "env" "db_idx128_remove" (func $db_idx128_remove (param i32)))
 (import "env" "db_idx128_store" (func $db_idx128_store (param i64 i64 i64 i64 i32) (result i32)))
 (import "env" "db_idx128_update" (func $db_idx128_update (param i32 i64 i32)))
 (import "env" "db_idx128_upperbound" (func $db_idx128_upperbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx256_end" (func $db_idx256_end (param i64 i64 i64) (result i32)))
 (import "env" "db_idx256_find_primary" (func $db_idx256_find_primary (param i64 i64 i64 i32 i32 i64) (result i32)))
 (import "env" "db_idx256_find_secondary" (func $db_idx256_find_secondary (param i64 i64 i64 i32 i32 i32) (result i32)))
 (import "env" "db_idx256_lowerbound" (func $db_idx256_lowerbound (param i64 i64 i64 i32 i32 i32) (result i32)))
 (import "env" "db_idx256_next" (func $db_idx256_next (param i32 i32) (result i32)))
 (import "env" "db_idx256_previous" (func $db_idx256_previous (param i32 i32) (result i32)))
 (import "env" "db_idx256_remove" (func $db_idx256_remove (param i32)))
 (import "env" "db_idx256_store" (func $db_idx256_store (param i64 i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx256_update" (func $db_idx256_update (param i32 i64 i32 i32)))
 (import "env" "db_idx256_upperbound" (func $db_idx256_upperbound (param i64 i64 i64 i32 i32 i32) (result i32)))
 (import "env" "db_idx64_end" (func $db_idx64_end (param i64 i64 i64) (result i32)))
 (import "env" "db_idx64_find_primary" (func $db_idx64_find_primary (param i64 i64 i64 i32 i64) (result i32)))
 (import "env" "db_idx64_find_secondary" (func $db_idx64_find_secondary (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx64_lowerbound" (func $db_idx64_lowerbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx64_next" (func $db_idx64_next (param i32 i32) (result i32)))
 (import "env" "db_idx64_previous" (func $db_idx64_previous (param i32 i32) (result i32)))
 (import "env" "db_idx64_remove" (func $db_idx64_remove (param i32)))
 (import "env" "db_idx64_store" (func $db_idx64_store (param i64 i64 i64 i64 i32) (result i32)))
 (import "env" "db_idx64_update" (func $db_idx64_update (param i32 i64 i32)))
 (import "env" "db_idx64_upperbound" (func $db_idx64_upperbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_double_end" (func $db_idx_double_end (param i64 i64 i64) (result i32)))
 (import "env" "db_idx_double_find_primary" (func $db_idx_double_find_primary (param i64 i64 i64 i32 i64) (result i32)))
 (import "env" "db_idx_double_find_secondary" (func $db_idx_double_find_secondary (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_double_lowerbound" (func $db_idx_double_lowerbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_double_next" (func $db_idx_double_next (param i32 i32) (result i32)))
 (import "env" "db_idx_double_previous" (func $db_idx_double_previous (param i32 i32) (result i32)))
 (import "env" "db_idx_double_remove" (func $db_idx_double_remove (param i32)))
 (import "env" "db_idx_double_store" (func $db_idx_double_store (param i64 i64 i64 i64 i32) (result i32)))
 (import "env" "db_idx_double_update" (func $db_idx_double_update (param i32 i64 i32)))
 (import "env" "db_idx_double_upperbound" (func $db_idx_double_upperbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_long_double_end" (func $db_idx_long_double_end (param i64 i64 i64) (result i32)))
 (import "env" "db_idx_long_double_find_primary" (func $db_idx_long_double_find_primary (param i64 i64 i64 i32 i64) (result i32)))
 (import "env" "db_idx_long_double_find_secondary" (func $db_idx_long_double_find_secondary (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_long_double_lowerbound" (func $db_idx_long_double_lowerbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_idx_long_double_next" (func $db_idx_long_double_next (param i32 i32) (result i32)))
 (import "env" "db_idx_long_double_previous" (func $db_idx_long_double_previous (param i32 i32) (result i32)))
 (import "env" "db_idx_long_double_remove" (func $db_idx_long_double_remove (param i32)))
 (import "env" "db_idx_long_double_store" (func $db_idx_long_double_store (param i64 i64 i64 i64 i32) (result i32)))
 (import "env" "db_idx_long_double_update" (func $db_idx_long_double_update (param i32 i64 i32)))
 (import "env" "db_idx_long_double_upperbound" (func $db_idx_long_double_upperbound (param i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_lowerbound_i64" (func $db_lowerbound_i64 (param i64 i64 i64 i64) (result i32)))
 (import "env" "db_next_i64" (func $db_next_i64 (param i32 i32) (result i32)))
 (import "env" "db_previous_i64" (func $db_previous_i64 (param i32 i32) (result i32)))
 (import "env" "db_remove_i64" (func $db_remove_i64 (param i32)))
 (import "env" "db_store_i64" (func $db_store_i64 (param i64 i64 i64 i64 i32 i32) (result i32)))
 (import "env" "db_update_i64" (func $db_update_i64 (param i32 i64 i32 i32)))
 (import "env" "db_upperbound_i64" (func $db_upperbound_i64 (param i64 i64 i64 i64) (result i32)))
 (import "env" "eosio_assert" (func $eosio_assert (param i32 i32)))
 (import "env" "get_account_creation_time" (func $get_account_creation_time (param i64) (result i64)))
 (import "env" "get_active_producers" (func $get_active_producers (param i32 i32) (result i32)))
 (import "env" "get_permission_last_used" (func $get_permission_last_used (param i64 i64) (result i64)))
 (import "env" "has_auth" (func $has_auth (param i64) (result i32)))
 (import "env" "is_account" (func $is_account (param i64) (result i32)))
 (import "env" "memcpy" (func $memcpy (param i32 i32 i32) (result i32)))
 (import "env" "memmove" (func $memmove (param i32 i32 i32) (result i32)))
 (import "env" "memset" (func $memset (param i32 i32 i32) (result i32)))
 (import "env" "printdf" (func $printdf (param f64)))
 (import "env" "printhex" (func $printhex (param i32 i32)))
 (import "env" "printi" (func $printi (param i64)))
 (import "env" "printi128" (func $printi128 (param i32)))
 (import "env" "printn" (func $printn (param i64)))
 (import "env" "printqf" (func $printqf (param i32)))
 (import "env" "prints" (func $prints (param i32)))
 (import "env" "prints_l" (func $prints_l (param i32 i32)))
 (import "env" "printsf" (func $printsf (param f32)))
 (import "env" "printui" (func $printui (param i64)))
 (import "env" "printui128" (func $printui128 (param i32)))
 (import "env" "publication_time" (func $publication_time (result i64)))
 (import "env" "read_action_data" (func $read_action_data (param i32 i32) (result i32)))
 (import "env" "recover_key" (func $recover_key (param i32 i32 i32 i32 i32) (result i32)))
 (import "env" "require_auth" (func $require_auth (param i64)))
 (import "env" "require_auth2" (func $require_auth2 (param i64 i64)))
 (import "env" "require_recipient" (func $require_recipient (param i64)))
 (import "env" "ripemd160" (func $ripemd160 (param i32 i32 i32)))
 (import "env" "send_inline" (func $send_inline (param i32 i32)))
 (import "env" "sha1" (func $sha1 (param i32 i32 i32)))
 (import "env" "sha256" (func $sha256 (param i32 i32 i32)))
 (import "env" "sha512" (func $sha512 (param i32 i32 i32)))
 (table 13 13 anyfunc)
 (elem (i32.const 0) $__wasm_nullptr $_ZN5eosio5token10testcryptoEy $_ZN5eosio5token11testtrxauthEy $_ZN5eosio5token7testmemEy $_ZN5eosio5token6createEyNS_5assetE $_ZN5eosio5token6testcbEy $_ZN5eosio5token9testchainEy $_ZN5eosio5token9testprintEy $_ZN5eosio5token13testsystemapiEy $_ZN5eosio5token6testdbEy $_ZN5eosio5token9testfloatEy $_ZN5eosio5token8transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE $_ZN5eosio5token5issueEyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE)
 (memory $0 1)
 (data (i32.const 4) "0i\00\00")
 (data (i32.const 16) "active\00")
 (data (i32.const 32) "invalid symbol name\00")
 (data (i32.const 64) "invalid supply\00")
 (data (i32.const 80) "max-supply must be positive\00")
 (data (i32.const 112) "object passed to iterator_to is not in multi_index\00")
 (data (i32.const 176) "token with symbol already exists\00")
 (data (i32.const 224) "cannot create objects in table of another contract\00")
 (data (i32.const 288) "oops!\00")
 (data (i32.const 304) "write\00")
 (data (i32.const 320) "magnitude of asset amount must be less than 2^62\00")
 (data (i32.const 384) "error reading iterator\00")
 (data (i32.const 416) "read\00")
 (data (i32.const 432) "memo has more than 256 bytes\00")
 (data (i32.const 464) "token with symbol does not exist, create token before issue\00")
 (data (i32.const 528) "invalid quantity\00")
 (data (i32.const 560) "must issue positive quantity\00")
 (data (i32.const 592) "symbol precision mismatch\00")
 (data (i32.const 624) "quantity exceeds available supply\00")
 (data (i32.const 672) "object passed to modify is not in multi_index\00")
 (data (i32.const 720) "cannot modify objects in table of another contract\00")
 (data (i32.const 784) "attempt to add asset with different symbol\00")
 (data (i32.const 832) "addition underflow\00")
 (data (i32.const 864) "addition overflow\00")
 (data (i32.const 896) "updater cannot change primary key when modifying an object\00")
 (data (i32.const 960) "cannot pass end iterator to modify\00")
 (data (i32.const 1008) "cannot transfer to self\00")
 (data (i32.const 1040) "to account does not exist\00")
 (data (i32.const 1072) "unable to find key\00")
 (data (i32.const 1104) "must transfer positive quantity\00")
 (data (i32.const 1136) "no balance object found\00")
 (data (i32.const 1168) "overdrawn balance\00")
 (data (i32.const 1200) "attempt to subtract asset with different symbol\00")
 (data (i32.const 1248) "subtraction underflow\00")
 (data (i32.const 1280) "subtraction overflow\00")
 (data (i32.const 1312) "object passed to erase is not in multi_index\00")
 (data (i32.const 1360) "cannot erase objects in table of another contract\00")
 (data (i32.const 1424) "attempt to remove object that was not in multi_index\00")
 (data (i32.const 1488) "hello world.\00")
 (data (i32.const 1504) "cannot increment end iterator\00")
 (data (i32.const 1536) "records\00")
 (data (i32.const 1552) "unexpected error in fixed_key constructor\00")
 (data (i32.const 1600) "cannot pass end iterator to erase\00")
 (data (i32.const 1648) "cannot decrement end iterator when the table is empty\00")
 (data (i32.const 1712) "cannot decrement iterator at beginning of table\00")
 (data (i32.const 1760) "cannot decrement end iterator when the index is empty\00")
 (data (i32.const 1824) "cannot decrement iterator at beginning of index\00")
 (data (i32.const 1872) "get\00")
 (data (i32.const 1888) "next primary key in table is at autoincrement limit\00")
 (data (i32.const 1952) "onerror\00")
 (data (i32.const 1968) "eosio\00")
 (data (i32.const 1984) "onerror action\'s are only valid from the \"eosio\" system account\00")
 (data (i32.const 10448) "malloc_from_freed was designed to only be called after _heap was completely allocated\00")
 (export "memory" (memory $0))
 (export "_ZeqRK11checksum256S1_" (func $_ZeqRK11checksum256S1_))
 (export "_ZeqRK11checksum160S1_" (func $_ZeqRK11checksum160S1_))
 (export "_ZneRK11checksum160S1_" (func $_ZneRK11checksum160S1_))
 (export "now" (func $now))
 (export "_ZN5eosio12require_authERKNS_16permission_levelE" (func $_ZN5eosio12require_authERKNS_16permission_levelE))
 (export "_ZN5eosio11test_switchEy" (func $_ZN5eosio11test_switchEy))
 (export "_ZN5eosio5token6createEyNS_5assetE" (func $_ZN5eosio5token6createEyNS_5assetE))
 (export "_ZN5eosio5token5issueEyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE" (func $_ZN5eosio5token5issueEyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE))
 (export "_ZN5eosio5token11add_balanceEyNS_5assetEy" (func $_ZN5eosio5token11add_balanceEyNS_5assetEy))
 (export "_ZN5eosio5token8transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE" (func $_ZN5eosio5token8transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE))
 (export "_ZN5eosio5token11sub_balanceEyNS_5assetE" (func $_ZN5eosio5token11sub_balanceEyNS_5assetE))
 (export "_ZN5eosio5token6testcbEy" (func $_ZN5eosio5token6testcbEy))
 (export "_ZN5eosio5token9testchainEy" (func $_ZN5eosio5token9testchainEy))
 (export "_ZN5eosio5token9testfloatEy" (func $_ZN5eosio5token9testfloatEy))
 (export "_ZN5eosio5token10testcryptoEy" (func $_ZN5eosio5token10testcryptoEy))
 (export "_ZN5eosio5token9testprintEy" (func $_ZN5eosio5token9testprintEy))
 (export "_ZN5eosio5token13testsystemapiEy" (func $_ZN5eosio5token13testsystemapiEy))
 (export "_ZN5eosio5token7testmemEy" (func $_ZN5eosio5token7testmemEy))
 (export "_ZN5eosio5token6testdbEy" (func $_ZN5eosio5token6testdbEy))
 (export "_ZN5eosio5token11testtrxauthEy" (func $_ZN5eosio5token11testtrxauthEy))
 (export "apply" (func $apply))
 (export "malloc" (func $malloc))
 (export "free" (func $free))
 (export "memcmp" (func $memcmp))
 (func $_ZeqRK11checksum256S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.eqz
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $_ZeqRK11checksum160S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.eqz
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
  )
 )
 (func $_ZneRK11checksum160S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.ne
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 32)
   )
   (i32.const 0)
  )
 )
 (func $now (result i32)
  (i32.wrap/i64
   (i64.div_u
    (call $current_time)
    (i64.const 1000000)
   )
  )
 )
 (func $_ZN5eosio12require_authERKNS_16permission_levelE (param $0 i32)
  (call $require_auth2
   (i64.load
    (get_local $0)
   )
   (i64.load offset=8
    (get_local $0)
   )
  )
 )
 (func $_ZN5eosio11test_switchEy (param $0 i64) (result i32)
  (local $1 i32)
  (local $2 i32)
  (set_local $2
   (i32.const 100)
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (br_if $label$6
          (i32.gt_u
           (tee_local $1
            (i32.and
             (i32.wrap/i64
              (get_local $0)
             )
             (i32.const 255)
            )
           )
           (i32.const 32)
          )
         )
         (block $label$7
          (br_table $label$7 $label$5 $label$0 $label$0 $label$0 $label$4 $label$0 $label$0 $label$0 $label$0 $label$3 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$0 $label$2 $label$7
           (get_local $1)
          )
         )
         (return
          (i32.const 1)
         )
        )
        (br_if $label$1
         (i32.eq
          (get_local $1)
          (i32.const 64)
         )
        )
        (br_if $label$0
         (i32.ne
          (get_local $1)
          (i32.const 99)
         )
        )
        (return
         (i32.const 62)
        )
       )
       (return
        (i32.const 12)
       )
      )
      (return
       (i32.const 14)
      )
     )
     (return
      (i32.const 41)
     )
    )
    (return
     (i32.const 31)
    )
   )
   (set_local $2
    (i32.const 71)
   )
  )
  (get_local $2)
 )
 (func $_ZN5eosio5token6createEyNS_5assetE (type $FUNCSIG$viji) (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i64)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 128)
    )
   )
  )
  (call $require_auth
   (i64.load
    (get_local $0)
   )
  )
  (set_local $3
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (i64.const 0)
  )
  (set_local $6
   (i64.const 59)
  )
  (set_local $5
   (i32.const 16)
  )
  (set_local $8
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $7)
          (i64.const 5)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $4
             (i32.load8_s
              (get_local $5)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $4
         (i32.add
          (get_local $4)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $9
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $7)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $4
       (select
        (i32.add
         (get_local $4)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $4)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $9
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $4)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $9
     (i64.shl
      (i64.and
       (get_local $9)
       (i64.const 31)
      )
      (i64.and
       (get_local $6)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $5
    (i32.add
     (get_local $5)
     (i32.const 1)
    )
   )
   (set_local $7
    (i64.add
     (get_local $7)
     (i64.const 1)
    )
   )
   (set_local $8
    (i64.or
     (get_local $9)
     (get_local $8)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $6
      (i64.add
       (get_local $6)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (call $require_auth2
   (get_local $3)
   (get_local $8)
  )
  (drop
   (call $has_auth
    (i64.load
     (get_local $0)
    )
   )
  )
  (set_local $5
   (i32.const 0)
  )
  (set_local $7
   (tee_local $9
    (i64.shr_u
     (tee_local $6
      (i64.load offset=8
       (get_local $2)
      )
     )
     (i64.const 8)
    )
   )
  )
  (block $label$6
   (block $label$7
    (loop $label$8
     (br_if $label$7
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $7)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$9
      (br_if $label$9
       (i64.ne
        (i64.and
         (tee_local $7
          (i64.shr_u
           (get_local $7)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$10
       (br_if $label$7
        (i64.ne
         (i64.and
          (tee_local $7
           (i64.shr_u
            (get_local $7)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$10
        (i32.lt_s
         (tee_local $5
          (i32.add
           (get_local $5)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$8
      (i32.lt_s
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$6)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 32)
  )
  (set_local $4
   (i32.const 0)
  )
  (block $label$11
   (br_if $label$11
    (i64.gt_u
     (i64.add
      (tee_local $8
       (i64.load
        (get_local $2)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $5
    (i32.const 0)
   )
   (set_local $7
    (get_local $9)
   )
   (block $label$12
    (loop $label$13
     (br_if $label$12
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $7)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$14
      (br_if $label$14
       (i64.ne
        (i64.and
         (tee_local $7
          (i64.shr_u
           (get_local $7)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$15
       (br_if $label$12
        (i64.ne
         (i64.and
          (tee_local $7
           (i64.shr_u
            (get_local $7)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$15
        (i32.lt_s
         (tee_local $5
          (i32.add
           (get_local $5)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$13
      (i32.lt_s
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$11)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 64)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $8)
    (i64.const 0)
   )
   (i32.const 80)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 8)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const -1)
  )
  (i64.store offset=32
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $10)
   (tee_local $7
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=16
   (get_local $10)
   (get_local $9)
  )
  (block $label$16
   (block $label$17
    (br_if $label$17
     (i32.lt_s
      (tee_local $5
       (call $db_find_i64
        (get_local $7)
        (get_local $9)
        (i64.const -4157508551318700032)
        (get_local $9)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=40
       (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE31load_object_by_primary_iteratorEl
        (i32.add
         (get_local $10)
         (i32.const 8)
        )
        (get_local $5)
       )
      )
      (i32.add
       (get_local $10)
       (i32.const 8)
      )
     )
     (i32.const 112)
    )
    (set_local $5
     (i32.const 0)
    )
    (br $label$16)
   )
   (set_local $5
    (i32.const 1)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 176)
  )
  (set_local $9
   (i64.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=8
     (get_local $10)
    )
    (call $current_receiver)
   )
   (i32.const 224)
  )
  (drop
   (call $_ZN5eosio5token14currency_statsC2Ev
    (tee_local $5
     (call $_Znwj
      (i32.const 56)
     )
    )
   )
  )
  (i32.store offset=40
   (get_local $5)
   (i32.add
    (get_local $10)
    (i32.const 8)
   )
  )
  (i64.store offset=8
   (get_local $5)
   (get_local $6)
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 28)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 24)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 20)
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i32.store offset=16
   (get_local $5)
   (i32.load
    (get_local $2)
   )
  )
  (i64.store offset=32
   (get_local $5)
   (get_local $1)
  )
  (i32.store offset=96
   (get_local $10)
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.const 40)
   )
  )
  (i32.store offset=92
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
  (i32.store offset=88
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
  (i32.store offset=104
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 88)
   )
  )
  (i32.store offset=116
   (get_local $10)
   (i32.add
    (get_local $5)
    (i32.const 16)
   )
  )
  (i32.store offset=112
   (get_local $10)
   (get_local $5)
  )
  (i32.store offset=120
   (get_local $10)
   (i32.add
    (get_local $5)
    (i32.const 32)
   )
  )
  (call $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRKN5eosio5assetES8_RKyEEEZNS5_lsINS5_10datastreamIPcEENS5_5token14currency_statsELPv0EEERT_SK_RKT0_EUlRKSJ_E_JLj0ELj1ELj2EEEEvSK_OSL_NSt3__116integer_sequenceIjJXspT1_EEEENSS_17integral_constantIbLb0EEE
   (i32.add
    (get_local $10)
    (i32.const 112)
   )
   (i32.add
    (get_local $10)
    (i32.const 104)
   )
  )
  (i32.store offset=44
   (get_local $5)
   (tee_local $2
    (call $db_store_i64
     (i64.load
      (i32.add
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
       (i32.const 8)
      )
     )
     (i64.const -4157508551318700032)
     (get_local $9)
     (tee_local $7
      (i64.shr_u
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const 8)
      )
     )
     (i32.add
      (get_local $10)
      (i32.const 48)
     )
     (i32.const 40)
    )
   )
  )
  (block $label$18
   (br_if $label$18
    (i64.lt_u
     (get_local $7)
     (i64.load
      (tee_local $4
       (i32.add
        (i32.add
         (get_local $10)
         (i32.const 8)
        )
        (i32.const 16)
       )
      )
     )
    )
   )
   (i64.store
    (get_local $4)
    (i64.add
     (get_local $7)
     (i64.const 1)
    )
   )
  )
  (i32.store offset=112
   (get_local $10)
   (get_local $5)
  )
  (i64.store offset=48
   (get_local $10)
   (tee_local $7
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $5)
       (i32.const 8)
      )
     )
     (i64.const 8)
    )
   )
  )
  (i32.store offset=88
   (get_local $10)
   (get_local $2)
  )
  (block $label$19
   (block $label$20
    (br_if $label$20
     (i32.ge_u
      (tee_local $4
       (i32.load
        (i32.add
         (i32.add
          (get_local $10)
          (i32.const 8)
         )
         (i32.const 28)
        )
       )
      )
      (i32.load
       (i32.add
        (get_local $10)
        (i32.const 40)
       )
      )
     )
    )
    (i64.store offset=8
     (get_local $4)
     (get_local $7)
    )
    (i32.store offset=16
     (get_local $4)
     (get_local $2)
    )
    (i32.store offset=112
     (get_local $10)
     (i32.const 0)
    )
    (i32.store
     (get_local $4)
     (get_local $5)
    )
    (i32.store
     (i32.add
      (get_local $10)
      (i32.const 36)
     )
     (i32.add
      (get_local $4)
      (i32.const 24)
     )
    )
    (br $label$19)
   )
   (call $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_5token14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
    (i32.add
     (get_local $10)
     (i32.const 32)
    )
    (i32.add
     (get_local $10)
     (i32.const 112)
    )
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.add
     (get_local $10)
     (i32.const 88)
    )
   )
  )
  (set_local $5
   (i32.load offset=112
    (get_local $10)
   )
  )
  (i32.store offset=112
   (get_local $10)
   (i32.const 0)
  )
  (block $label$21
   (br_if $label$21
    (i32.eqz
     (get_local $5)
    )
   )
   (call $_ZdlPv
    (get_local $5)
   )
  )
  (set_local $5
   (i32.const 100)
  )
  (block $label$22
   (block $label$23
    (block $label$24
     (block $label$25
      (block $label$26
       (block $label$27
        (block $label$28
         (br_if $label$28
          (i32.gt_u
           (tee_local $4
            (i32.and
             (i32.wrap/i64
              (get_local $1)
             )
             (i32.const 255)
            )
           )
           (i32.const 32)
          )
         )
         (block $label$29
          (br_table $label$29 $label$27 $label$22 $label$22 $label$22 $label$26 $label$22 $label$22 $label$22 $label$22 $label$25 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$22 $label$24 $label$29
           (get_local $4)
          )
         )
         (set_local $5
          (i32.const 1)
         )
         (br $label$22)
        )
        (br_if $label$23
         (i32.eq
          (get_local $4)
          (i32.const 64)
         )
        )
        (br_if $label$22
         (i32.ne
          (get_local $4)
          (i32.const 99)
         )
        )
        (set_local $5
         (i32.const 62)
        )
        (br $label$22)
       )
       (set_local $5
        (i32.const 12)
       )
       (br $label$22)
      )
      (set_local $5
       (i32.const 14)
      )
      (br $label$22)
     )
     (set_local $5
      (i32.const 41)
     )
     (br $label$22)
    )
    (set_local $5
     (i32.const 31)
    )
    (br $label$22)
   )
   (set_local $5
    (i32.const 71)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 288)
  )
  (set_local $2
   (i32.const 0)
  )
  (loop $label$30
   (set_local $1
    (i64.load
     (get_local $0)
    )
   )
   (set_local $7
    (i64.const 0)
   )
   (set_local $6
    (i64.const 59)
   )
   (set_local $5
    (i32.const 16)
   )
   (set_local $8
    (i64.const 0)
   )
   (loop $label$31
    (block $label$32
     (block $label$33
      (block $label$34
       (block $label$35
        (block $label$36
         (br_if $label$36
          (i64.gt_u
           (get_local $7)
           (i64.const 5)
          )
         )
         (br_if $label$35
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $4
              (i32.load8_s
               (get_local $5)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $4
          (i32.add
           (get_local $4)
           (i32.const 165)
          )
         )
         (br $label$34)
        )
        (set_local $9
         (i64.const 0)
        )
        (br_if $label$33
         (i64.le_u
          (get_local $7)
          (i64.const 11)
         )
        )
        (br $label$32)
       )
       (set_local $4
        (select
         (i32.add
          (get_local $4)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $4)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $9
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $4)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $9
      (i64.shl
       (i64.and
        (get_local $9)
        (i64.const 31)
       )
       (i64.and
        (get_local $6)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $5
     (i32.add
      (get_local $5)
      (i32.const 1)
     )
    )
    (set_local $7
     (i64.add
      (get_local $7)
      (i64.const 1)
     )
    )
    (set_local $8
     (i64.or
      (get_local $9)
      (get_local $8)
     )
    )
    (br_if $label$31
     (i64.ne
      (tee_local $6
       (i64.add
        (get_local $6)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $get_permission_last_used
     (get_local $1)
     (get_local $8)
    )
   )
   (drop
    (call $get_account_creation_time
     (i64.load
      (get_local $0)
     )
    )
   )
   (br_if $label$30
    (i32.ne
     (tee_local $2
      (i32.add
       (get_local $2)
       (i32.const 1)
      )
     )
     (i32.const 100)
    )
   )
  )
  (block $label$37
   (br_if $label$37
    (i32.eqz
     (tee_local $0
      (i32.load offset=32
       (get_local $10)
      )
     )
    )
   )
   (block $label$38
    (block $label$39
     (br_if $label$39
      (i32.eq
       (tee_local $5
        (i32.load
         (tee_local $2
          (i32.add
           (get_local $10)
           (i32.const 36)
          )
         )
        )
       )
       (get_local $0)
      )
     )
     (loop $label$40
      (set_local $4
       (i32.load
        (tee_local $5
         (i32.add
          (get_local $5)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $5)
       (i32.const 0)
      )
      (block $label$41
       (br_if $label$41
        (i32.eqz
         (get_local $4)
        )
       )
       (call $_ZdlPv
        (get_local $4)
       )
      )
      (br_if $label$40
       (i32.ne
        (get_local $0)
        (get_local $5)
       )
      )
     )
     (set_local $5
      (i32.load
       (i32.add
        (get_local $10)
        (i32.const 32)
       )
      )
     )
     (br $label$38)
    )
    (set_local $5
     (get_local $0)
    )
   )
   (i32.store
    (get_local $2)
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 128)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 384)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=12
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=8
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=16
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $6)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $6)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (drop
    (call $_ZN5eosio5token14currency_statsC2Ev
     (tee_local $6
      (call $_Znwj
       (i32.const 56)
      )
     )
    )
   )
   (i32.store offset=40
    (get_local $6)
    (get_local $0)
   )
   (i32.store offset=24
    (get_local $8)
    (i32.add
     (get_local $8)
     (i32.const 8)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (i32.add
     (get_local $6)
     (i32.const 16)
    )
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $6)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $6)
     (i32.const 32)
    )
   )
   (call $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRN5eosio5assetES7_RyEEEZNS5_rsINS5_10datastreamIPKcEENS5_5token14currency_statsELPv0EEERT_SJ_RT0_EUlSJ_E_JLj0ELj1ELj2EEEEvSJ_OSK_NSt3__116integer_sequenceIjJXspT1_EEEENSO_17integral_constantIbLb0EEE
    (i32.add
     (get_local $8)
     (i32.const 32)
    )
    (i32.add
     (get_local $8)
     (i32.const 24)
    )
   )
   (i32.store offset=44
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=32
    (get_local $8)
    (tee_local $5
     (i64.shr_u
      (i64.load offset=8
       (get_local $6)
      )
      (i64.const 8)
     )
    )
   )
   (i32.store offset=4
    (get_local $8)
    (tee_local $7
     (i32.load offset=44
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_5token14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (i32.add
      (get_local $8)
      (i32.const 4)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZN5eosio5token14currency_statsC2Ev (param $0 i32) (result i32)
  (local $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 1398362884)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 320)
  )
  (set_local $1
   (i64.shr_u
    (i64.load offset=8
     (get_local $0)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 32)
  )
  (i64.store
   (tee_local $2
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.const 1398362884)
  )
  (i64.store offset=16
   (get_local $0)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 320)
  )
  (set_local $1
   (i64.shr_u
    (i64.load
     (get_local $2)
    )
    (i64.const 8)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$5
   (block $label$6
    (loop $label$7
     (br_if $label$6
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $1)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.ne
        (i64.and
         (tee_local $1
          (i64.shr_u
           (get_local $1)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$9
       (br_if $label$6
        (i64.ne
         (i64.and
          (tee_local $1
           (i64.shr_u
            (get_local $1)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$9
        (i32.lt_s
         (tee_local $2
          (i32.add
           (get_local $2)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $3
      (i32.const 1)
     )
     (br_if $label$7
      (i32.lt_s
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$5)
    )
   )
   (set_local $3
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $3)
   (i32.const 32)
  )
  (get_local $0)
 )
 (func $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRKN5eosio5assetES8_RKyEEEZNS5_lsINS5_10datastreamIPcEENS5_5token14currency_statsELPv0EEERT_SK_RKT0_EUlRKSJ_E_JLj0ELj1ELj2EEEEvSK_OSL_NSt3__116integer_sequenceIjJXspT1_EEEENSS_17integral_constantIbLb0EEE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (set_local $3
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $2)
    )
    (get_local $3)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $2)
    )
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=4
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $2)
    )
    (get_local $3)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $2)
    )
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load offset=8
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $2)
    )
    (get_local $0)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy14289235522390851584ENS1_5token14currency_statsEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRN5eosio5assetES7_RyEEEZNS5_rsINS5_10datastreamIPKcEENS5_5token14currency_statsELPv0EEERT_SJ_RT0_EUlSJ_E_JLj0ELj1ELj2EEEEvSJ_OSK_NSt3__116integer_sequenceIjJXspT1_EEEENSO_17integral_constantIbLb0EEE (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (set_local $3
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.load offset=4
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $3)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (tee_local $4
    (i32.add
     (i32.load offset=4
      (get_local $2)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $2)
     )
     (get_local $4)
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load offset=8
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $2)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $2)
   (i32.add
    (i32.load offset=4
     (get_local $2)
    )
    (i32.const 8)
   )
  )
 )
 (func $_ZN5eosio5token5issueEyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE (type $FUNCSIG$vijii) (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i64)
  (local $11 i64)
  (local $12 i64)
  (local $13 i64)
  (local $14 i64)
  (local $15 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $15
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 224)
    )
   )
  )
  (set_local $9
   (i32.const 0)
  )
  (set_local $11
   (tee_local $14
    (i64.shr_u
     (tee_local $4
      (i64.load offset=8
       (get_local $2)
      )
     )
     (i64.const 8)
    )
   )
  )
  (block $label$0
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $11)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$3
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $11
          (i64.shr_u
           (get_local $11)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$4
       (br_if $label$1
        (i64.ne
         (i64.and
          (tee_local $11
           (i64.shr_u
            (get_local $11)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$4
        (i32.lt_s
         (tee_local $9
          (i32.add
           (get_local $9)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $7
      (i32.const 1)
     )
     (br_if $label$2
      (i32.lt_s
       (tee_local $9
        (i32.add
         (get_local $9)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$0)
    )
   )
   (set_local $7
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $7)
   (i32.const 32)
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.and
      (tee_local $9
       (i32.load8_u
        (get_local $3)
       )
      )
      (i32.const 1)
     )
    )
    (set_local $9
     (i32.shr_u
      (get_local $9)
      (i32.const 1)
     )
    )
    (br $label$5)
   )
   (set_local $9
    (i32.load offset=4
     (get_local $3)
    )
   )
  )
  (call $eosio_assert
   (i32.lt_u
    (get_local $9)
    (i32.const 257)
   )
   (i32.const 432)
  )
  (set_local $9
   (i32.const 100)
  )
  (block $label$7
   (block $label$8
    (block $label$9
     (block $label$10
      (block $label$11
       (block $label$12
        (block $label$13
         (br_if $label$13
          (i32.gt_u
           (tee_local $7
            (i32.and
             (i32.wrap/i64
              (get_local $1)
             )
             (i32.const 255)
            )
           )
           (i32.const 32)
          )
         )
         (block $label$14
          (br_table $label$14 $label$12 $label$7 $label$7 $label$7 $label$11 $label$7 $label$7 $label$7 $label$7 $label$10 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$7 $label$9 $label$14
           (get_local $7)
          )
         )
         (set_local $9
          (i32.const 1)
         )
         (br $label$7)
        )
        (br_if $label$8
         (i32.eq
          (get_local $7)
          (i32.const 64)
         )
        )
        (br_if $label$7
         (i32.ne
          (get_local $7)
          (i32.const 99)
         )
        )
        (set_local $9
         (i32.const 62)
        )
        (br $label$7)
       )
       (set_local $9
        (i32.const 12)
       )
       (br $label$7)
      )
      (set_local $9
       (i32.const 14)
      )
      (br $label$7)
     )
     (set_local $9
      (i32.const 41)
     )
     (br $label$7)
    )
    (set_local $9
     (i32.const 31)
    )
    (br $label$7)
   )
   (set_local $9
    (i32.const 71)
   )
  )
  (call $eosio_assert
   (get_local $9)
   (i32.const 288)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $15)
     (i32.const 88)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i64.store offset=104
   (get_local $15)
   (i64.const -1)
  )
  (set_local $11
   (i64.const 0)
  )
  (i64.store offset=112
   (get_local $15)
   (i64.const 0)
  )
  (i64.store offset=88
   (get_local $15)
   (tee_local $13
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=96
   (get_local $15)
   (get_local $14)
  )
  (set_local $8
   (i32.const 0)
  )
  (block $label$15
   (br_if $label$15
    (i32.lt_s
     (tee_local $9
      (call $db_find_i64
       (get_local $13)
       (get_local $14)
       (i64.const -4157508551318700032)
       (get_local $14)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=40
      (tee_local $8
       (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE31load_object_by_primary_iteratorEl
        (i32.add
         (get_local $15)
         (i32.const 88)
        )
        (get_local $9)
       )
      )
     )
     (i32.add
      (get_local $15)
      (i32.const 88)
     )
    )
    (i32.const 112)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $8)
    (i32.const 0)
   )
   (i32.const 464)
  )
  (call $require_auth
   (i64.load offset=32
    (get_local $8)
   )
  )
  (set_local $5
   (i32.add
    (get_local $8)
    (i32.const 32)
   )
  )
  (set_local $6
   (i64.load offset=32
    (get_local $8)
   )
  )
  (set_local $10
   (i64.const 59)
  )
  (set_local $9
   (i32.const 16)
  )
  (set_local $12
   (i64.const 0)
  )
  (loop $label$16
   (block $label$17
    (block $label$18
     (block $label$19
      (block $label$20
       (block $label$21
        (br_if $label$21
         (i64.gt_u
          (get_local $11)
          (i64.const 5)
         )
        )
        (br_if $label$20
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $7
             (i32.load8_s
              (get_local $9)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $7
         (i32.add
          (get_local $7)
          (i32.const 165)
         )
        )
        (br $label$19)
       )
       (set_local $13
        (i64.const 0)
       )
       (br_if $label$18
        (i64.le_u
         (get_local $11)
         (i64.const 11)
        )
       )
       (br $label$17)
      )
      (set_local $7
       (select
        (i32.add
         (get_local $7)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $7)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $13
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $7)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $13
     (i64.shl
      (i64.and
       (get_local $13)
       (i64.const 31)
      )
      (i64.and
       (get_local $10)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $9
    (i32.add
     (get_local $9)
     (i32.const 1)
    )
   )
   (set_local $11
    (i64.add
     (get_local $11)
     (i64.const 1)
    )
   )
   (set_local $12
    (i64.or
     (get_local $13)
     (get_local $12)
    )
   )
   (br_if $label$16
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (call $require_auth2
   (get_local $6)
   (get_local $12)
  )
  (drop
   (call $has_auth
    (i64.load
     (get_local $5)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (block $label$22
   (br_if $label$22
    (i64.gt_u
     (i64.add
      (tee_local $11
       (i64.load
        (get_local $2)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $9
    (i32.const 0)
   )
   (block $label$23
    (loop $label$24
     (br_if $label$23
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $14)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$25
      (br_if $label$25
       (i64.ne
        (i64.and
         (tee_local $14
          (i64.shr_u
           (get_local $14)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$26
       (br_if $label$23
        (i64.ne
         (i64.and
          (tee_local $14
           (i64.shr_u
            (get_local $14)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$26
        (i32.lt_s
         (tee_local $9
          (i32.add
           (get_local $9)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $7
      (i32.const 1)
     )
     (br_if $label$24
      (i32.lt_s
       (tee_local $9
        (i32.add
         (get_local $9)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$22)
    )
   )
   (set_local $7
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $7)
   (i32.const 528)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $11)
    (i64.const 0)
   )
   (i32.const 560)
  )
  (call $eosio_assert
   (i64.eq
    (get_local $4)
    (i64.load offset=8
     (get_local $8)
    )
   )
   (i32.const 592)
  )
  (call $eosio_assert
   (i64.le_s
    (get_local $11)
    (i64.sub
     (i64.load offset=16
      (get_local $8)
     )
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.const 624)
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=40
     (get_local $8)
    )
    (i32.add
     (get_local $15)
     (i32.const 88)
    )
   )
   (i32.const 672)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load offset=88
     (get_local $15)
    )
    (call $current_receiver)
   )
   (i32.const 720)
  )
  (call $eosio_assert
   (i64.eq
    (get_local $4)
    (tee_local $13
     (i64.load offset=8
      (get_local $8)
     )
    )
   )
   (i32.const 784)
  )
  (i64.store
   (get_local $8)
   (tee_local $11
    (i64.add
     (i64.load
      (get_local $8)
     )
     (get_local $11)
    )
   )
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $11)
    (i64.const -4611686018427387904)
   )
   (i32.const 832)
  )
  (call $eosio_assert
   (i64.lt_s
    (i64.load
     (get_local $8)
    )
    (i64.const 4611686018427387904)
   )
   (i32.const 864)
  )
  (call $eosio_assert
   (i64.eq
    (tee_local $11
     (i64.shr_u
      (get_local $13)
      (i64.const 8)
     )
    )
    (i64.shr_u
     (i64.load offset=8
      (get_local $8)
     )
     (i64.const 8)
    )
   )
   (i32.const 896)
  )
  (i32.store offset=192
   (get_local $15)
   (i32.add
    (i32.add
     (get_local $15)
     (i32.const 128)
    )
    (i32.const 40)
   )
  )
  (i32.store offset=188
   (get_local $15)
   (i32.add
    (get_local $15)
    (i32.const 128)
   )
  )
  (i32.store offset=184
   (get_local $15)
   (i32.add
    (get_local $15)
    (i32.const 128)
   )
  )
  (i32.store offset=200
   (get_local $15)
   (i32.add
    (get_local $15)
    (i32.const 184)
   )
  )
  (i32.store offset=212
   (get_local $15)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (i32.store offset=208
   (get_local $15)
   (get_local $8)
  )
  (i32.store offset=216
   (get_local $15)
   (get_local $5)
  )
  (call $_ZN5boost3pfr6detail19for_each_field_implINS1_14sequence_tuple5tupleIJRKN5eosio5assetES8_RKyEEEZNS5_lsINS5_10datastreamIPcEENS5_5token14currency_statsELPv0EEERT_SK_RKT0_EUlRKSJ_E_JLj0ELj1ELj2EEEEvSK_OSL_NSt3__116integer_sequenceIjJXspT1_EEEENSS_17integral_constantIbLb0EEE
   (i32.add
    (get_local $15)
    (i32.const 208)
   )
   (i32.add
    (get_local $15)
    (i32.const 200)
   )
  )
  (call $db_update_i64
   (i32.load offset=44
    (get_local $8)
   )
   (i64.const 0)
   (i32.add
    (get_local $15)
    (i32.const 128)
   )
   (i32.const 40)
  )
  (block $label$27
   (br_if $label$27
    (i64.lt_u
     (get_local $11)
     (i64.load
      (tee_local $9
       (i32.add
        (i32.add
         (get_local $15)
         (i32.const 88)
        )
        (i32.const 16)
       )
      )
     )
    )
   )
   (i64.store
    (get_local $9)
    (i64.add
     (get_local $11)
     (i64.const 1)
    )
   )
  )
  (i32.store
   (tee_local $9
    (i32.add
     (i32.add
      (get_local $15)
      (i32.const 72)
     )
     (i32.const 12)
    )
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $15)
      (i32.const 72)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=76
   (get_local $15)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i32.store offset=72
   (get_local $15)
   (i32.load
    (get_local $2)
   )
  )
  (set_local $11
   (i64.load
    (get_local $5)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $15)
     (i32.const 8)
    )
    (i32.const 12)
   )
   (i32.load
    (get_local $9)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $15)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (i32.load
    (get_local $7)
   )
  )
  (i32.store offset=12
   (get_local $15)
   (i32.load offset=76
    (get_local $15)
   )
  )
  (i32.store offset=8
   (get_local $15)
   (i32.load offset=72
    (get_local $15)
   )
  )
  (call $_ZN5eosio5token11add_balanceEyNS_5assetEy
   (get_local $0)
   (get_local $11)
   (i32.add
    (get_local $15)
    (i32.const 8)
   )
   (get_local $11)
  )
  (block $label$28
   (br_if $label$28
    (i64.eq
     (tee_local $14
      (i64.load
       (get_local $5)
      )
     )
     (get_local $1)
    )
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $11
    (i64.const 0)
   )
   (set_local $10
    (i64.const 59)
   )
   (set_local $9
    (i32.const 16)
   )
   (set_local $12
    (i64.const 0)
   )
   (loop $label$29
    (block $label$30
     (block $label$31
      (block $label$32
       (block $label$33
        (block $label$34
         (br_if $label$34
          (i64.gt_u
           (get_local $11)
           (i64.const 5)
          )
         )
         (br_if $label$33
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $7
              (i32.load8_s
               (get_local $9)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $7
          (i32.add
           (get_local $7)
           (i32.const 165)
          )
         )
         (br $label$32)
        )
        (set_local $13
         (i64.const 0)
        )
        (br_if $label$31
         (i64.le_u
          (get_local $11)
          (i64.const 11)
         )
        )
        (br $label$30)
       )
       (set_local $7
        (select
         (i32.add
          (get_local $7)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $7)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $13
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $7)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $13
      (i64.shl
       (i64.and
        (get_local $13)
        (i64.const 31)
       )
       (i64.and
        (get_local $10)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $9
     (i32.add
      (get_local $9)
      (i32.const 1)
     )
    )
    (set_local $11
     (i64.add
      (get_local $11)
      (i64.const 1)
     )
    )
    (set_local $12
     (i64.or
      (get_local $13)
      (get_local $12)
     )
    )
    (br_if $label$29
     (i64.ne
      (tee_local $10
       (i64.add
        (get_local $10)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 52)
    )
    (i32.load
     (i32.add
      (get_local $2)
      (i32.const 12)
     )
    )
   )
   (i32.store
    (tee_local $7
     (i32.add
      (i32.add
       (get_local $15)
       (i32.const 24)
      )
      (i32.const 24)
     )
    )
    (i32.load
     (i32.add
      (get_local $2)
      (i32.const 8)
     )
    )
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 44)
    )
    (i32.load
     (i32.add
      (get_local $2)
      (i32.const 4)
     )
    )
   )
   (i64.store offset=32
    (get_local $15)
    (get_local $1)
   )
   (i64.store offset=24
    (get_local $15)
    (get_local $14)
   )
   (i32.store offset=40
    (get_local $15)
    (i32.load
     (get_local $2)
    )
   )
   (drop
    (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
     (i32.add
      (get_local $15)
      (i32.const 56)
     )
     (get_local $3)
    )
   )
   (i64.store
    (tee_local $9
     (call $_Znwj
      (i32.const 16)
     )
    )
    (get_local $14)
   )
   (i64.store offset=8
    (get_local $9)
    (get_local $12)
   )
   (i32.store offset=208
    (get_local $15)
    (get_local $9)
   )
   (i32.store offset=216
    (get_local $15)
    (tee_local $9
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
    )
   )
   (i32.store offset=212
    (get_local $15)
    (get_local $9)
   )
   (i64.store offset=128
    (get_local $15)
    (i64.load offset=24
     (get_local $15)
    )
   )
   (i64.store offset=136
    (get_local $15)
    (i64.load offset=32
     (get_local $15)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $15)
      (i32.const 128)
     )
     (i32.const 24)
    )
    (i64.load
     (get_local $7)
    )
   )
   (i64.store offset=144
    (get_local $15)
    (i64.load offset=40
     (get_local $15)
    )
   )
   (i32.store
    (tee_local $7
     (i32.add
      (i32.add
       (get_local $15)
       (i32.const 128)
      )
      (i32.const 40)
     )
    )
    (i32.load
     (tee_local $9
      (i32.add
       (i32.add
        (get_local $15)
        (i32.const 24)
       )
       (i32.const 40)
      )
     )
    )
   )
   (i64.store offset=160
    (get_local $15)
    (i64.load offset=56
     (get_local $15)
    )
   )
   (i32.store offset=56
    (get_local $15)
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 60)
    )
    (i32.const 0)
   )
   (i32.store
    (get_local $9)
    (i32.const 0)
   )
   (call $_ZN5eosio15dispatch_inlineIJyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEEEEvyyNS2_6vectorINS_16permission_levelENS6_ISA_EEEENS2_5tupleIJDpT_EEE
    (get_local $4)
    (i64.const -3617168760277827584)
    (i32.add
     (get_local $15)
     (i32.const 208)
    )
    (i32.add
     (get_local $15)
     (i32.const 128)
    )
   )
   (block $label$35
    (br_if $label$35
     (i32.eqz
      (i32.and
       (i32.load8_u offset=160
        (get_local $15)
       )
       (i32.const 1)
      )
     )
    )
    (call $_ZdlPv
     (i32.load
      (get_local $7)
     )
    )
   )
   (block $label$36
    (br_if $label$36
     (i32.eqz
      (tee_local $9
       (i32.load offset=208
        (get_local $15)
       )
      )
     )
    )
    (i32.store offset=212
     (get_local $15)
     (get_local $9)
    )
    (call $_ZdlPv
     (get_local $9)
    )
   )
   (br_if $label$28
    (i32.eqz
     (i32.and
      (i32.load8_u
       (i32.add
        (get_local $15)
        (i32.const 56)
       )
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $15)
      (i32.const 64)
     )
    )
   )
  )
  (block $label$37
   (br_if $label$37
    (i32.eqz
     (tee_local $8
      (i32.load offset=112
       (get_local $15)
      )
     )
    )
   )
   (block $label$38
    (block $label$39
     (br_if $label$39
      (i32.eq
       (tee_local $9
        (i32.load
         (tee_local $2
          (i32.add
           (get_local $15)
           (i32.const 116)
          )
         )
        )
       )
       (get_local $8)
      )
     )
     (loop $label$40
      (set_local $7
       (i32.load
        (tee_local $9
         (i32.add
          (get_local $9)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $9)
       (i32.const 0)
      )
      (block $label$41
       (br_if $label$41
        (i32.eqz
         (get_local $7)
        )
       )
       (call $_ZdlPv
        (get_local $7)
       )
      )
      (br_if $label$40
       (i32.ne
        (get_local $8)
        (get_local $9)
       )
      )
     )
     (set_local $9
      (i32.load
       (i32.add
        (get_local $15)
        (i32.const 112)
       )
      )
     )
     (br $label$38)
    )
    (set_local $9
     (get_local $8)
    )
   )
   (i32.store
    (get_local $2)
    (get_local $8)
   )
   (call $_ZdlPv
    (get_local $9)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $15)
    (i32.const 224)
   )
  )
 )
 (func $_ZN5eosio5token11add_balanceEyNS_5assetEy (param $0 i32) (param $1 i64) (param $2 i32) (param $3 i64)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 80)
    )
   )
  )
  (set_local $8
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i32.const 32)
   )
   (i32.const 0)
  )
  (i64.store offset=24
   (get_local $9)
   (i64.const -1)
  )
  (i64.store offset=32
   (get_local $9)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $9)
   (tee_local $6
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=16
   (get_local $9)
   (get_local $1)
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.lt_s
        (tee_local $0
         (call $db_find_i64
          (get_local $6)
          (get_local $1)
          (i64.const 3607749779137757184)
          (i64.shr_u
           (tee_local $4
            (i64.load offset=8
             (get_local $2)
            )
           )
           (i64.const 8)
          )
         )
        )
        (i32.const 0)
       )
      )
      (call $eosio_assert
       (i32.eq
        (i32.load offset=16
         (tee_local $8
          (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE31load_object_by_primary_iteratorEl
           (i32.add
            (get_local $9)
            (i32.const 8)
           )
           (get_local $0)
          )
         )
        )
        (i32.add
         (get_local $9)
         (i32.const 8)
        )
       )
       (i32.const 112)
      )
      (call $eosio_assert
       (i32.const 1)
       (i32.const 960)
      )
      (call $eosio_assert
       (i32.eq
        (i32.load offset=16
         (get_local $8)
        )
        (i32.add
         (get_local $9)
         (i32.const 8)
        )
       )
       (i32.const 672)
      )
      (call $eosio_assert
       (i64.eq
        (i64.load offset=8
         (get_local $9)
        )
        (call $current_receiver)
       )
       (i32.const 720)
      )
      (call $eosio_assert
       (i64.eq
        (get_local $4)
        (tee_local $1
         (i64.load offset=8
          (get_local $8)
         )
        )
       )
       (i32.const 784)
      )
      (i64.store
       (get_local $8)
       (tee_local $6
        (i64.add
         (i64.load
          (get_local $8)
         )
         (i64.load
          (get_local $2)
         )
        )
       )
      )
      (call $eosio_assert
       (i64.gt_s
        (get_local $6)
        (i64.const -4611686018427387904)
       )
       (i32.const 832)
      )
      (call $eosio_assert
       (i64.lt_s
        (i64.load
         (get_local $8)
        )
        (i64.const 4611686018427387904)
       )
       (i32.const 864)
      )
      (call $eosio_assert
       (i64.eq
        (tee_local $1
         (i64.shr_u
          (get_local $1)
          (i64.const 8)
         )
        )
        (i64.shr_u
         (i64.load offset=8
          (get_local $8)
         )
         (i64.const 8)
        )
       )
       (i32.const 896)
      )
      (call $eosio_assert
       (i32.const 1)
       (i32.const 304)
      )
      (drop
       (call $memcpy
        (i32.add
         (get_local $9)
         (i32.const 64)
        )
        (get_local $8)
        (i32.const 8)
       )
      )
      (call $eosio_assert
       (i32.const 1)
       (i32.const 304)
      )
      (drop
       (call $memcpy
        (i32.or
         (i32.add
          (get_local $9)
          (i32.const 64)
         )
         (i32.const 8)
        )
        (i32.add
         (get_local $8)
         (i32.const 8)
        )
        (i32.const 8)
       )
      )
      (call $db_update_i64
       (i32.load offset=20
        (get_local $8)
       )
       (i64.const 0)
       (i32.add
        (get_local $9)
        (i32.const 64)
       )
       (i32.const 16)
      )
      (br_if $label$2
       (i64.lt_u
        (get_local $1)
        (i64.load
         (tee_local $8
          (i32.add
           (i32.add
            (get_local $9)
            (i32.const 8)
           )
           (i32.const 16)
          )
         )
        )
       )
      )
      (i64.store
       (get_local $8)
       (i64.add
        (get_local $1)
        (i64.const 1)
       )
      )
      (br_if $label$1
       (tee_local $2
        (i32.load offset=32
         (get_local $9)
        )
       )
      )
      (br $label$0)
     )
     (call $eosio_assert
      (i64.eq
       (i64.load offset=8
        (get_local $9)
       )
       (call $current_receiver)
      )
      (i32.const 224)
     )
     (i64.store offset=8
      (tee_local $0
       (call $_Znwj
        (i32.const 32)
       )
      )
      (i64.const 1398362884)
     )
     (i64.store
      (get_local $0)
      (i64.const 0)
     )
     (call $eosio_assert
      (i32.const 1)
      (i32.const 320)
     )
     (set_local $5
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
     (set_local $1
      (i64.const 5462355)
     )
     (block $label$4
      (loop $label$5
       (set_local $7
        (i32.const 0)
       )
       (br_if $label$4
        (i32.gt_u
         (i32.add
          (i32.shl
           (i32.wrap/i64
            (get_local $1)
           )
           (i32.const 24)
          )
          (i32.const -1073741825)
         )
         (i32.const 452984830)
        )
       )
       (block $label$6
        (br_if $label$6
         (i64.ne
          (i64.and
           (tee_local $1
            (i64.shr_u
             (get_local $1)
             (i64.const 8)
            )
           )
           (i64.const 255)
          )
          (i64.const 0)
         )
        )
        (loop $label$7
         (br_if $label$4
          (i64.ne
           (i64.and
            (tee_local $1
             (i64.shr_u
              (get_local $1)
              (i64.const 8)
             )
            )
            (i64.const 255)
           )
           (i64.const 0)
          )
         )
         (br_if $label$7
          (i32.lt_s
           (tee_local $8
            (i32.add
             (get_local $8)
             (i32.const 1)
            )
           )
           (i32.const 7)
          )
         )
        )
       )
       (set_local $7
        (i32.const 1)
       )
       (br_if $label$5
        (i32.lt_s
         (tee_local $8
          (i32.add
           (get_local $8)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (call $eosio_assert
      (get_local $7)
      (i32.const 32)
     )
     (i32.store offset=16
      (get_local $0)
      (i32.add
       (get_local $9)
       (i32.const 8)
      )
     )
     (i64.store
      (tee_local $8
       (i32.add
        (get_local $0)
        (i32.const 8)
       )
      )
      (i64.load
       (i32.add
        (get_local $2)
        (i32.const 8)
       )
      )
     )
     (i64.store
      (get_local $0)
      (i64.load
       (get_local $2)
      )
     )
     (call $eosio_assert
      (i32.const 1)
      (i32.const 304)
     )
     (drop
      (call $memcpy
       (i32.add
        (get_local $9)
        (i32.const 64)
       )
       (get_local $0)
       (i32.const 8)
      )
     )
     (call $eosio_assert
      (i32.const 1)
      (i32.const 304)
     )
     (drop
      (call $memcpy
       (i32.or
        (i32.add
         (get_local $9)
         (i32.const 64)
        )
        (i32.const 8)
       )
       (get_local $5)
       (i32.const 8)
      )
     )
     (i32.store offset=20
      (get_local $0)
      (tee_local $2
       (call $db_store_i64
        (i64.load
         (i32.add
          (i32.add
           (get_local $9)
           (i32.const 8)
          )
          (i32.const 8)
         )
        )
        (i64.const 3607749779137757184)
        (get_local $3)
        (tee_local $1
         (i64.shr_u
          (i64.load
           (get_local $8)
          )
          (i64.const 8)
         )
        )
        (i32.add
         (get_local $9)
         (i32.const 64)
        )
        (i32.const 16)
       )
      )
     )
     (block $label$8
      (br_if $label$8
       (i64.lt_u
        (get_local $1)
        (i64.load
         (tee_local $7
          (i32.add
           (i32.add
            (get_local $9)
            (i32.const 8)
           )
           (i32.const 16)
          )
         )
        )
       )
      )
      (i64.store
       (get_local $7)
       (i64.add
        (get_local $1)
        (i64.const 1)
       )
      )
     )
     (i32.store offset=56
      (get_local $9)
      (get_local $0)
     )
     (i64.store offset=64
      (get_local $9)
      (tee_local $1
       (i64.shr_u
        (i64.load
         (get_local $8)
        )
        (i64.const 8)
       )
      )
     )
     (i32.store offset=52
      (get_local $9)
      (get_local $2)
     )
     (block $label$9
      (block $label$10
       (br_if $label$10
        (i32.ge_u
         (tee_local $8
          (i32.load
           (tee_local $7
            (i32.add
             (get_local $9)
             (i32.const 36)
            )
           )
          )
         )
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const 40)
          )
         )
        )
       )
       (i64.store offset=8
        (get_local $8)
        (get_local $1)
       )
       (i32.store offset=16
        (get_local $8)
        (get_local $2)
       )
       (i32.store offset=56
        (get_local $9)
        (i32.const 0)
       )
       (i32.store
        (get_local $8)
        (get_local $0)
       )
       (i32.store
        (get_local $7)
        (i32.add
         (get_local $8)
         (i32.const 24)
        )
       )
       (br $label$9)
      )
      (call $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_5token7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
       (i32.add
        (get_local $9)
        (i32.const 32)
       )
       (i32.add
        (get_local $9)
        (i32.const 56)
       )
       (i32.add
        (get_local $9)
        (i32.const 64)
       )
       (i32.add
        (get_local $9)
        (i32.const 52)
       )
      )
     )
     (set_local $8
      (i32.load offset=56
       (get_local $9)
      )
     )
     (i32.store offset=56
      (get_local $9)
      (i32.const 0)
     )
     (br_if $label$2
      (i32.eqz
       (get_local $8)
      )
     )
     (call $_ZdlPv
      (get_local $8)
     )
    )
    (br_if $label$0
     (i32.eqz
      (tee_local $2
       (i32.load offset=32
        (get_local $9)
       )
      )
     )
    )
   )
   (block $label$11
    (block $label$12
     (br_if $label$12
      (i32.eq
       (tee_local $8
        (i32.load
         (tee_local $7
          (i32.add
           (get_local $9)
           (i32.const 36)
          )
         )
        )
       )
       (get_local $2)
      )
     )
     (loop $label$13
      (set_local $0
       (i32.load
        (tee_local $8
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $8)
       (i32.const 0)
      )
      (block $label$14
       (br_if $label$14
        (i32.eqz
         (get_local $0)
        )
       )
       (call $_ZdlPv
        (get_local $0)
       )
      )
      (br_if $label$13
       (i32.ne
        (get_local $2)
        (get_local $8)
       )
      )
     )
     (set_local $8
      (i32.load
       (i32.add
        (get_local $9)
        (i32.const 32)
       )
      )
     )
     (br $label$11)
    )
    (set_local $8
     (get_local $2)
    )
   )
   (i32.store
    (get_local $7)
    (get_local $2)
   )
   (call $_ZdlPv
    (get_local $8)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 80)
   )
  )
 )
 (func $_ZN5eosio15dispatch_inlineIJyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEEEEvyyNS2_6vectorINS_16permission_levelENS6_ISA_EEEENS2_5tupleIJDpT_EEE (param $0 i64) (param $1 i64) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i32.store offset=16
   (get_local $9)
   (i32.const 0)
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (set_local $6
   (i32.const 0)
  )
  (set_local $7
   (i32.const 0)
  )
  (set_local $8
   (i32.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $5
       (i32.shr_s
        (tee_local $4
         (i32.sub
          (i32.load offset=4
           (get_local $2)
          )
          (i32.load
           (get_local $2)
          )
         )
        )
        (i32.const 4)
       )
      )
     )
    )
    (br_if $label$0
     (i32.ge_u
      (get_local $5)
      (i32.const 268435456)
     )
    )
    (i32.store
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
     (tee_local $6
      (i32.add
       (tee_local $8
        (call $_Znwj
         (get_local $4)
        )
       )
       (i32.shl
        (get_local $5)
        (i32.const 4)
       )
      )
     )
    )
    (i32.store offset=8
     (get_local $9)
     (get_local $8)
    )
    (i32.store offset=12
     (get_local $9)
     (get_local $8)
    )
    (block $label$2
     (br_if $label$2
      (i32.lt_s
       (tee_local $2
        (i32.sub
         (i32.load
          (i32.add
           (get_local $2)
           (i32.const 4)
          )
         )
         (tee_local $7
          (i32.load
           (get_local $2)
          )
         )
        )
       )
       (i32.const 1)
      )
     )
     (drop
      (call $memcpy
       (get_local $8)
       (get_local $7)
       (get_local $2)
      )
     )
     (i32.store offset=12
      (get_local $9)
      (tee_local $7
       (i32.add
        (get_local $8)
        (get_local $2)
       )
      )
     )
     (br $label$1)
    )
    (set_local $7
     (get_local $8)
    )
   )
   (i32.store
    (i32.add
     (get_local $9)
     (i32.const 44)
    )
    (get_local $7)
   )
   (i64.store offset=32
    (get_local $9)
    (get_local $1)
   )
   (i32.store
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $9)
     (i32.const 48)
    )
    (get_local $6)
   )
   (i64.store offset=24
    (get_local $9)
    (get_local $0)
   )
   (i32.store offset=40
    (get_local $9)
    (get_local $8)
   )
   (i64.store offset=8
    (get_local $9)
    (i64.const 0)
   )
   (i32.store offset=52
    (get_local $9)
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i32.const 32)
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i32.const 36)
    )
    (i32.const 0)
   )
   (set_local $8
    (i32.add
     (tee_local $2
      (select
       (i32.load
        (i32.add
         (get_local $3)
         (i32.const 36)
        )
       )
       (i32.shr_u
        (tee_local $8
         (i32.load8_u offset=32
          (get_local $3)
         )
        )
        (i32.const 1)
       )
       (i32.and
        (get_local $8)
        (i32.const 1)
       )
      )
     )
     (i32.const 32)
    )
   )
   (set_local $0
    (i64.extend_u/i32
     (get_local $2)
    )
   )
   (set_local $2
    (i32.add
     (get_local $9)
     (i32.const 52)
    )
   )
   (loop $label$3
    (set_local $8
     (i32.add
      (get_local $8)
      (i32.const 1)
     )
    )
    (br_if $label$3
     (i64.ne
      (tee_local $0
       (i64.shr_u
        (get_local $0)
        (i64.const 7)
       )
      )
      (i64.const 0)
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eqz
       (get_local $8)
      )
     )
     (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
      (get_local $2)
      (get_local $8)
     )
     (set_local $2
      (i32.load
       (i32.add
        (get_local $9)
        (i32.const 56)
       )
      )
     )
     (set_local $8
      (i32.load
       (i32.add
        (get_local $9)
        (i32.const 52)
       )
      )
     )
     (br $label$4)
    )
    (set_local $2
     (i32.const 0)
    )
    (set_local $8
     (i32.const 0)
    )
   )
   (i32.store offset=84
    (get_local $9)
    (get_local $8)
   )
   (i32.store offset=80
    (get_local $9)
    (get_local $8)
   )
   (i32.store offset=88
    (get_local $9)
    (get_local $2)
   )
   (i32.store offset=64
    (get_local $9)
    (i32.add
     (get_local $9)
     (i32.const 80)
    )
   )
   (i32.store offset=72
    (get_local $9)
    (get_local $3)
   )
   (call $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorIKNSt3__15tupleIJyyN5eosio5assetENS6_12basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEEEELi0EEEZNS8_lsINS8_10datastreamIPcEEJyyS9_SF_EEERT_SO_RKNS7_IJDpT0_EEEEUlRKSN_E_EEvSV_RKT0_
    (i32.add
     (get_local $9)
     (i32.const 72)
    )
    (i32.add
     (get_local $9)
     (i32.const 64)
    )
   )
   (call $_ZN5eosio4packINS_6actionEEENSt3__16vectorIcNS2_9allocatorIcEEEERKT_
    (i32.add
     (get_local $9)
     (i32.const 80)
    )
    (i32.add
     (get_local $9)
     (i32.const 24)
    )
   )
   (call $send_inline
    (tee_local $8
     (i32.load offset=80
      (get_local $9)
     )
    )
    (i32.sub
     (i32.load offset=84
      (get_local $9)
     )
     (get_local $8)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.eqz
      (tee_local $8
       (i32.load offset=80
        (get_local $9)
       )
      )
     )
    )
    (i32.store offset=84
     (get_local $9)
     (get_local $8)
    )
    (call $_ZdlPv
     (get_local $8)
    )
   )
   (block $label$7
    (br_if $label$7
     (i32.eqz
      (tee_local $8
       (i32.load offset=52
        (get_local $9)
       )
      )
     )
    )
    (i32.store
     (i32.add
      (get_local $9)
      (i32.const 56)
     )
     (get_local $8)
    )
    (call $_ZdlPv
     (get_local $8)
    )
   )
   (block $label$8
    (br_if $label$8
     (i32.eqz
      (tee_local $8
       (i32.load offset=40
        (get_local $9)
       )
      )
     )
    )
    (i32.store
     (i32.add
      (get_local $9)
      (i32.const 44)
     )
     (get_local $8)
    )
    (call $_ZdlPv
     (get_local $8)
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.eqz
      (tee_local $8
       (i32.load offset=8
        (get_local $9)
       )
      )
     )
    )
    (i32.store offset=12
     (get_local $9)
     (get_local $8)
    )
    (call $_ZdlPv
     (get_local $8)
    )
   )
   (i32.store offset=4
    (i32.const 0)
    (i32.add
     (get_local $9)
     (i32.const 96)
    )
   )
   (return)
  )
  (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
  )
  (unreachable)
 )
 (func $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (br_if $label$4
        (i32.ge_u
         (i32.sub
          (tee_local $2
           (i32.load offset=8
            (get_local $0)
           )
          )
          (tee_local $6
           (i32.load offset=4
            (get_local $0)
           )
          )
         )
         (get_local $1)
        )
       )
       (br_if $label$2
        (i32.le_s
         (tee_local $4
          (i32.add
           (tee_local $3
            (i32.sub
             (get_local $6)
             (tee_local $5
              (i32.load
               (get_local $0)
              )
             )
            )
           )
           (get_local $1)
          )
         )
         (i32.const -1)
        )
       )
       (set_local $6
        (i32.const 2147483647)
       )
       (block $label$5
        (br_if $label$5
         (i32.gt_u
          (tee_local $2
           (i32.sub
            (get_local $2)
            (get_local $5)
           )
          )
          (i32.const 1073741822)
         )
        )
        (br_if $label$3
         (i32.eqz
          (tee_local $6
           (select
            (get_local $4)
            (tee_local $6
             (i32.shl
              (get_local $2)
              (i32.const 1)
             )
            )
            (i32.lt_u
             (get_local $6)
             (get_local $4)
            )
           )
          )
         )
        )
       )
       (set_local $2
        (call $_Znwj
         (get_local $6)
        )
       )
       (br $label$1)
      )
      (set_local $0
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
      (loop $label$6
       (i32.store8
        (get_local $6)
        (i32.const 0)
       )
       (i32.store
        (get_local $0)
        (tee_local $6
         (i32.add
          (i32.load
           (get_local $0)
          )
          (i32.const 1)
         )
        )
       )
       (br_if $label$6
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const -1)
         )
        )
       )
       (br $label$0)
      )
     )
     (set_local $6
      (i32.const 0)
     )
     (set_local $2
      (i32.const 0)
     )
     (br $label$1)
    )
    (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
     (get_local $0)
    )
    (unreachable)
   )
   (set_local $4
    (i32.add
     (get_local $2)
     (get_local $6)
    )
   )
   (set_local $6
    (tee_local $5
     (i32.add
      (get_local $2)
      (get_local $3)
     )
    )
   )
   (loop $label$7
    (i32.store8
     (get_local $6)
     (i32.const 0)
    )
    (set_local $6
     (i32.add
      (get_local $6)
      (i32.const 1)
     )
    )
    (br_if $label$7
     (tee_local $1
      (i32.add
       (get_local $1)
       (i32.const -1)
      )
     )
    )
   )
   (set_local $5
    (i32.sub
     (get_local $5)
     (tee_local $2
      (i32.sub
       (i32.load
        (tee_local $3
         (i32.add
          (get_local $0)
          (i32.const 4)
         )
        )
       )
       (tee_local $1
        (i32.load
         (get_local $0)
        )
       )
      )
     )
    )
   )
   (block $label$8
    (br_if $label$8
     (i32.lt_s
      (get_local $2)
      (i32.const 1)
     )
    )
    (drop
     (call $memcpy
      (get_local $5)
      (get_local $1)
      (get_local $2)
     )
    )
    (set_local $1
     (i32.load
      (get_local $0)
     )
    )
   )
   (i32.store
    (get_local $0)
    (get_local $5)
   )
   (i32.store
    (get_local $3)
    (get_local $6)
   )
   (i32.store
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (get_local $4)
   )
   (br_if $label$0
    (i32.eqz
     (get_local $1)
    )
   )
   (call $_ZdlPv
    (get_local $1)
   )
   (return)
  )
 )
 (func $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorIKNSt3__15tupleIJyyN5eosio5assetENS6_12basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEEEELi0EEEZNS8_lsINS8_10datastreamIPcEEJyyS9_SF_EEERT_SO_RKNS7_IJDpT0_EEEEUlRKSN_E_EEvSV_RKT0_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $3)
    )
    (get_local $2)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $3)
    )
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $3)
    )
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $3)
    )
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE
    (i32.load
     (get_local $1)
    )
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
   )
  )
 )
 (func $_ZN5eosio4packINS_6actionEEENSt3__16vectorIcNS2_9allocatorIcEEEERKT_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=8
   (get_local $0)
   (i32.const 0)
  )
  (i64.store align=4
   (get_local $0)
   (i64.const 0)
  )
  (set_local $5
   (i32.const 16)
  )
  (set_local $2
   (i32.add
    (get_local $1)
    (i32.const 16)
   )
  )
  (set_local $6
   (i64.extend_u/i32
    (i32.shr_s
     (tee_local $4
      (i32.sub
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $1)
          (i32.const 20)
         )
        )
       )
       (tee_local $3
        (i32.load offset=16
         (get_local $1)
        )
       )
      )
     )
     (i32.const 4)
    )
   )
  )
  (loop $label$0
   (set_local $5
    (i32.add
     (get_local $5)
     (i32.const 1)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $6
      (i64.shr_u
       (get_local $6)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eq
     (get_local $3)
     (get_local $7)
    )
   )
   (set_local $5
    (i32.add
     (i32.and
      (get_local $4)
      (i32.const -16)
     )
     (get_local $5)
    )
   )
  )
  (set_local $5
   (i32.sub
    (i32.sub
     (tee_local $7
      (i32.load offset=28
       (get_local $1)
      )
     )
     (get_local $5)
    )
    (tee_local $3
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 32)
      )
     )
    )
   )
  )
  (set_local $4
   (i32.add
    (get_local $1)
    (i32.const 28)
   )
  )
  (set_local $6
   (i64.extend_u/i32
    (i32.sub
     (get_local $3)
     (get_local $7)
    )
   )
  )
  (loop $label$2
   (set_local $5
    (i32.add
     (get_local $5)
     (i32.const -1)
    )
   )
   (br_if $label$2
    (i64.ne
     (tee_local $6
      (i64.shr_u
       (get_local $6)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (block $label$3
   (block $label$4
    (br_if $label$4
     (i32.eqz
      (get_local $5)
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $0)
     (i32.sub
      (i32.const 0)
      (get_local $5)
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $5
     (i32.load
      (get_local $0)
     )
    )
    (br $label$3)
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (i32.store
   (get_local $8)
   (get_local $5)
  )
  (i32.store offset=8
   (get_local $8)
   (get_local $7)
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (get_local $7)
     (get_local $5)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (get_local $5)
    (get_local $1)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (get_local $7)
     (tee_local $0
      (i32.add
       (get_local $5)
       (i32.const 8)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $8)
   (i32.add
    (get_local $5)
    (i32.const 16)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__16vectorIcNS6_9allocatorIcEEEE
    (call $_ZN5eosiolsINS_10datastreamIPcEENS_16permission_levelEEERT_S6_RKNSt3__16vectorIT0_NS7_9allocatorIS9_EEEE
     (get_local $8)
     (get_local $2)
    )
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEENS_16permission_levelEEERT_S6_RKNSt3__16vectorIT0_NS7_9allocatorIS9_EEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $4
   (i64.extend_u/i32
    (i32.shr_s
     (i32.sub
      (i32.load offset=4
       (get_local $1)
      )
      (i32.load
       (get_local $1)
      )
     )
     (i32.const 4)
    )
   )
  )
  (set_local $5
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $2
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (loop $label$0
   (set_local $3
    (i32.wrap/i64
     (get_local $4)
    )
   )
   (i32.store8 offset=15
    (get_local $7)
    (i32.or
     (i32.shl
      (tee_local $6
       (i64.ne
        (tee_local $4
         (i64.shr_u
          (get_local $4)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $3)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $2)
      )
      (get_local $5)
     )
     (i32.const 0)
    )
    (i32.const 304)
   )
   (drop
    (call $memcpy
     (i32.load
      (tee_local $3
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
     )
     (i32.add
      (get_local $7)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $3)
    (tee_local $5
     (i32.add
      (i32.load
       (get_local $3)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $6)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eq
     (tee_local $6
      (i32.load
       (get_local $1)
      )
     )
     (tee_local $1
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
     )
    )
   )
   (set_local $3
    (i32.add
     (get_local $0)
     (i32.const 4)
    )
   )
   (loop $label$2
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (tee_local $2
         (i32.add
          (get_local $0)
          (i32.const 8)
         )
        )
       )
       (get_local $5)
      )
      (i32.const 7)
     )
     (i32.const 304)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $3)
      )
      (get_local $6)
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $5
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (call $eosio_assert
     (i32.gt_s
      (i32.sub
       (i32.load
        (get_local $2)
       )
       (get_local $5)
      )
      (i32.const 7)
     )
     (i32.const 304)
    )
    (drop
     (call $memcpy
      (i32.load
       (get_local $3)
      )
      (i32.add
       (get_local $6)
       (i32.const 8)
      )
      (i32.const 8)
     )
    )
    (i32.store
     (get_local $3)
     (tee_local $5
      (i32.add
       (i32.load
        (get_local $3)
       )
       (i32.const 8)
      )
     )
    )
    (br_if $label$2
     (i32.ne
      (tee_local $6
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__16vectorIcNS6_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i64.extend_u/i32
    (i32.sub
     (i32.load offset=4
      (get_local $1)
     )
     (i32.load
      (get_local $1)
     )
    )
   )
  )
  (set_local $6
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $4
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $5
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (set_local $2
    (i32.wrap/i64
     (get_local $7)
    )
   )
   (i32.store8 offset=15
    (get_local $8)
    (i32.or
     (i32.shl
      (tee_local $3
       (i64.ne
        (tee_local $7
         (i64.shr_u
          (get_local $7)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $2)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $4)
      )
      (get_local $6)
     )
     (i32.const 0)
    )
    (i32.const 304)
   )
   (drop
    (call $memcpy
     (i32.load
      (get_local $5)
     )
     (i32.add
      (get_local $8)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $5)
    (tee_local $6
     (i32.add
      (i32.load
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $3)
   )
  )
  (call $eosio_assert
   (i32.ge_s
    (i32.sub
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
     (get_local $6)
    )
    (tee_local $5
     (i32.sub
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 4)
       )
      )
      (tee_local $2
       (i32.load
        (get_local $1)
       )
      )
     )
    )
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load
     (tee_local $6
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (get_local $2)
    (get_local $5)
   )
  )
  (i32.store
   (get_local $6)
   (i32.add
    (i32.load
     (get_local $6)
    )
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i64.extend_u/i32
    (select
     (i32.load offset=4
      (get_local $1)
     )
     (i32.shr_u
      (tee_local $5
       (i32.load8_u
        (get_local $1)
       )
      )
      (i32.const 1)
     )
     (i32.and
      (get_local $5)
      (i32.const 1)
     )
    )
   )
  )
  (set_local $6
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $4
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $5
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (set_local $2
    (i32.wrap/i64
     (get_local $7)
    )
   )
   (i32.store8 offset=15
    (get_local $8)
    (i32.or
     (i32.shl
      (tee_local $3
       (i64.ne
        (tee_local $7
         (i64.shr_u
          (get_local $7)
          (i64.const 7)
         )
        )
        (i64.const 0)
       )
      )
      (i32.const 7)
     )
     (i32.and
      (get_local $2)
      (i32.const 127)
     )
    )
   )
   (call $eosio_assert
    (i32.gt_s
     (i32.sub
      (i32.load
       (get_local $4)
      )
      (get_local $6)
     )
     (i32.const 0)
    )
    (i32.const 304)
   )
   (drop
    (call $memcpy
     (i32.load
      (get_local $5)
     )
     (i32.add
      (get_local $8)
      (i32.const 15)
     )
     (i32.const 1)
    )
   )
   (i32.store
    (get_local $5)
    (tee_local $6
     (i32.add
      (i32.load
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (br_if $label$0
    (get_local $3)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (tee_local $5
      (select
       (i32.load
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
       )
       (i32.shr_u
        (tee_local $5
         (i32.load8_u
          (get_local $1)
         )
        )
        (i32.const 1)
       )
       (tee_local $2
        (i32.and
         (get_local $5)
         (i32.const 1)
        )
       )
      )
     )
    )
   )
   (set_local $3
    (i32.load offset=8
     (get_local $1)
    )
   )
   (call $eosio_assert
    (i32.ge_s
     (i32.sub
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 8)
       )
      )
      (get_local $6)
     )
     (get_local $5)
    )
    (i32.const 304)
   )
   (drop
    (call $memcpy
     (i32.load
      (tee_local $6
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
     )
     (select
      (get_local $3)
      (i32.add
       (get_local $1)
       (i32.const 1)
      )
      (get_local $2)
     )
     (get_local $5)
    )
   )
   (i32.store
    (get_local $6)
    (i32.add
     (i32.load
      (get_local $6)
     )
     (get_local $5)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i64)
  (local $9 i32)
  (local $10 i32)
  (set_local $9
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $10)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $3)
     )
    )
    (set_local $5
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $7
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 384)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.le_u
       (get_local $7)
       (i32.const 512)
      )
     )
     (drop
      (call $db_get_i64
       (get_local $1)
       (tee_local $3
        (call $malloc
         (get_local $7)
        )
       )
       (get_local $7)
      )
     )
     (call $free
      (get_local $3)
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $3
      (i32.sub
       (get_local $10)
       (i32.and
        (i32.add
         (get_local $7)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
    (drop
     (call $db_get_i64
      (get_local $1)
      (get_local $3)
      (get_local $7)
     )
    )
   )
   (set_local $2
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
   )
   (i64.store offset=8
    (tee_local $5
     (call $_Znwj
      (i32.const 32)
     )
    )
    (i64.const 1398362884)
   )
   (i64.store
    (get_local $5)
    (i64.const 0)
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 320)
   )
   (set_local $10
    (i32.add
     (get_local $5)
     (i32.const 8)
    )
   )
   (set_local $8
    (i64.const 5462355)
   )
   (set_local $6
    (i32.const 0)
   )
   (block $label$6
    (block $label$7
     (loop $label$8
      (br_if $label$7
       (i32.gt_u
        (i32.add
         (i32.shl
          (i32.wrap/i64
           (get_local $8)
          )
          (i32.const 24)
         )
         (i32.const -1073741825)
        )
        (i32.const 452984830)
       )
      )
      (block $label$9
       (br_if $label$9
        (i64.ne
         (i64.and
          (tee_local $8
           (i64.shr_u
            (get_local $8)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (loop $label$10
        (br_if $label$7
         (i64.ne
          (i64.and
           (tee_local $8
            (i64.shr_u
             (get_local $8)
             (i64.const 8)
            )
           )
           (i64.const 255)
          )
          (i64.const 0)
         )
        )
        (br_if $label$10
         (i32.lt_s
          (tee_local $6
           (i32.add
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.const 7)
         )
        )
       )
      )
      (set_local $4
       (i32.const 1)
      )
      (br_if $label$8
       (i32.lt_s
        (tee_local $6
         (i32.add
          (get_local $6)
          (i32.const 1)
         )
        )
        (i32.const 7)
       )
      )
      (br $label$6)
     )
    )
    (set_local $4
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (get_local $4)
    (i32.const 32)
   )
   (i32.store offset=16
    (get_local $5)
    (get_local $0)
   )
   (call $eosio_assert
    (i32.gt_u
     (get_local $7)
     (i32.const 7)
    )
    (i32.const 416)
   )
   (drop
    (call $memcpy
     (get_local $5)
     (get_local $3)
     (i32.const 8)
    )
   )
   (call $eosio_assert
    (i32.ne
     (i32.and
      (get_local $7)
      (i32.const -8)
     )
     (i32.const 8)
    )
    (i32.const 416)
   )
   (drop
    (call $memcpy
     (get_local $10)
     (i32.add
      (get_local $3)
      (i32.const 8)
     )
     (i32.const 8)
    )
   )
   (i32.store offset=20
    (get_local $5)
    (get_local $1)
   )
   (i32.store offset=24
    (get_local $9)
    (get_local $5)
   )
   (i64.store offset=16
    (get_local $9)
    (tee_local $8
     (i64.shr_u
      (i64.load
       (i32.add
        (get_local $5)
        (i32.const 8)
       )
      )
      (i64.const 8)
     )
    )
   )
   (i32.store offset=12
    (get_local $9)
    (tee_local $7
     (i32.load offset=20
      (get_local $5)
     )
    )
   )
   (block $label$11
    (block $label$12
     (br_if $label$12
      (i32.ge_u
       (tee_local $6
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $6)
      (get_local $8)
     )
     (i32.store offset=16
      (get_local $6)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $9)
      (i32.const 0)
     )
     (i32.store
      (get_local $6)
      (get_local $5)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $6)
       (i32.const 24)
      )
     )
     (br $label$11)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_5token7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_
     (get_local $2)
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
     (i32.add
      (get_local $9)
      (i32.const 12)
     )
    )
   )
   (set_local $6
    (i32.load offset=24
     (get_local $9)
    )
   )
   (i32.store offset=24
    (get_local $9)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
  )
  (get_local $5)
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy3607749779137757184ENS1_5token7accountEJEE8item_ptrENS_9allocatorIS6_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINS5_4itemENS_14default_deleteISC_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$10
   (br_if $label$10
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZN5eosio5token8transferEyyNS_5assetENSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEE (type $FUNCSIG$vijjii) (param $0 i32) (param $1 i64) (param $2 i64) (param $3 i32) (param $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i64)
  (local $9 i64)
  (local $10 i64)
  (local $11 i64)
  (local $12 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $12
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (call $eosio_assert
   (i64.ne
    (get_local $1)
    (get_local $2)
   )
   (i32.const 1008)
  )
  (call $require_auth
   (get_local $1)
  )
  (set_local $9
   (i64.const 0)
  )
  (set_local $8
   (i64.const 59)
  )
  (set_local $7
   (i32.const 16)
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $9)
          (i64.const 5)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $5
             (i32.load8_s
              (get_local $7)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $5
         (i32.add
          (get_local $5)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $11
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $9)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $5
       (select
        (i32.add
         (get_local $5)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $5)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $11
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $5)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $11
     (i64.shl
      (i64.and
       (get_local $11)
       (i64.const 31)
      )
      (i64.and
       (get_local $8)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $7)
     (i32.const 1)
    )
   )
   (set_local $9
    (i64.add
     (get_local $9)
     (i64.const 1)
    )
   )
   (set_local $10
    (i64.or
     (get_local $11)
     (get_local $10)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $8
      (i64.add
       (get_local $8)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (call $require_auth2
   (get_local $1)
   (get_local $10)
  )
  (drop
   (call $has_auth
    (get_local $1)
   )
  )
  (call $eosio_assert
   (call $is_account
    (get_local $2)
   )
   (i32.const 1040)
  )
  (set_local $7
   (i32.const 100)
  )
  (block $label$6
   (block $label$7
    (block $label$8
     (block $label$9
      (block $label$10
       (block $label$11
        (block $label$12
         (br_if $label$12
          (i32.gt_u
           (tee_local $5
            (i32.and
             (i32.wrap/i64
              (get_local $1)
             )
             (i32.const 255)
            )
           )
           (i32.const 32)
          )
         )
         (block $label$13
          (br_table $label$13 $label$11 $label$6 $label$6 $label$6 $label$10 $label$6 $label$6 $label$6 $label$6 $label$9 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$6 $label$8 $label$13
           (get_local $5)
          )
         )
         (set_local $7
          (i32.const 1)
         )
         (br $label$6)
        )
        (br_if $label$7
         (i32.eq
          (get_local $5)
          (i32.const 64)
         )
        )
        (br_if $label$6
         (i32.ne
          (get_local $5)
          (i32.const 99)
         )
        )
        (set_local $7
         (i32.const 62)
        )
        (br $label$6)
       )
       (set_local $7
        (i32.const 12)
       )
       (br $label$6)
      )
      (set_local $7
       (i32.const 14)
      )
      (br $label$6)
     )
     (set_local $7
      (i32.const 41)
     )
     (br $label$6)
    )
    (set_local $7
     (i32.const 31)
    )
    (br $label$6)
   )
   (set_local $7
    (i32.const 71)
   )
  )
  (call $eosio_assert
   (get_local $7)
   (i32.const 288)
  )
  (set_local $7
   (i32.const 100)
  )
  (block $label$14
   (block $label$15
    (block $label$16
     (block $label$17
      (block $label$18
       (block $label$19
        (block $label$20
         (br_if $label$20
          (i32.gt_u
           (tee_local $5
            (i32.and
             (i32.wrap/i64
              (get_local $2)
             )
             (i32.const 255)
            )
           )
           (i32.const 32)
          )
         )
         (block $label$21
          (br_table $label$21 $label$19 $label$14 $label$14 $label$14 $label$18 $label$14 $label$14 $label$14 $label$14 $label$17 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$14 $label$16 $label$21
           (get_local $5)
          )
         )
         (set_local $7
          (i32.const 1)
         )
         (br $label$14)
        )
        (br_if $label$15
         (i32.eq
          (get_local $5)
          (i32.const 64)
         )
        )
        (br_if $label$14
         (i32.ne
          (get_local $5)
          (i32.const 99)
         )
        )
        (set_local $7
         (i32.const 62)
        )
        (br $label$14)
       )
       (set_local $7
        (i32.const 12)
       )
       (br $label$14)
      )
      (set_local $7
       (i32.const 14)
      )
      (br $label$14)
     )
     (set_local $7
      (i32.const 41)
     )
     (br $label$14)
    )
    (set_local $7
     (i32.const 31)
    )
    (br $label$14)
   )
   (set_local $7
    (i32.const 71)
   )
  )
  (call $eosio_assert
   (get_local $7)
   (i32.const 288)
  )
  (set_local $11
   (i64.load offset=8
    (get_local $3)
   )
  )
  (set_local $5
   (i32.const 0)
  )
  (i32.store
   (i32.add
    (get_local $12)
    (i32.const 104)
   )
   (i32.const 0)
  )
  (i64.store offset=80
   (get_local $12)
   (tee_local $9
    (i64.shr_u
     (get_local $11)
     (i64.const 8)
    )
   )
  )
  (i64.store offset=88
   (get_local $12)
   (i64.const -1)
  )
  (i64.store offset=96
   (get_local $12)
   (i64.const 0)
  )
  (i64.store offset=72
   (get_local $12)
   (i64.load
    (get_local $0)
   )
  )
  (set_local $6
   (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE3getEyPKc
    (i32.add
     (get_local $12)
     (i32.const 72)
    )
    (get_local $9)
    (i32.const 1072)
   )
  )
  (call $require_recipient
   (get_local $1)
  )
  (call $require_recipient
   (get_local $2)
  )
  (block $label$22
   (br_if $label$22
    (i64.gt_u
     (i64.add
      (tee_local $8
       (i64.load
        (get_local $3)
       )
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $7
    (i32.const 0)
   )
   (block $label$23
    (loop $label$24
     (br_if $label$23
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $9)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$25
      (br_if $label$25
       (i64.ne
        (i64.and
         (tee_local $9
          (i64.shr_u
           (get_local $9)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$26
       (br_if $label$23
        (i64.ne
         (i64.and
          (tee_local $9
           (i64.shr_u
            (get_local $9)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$26
        (i32.lt_s
         (tee_local $7
          (i32.add
           (get_local $7)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $5
      (i32.const 1)
     )
     (br_if $label$24
      (i32.lt_s
       (tee_local $7
        (i32.add
         (get_local $7)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$22)
    )
   )
   (set_local $5
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $5)
   (i32.const 528)
  )
  (call $eosio_assert
   (i64.gt_s
    (get_local $8)
    (i64.const 0)
   )
   (i32.const 1104)
  )
  (call $eosio_assert
   (i64.eq
    (get_local $11)
    (i64.load offset=8
     (get_local $6)
    )
   )
   (i32.const 592)
  )
  (block $label$27
   (block $label$28
    (br_if $label$28
     (i32.and
      (tee_local $7
       (i32.load8_u
        (get_local $4)
       )
      )
      (i32.const 1)
     )
    )
    (set_local $7
     (i32.shr_u
      (get_local $7)
      (i32.const 1)
     )
    )
    (br $label$27)
   )
   (set_local $7
    (i32.load offset=4
     (get_local $4)
    )
   )
  )
  (call $eosio_assert
   (i32.lt_u
    (get_local $7)
    (i32.const 257)
   )
   (i32.const 432)
  )
  (i64.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 56)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (tee_local $5
     (i32.add
      (get_local $3)
      (i32.const 8)
     )
    )
   )
  )
  (set_local $9
   (i64.load
    (get_local $3)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 24)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 56)
     )
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 24)
    )
    (i32.const 8)
   )
   (i32.load
    (get_local $7)
   )
  )
  (i64.store offset=56
   (get_local $12)
   (get_local $9)
  )
  (i32.store offset=28
   (get_local $12)
   (i32.load offset=60
    (get_local $12)
   )
  )
  (i32.store offset=24
   (get_local $12)
   (i32.load offset=56
    (get_local $12)
   )
  )
  (call $_ZN5eosio5token11sub_balanceEyNS_5assetE
   (get_local $0)
   (get_local $1)
   (i32.add
    (get_local $12)
    (i32.const 24)
   )
  )
  (i64.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 40)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (get_local $5)
   )
  )
  (set_local $9
   (i64.load
    (get_local $3)
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (i32.add
      (get_local $12)
      (i32.const 40)
     )
     (i32.const 12)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $12)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (i32.load
    (get_local $7)
   )
  )
  (i64.store offset=40
   (get_local $12)
   (get_local $9)
  )
  (i32.store offset=12
   (get_local $12)
   (i32.load offset=44
    (get_local $12)
   )
  )
  (i32.store offset=8
   (get_local $12)
   (i32.load offset=40
    (get_local $12)
   )
  )
  (call $_ZN5eosio5token11add_balanceEyNS_5assetEy
   (get_local $0)
   (get_local $2)
   (i32.add
    (get_local $12)
    (i32.const 8)
   )
   (get_local $1)
  )
  (block $label$29
   (br_if $label$29
    (i32.eqz
     (tee_local $3
      (i32.load offset=96
       (get_local $12)
      )
     )
    )
   )
   (block $label$30
    (block $label$31
     (br_if $label$31
      (i32.eq
       (tee_local $7
        (i32.load
         (tee_local $0
          (i32.add
           (get_local $12)
           (i32.const 100)
          )
         )
        )
       )
       (get_local $3)
      )
     )
     (loop $label$32
      (set_local $5
       (i32.load
        (tee_local $7
         (i32.add
          (get_local $7)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $7)
       (i32.const 0)
      )
      (block $label$33
       (br_if $label$33
        (i32.eqz
         (get_local $5)
        )
       )
       (call $_ZdlPv
        (get_local $5)
       )
      )
      (br_if $label$32
       (i32.ne
        (get_local $3)
        (get_local $7)
       )
      )
     )
     (set_local $7
      (i32.load
       (i32.add
        (get_local $12)
        (i32.const 96)
       )
      )
     )
     (br $label$30)
    )
    (set_local $7
     (get_local $3)
    )
   )
   (i32.store
    (get_local $0)
    (get_local $3)
   )
   (call $_ZdlPv
    (get_local $7)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $12)
    (i32.const 112)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE3getEyPKc (param $0 i32) (param $1 i64) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.shr_u
       (i64.load offset=8
        (i32.load
         (get_local $6)
        )
       )
       (i64.const 8)
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=40
       (tee_local $6
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $0)
     )
     (i32.const 112)
    )
    (br $label$2)
   )
   (set_local $6
    (i32.const 0)
   )
   (br_if $label$2
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -4157508551318700032)
       (get_local $1)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=40
      (tee_local $6
       (call $_ZNK5eosio11multi_indexILy14289235522390851584ENS_5token14currency_statsEJEE31load_object_by_primary_iteratorEl
        (get_local $0)
        (get_local $5)
       )
      )
     )
     (get_local $0)
    )
    (i32.const 112)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $6)
    (i32.const 0)
   )
   (get_local $2)
  )
  (get_local $6)
 )
 (func $_ZN5eosio5token11sub_balanceEyNS_5assetE (param $0 i32) (param $1 i64) (param $2 i32)
  (local $3 i64)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $8)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=16
   (get_local $8)
   (get_local $1)
  )
  (i64.store offset=24
   (get_local $8)
   (i64.const -1)
  )
  (i64.store offset=32
   (get_local $8)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $8)
   (i64.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i64.ge_s
    (i64.load
     (tee_local $0
      (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE3getEyPKc
       (i32.add
        (get_local $8)
        (i32.const 8)
       )
       (i64.shr_u
        (tee_local $3
         (i64.load offset=8
          (get_local $2)
         )
        )
        (i64.const 8)
       )
       (i32.const 1136)
      )
     )
    )
    (tee_local $4
     (i64.load
      (get_local $2)
     )
    )
   )
   (i32.const 1168)
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i64.ne
       (get_local $4)
       (i64.load
        (get_local $0)
       )
      )
     )
     (call $_ZN5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE5eraseERKS2_
      (i32.add
       (get_local $8)
       (i32.const 8)
      )
      (get_local $0)
     )
     (br_if $label$1
      (tee_local $5
       (i32.load offset=32
        (get_local $8)
       )
      )
     )
     (br $label$0)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=16
       (get_local $0)
      )
      (i32.add
       (get_local $8)
       (i32.const 8)
      )
     )
     (i32.const 672)
    )
    (call $eosio_assert
     (i64.eq
      (i64.load offset=8
       (get_local $8)
      )
      (call $current_receiver)
     )
     (i32.const 720)
    )
    (call $eosio_assert
     (i64.eq
      (get_local $3)
      (tee_local $6
       (i64.load offset=8
        (get_local $0)
       )
      )
     )
     (i32.const 1200)
    )
    (i64.store
     (get_local $0)
     (tee_local $4
      (i64.sub
       (i64.load
        (get_local $0)
       )
       (get_local $4)
      )
     )
    )
    (call $eosio_assert
     (i64.gt_s
      (get_local $4)
      (i64.const -4611686018427387904)
     )
     (i32.const 1248)
    )
    (call $eosio_assert
     (i64.lt_s
      (i64.load
       (get_local $0)
      )
      (i64.const 4611686018427387904)
     )
     (i32.const 1280)
    )
    (call $eosio_assert
     (i64.eq
      (tee_local $4
       (i64.shr_u
        (get_local $6)
        (i64.const 8)
       )
      )
      (i64.shr_u
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const 8)
      )
     )
     (i32.const 896)
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 304)
    )
    (drop
     (call $memcpy
      (i32.add
       (get_local $8)
       (i32.const 48)
      )
      (get_local $0)
      (i32.const 8)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 304)
    )
    (drop
     (call $memcpy
      (i32.or
       (i32.add
        (get_local $8)
        (i32.const 48)
       )
       (i32.const 8)
      )
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
      (i32.const 8)
     )
    )
    (call $db_update_i64
     (i32.load offset=20
      (get_local $0)
     )
     (get_local $1)
     (i32.add
      (get_local $8)
      (i32.const 48)
     )
     (i32.const 16)
    )
    (block $label$3
     (br_if $label$3
      (i64.lt_u
       (get_local $4)
       (i64.load
        (tee_local $0
         (i32.add
          (i32.add
           (get_local $8)
           (i32.const 8)
          )
          (i32.const 16)
         )
        )
       )
      )
     )
     (i64.store
      (get_local $0)
      (i64.add
       (get_local $4)
       (i64.const 1)
      )
     )
    )
    (br_if $label$0
     (i32.eqz
      (tee_local $5
       (i32.load offset=32
        (get_local $8)
       )
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (tee_local $0
        (i32.load
         (tee_local $7
          (i32.add
           (get_local $8)
           (i32.const 36)
          )
         )
        )
       )
       (get_local $5)
      )
     )
     (loop $label$6
      (set_local $2
       (i32.load
        (tee_local $0
         (i32.add
          (get_local $0)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $0)
       (i32.const 0)
      )
      (block $label$7
       (br_if $label$7
        (i32.eqz
         (get_local $2)
        )
       )
       (call $_ZdlPv
        (get_local $2)
       )
      )
      (br_if $label$6
       (i32.ne
        (get_local $5)
        (get_local $0)
       )
      )
     )
     (set_local $0
      (i32.load
       (i32.add
        (get_local $8)
        (i32.const 32)
       )
      )
     )
     (br $label$4)
    )
    (set_local $0
     (get_local $5)
    )
   )
   (i32.store
    (get_local $7)
    (get_local $5)
   )
   (call $_ZdlPv
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 64)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE3getEyPKc (param $0 i32) (param $1 i64) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.shr_u
       (i64.load offset=8
        (i32.load
         (get_local $6)
        )
       )
       (i64.const 8)
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $5
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=16
       (tee_local $6
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $0)
     )
     (i32.const 112)
    )
    (br $label$2)
   )
   (set_local $6
    (i32.const 0)
   )
   (br_if $label$2
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const 3607749779137757184)
       (get_local $1)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=16
      (tee_local $6
       (call $_ZNK5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE31load_object_by_primary_iteratorEl
        (get_local $0)
        (get_local $5)
       )
      )
     )
     (get_local $0)
    )
    (i32.const 112)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $6)
    (i32.const 0)
   )
   (get_local $2)
  )
  (get_local $6)
 )
 (func $_ZN5eosio11multi_indexILy3607749779137757184ENS_5token7accountEJEE5eraseERKS2_ (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (call $eosio_assert
   (i32.eq
    (i32.load offset=16
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 1312)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 1360)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (tee_local $5
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $2
    (i64.load offset=8
     (get_local $1)
    )
   )
   (set_local $6
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $8
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.lt_u
      (i64.xor
       (i64.load offset=8
        (i32.load
         (get_local $8)
        )
       )
       (get_local $2)
      )
      (i64.const 256)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (set_local $8
     (tee_local $4
      (i32.add
       (get_local $8)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $6)
      )
      (i32.const -24)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $7)
    (get_local $3)
   )
   (i32.const 1424)
  )
  (set_local $8
   (i32.add
    (get_local $7)
    (i32.const -24)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (tee_local $4
       (i32.load
        (get_local $5)
       )
      )
     )
    )
    (set_local $3
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (loop $label$4
     (set_local $6
      (i32.load
       (tee_local $8
        (i32.add
         (get_local $7)
         (i32.const 24)
        )
       )
      )
     )
     (i32.store
      (get_local $8)
      (i32.const 0)
     )
     (set_local $4
      (i32.load
       (get_local $7)
      )
     )
     (i32.store
      (get_local $7)
      (get_local $6)
     )
     (block $label$5
      (br_if $label$5
       (i32.eqz
        (get_local $4)
       )
      )
      (call $_ZdlPv
       (get_local $4)
      )
     )
     (i32.store
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 40)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $7)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $7)
        (i32.const 32)
       )
      )
     )
     (set_local $7
      (get_local $8)
     )
     (br_if $label$4
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $3)
       )
       (i32.const -24)
      )
     )
    )
    (br_if $label$2
     (i32.eq
      (tee_local $7
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
      (get_local $8)
     )
    )
   )
   (loop $label$6
    (set_local $4
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$7
     (br_if $label$7
      (i32.eqz
       (get_local $4)
      )
     )
     (call $_ZdlPv
      (get_local $4)
     )
    )
    (br_if $label$6
     (i32.ne
      (get_local $8)
      (get_local $7)
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 28)
   )
   (get_local $8)
  )
  (call $db_remove_i64
   (i32.load offset=20
    (get_local $1)
   )
  )
 )
 (func $_ZN5eosio5token6testcbEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=32
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $3)
   (i64.const 0)
  )
  (i64.store
   (get_local $3)
   (i64.const 0)
  )
  (set_local $2
   (i32.const 100)
  )
  (loop $label$0
   (call $__ashlti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i32.const 56)
   )
   (call $__ashrti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i32.const 56)
   )
   (call $__lshlti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i32.const 56)
   )
   (call $__lshrti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i32.const 56)
   )
   (call $__divti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__udivti3
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__modti3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__umodti3
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__multi3
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__addtf3
    (get_local $3)
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__subtf3
    (get_local $3)
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__multf3
    (get_local $3)
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (call $__divtf3
    (get_local $3)
    (i64.const 12)
    (i64.const 34)
    (i64.const 56)
    (i64.const 78)
   )
   (drop
    (call $__eqtf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__netf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__getf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__gttf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__lttf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__letf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__cmptf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (drop
    (call $__unordtf2
     (i64.const 12)
     (i64.const 34)
     (i64.const 56)
     (i64.const 78)
    )
   )
   (call $__negtf2
    (get_local $3)
    (i64.const 12)
    (i64.const 34)
   )
   (call $__floatsitf
    (get_local $3)
    (i32.const 12)
   )
   (call $__floatunsitf
    (get_local $3)
    (i32.const 12)
   )
   (call $__floatditf
    (get_local $3)
    (i64.const 12)
   )
   (call $__floatunditf
    (get_local $3)
    (i64.const 12)
   )
   (drop
    (call $__floattidf
     (i64.const 12)
     (i64.const 34)
    )
   )
   (drop
    (call $__floatuntidf
     (i64.const 12)
     (i64.const 34)
    )
   )
   (drop
    (call $__floatsidf
     (i32.const 12)
    )
   )
   (call $__extendsftf2
    (get_local $3)
    (f32.const 12)
   )
   (call $__extenddftf2
    (get_local $3)
    (f64.const 12)
   )
   (call $__fixtfti
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (i64.const 12)
    (i64.const 34)
   )
   (drop
    (call $__fixtfdi
     (i64.const 12)
     (i64.const 34)
    )
   )
   (drop
    (call $__fixtfsi
     (i64.const 12)
     (i64.const 34)
    )
   )
   (call $__fixunstfti
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (i64.const 12)
    (i64.const 34)
   )
   (drop
    (call $__fixunstfdi
     (i64.const 12)
     (i64.const 34)
    )
   )
   (drop
    (call $__fixunstfsi
     (i64.const 12)
     (i64.const 34)
    )
   )
   (call $__fixsfti
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (f32.const 12)
   )
   (call $__fixdfti
    (i32.add
     (get_local $3)
     (i32.const 32)
    )
    (f64.const 12)
   )
   (call $__fixunssfti
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (f32.const 12)
   )
   (call $__fixunsdfti
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
    (f64.const 12)
   )
   (drop
    (call $__trunctfdf2
     (i64.const 12)
     (i64.const 34)
    )
   )
   (drop
    (call $__trunctfsf2
     (i64.const 12)
     (i64.const 34)
    )
   )
   (br_if $label$0
    (tee_local $2
     (i32.add
      (get_local $2)
      (i32.const -1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio5token9testchainEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 176)
    )
   )
  )
  (set_local $2
   (i32.const 100)
  )
  (loop $label$0
   (drop
    (call $get_active_producers
     (get_local $3)
     (i32.const 168)
    )
   )
   (br_if $label$0
    (tee_local $2
     (i32.add
      (get_local $2)
      (i32.const -1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 176)
   )
  )
 )
 (func $_ZN5eosio5token9testfloatEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 f32)
  (local $3 f64)
  (local $4 i32)
  (local $5 f32)
  (local $6 f64)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (set_local $6
   (f64.promote/f32
    (tee_local $5
     (f32.convert_u/i64
      (get_local $1)
     )
    )
   )
  )
  (set_local $8
   (i32.const 0)
  )
  (set_local $1
   (i64.const 0)
  )
  (set_local $4
   (i32.const 1)
  )
  (set_local $7
   (i64.const 0)
  )
  (set_local $9
   (i32.const 0)
  )
  (loop $label$0
   (set_local $5
    (f32.add
     (tee_local $5
      (f32.add
       (tee_local $5
        (f32.add
         (tee_local $5
          (f32.add
           (tee_local $5
            (f32.add
             (tee_local $5
              (f32.add
               (tee_local $5
                (f32.div
                 (f32.sub
                  (f32.mul
                   (tee_local $2
                    (f32.convert_s/i32
                     (get_local $4)
                    )
                   )
                   (f32.add
                    (get_local $5)
                    (get_local $2)
                   )
                  )
                  (get_local $2)
                 )
                 (get_local $2)
                )
               )
               (select
                (f32.const 1)
                (f32.const 0)
                (f32.lt
                 (get_local $5)
                 (f32.const 1)
                )
               )
              )
             )
             (select
              (f32.const 1)
              (f32.const 0)
              (f32.le
               (get_local $5)
               (f32.const 1)
              )
             )
            )
           )
           (select
            (f32.const 1)
            (f32.const 0)
            (f32.gt
             (get_local $5)
             (f32.const 0)
            )
           )
          )
         )
         (select
          (f32.const 1)
          (f32.const 0)
          (f32.ge
           (get_local $5)
           (f32.const 0)
          )
         )
        )
       )
       (select
        (f32.const 1)
        (f32.const 0)
        (f32.ne
         (get_local $5)
         (f32.const 1)
        )
       )
      )
     )
     (select
      (f32.const 1)
      (f32.const 0)
      (f32.eq
       (get_local $5)
       (f32.const 1)
      )
     )
    )
   )
   (set_local $6
    (f64.add
     (tee_local $3
      (f64.add
       (tee_local $3
        (f64.add
         (tee_local $3
          (f64.add
           (tee_local $3
            (f64.add
             (tee_local $3
              (f64.add
               (tee_local $3
                (f64.div
                 (f64.sub
                  (f64.mul
                   (tee_local $3
                    (f64.promote/f32
                     (get_local $2)
                    )
                   )
                   (f64.add
                    (get_local $6)
                    (get_local $3)
                   )
                  )
                  (get_local $3)
                 )
                 (get_local $3)
                )
               )
               (select
                (f64.const 1)
                (f64.const 0)
                (f64.lt
                 (get_local $3)
                 (f64.const 1)
                )
               )
              )
             )
             (select
              (f64.const 1)
              (f64.const 0)
              (f64.le
               (get_local $3)
               (f64.const 1)
              )
             )
            )
           )
           (select
            (f64.const 1)
            (f64.const 0)
            (f64.gt
             (get_local $3)
             (f64.const 0)
            )
           )
          )
         )
         (select
          (f64.const 1)
          (f64.const 0)
          (f64.ge
           (get_local $3)
           (f64.const 0)
          )
         )
        )
       )
       (select
        (f64.const 1)
        (f64.const 0)
        (f64.ne
         (get_local $3)
         (f64.const 1)
        )
       )
      )
     )
     (select
      (f64.const 1)
      (f64.const 0)
      (f64.eq
       (get_local $3)
       (f64.const 1)
      )
     )
    )
   )
   (set_local $1
    (i64.add
     (i64.shl
      (i64.trunc_u/f32
       (get_local $2)
      )
      (i64.const 1)
     )
     (get_local $1)
    )
   )
   (set_local $7
    (i64.add
     (i64.shl
      (i64.trunc_s/f32
       (get_local $2)
      )
      (i64.const 1)
     )
     (get_local $7)
    )
   )
   (set_local $8
    (i32.add
     (i32.shl
      (i32.trunc_u/f32
       (get_local $2)
      )
      (i32.const 1)
     )
     (get_local $8)
    )
   )
   (set_local $9
    (i32.add
     (i32.shl
      (i32.trunc_s/f32
       (get_local $2)
      )
      (i32.const 1)
     )
     (get_local $9)
    )
   )
   (br_if $label$0
    (i32.ne
     (tee_local $4
      (i32.add
       (get_local $4)
       (i32.const 1)
      )
     )
     (i32.const 101)
    )
   )
  )
  (call $eosio_assert
   (f32.ne
    (get_local $5)
    (f32.const 0)
   )
   (i32.const 288)
  )
  (call $eosio_assert
   (f64.ne
    (get_local $6)
    (f64.const 0)
   )
   (i32.const 288)
  )
  (call $eosio_assert
   (i32.ne
    (get_local $9)
    (i32.const 0)
   )
   (i32.const 288)
  )
  (call $eosio_assert
   (i32.ne
    (get_local $8)
    (i32.const 0)
   )
   (i32.const 288)
  )
  (call $eosio_assert
   (i64.ne
    (get_local $7)
    (i64.const 0)
   )
   (i32.const 288)
  )
  (call $eosio_assert
   (i64.ne
    (get_local $1)
    (i64.const 0)
   )
   (i32.const 288)
  )
 )
 (func $_ZN5eosio5token10testcryptoEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 4384)
    )
   )
  )
  (set_local $2
   (i32.or
    (i32.add
     (get_local $4)
     (i32.const 48)
    )
    (i32.const 1)
   )
  )
  (set_local $3
   (i32.const 100)
  )
  (loop $label$0
   (call $sha1
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4352)
    )
   )
   (call $ripemd160
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4320)
    )
   )
   (call $sha256
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4288)
    )
   )
   (call $sha512
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4224)
    )
   )
   (call $assert_sha1
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4352)
    )
   )
   (call $assert_ripemd160
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4320)
    )
   )
   (call $assert_sha256
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4288)
    )
   )
   (call $assert_sha512
    (i32.add
     (get_local $4)
     (i32.const 128)
    )
    (i32.const 4096)
    (i32.add
     (get_local $4)
     (i32.const 4224)
    )
   )
   (i32.store8 offset=48
    (get_local $4)
    (i32.const 31)
   )
   (drop
    (call $memcpy
     (get_local $2)
     (i32.add
      (get_local $4)
      (i32.const 4224)
     )
     (i32.const 64)
    )
   )
   (drop
    (call $recover_key
     (i32.add
      (get_local $4)
      (i32.const 4288)
     )
     (i32.add
      (get_local $4)
      (i32.const 48)
     )
     (i32.const 65)
     (get_local $4)
     (i32.const 33)
    )
   )
   (call $assert_recover_key
    (i32.add
     (get_local $4)
     (i32.const 4288)
    )
    (i32.add
     (get_local $4)
     (i32.const 48)
    )
    (i32.const 65)
    (get_local $4)
    (i32.const 33)
   )
   (br_if $label$0
    (tee_local $3
     (i32.add
      (get_local $3)
      (i32.const -1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $4)
    (i32.const 4384)
   )
  )
 )
 (func $_ZN5eosio5token9testprintEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 4144)
    )
   )
  )
  (i64.store offset=4136
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=4128
   (get_local $3)
   (i64.const 10)
  )
  (i64.store offset=4120
   (get_local $3)
   (i64.const 0)
  )
  (i64.store offset=4112
   (get_local $3)
   (i64.const 20)
  )
  (i64.store offset=4104
   (get_local $3)
   (i64.const 4612037862148276224)
  )
  (i64.store offset=4096
   (get_local $3)
   (i64.const 0)
  )
  (drop
   (call $memset
    (get_local $3)
    (i32.const 65)
    (i32.const 4096)
   )
  )
  (set_local $2
   (i32.const 100)
  )
  (loop $label$0
   (call $prints
    (i32.const 1488)
   )
   (call $prints_l
    (get_local $3)
    (i32.const 128)
   )
   (call $printi
    (i64.const 1)
   )
   (call $printui
    (i64.const 1)
   )
   (call $printi128
    (i32.add
     (get_local $3)
     (i32.const 4128)
    )
   )
   (call $printui128
    (i32.add
     (get_local $3)
     (i32.const 4112)
    )
   )
   (call $printsf
    (f32.const 2)
   )
   (call $printdf
    (f64.const 3)
   )
   (call $printqf
    (i32.add
     (get_local $3)
     (i32.const 4096)
    )
   )
   (call $printn
    (i64.const 7)
   )
   (call $printhex
    (get_local $3)
    (i32.const 128)
   )
   (br_if $label$0
    (tee_local $2
     (i32.add
      (get_local $2)
      (i32.const -1)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $3)
    (i32.const 4144)
   )
  )
 )
 (func $_ZN5eosio5token13testsystemapiEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i64)
  (set_local $3
   (i64.const 0)
  )
  (set_local $2
   (i32.const 100)
  )
  (loop $label$0
   (set_local $3
    (i64.add
     (i64.add
      (call $current_time)
      (get_local $3)
     )
     (call $publication_time)
    )
   )
   (br_if $label$0
    (tee_local $2
     (i32.add
      (get_local $2)
      (i32.const -1)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.wrap/i64
    (get_local $3)
   )
   (i32.const 288)
  )
 )
 (func $_ZN5eosio5token7testmemEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $5
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 8192)
    )
   )
  )
  (i32.store8 offset=4096
   (get_local $5)
   (i32.const 1)
  )
  (i32.store8
   (get_local $5)
   (i32.const 2)
  )
  (set_local $3
   (i32.const 100)
  )
  (set_local $4
   (i32.const 0)
  )
  (loop $label$0
   (set_local $2
    (call $memcmp
     (i32.add
      (get_local $5)
      (i32.const 4096)
     )
     (get_local $5)
     (i32.const 4096)
    )
   )
   (drop
    (call $memcpy
     (i32.add
      (get_local $5)
      (i32.const 4096)
     )
     (get_local $5)
     (i32.const 4096)
    )
   )
   (drop
    (call $memmove
     (i32.add
      (get_local $5)
      (i32.const 4096)
     )
     (get_local $5)
     (i32.const 4096)
    )
   )
   (drop
    (call $memset
     (i32.add
      (get_local $5)
      (i32.const 4096)
     )
     (i32.const 0)
     (i32.const 4096)
    )
   )
   (set_local $4
    (i32.add
     (i32.ne
      (get_local $2)
      (i32.const 0)
     )
     (get_local $4)
    )
   )
   (br_if $label$0
    (tee_local $3
     (i32.add
      (get_local $3)
      (i32.const -1)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (get_local $4)
    (i32.const 100)
   )
   (i32.const 288)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 8192)
   )
  )
 )
 (func $_ZN5eosio5token6testdbEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i64)
  (local $11 i32)
  (local $12 i64)
  (local $13 i64)
  (local $14 i64)
  (local $15 i64)
  (local $16 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $16
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 144)
    )
   )
  )
  (i32.store
   (tee_local $6
    (i32.add
     (get_local $16)
     (i32.const 80)
    )
   )
   (i32.const 0)
  )
  (i64.store offset=64
   (get_local $16)
   (i64.const -1)
  )
  (i64.store offset=72
   (get_local $16)
   (i64.const 0)
  )
  (i64.store offset=48
   (get_local $16)
   (tee_local $13
    (i64.load
     (get_local $0)
    )
   )
  )
  (i64.store offset=56
   (get_local $16)
   (get_local $13)
  )
  (i32.store8
   (i32.add
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i32.store offset=84
   (get_local $16)
   (i32.const 0)
  )
  (set_local $2
   (i32.add
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
    (i32.const 24)
   )
  )
  (set_local $9
   (i32.const 99)
  )
  (set_local $7
   (i32.add
    (get_local $16)
    (i32.const 104)
   )
  )
  (set_local $8
   (i32.add
    (get_local $16)
    (i32.const 76)
   )
  )
  (set_local $15
   (get_local $13)
  )
  (loop $label$0
   (i32.store offset=24
    (get_local $16)
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
   )
   (i64.store
    (get_local $16)
    (get_local $15)
   )
   (call $eosio_assert
    (i64.eq
     (get_local $13)
     (call $current_receiver)
    )
    (i32.const 224)
   )
   (i32.store
    (get_local $7)
    (get_local $16)
   )
   (i32.store offset=100
    (get_local $16)
    (i32.add
     (get_local $16)
     (i32.const 24)
    )
   )
   (i32.store offset=96
    (get_local $16)
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
   )
   (i64.store offset=32
    (tee_local $11
     (call $_Znwj
      (i32.const 144)
     )
    )
    (i64.const 0)
   )
   (i64.store offset=96 align=4
    (get_local $11)
    (i64.const 0)
   )
   (i32.store offset=104
    (get_local $11)
    (i32.const 0)
   )
   (i64.store
    (i32.add
     (get_local $11)
     (i32.const 56)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $11)
     (i32.const 48)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $11)
     (i32.const 40)
    )
    (i64.const 0)
   )
   (i32.store offset=108
    (get_local $11)
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
   )
   (call $_ZZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE7emplaceIZNS1_6testdbEyE3$_5EENSJ_14const_iteratorEyOT_ENKUlRSN_E_clINSJ_4itemEEEDaSP_
    (i32.add
     (get_local $16)
     (i32.const 96)
    )
    (get_local $11)
   )
   (i32.store offset=136
    (get_local $16)
    (get_local $11)
   )
   (i64.store offset=96
    (get_local $16)
    (tee_local $13
     (i64.load
      (get_local $11)
     )
    )
   )
   (i32.store offset=32
    (get_local $16)
    (tee_local $3
     (i32.load offset=112
      (get_local $11)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.ge_u
       (tee_local $5
        (i32.load
         (get_local $8)
        )
       )
       (i32.load
        (get_local $6)
       )
      )
     )
     (i64.store offset=8
      (get_local $5)
      (get_local $13)
     )
     (i32.store offset=16
      (get_local $5)
      (get_local $3)
     )
     (i32.store offset=136
      (get_local $16)
      (i32.const 0)
     )
     (i32.store
      (get_local $5)
      (get_local $11)
     )
     (i32.store
      (get_local $8)
      (i32.add
       (get_local $5)
       (i32.const 24)
      )
     )
     (br $label$1)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy13443609543309262848ENS1_5token6recordEJNS1_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_15get_secondary_1EvEEEEEENS5_ILy4589348694149954592ENS8_IS4_oXadL_ZNKS4_15get_secondary_2EvEEEEEENS5_ILy4589348694149954608ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_15get_secondary_3EvEEEEEENS5_ILy4589348694149954624ENS8_IS4_dXadL_ZNKS4_15get_secondary_4EvEEEEEENS5_ILy4589348694149954640ENS8_IS4_eXadL_ZNKS4_15get_secondary_5EvEEEEEEEE8item_ptrENS_9allocatorISM_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSL_4itemENS_14default_deleteISS_EEEERyRlEEEvDpOT_
     (get_local $2)
     (i32.add
      (get_local $16)
      (i32.const 136)
     )
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (i32.add
      (get_local $16)
      (i32.const 32)
     )
    )
   )
   (set_local $11
    (i32.load offset=136
     (get_local $16)
    )
   )
   (i32.store offset=136
    (get_local $16)
    (i32.const 0)
   )
   (block $label$3
    (br_if $label$3
     (i32.eqz
      (get_local $11)
     )
    )
    (block $label$4
     (br_if $label$4
      (i32.eqz
       (i32.and
        (i32.load8_u offset=96
         (get_local $11)
        )
        (i32.const 1)
       )
      )
     )
     (call $_ZdlPv
      (i32.load
       (i32.add
        (get_local $11)
        (i32.const 104)
       )
      )
     )
    )
    (call $_ZdlPv
     (get_local $11)
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eqz
      (get_local $9)
     )
    )
    (set_local $9
     (i32.add
      (get_local $9)
      (i32.const -1)
     )
    )
    (set_local $15
     (i64.load
      (get_local $0)
     )
    )
    (set_local $13
     (i64.load offset=48
      (get_local $16)
     )
    )
    (br $label$0)
   )
  )
  (set_local $13
   (i64.const 0)
  )
  (set_local $11
   (i32.add
    (get_local $16)
    (i32.const 56)
   )
  )
  (loop $label$6
   (block $label$7
    (br_if $label$7
     (i32.lt_s
      (tee_local $5
       (call $db_lowerbound_i64
        (i64.load offset=48
         (get_local $16)
        )
        (i64.load
         (get_local $11)
        )
        (i64.const -5003134530400288768)
        (get_local $13)
       )
      )
      (i32.const 0)
     )
    )
    (drop
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $5)
     )
    )
   )
   (block $label$8
    (br_if $label$8
     (i32.lt_s
      (tee_local $5
       (call $db_upperbound_i64
        (i64.load offset=48
         (get_local $16)
        )
        (i64.load
         (get_local $11)
        )
        (i64.const -5003134530400288768)
        (get_local $13)
       )
      )
      (i32.const 0)
     )
    )
    (drop
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $5)
     )
    )
   )
   (br_if $label$6
    (i64.ne
     (tee_local $13
      (i64.add
       (get_local $13)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (set_local $10
   (i64.const 0)
  )
  (block $label$9
   (br_if $label$9
    (i32.lt_s
     (tee_local $11
      (call $db_lowerbound_i64
       (i64.load offset=48
        (get_local $16)
       )
       (i64.load
        (i32.add
         (get_local $16)
         (i32.const 56)
        )
       )
       (i64.const -5003134530400288768)
       (i64.const 0)
      )
     )
     (i32.const 0)
    )
   )
   (set_local $11
    (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
     (i32.add
      (get_local $16)
      (i32.const 48)
     )
     (get_local $11)
    )
   )
   (loop $label$10
    (set_local $13
     (i64.load
      (get_local $0)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 960)
    )
    (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE6modifyIZNS1_6testdbEyE3$_6EEvRKS2_yOT_
     (i32.add
      (get_local $16)
      (i32.const 48)
     )
     (get_local $11)
     (get_local $13)
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 1504)
    )
    (br_if $label$9
     (i32.lt_s
      (tee_local $11
       (call $db_next_i64
        (i32.load offset=112
         (get_local $11)
        )
        (i32.add
         (get_local $16)
         (i32.const 96)
        )
       )
      )
      (i32.const 0)
     )
    )
    (set_local $11
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $11)
     )
    )
    (br $label$10)
   )
  )
  (i32.store offset=40
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (loop $label$11
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$12
    (block $label$13
     (block $label$14
      (block $label$15
       (block $label$16
        (block $label$17
         (br_if $label$17
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$16
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$15)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$14
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$13)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$12
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx64_find_primary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (get_local $16)
     (get_local $10)
    )
   )
   (i64.store
    (get_local $16)
    (i64.const 100)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$18
    (block $label$19
     (block $label$20
      (block $label$21
       (block $label$22
        (block $label$23
         (br_if $label$23
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$22
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$21)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$20
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$19)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$18
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx64_find_secondary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (get_local $16)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
    )
   )
   (br_if $label$11
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 100)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE11lower_boundERKy
   (i32.add
    (get_local $16)
    (i32.const 32)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 100)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE11upper_boundERKy
   (i32.add
    (get_local $16)
    (i32.const 24)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$24
   (br_if $label$24
    (i32.eq
     (i32.load offset=36
      (get_local $16)
     )
     (i32.load offset=28
      (get_local $16)
     )
    )
   )
   (loop $label$25
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE14const_iteratorppEv
      (i32.add
       (get_local $16)
       (i32.const 32)
      )
     )
    )
    (br_if $label$25
     (i32.ne
      (i32.load offset=36
       (get_local $16)
      )
      (i32.load offset=28
       (get_local $16)
      )
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $16)
    (i32.const 104)
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $11
    (i32.add
     (get_local $16)
     (i32.const 112)
    )
   )
   (i32.const 0)
  )
  (i32.store offset=100
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i32.store offset=108
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (set_local $10
   (i64.const 0)
  )
  (i64.store
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE11lower_boundERKy
   (i32.add
    (get_local $16)
    (i32.const 136)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (get_local $16)
  )
  (block $label$26
   (br_if $label$26
    (i32.eq
     (i32.load
      (get_local $11)
     )
     (tee_local $5
      (i32.load offset=140
       (get_local $16)
      )
     )
    )
   )
   (set_local $9
    (i32.add
     (get_local $16)
     (i32.const 108)
    )
   )
   (loop $label$27
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE14const_iteratormmEv
      (get_local $9)
     )
    )
    (br_if $label$27
     (i32.ne
      (i32.load
       (get_local $11)
      )
      (get_local $5)
     )
    )
   )
  )
  (i32.store offset=40
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (loop $label$28
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$29
    (block $label$30
     (block $label$31
      (block $label$32
       (block $label$33
        (block $label$34
         (br_if $label$34
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$33
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$32)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$31
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$30)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$29
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx128_find_primary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (get_local $10)
    )
   )
   (set_local $13
    (i64.const 0)
   )
   (i64.store offset=104
    (get_local $16)
    (i64.const 0)
   )
   (i64.store offset=96
    (get_local $16)
    (i64.const 100)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$35
    (block $label$36
     (block $label$37
      (block $label$38
       (block $label$39
        (block $label$40
         (br_if $label$40
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$39
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$38)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$37
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$36)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$35
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx128_find_secondary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (get_local $16)
    )
   )
   (br_if $label$28
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 0)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 100)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE11lower_boundERKo
   (i32.add
    (get_local $16)
    (i32.const 32)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 0)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 100)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE11upper_boundERKo
   (i32.add
    (get_local $16)
    (i32.const 24)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$41
   (br_if $label$41
    (i32.eq
     (i32.load offset=36
      (get_local $16)
     )
     (i32.load offset=28
      (get_local $16)
     )
    )
   )
   (loop $label$42
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE14const_iteratorppEv
      (i32.add
       (get_local $16)
       (i32.const 32)
      )
     )
    )
    (br_if $label$42
     (i32.ne
      (i32.load offset=36
       (get_local $16)
      )
      (i32.load offset=28
       (get_local $16)
      )
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $16)
    (i32.const 104)
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $9
    (i32.add
     (get_local $16)
     (i32.const 112)
    )
   )
   (i32.const 0)
  )
  (i32.store offset=100
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i32.store offset=108
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i64.store offset=8
   (get_local $16)
   (i64.const 0)
  )
  (i64.store
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE11lower_boundERKo
   (i32.add
    (get_local $16)
    (i32.const 136)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (get_local $16)
  )
  (block $label$43
   (br_if $label$43
    (i32.eq
     (i32.load
      (get_local $9)
     )
     (tee_local $11
      (i32.load offset=140
       (get_local $16)
      )
     )
    )
   )
   (set_local $5
    (i32.add
     (get_local $16)
     (i32.const 108)
    )
   )
   (loop $label$44
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE14const_iteratormmEv
      (get_local $5)
     )
    )
    (br_if $label$44
     (i32.ne
      (i32.load
       (get_local $9)
      )
      (get_local $11)
     )
    )
   )
  )
  (i32.store offset=40
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (set_local $8
   (i32.add
    (get_local $16)
    (i32.const 120)
   )
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$45
   (i64.store
    (get_local $8)
    (i64.const 0)
   )
   (i64.store
    (get_local $9)
    (i64.const 0)
   )
   (i64.store offset=104
    (get_local $16)
    (i64.const 0)
   )
   (i64.store offset=96
    (get_local $16)
    (i64.const 0)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$46
    (block $label$47
     (block $label$48
      (block $label$49
       (block $label$50
        (block $label$51
         (br_if $label$51
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$50
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$49)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$48
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$47)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$46
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx256_find_primary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (i32.const 2)
     (get_local $10)
    )
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 1552)
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 1552)
   )
   (set_local $13
    (i64.const 0)
   )
   (i64.store
    (get_local $8)
    (i64.const 0)
   )
   (i64.store
    (get_local $9)
    (i64.const 0)
   )
   (i64.store offset=104
    (get_local $16)
    (i64.const 100)
   )
   (i64.store offset=96
    (get_local $16)
    (i64.const 0)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$52
    (block $label$53
     (block $label$54
      (block $label$55
       (block $label$56
        (block $label$57
         (br_if $label$57
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$56
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$55)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$54
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$53)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$52
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx256_find_secondary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (i32.const 2)
     (get_local $16)
    )
   )
   (br_if $label$45
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 100)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store
   (tee_local $5
    (i32.add
     (get_local $16)
     (i32.const 120)
    )
   )
   (i64.const 0)
  )
  (i64.store offset=112
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE11lower_boundERKSC_
   (i32.add
    (get_local $16)
    (i32.const 32)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 100)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store
   (get_local $5)
   (i64.const 0)
  )
  (i64.store offset=112
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE11upper_boundERKSC_
   (i32.add
    (get_local $16)
    (i32.const 24)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$58
   (br_if $label$58
    (i32.eq
     (i32.load offset=36
      (get_local $16)
     )
     (i32.load offset=28
      (get_local $16)
     )
    )
   )
   (loop $label$59
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE14const_iteratorppEv
      (i32.add
       (get_local $16)
       (i32.const 32)
      )
     )
    )
    (br_if $label$59
     (i32.ne
      (i32.load offset=36
       (get_local $16)
      )
      (i32.load offset=28
       (get_local $16)
      )
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $16)
    (i32.const 8)
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $11
    (i32.add
     (get_local $16)
     (i32.const 16)
    )
   )
   (i32.const 0)
  )
  (i32.store offset=4
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i32.store offset=12
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i64.store
   (get_local $5)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $16)
     (i32.const 96)
    )
    (i32.const 16)
   )
   (i64.const 0)
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 0)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE11lower_boundERKSC_
   (i32.add
    (get_local $16)
    (i32.const 136)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$60
   (br_if $label$60
    (i32.eq
     (i32.load
      (get_local $11)
     )
     (tee_local $5
      (i32.load offset=140
       (get_local $16)
      )
     )
    )
   )
   (set_local $9
    (i32.add
     (get_local $16)
     (i32.const 12)
    )
   )
   (loop $label$61
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE14const_iteratormmEv
      (get_local $9)
     )
    )
    (br_if $label$61
     (i32.ne
      (i32.load
       (get_local $11)
      )
      (get_local $5)
     )
    )
   )
  )
  (i32.store offset=40
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$62
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$63
    (block $label$64
     (block $label$65
      (block $label$66
       (block $label$67
        (block $label$68
         (br_if $label$68
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$67
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$66)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$65
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$64)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$63
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx_double_find_primary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (get_local $16)
     (get_local $10)
    )
   )
   (i64.store
    (get_local $16)
    (i64.const 4636737291354636288)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$69
    (block $label$70
     (block $label$71
      (block $label$72
       (block $label$73
        (block $label$74
         (br_if $label$74
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$73
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$72)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$71
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$70)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$69
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx_double_find_secondary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (get_local $16)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
    )
   )
   (br_if $label$62
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 4636737291354636288)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE11lower_boundERKd
   (i32.add
    (get_local $16)
    (i32.const 32)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 4636737291354636288)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE11upper_boundERKd
   (i32.add
    (get_local $16)
    (i32.const 24)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$75
   (br_if $label$75
    (i32.eq
     (i32.load offset=36
      (get_local $16)
     )
     (i32.load offset=28
      (get_local $16)
     )
    )
   )
   (loop $label$76
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE14const_iteratorppEv
      (i32.add
       (get_local $16)
       (i32.const 32)
      )
     )
    )
    (br_if $label$76
     (i32.ne
      (i32.load offset=36
       (get_local $16)
      )
      (i32.load offset=28
       (get_local $16)
      )
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $16)
    (i32.const 104)
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $11
    (i32.add
     (get_local $16)
     (i32.const 112)
    )
   )
   (i32.const 0)
  )
  (i32.store offset=100
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i32.store offset=108
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i64.store
   (get_local $16)
   (i64.const -4503599627370497)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE11lower_boundERKd
   (i32.add
    (get_local $16)
    (i32.const 136)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (get_local $16)
  )
  (block $label$77
   (br_if $label$77
    (i32.eq
     (i32.load
      (get_local $11)
     )
     (tee_local $5
      (i32.load offset=140
       (get_local $16)
      )
     )
    )
   )
   (set_local $9
    (i32.add
     (get_local $16)
     (i32.const 108)
    )
   )
   (loop $label$78
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE14const_iteratormmEv
      (get_local $9)
     )
    )
    (br_if $label$78
     (i32.ne
      (i32.load
       (get_local $11)
      )
      (get_local $5)
     )
    )
   )
  )
  (i32.store offset=40
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (set_local $10
   (i64.const 0)
  )
  (loop $label$79
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $13
    (i64.const 0)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$80
    (block $label$81
     (block $label$82
      (block $label$83
       (block $label$84
        (block $label$85
         (br_if $label$85
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$84
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$83)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$82
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$81)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$80
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx_long_double_find_primary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (get_local $10)
    )
   )
   (i64.store offset=104
    (get_local $16)
    (i64.const 4613251722985340928)
   )
   (set_local $13
    (i64.const 0)
   )
   (i64.store offset=96
    (get_local $16)
    (i64.const 0)
   )
   (set_local $4
    (i64.load
     (get_local $0)
    )
   )
   (set_local $12
    (i64.const 59)
   )
   (set_local $11
    (i32.const 1536)
   )
   (set_local $14
    (i64.const 0)
   )
   (loop $label$86
    (block $label$87
     (block $label$88
      (block $label$89
       (block $label$90
        (block $label$91
         (br_if $label$91
          (i64.gt_u
           (get_local $13)
           (i64.const 6)
          )
         )
         (br_if $label$90
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $5
              (i32.load8_s
               (get_local $11)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $5
          (i32.add
           (get_local $5)
           (i32.const 165)
          )
         )
         (br $label$89)
        )
        (set_local $15
         (i64.const 0)
        )
        (br_if $label$88
         (i64.le_u
          (get_local $13)
          (i64.const 11)
         )
        )
        (br $label$87)
       )
       (set_local $5
        (select
         (i32.add
          (get_local $5)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $5)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $15
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $5)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $15
      (i64.shl
       (i64.and
        (get_local $15)
        (i64.const 31)
       )
       (i64.and
        (get_local $12)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $11
     (i32.add
      (get_local $11)
      (i32.const 1)
     )
    )
    (set_local $13
     (i64.add
      (get_local $13)
      (i64.const 1)
     )
    )
    (set_local $14
     (i64.or
      (get_local $15)
      (get_local $14)
     )
    )
    (br_if $label$86
     (i64.ne
      (tee_local $12
       (i64.add
        (get_local $12)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (drop
    (call $db_idx_long_double_find_secondary
     (get_local $4)
     (get_local $4)
     (get_local $14)
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (get_local $16)
    )
   )
   (br_if $label$79
    (i64.ne
     (tee_local $10
      (i64.add
       (get_local $10)
       (i64.const 1)
      )
     )
     (i64.const 100)
    )
   )
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 4613251722985340928)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE11lower_boundERKe
   (i32.add
    (get_local $16)
    (i32.const 32)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (i64.store offset=104
   (get_local $16)
   (i64.const 4613251722985340928)
  )
  (i64.store offset=96
   (get_local $16)
   (i64.const 0)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE11upper_boundERKe
   (i32.add
    (get_local $16)
    (i32.const 24)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (i32.add
    (get_local $16)
    (i32.const 96)
   )
  )
  (block $label$92
   (br_if $label$92
    (i32.eq
     (i32.load offset=36
      (get_local $16)
     )
     (i32.load offset=28
      (get_local $16)
     )
    )
   )
   (loop $label$93
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE14const_iteratorppEv
      (i32.add
       (get_local $16)
       (i32.const 32)
      )
     )
    )
    (br_if $label$93
     (i32.ne
      (i32.load offset=36
       (get_local $16)
      )
      (i32.load offset=28
       (get_local $16)
      )
     )
    )
   )
  )
  (i32.store
   (tee_local $9
    (i32.add
     (i32.add
      (get_local $16)
      (i32.const 96)
     )
     (i32.const 8)
    )
   )
   (i32.const 0)
  )
  (i32.store
   (tee_local $5
    (i32.add
     (get_local $16)
     (i32.const 112)
    )
   )
   (i32.const 0)
  )
  (i32.store offset=100
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i32.store offset=108
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
  )
  (i64.store offset=8
   (get_local $16)
   (i64.const -281474976710657)
  )
  (i64.store
   (get_local $16)
   (i64.const -1)
  )
  (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE11lower_boundERKe
   (i32.add
    (get_local $16)
    (i32.const 136)
   )
   (i32.add
    (get_local $16)
    (i32.const 40)
   )
   (get_local $16)
  )
  (set_local $11
   (i32.add
    (get_local $16)
    (i32.const 108)
   )
  )
  (block $label$94
   (br_if $label$94
    (i32.eq
     (i32.load
      (get_local $5)
     )
     (tee_local $0
      (i32.load offset=140
       (get_local $16)
      )
     )
    )
   )
   (loop $label$95
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE14const_iteratormmEv
      (get_local $11)
     )
    )
    (br_if $label$95
     (i32.ne
      (i32.load
       (get_local $5)
      )
      (get_local $0)
     )
    )
   )
  )
  (i32.store
   (get_local $9)
   (i32.const 0)
  )
  (i32.store
   (get_local $5)
   (i32.const 0)
  )
  (i32.store offset=108
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (i32.store offset=100
   (get_local $16)
   (i32.add
    (get_local $16)
    (i32.const 48)
   )
  )
  (block $label$96
   (br_if $label$96
    (i32.lt_s
     (tee_local $5
      (call $db_lowerbound_i64
       (i64.load offset=48
        (get_local $16)
       )
       (i64.load
        (i32.add
         (i32.add
          (get_local $16)
          (i32.const 48)
         )
         (i32.const 8)
        )
       )
       (i64.const -5003134530400288768)
       (i64.const 0)
      )
     )
     (i32.const 0)
    )
   )
   (br_if $label$96
    (i32.eq
     (tee_local $5
      (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
       (i32.add
        (get_local $16)
        (i32.const 48)
       )
       (get_local $5)
      )
     )
     (i32.load
      (tee_local $0
       (i32.add
        (get_local $16)
        (i32.const 112)
       )
      )
     )
    )
   )
   (loop $label$97
    (drop
     (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE14const_iteratormmEv
      (get_local $11)
     )
    )
    (br_if $label$97
     (i32.ne
      (i32.load
       (get_local $0)
      )
      (get_local $5)
     )
    )
   )
  )
  (block $label$98
   (br_if $label$98
    (i32.lt_s
     (tee_local $11
      (call $db_lowerbound_i64
       (i64.load offset=48
        (get_local $16)
       )
       (i64.load
        (tee_local $9
         (i32.add
          (get_local $16)
          (i32.const 56)
         )
        )
       )
       (i64.const -5003134530400288768)
       (i64.const 0)
      )
     )
     (i32.const 0)
    )
   )
   (set_local $11
    (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
     (i32.add
      (get_local $16)
      (i32.const 48)
     )
     (get_local $11)
    )
   )
   (call $eosio_assert
    (i32.const 1)
    (i32.const 1504)
   )
   (br_if $label$98
    (i32.lt_s
     (tee_local $11
      (call $db_next_i64
       (i32.load offset=112
        (get_local $11)
       )
       (get_local $16)
      )
     )
     (i32.const 0)
    )
   )
   (loop $label$99
    (set_local $11
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $11)
     )
    )
    (call $eosio_assert
     (i32.const 1)
     (i32.const 1504)
    )
    (br_if $label$99
     (i32.ge_s
      (tee_local $11
       (call $db_next_i64
        (i32.load offset=112
         (get_local $11)
        )
        (get_local $16)
       )
      )
      (i32.const 0)
     )
    )
   )
  )
  (set_local $5
   (i32.const 100)
  )
  (loop $label$100
   (set_local $11
    (i32.const 0)
   )
   (block $label$101
    (br_if $label$101
     (i32.lt_s
      (tee_local $0
       (call $db_lowerbound_i64
        (i64.load offset=48
         (get_local $16)
        )
        (i64.load
         (get_local $9)
        )
        (i64.const -5003134530400288768)
        (i64.const 0)
       )
      )
      (i32.const 0)
     )
    )
    (set_local $11
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $0)
     )
    )
   )
   (call $eosio_assert
    (tee_local $0
     (i32.ne
      (get_local $11)
      (i32.const 0)
     )
    )
    (i32.const 1600)
   )
   (call $eosio_assert
    (get_local $0)
    (i32.const 1504)
   )
   (block $label$102
    (br_if $label$102
     (i32.lt_s
      (tee_local $0
       (call $db_next_i64
        (i32.load offset=112
         (get_local $11)
        )
        (get_local $16)
       )
      )
      (i32.const 0)
     )
    )
    (drop
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (i32.add
       (get_local $16)
       (i32.const 48)
      )
      (get_local $0)
     )
    )
   )
   (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5eraseERKS2_
    (i32.add
     (get_local $16)
     (i32.const 48)
    )
    (get_local $11)
   )
   (br_if $label$100
    (tee_local $5
     (i32.add
      (get_local $5)
      (i32.const -1)
     )
    )
   )
  )
  (block $label$103
   (br_if $label$103
    (i32.eqz
     (tee_local $0
      (i32.load offset=72
       (get_local $16)
      )
     )
    )
   )
   (block $label$104
    (block $label$105
     (br_if $label$105
      (i32.eq
       (tee_local $11
        (i32.load
         (tee_local $9
          (i32.add
           (get_local $16)
           (i32.const 76)
          )
         )
        )
       )
       (get_local $0)
      )
     )
     (loop $label$106
      (set_local $5
       (i32.load
        (tee_local $11
         (i32.add
          (get_local $11)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $11)
       (i32.const 0)
      )
      (block $label$107
       (br_if $label$107
        (i32.eqz
         (get_local $5)
        )
       )
       (block $label$108
        (br_if $label$108
         (i32.eqz
          (i32.and
           (i32.load8_u offset=96
            (get_local $5)
           )
           (i32.const 1)
          )
         )
        )
        (call $_ZdlPv
         (i32.load
          (i32.add
           (get_local $5)
           (i32.const 104)
          )
         )
        )
       )
       (call $_ZdlPv
        (get_local $5)
       )
      )
      (br_if $label$106
       (i32.ne
        (get_local $0)
        (get_local $11)
       )
      )
     )
     (set_local $11
      (i32.load
       (i32.add
        (get_local $16)
        (i32.const 72)
       )
      )
     )
     (br $label$104)
    )
    (set_local $11
     (get_local $0)
    )
   )
   (i32.store
    (get_local $9)
    (get_local $0)
   )
   (call $_ZdlPv
    (get_local $11)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $16)
    (i32.const 144)
   )
  )
 )
 (func $_ZZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE7emplaceIZNS1_6testdbEyE3$_5EENSJ_14const_iteratorEyOT_ENKUlRSN_E_clINSJ_4itemEEEDaSP_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (tee_local $4
      (i64.load offset=16
       (tee_local $5
        (i32.load
         (i32.load offset=4
          (get_local $0)
         )
        )
       )
      )
     )
     (i64.const -1)
    )
   )
   (set_local $4
    (i64.const 0)
   )
   (block $label$1
    (br_if $label$1
     (i32.lt_s
      (tee_local $3
       (call $db_lowerbound_i64
        (i64.load
         (get_local $5)
        )
        (i64.load offset=8
         (get_local $5)
        )
        (i64.const -5003134530400288768)
        (i64.const 0)
       )
      )
      (i32.const 0)
     )
    )
    (drop
     (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
      (get_local $5)
      (get_local $3)
     )
    )
    (i32.store offset=20
     (get_local $9)
     (i32.const 0)
    )
    (i32.store offset=16
     (get_local $9)
     (get_local $5)
    )
    (set_local $4
     (select
      (i64.const -2)
      (i64.add
       (tee_local $4
        (i64.load
         (i32.load offset=4
          (call $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE14const_iteratormmEv
           (i32.add
            (get_local $9)
            (i32.const 16)
           )
          )
         )
        )
       )
       (i64.const 1)
      )
      (i64.gt_u
       (get_local $4)
       (i64.const -3)
      )
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
    (get_local $4)
   )
  )
  (call $eosio_assert
   (i64.lt_u
    (get_local $4)
    (i64.const -2)
   )
   (i32.const 1888)
  )
  (set_local $4
   (i64.load
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $1)
   (i64.const 101)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.const 101)
  )
  (i64.store
   (get_local $1)
   (get_local $4)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 56)
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 48)
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 40)
   )
   (i64.const 101)
  )
  (i64.store offset=32
   (get_local $1)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 88)
   )
   (i64.const 4613256121031852032)
  )
  (i64.store offset=80
   (get_local $1)
   (i64.const 0)
  )
  (i64.store offset=64
   (get_local $1)
   (i64.const 4636807660098813952)
  )
  (drop
   (call $memset
    (tee_local $5
     (call $_Znwj
      (i32.const 4112)
     )
    )
    (i32.const 65)
    (i32.const 4096)
   )
  )
  (i32.store8 offset=4096
   (get_local $5)
   (i32.const 0)
  )
  (set_local $3
   (i32.add
    (get_local $1)
    (i32.const 96)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.and
      (i32.load8_u offset=96
       (get_local $1)
      )
      (i32.const 1)
     )
    )
    (i32.store16
     (get_local $3)
     (i32.const 0)
    )
    (set_local $8
     (i32.add
      (get_local $1)
      (i32.const 104)
     )
    )
    (br $label$2)
   )
   (i32.store8
    (i32.load
     (tee_local $8
      (i32.add
       (get_local $1)
       (i32.const 104)
      )
     )
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 100)
    )
    (i32.const 0)
   )
  )
  (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
   (get_local $3)
   (i32.const 0)
  )
  (i32.store
   (get_local $8)
   (get_local $5)
  )
  (i64.store offset=96 align=4
   (get_local $1)
   (i64.const 17592186048529)
  )
  (i32.store offset=4
   (get_local $9)
   (tee_local $5
    (call $malloc
     (i32.const 4156)
    )
   )
  )
  (i32.store
   (get_local $9)
   (get_local $5)
  )
  (i32.store offset=8
   (get_local $9)
   (i32.add
    (get_local $5)
    (i32.const 4156)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_5token6recordE
    (get_local $9)
    (get_local $1)
   )
  )
  (i32.store offset=112
   (get_local $1)
   (call $db_store_i64
    (i64.load offset=8
     (get_local $2)
    )
    (i64.const -5003134530400288768)
    (i64.load
     (i32.load offset=8
      (get_local $0)
     )
    )
    (tee_local $4
     (i64.load
      (get_local $1)
     )
    )
    (get_local $5)
    (i32.const 4156)
   )
  )
  (call $free
   (get_local $5)
  )
  (block $label$4
   (br_if $label$4
    (i64.lt_u
     (get_local $4)
     (i64.load offset=16
      (get_local $2)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (select
     (i64.const -2)
     (i64.add
      (get_local $4)
      (i64.const 1)
     )
     (i64.gt_u
      (get_local $4)
      (i64.const -3)
     )
    )
   )
  )
  (set_local $4
   (i64.load
    (tee_local $5
     (i32.add
      (get_local $2)
      (i32.const 8)
     )
    )
   )
  )
  (set_local $6
   (i64.load
    (tee_local $0
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
    )
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=16
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=116
   (get_local $1)
   (call $db_idx64_store
    (get_local $4)
    (i64.const -5003134530400288768)
    (get_local $6)
    (get_local $7)
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (set_local $4
   (i64.load
    (get_local $0)
   )
  )
  (set_local $6
   (i64.load
    (get_local $5)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=24
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=16
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $1)
    (i32.const 120)
   )
   (call $db_idx128_store
    (get_local $6)
    (i64.const -5003134530400288767)
    (get_local $4)
    (get_local $7)
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (set_local $4
   (i64.load
    (get_local $0)
   )
  )
  (set_local $6
   (i64.load
    (get_local $5)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
   )
  )
  (i64.store offset=24
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
   )
  )
  (i64.store offset=16
   (get_local $9)
   (i64.load offset=32
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $1)
    (i32.const 124)
   )
   (call $db_idx256_store
    (get_local $6)
    (i64.const -5003134530400288766)
    (get_local $4)
    (get_local $7)
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i32.const 2)
   )
  )
  (set_local $4
   (i64.load
    (get_local $0)
   )
  )
  (set_local $6
   (i64.load
    (get_local $5)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=16
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $1)
    (i32.const 128)
   )
   (call $db_idx_double_store
    (get_local $6)
    (i64.const -5003134530400288765)
    (get_local $4)
    (get_local $7)
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (set_local $4
   (i64.load
    (get_local $0)
   )
  )
  (set_local $6
   (i64.load
    (get_local $5)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=24
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 88)
    )
   )
  )
  (i64.store offset=16
   (get_local $9)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $1)
    (i32.const 132)
   )
   (call $db_idx_long_double_store
    (get_local $6)
    (i64.const -5003134530400288764)
    (get_local $4)
    (get_local $7)
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 48)
   )
  )
 )
 (func $_ZNSt3__16vectorIN5eosio11multi_indexILy13443609543309262848ENS1_5token6recordEJNS1_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_15get_secondary_1EvEEEEEENS5_ILy4589348694149954592ENS8_IS4_oXadL_ZNKS4_15get_secondary_2EvEEEEEENS5_ILy4589348694149954608ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_15get_secondary_3EvEEEEEENS5_ILy4589348694149954624ENS8_IS4_dXadL_ZNKS4_15get_secondary_4EvEEEEEENS5_ILy4589348694149954640ENS8_IS4_eXadL_ZNKS4_15get_secondary_5EvEEEEEEEE8item_ptrENS_9allocatorISM_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSL_4itemENS_14default_deleteISS_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.ge_u
      (tee_local $5
       (i32.add
        (tee_local $4
         (i32.div_s
          (i32.sub
           (i32.load offset=4
            (get_local $0)
           )
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
          (i32.const 24)
         )
        )
        (i32.const 1)
       )
      )
      (i32.const 178956971)
     )
    )
    (set_local $7
     (i32.const 178956970)
    )
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (tee_local $6
         (i32.div_s
          (i32.sub
           (i32.load offset=8
            (get_local $0)
           )
           (get_local $6)
          )
          (i32.const 24)
         )
        )
        (i32.const 89478484)
       )
      )
      (br_if $label$2
       (i32.eqz
        (tee_local $7
         (select
          (get_local $5)
          (tee_local $7
           (i32.shl
            (get_local $6)
            (i32.const 1)
           )
          )
          (i32.lt_u
           (get_local $7)
           (get_local $5)
          )
         )
        )
       )
      )
     )
     (set_local $6
      (call $_Znwj
       (i32.mul
        (get_local $7)
        (i32.const 24)
       )
      )
     )
     (br $label$0)
    )
    (set_local $7
     (i32.const 0)
    )
    (set_local $6
     (i32.const 0)
    )
    (br $label$0)
   )
   (call $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv
    (get_local $0)
   )
   (unreachable)
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (i32.store
   (get_local $1)
   (i32.const 0)
  )
  (i32.store
   (tee_local $1
    (i32.add
     (get_local $6)
     (i32.mul
      (get_local $4)
      (i32.const 24)
     )
    )
   )
   (get_local $5)
  )
  (i64.store offset=8
   (get_local $1)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=16
   (get_local $1)
   (i32.load
    (get_local $3)
   )
  )
  (set_local $4
   (i32.add
    (get_local $6)
    (i32.mul
     (get_local $7)
     (i32.const 24)
    )
   )
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.eq
      (tee_local $6
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
      )
      (tee_local $7
       (i32.load
        (get_local $0)
       )
      )
     )
    )
    (loop $label$6
     (set_local $3
      (i32.load
       (tee_local $2
        (i32.add
         (get_local $6)
         (i32.const -24)
        )
       )
      )
     )
     (i32.store
      (get_local $2)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
      (get_local $3)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -8)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -8)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -12)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -12)
       )
      )
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const -16)
      )
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const -16)
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const -24)
      )
     )
     (set_local $6
      (get_local $2)
     )
     (br_if $label$6
      (i32.ne
       (get_local $7)
       (get_local $2)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $6
     (i32.load
      (get_local $0)
     )
    )
    (br $label$4)
   )
   (set_local $6
    (get_local $7)
   )
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $5)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (get_local $4)
  )
  (block $label$7
   (br_if $label$7
    (i32.eq
     (get_local $7)
     (get_local $6)
    )
   )
   (loop $label$8
    (set_local $1
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$9
     (br_if $label$9
      (i32.eqz
       (get_local $1)
      )
     )
     (block $label$10
      (br_if $label$10
       (i32.eqz
        (i32.and
         (i32.load8_u offset=96
          (get_local $1)
         )
         (i32.const 1)
        )
       )
      )
      (call $_ZdlPv
       (i32.load
        (i32.add
         (get_local $1)
         (i32.const 104)
        )
       )
      )
     )
     (call $_ZdlPv
      (get_local $1)
     )
    )
    (br_if $label$8
     (i32.ne
      (get_local $6)
      (get_local $7)
     )
    )
   )
  )
  (block $label$11
   (br_if $label$11
    (i32.eqz
     (get_local $6)
    )
   )
   (call $_ZdlPv
    (get_local $6)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $8
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $9)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 28)
       )
      )
     )
     (tee_local $2
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $3
    (i32.sub
     (i32.const 0)
     (get_local $2)
    )
   )
   (set_local $6
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $6)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $7
     (get_local $6)
    )
    (set_local $6
     (tee_local $4
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $3)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (get_local $2)
     )
    )
    (set_local $6
     (i32.load
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_get_i64
        (get_local $1)
        (i32.const 0)
        (i32.const 0)
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 384)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $6)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $6)
      )
     )
     (br $label$4)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $9)
       (i32.and
        (i32.add
         (get_local $6)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $db_get_i64
     (get_local $1)
     (get_local $4)
     (get_local $6)
    )
   )
   (i32.store offset=36
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=32
    (get_local $8)
    (get_local $4)
   )
   (i32.store offset=40
    (get_local $8)
    (i32.add
     (get_local $4)
     (get_local $6)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $6)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (i64.store offset=32
    (tee_local $6
     (call $_Znwj
      (i32.const 144)
     )
    )
    (i64.const 0)
   )
   (i64.store offset=96 align=4
    (get_local $6)
    (i64.const 0)
   )
   (i32.store offset=104
    (get_local $6)
    (i32.const 0)
   )
   (i64.store
    (i32.add
     (get_local $6)
     (i32.const 56)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $6)
     (i32.const 48)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $6)
     (i32.const 40)
    )
    (i64.const 0)
   )
   (i32.store offset=108
    (get_local $6)
    (get_local $0)
   )
   (drop
    (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_5token6recordE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (get_local $6)
    )
   )
   (i32.store offset=116
    (get_local $6)
    (i32.const -1)
   )
   (i32.store offset=112
    (get_local $6)
    (get_local $1)
   )
   (i32.store offset=120
    (get_local $6)
    (i32.const -1)
   )
   (i32.store offset=124
    (get_local $6)
    (i32.const -1)
   )
   (i32.store offset=128
    (get_local $6)
    (i32.const -1)
   )
   (i32.store offset=132
    (get_local $6)
    (i32.const -1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $6)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $5
     (i64.load
      (get_local $6)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $7
     (i32.load offset=112
      (get_local $6)
     )
    )
   )
   (block $label$7
    (block $label$8
     (br_if $label$8
      (i32.ge_u
       (tee_local $4
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 28)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 32)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $4)
      (get_local $5)
     )
     (i32.store offset=16
      (get_local $4)
      (get_local $7)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $4)
      (get_local $6)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $4)
       (i32.const 24)
      )
     )
     (br $label$7)
    )
    (call $_ZNSt3__16vectorIN5eosio11multi_indexILy13443609543309262848ENS1_5token6recordEJNS1_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_15get_secondary_1EvEEEEEENS5_ILy4589348694149954592ENS8_IS4_oXadL_ZNKS4_15get_secondary_2EvEEEEEENS5_ILy4589348694149954608ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_15get_secondary_3EvEEEEEENS5_ILy4589348694149954624ENS8_IS4_dXadL_ZNKS4_15get_secondary_4EvEEEEEENS5_ILy4589348694149954640ENS8_IS4_eXadL_ZNKS4_15get_secondary_5EvEEEEEEEE8item_ptrENS_9allocatorISM_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSL_4itemENS_14default_deleteISS_EEEERyRlEEEvDpOT_
     (i32.add
      (get_local $0)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 24)
     )
     (i32.add
      (get_local $8)
      (i32.const 16)
     )
     (i32.add
      (get_local $8)
      (i32.const 12)
     )
    )
   )
   (set_local $4
    (i32.load offset=24
     (get_local $8)
    )
   )
   (i32.store offset=24
    (get_local $8)
    (i32.const 0)
   )
   (br_if $label$2
    (i32.eqz
     (get_local $4)
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.eqz
      (i32.and
       (i32.load8_u offset=96
        (get_local $4)
       )
       (i32.const 1)
      )
     )
    )
    (call $_ZdlPv
     (i32.load
      (i32.add
       (get_local $4)
       (i32.const 104)
      )
     )
    )
   )
   (call $_ZdlPv
    (get_local $4)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $6)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE6modifyIZNS1_6testdbEyE3$_6EEvRKS2_yOT_ (param $0 i32) (param $1 i32) (param $2 i64)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i64)
  (local $14 i32)
  (local $15 i64)
  (local $16 i32)
  (local $17 i64)
  (local $18 i32)
  (local $19 i64)
  (local $20 i32)
  (local $21 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $20
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 176)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=108
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 672)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 720)
  )
  (set_local $19
   (i64.load
    (tee_local $18
     (i32.add
      (get_local $1)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $4
   (i64.load
    (tee_local $3
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
  )
  (set_local $6
   (i64.load
    (tee_local $5
     (i32.add
      (get_local $1)
      (i32.const 8)
     )
    )
   )
  )
  (i64.store
   (tee_local $8
    (i32.add
     (i32.add
      (tee_local $21
       (get_local $20)
      )
      (i32.const 144)
     )
     (i32.const 24)
    )
   )
   (i64.load
    (tee_local $7
     (i32.add
      (get_local $1)
      (i32.const 56)
     )
    )
   )
  )
  (i64.store
   (tee_local $10
    (i32.add
     (i32.add
      (get_local $21)
      (i32.const 144)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (tee_local $9
     (i32.add
      (get_local $1)
      (i32.const 48)
     )
    )
   )
  )
  (i64.store offset=152
   (get_local $21)
   (i64.load
    (tee_local $11
     (i32.add
      (get_local $1)
      (i32.const 40)
     )
    )
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load offset=32
    (get_local $1)
   )
  )
  (set_local $13
   (i64.load
    (tee_local $12
     (i32.add
      (get_local $1)
      (i32.const 80)
     )
    )
   )
  )
  (set_local $15
   (i64.load
    (tee_local $14
     (i32.add
      (get_local $1)
      (i32.const 88)
     )
    )
   )
  )
  (set_local $17
   (i64.load
    (tee_local $16
     (i32.add
      (get_local $1)
      (i32.const 64)
     )
    )
   )
  )
  (i64.store offset=16
   (get_local $21)
   (get_local $6)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 24)
   )
   (get_local $4)
  )
  (i64.store offset=32
   (get_local $21)
   (get_local $19)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 56)
   )
   (i64.load
    (get_local $8)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 48)
   )
   (i64.load
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 40)
   )
   (i64.load offset=152
    (get_local $21)
   )
  )
  (i64.store offset=48
   (get_local $21)
   (i64.load offset=144
    (get_local $21)
   )
  )
  (i64.store offset=80
   (get_local $21)
   (get_local $17)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 88)
   )
   (get_local $15)
  )
  (i64.store offset=96
   (get_local $21)
   (get_local $13)
  )
  (i64.store
   (get_local $3)
   (i64.const 0)
  )
  (i64.store
   (get_local $18)
   (i64.const 100)
  )
  (i64.store
   (get_local $5)
   (i64.const 100)
  )
  (set_local $4
   (i64.load
    (get_local $1)
   )
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 1552)
  )
  (i64.store
   (get_local $7)
   (i64.const 0)
  )
  (i64.store
   (get_local $9)
   (i64.const 0)
  )
  (i64.store
   (get_local $11)
   (i64.const 100)
  )
  (i64.store offset=32
   (get_local $1)
   (i64.const 0)
  )
  (i64.store
   (get_local $14)
   (i64.const 4613251722985340928)
  )
  (i64.store
   (get_local $12)
   (i64.const 0)
  )
  (i64.store
   (get_local $16)
   (i64.const 4636737291354636288)
  )
  (drop
   (call $memset
    (tee_local $18
     (call $_Znwj
      (i32.const 4112)
     )
    )
    (i32.const 66)
    (i32.const 4096)
   )
  )
  (i32.store8 offset=4096
   (get_local $18)
   (i32.const 0)
  )
  (set_local $5
   (i32.add
    (get_local $1)
    (i32.const 96)
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.and
      (i32.load8_u offset=96
       (get_local $1)
      )
      (i32.const 1)
     )
    )
    (i32.store16
     (get_local $5)
     (i32.const 0)
    )
    (set_local $8
     (i32.add
      (get_local $1)
      (i32.const 104)
     )
    )
    (br $label$0)
   )
   (i32.store8
    (i32.load
     (tee_local $8
      (i32.add
       (get_local $1)
       (i32.const 104)
      )
     )
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 100)
    )
    (i32.const 0)
   )
  )
  (set_local $3
   (i32.add
    (get_local $1)
    (i32.const 32)
   )
  )
  (set_local $7
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 80)
   )
  )
  (set_local $10
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 16)
    )
    (i32.const 16)
   )
  )
  (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
   (get_local $5)
   (i32.const 0)
  )
  (i32.store
   (get_local $8)
   (get_local $18)
  )
  (i64.store align=4
   (tee_local $18
    (i32.add
     (get_local $1)
     (i32.const 96)
    )
   )
   (i64.const 17592186048529)
  )
  (call $eosio_assert
   (i64.eq
    (get_local $4)
    (i64.load
     (get_local $1)
    )
   )
   (i32.const 896)
  )
  (set_local $18
   (i32.add
    (tee_local $5
     (select
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 100)
       )
      )
      (i32.shr_u
       (tee_local $18
        (i32.load8_u
         (get_local $18)
        )
       )
       (i32.const 1)
      )
      (i32.and
       (get_local $18)
       (i32.const 1)
      )
     )
    )
    (i32.const 58)
   )
  )
  (set_local $19
   (i64.extend_u/i32
    (get_local $5)
   )
  )
  (loop $label$2
   (set_local $18
    (i32.add
     (get_local $18)
     (i32.const 1)
    )
   )
   (br_if $label$2
    (i64.ne
     (tee_local $19
      (i64.shr_u
       (get_local $19)
       (i64.const 7)
      )
     )
     (i64.const 0)
    )
   )
  )
  (block $label$3
   (block $label$4
    (br_if $label$4
     (i32.lt_u
      (get_local $18)
      (i32.const 513)
     )
    )
    (set_local $20
     (call $malloc
      (get_local $18)
     )
    )
    (br $label$3)
   )
   (i32.store offset=4
    (i32.const 0)
    (tee_local $20
     (i32.sub
      (get_local $20)
      (i32.and
       (i32.add
        (get_local $18)
        (i32.const 15)
       )
       (i32.const -16)
      )
     )
    )
   )
  )
  (i32.store offset=4
   (get_local $21)
   (get_local $20)
  )
  (i32.store
   (get_local $21)
   (get_local $20)
  )
  (i32.store offset=8
   (get_local $21)
   (i32.add
    (get_local $20)
    (get_local $18)
   )
  )
  (drop
   (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_5token6recordE
    (get_local $21)
    (get_local $1)
   )
  )
  (call $db_update_i64
   (i32.load offset=112
    (get_local $1)
   )
   (get_local $2)
   (get_local $20)
   (get_local $18)
  )
  (block $label$5
   (br_if $label$5
    (i32.lt_u
     (get_local $18)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $20)
   )
  )
  (block $label$6
   (br_if $label$6
    (i64.lt_u
     (get_local $4)
     (i64.load offset=16
      (get_local $0)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (select
     (i64.const -2)
     (i64.add
      (get_local $4)
      (i64.const 1)
     )
     (i64.gt_u
      (get_local $4)
      (i64.const -3)
     )
    )
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (block $label$7
   (br_if $label$7
    (i32.eqz
     (call $memcmp
      (i32.add
       (get_local $21)
       (i32.const 16)
      )
      (i32.add
       (get_local $21)
       (i32.const 144)
      )
      (i32.const 8)
     )
    )
   )
   (block $label$8
    (br_if $label$8
     (i32.gt_s
      (tee_local $18
       (i32.load offset=116
        (get_local $1)
       )
      )
      (i32.const -1)
     )
    )
    (i32.store
     (i32.add
      (get_local $1)
      (i32.const 116)
     )
     (tee_local $18
      (call $db_idx64_find_primary
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -5003134530400288768)
       (i32.add
        (get_local $21)
        (i32.const 112)
       )
       (get_local $4)
      )
     )
    )
   )
   (call $db_idx64_update
    (get_local $18)
    (get_local $2)
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
   )
  )
  (i64.store offset=152
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (block $label$9
   (br_if $label$9
    (i32.eqz
     (call $memcmp
      (get_local $10)
      (i32.add
       (get_local $21)
       (i32.const 144)
      )
      (i32.const 16)
     )
    )
   )
   (block $label$10
    (br_if $label$10
     (i32.gt_s
      (tee_local $18
       (i32.load
        (tee_local $20
         (i32.add
          (get_local $1)
          (i32.const 120)
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (i32.store
     (get_local $20)
     (tee_local $18
      (call $db_idx128_find_primary
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -5003134530400288767)
       (i32.add
        (get_local $21)
        (i32.const 112)
       )
       (get_local $4)
      )
     )
    )
   )
   (call $db_idx128_update
    (get_local $18)
    (get_local $2)
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $3)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=152
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load
    (get_local $3)
   )
  )
  (block $label$11
   (br_if $label$11
    (i32.eqz
     (call $memcmp
      (i32.add
       (i32.add
        (get_local $21)
        (i32.const 16)
       )
       (i32.const 32)
      )
      (i32.add
       (get_local $21)
       (i32.const 144)
      )
      (i32.const 32)
     )
    )
   )
   (block $label$12
    (br_if $label$12
     (i32.gt_s
      (tee_local $18
       (i32.load
        (tee_local $20
         (i32.add
          (get_local $1)
          (i32.const 124)
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (i64.store
     (i32.add
      (get_local $21)
      (i32.const 136)
     )
     (i64.const 0)
    )
    (i64.store
     (i32.add
      (get_local $21)
      (i32.const 128)
     )
     (i64.const 0)
    )
    (i64.store offset=120
     (get_local $21)
     (i64.const 0)
    )
    (i64.store offset=112
     (get_local $21)
     (i64.const 0)
    )
    (i32.store
     (get_local $20)
     (tee_local $18
      (call $db_idx256_find_primary
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -5003134530400288766)
       (i32.add
        (get_local $21)
        (i32.const 112)
       )
       (i32.const 2)
       (get_local $4)
      )
     )
    )
   )
   (call $db_idx256_update
    (get_local $18)
    (get_local $2)
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
    (i32.const 2)
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
   )
  )
  (block $label$13
   (br_if $label$13
    (i32.eqz
     (call $memcmp
      (i32.add
       (i32.add
        (get_local $21)
        (i32.const 16)
       )
       (i32.const 64)
      )
      (i32.add
       (get_local $21)
       (i32.const 144)
      )
      (i32.const 8)
     )
    )
   )
   (block $label$14
    (br_if $label$14
     (i32.gt_s
      (tee_local $18
       (i32.load
        (tee_local $20
         (i32.add
          (get_local $1)
          (i32.const 128)
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (i32.store
     (get_local $20)
     (tee_local $18
      (call $db_idx_double_find_primary
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -5003134530400288765)
       (i32.add
        (get_local $21)
        (i32.const 112)
       )
       (get_local $4)
      )
     )
    )
   )
   (call $db_idx_double_update
    (get_local $18)
    (get_local $2)
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
   )
  )
  (i64.store offset=152
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 88)
    )
   )
  )
  (i64.store offset=144
   (get_local $21)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
   )
  )
  (block $label$15
   (br_if $label$15
    (i32.eqz
     (call $memcmp
      (get_local $7)
      (i32.add
       (get_local $21)
       (i32.const 144)
      )
      (i32.const 16)
     )
    )
   )
   (block $label$16
    (br_if $label$16
     (i32.gt_s
      (tee_local $18
       (i32.load
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const 132)
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (i32.store
     (get_local $1)
     (tee_local $18
      (call $db_idx_long_double_find_primary
       (i64.load
        (get_local $0)
       )
       (i64.load offset=8
        (get_local $0)
       )
       (i64.const -5003134530400288764)
       (i32.add
        (get_local $21)
        (i32.const 112)
       )
       (get_local $4)
      )
     )
    )
   )
   (call $db_idx_long_double_update
    (get_local $18)
    (get_local $2)
    (i32.add
     (get_local $21)
     (i32.const 144)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $21)
    (i32.const 176)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE11lower_boundERKy (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx64_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288768)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=8
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store offset=116
    (get_local $2)
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE11upper_boundERKy (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx64_upperbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288768)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=8
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store offset=116
    (get_local $2)
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1504)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $6
      (i32.load offset=116
       (tee_local $8
        (i32.load offset=4
         (get_local $0)
        )
       )
      )
     )
     (i32.const -1)
    )
   )
   (set_local $6
    (call $db_idx64_find_primary
     (i64.load
      (tee_local $6
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $6)
     )
     (i64.const -5003134530400288768)
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store offset=116
    (i32.load
     (i32.add
      (get_local $0)
      (i32.const 4)
     )
    )
    (get_local $6)
   )
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx64_next
       (get_local $6)
       (i32.add
        (get_local $9)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load offset=8
     (get_local $9)
    )
   )
   (block $label$2
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $2
          (i32.load
           (i32.load
            (get_local $0)
           )
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $4
       (i32.load offset=24
        (get_local $2)
       )
      )
     )
    )
    (set_local $7
     (i32.add
      (get_local $8)
      (i32.const -24)
     )
    )
    (set_local $5
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (loop $label$3
     (br_if $label$2
      (i64.eq
       (i64.load
        (i32.load
         (get_local $7)
        )
       )
       (get_local $3)
      )
     )
     (set_local $8
      (get_local $7)
     )
     (set_local $7
      (tee_local $6
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
     (br_if $label$3
      (i32.ne
       (i32.add
        (get_local $6)
        (get_local $5)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (get_local $8)
       (get_local $4)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $7
         (i32.load
          (i32.add
           (get_local $8)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $2)
      )
      (i32.const 112)
     )
     (br $label$4)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (call $db_find_i64
          (i64.load
           (get_local $2)
          )
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const -5003134530400288768)
          (get_local $3)
         )
        )
       )
      )
      (get_local $2)
     )
     (i32.const 112)
    )
   )
   (i32.store offset=116
    (get_local $7)
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954576ES7_Ly0ELb0EE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $7
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (block $label$2
     (br_if $label$2
      (i32.ne
       (tee_local $5
        (i32.load offset=116
         (get_local $7)
        )
       )
       (i32.const -1)
      )
     )
     (set_local $5
      (call $db_idx64_find_primary
       (i64.load
        (tee_local $5
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const -5003134530400288768)
       (get_local $9)
       (i64.load
        (get_local $7)
       )
      )
     )
     (i32.store offset=116
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 4)
       )
      )
      (get_local $5)
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $6
        (call $db_idx64_previous
         (get_local $5)
         (i32.add
          (get_local $9)
          (i32.const 8)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1824)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $7
      (call $db_idx64_end
       (i64.load
        (tee_local $7
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $7)
       )
       (i64.const -5003134530400288768)
      )
     )
     (i32.const -1)
    )
    (i32.const 1760)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_idx64_previous
        (get_local $7)
        (i32.add
         (get_local $9)
         (i32.const 8)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1760)
   )
  )
  (set_local $2
   (i64.load offset=8
    (get_local $9)
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.eq
     (tee_local $8
      (i32.load
       (i32.add
        (tee_local $1
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$4
    (br_if $label$3
     (i64.eq
      (i64.load
       (i32.load
        (get_local $7)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $7)
    )
    (set_local $7
     (tee_local $5
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br_if $label$4
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $8)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $1)
     )
     (i32.const 112)
    )
    (br $label$5)
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=108
      (tee_local $7
       (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (call $db_find_i64
         (i64.load
          (get_local $1)
         )
         (i64.load offset=8
          (get_local $1)
         )
         (i64.const -5003134530400288768)
         (get_local $2)
        )
       )
      )
     )
     (get_local $1)
    )
    (i32.const 112)
   )
  )
  (i32.store offset=116
   (get_local $7)
   (get_local $6)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE11lower_boundERKo (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx128_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288767)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 24)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=24
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (i64.load
           (get_local $4)
          )
          (i64.load offset=8
           (get_local $4)
          )
          (i64.const -5003134530400288768)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 120)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE11upper_boundERKo (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx128_upperbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288767)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 24)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=24
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (i64.load
           (get_local $4)
          )
          (i64.load offset=8
           (get_local $4)
          )
          (i64.const -5003134530400288768)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 120)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1504)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $6
      (i32.load
       (i32.add
        (tee_local $8
         (i32.load offset=4
          (get_local $0)
         )
        )
        (i32.const 120)
       )
      )
     )
     (i32.const -1)
    )
   )
   (set_local $6
    (call $db_idx128_find_primary
     (i64.load
      (tee_local $6
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $6)
     )
     (i64.const -5003134530400288767)
     (get_local $9)
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
     (i32.const 120)
    )
    (get_local $6)
   )
  )
  (i64.store
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx128_next
       (get_local $6)
       (get_local $9)
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load
     (get_local $9)
    )
   )
   (block $label$2
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $2
          (i32.load
           (i32.load
            (get_local $0)
           )
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $4
       (i32.load offset=24
        (get_local $2)
       )
      )
     )
    )
    (set_local $7
     (i32.add
      (get_local $8)
      (i32.const -24)
     )
    )
    (set_local $5
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (loop $label$3
     (br_if $label$2
      (i64.eq
       (i64.load
        (i32.load
         (get_local $7)
        )
       )
       (get_local $3)
      )
     )
     (set_local $8
      (get_local $7)
     )
     (set_local $7
      (tee_local $6
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
     (br_if $label$3
      (i32.ne
       (i32.add
        (get_local $6)
        (get_local $5)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (get_local $8)
       (get_local $4)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $7
         (i32.load
          (i32.add
           (get_local $8)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $2)
      )
      (i32.const 112)
     )
     (br $label$4)
    )
    (set_local $7
     (i32.const 0)
    )
    (br_if $label$4
     (i32.lt_s
      (tee_local $6
       (call $db_find_i64
        (i64.load
         (get_local $2)
        )
        (i64.load offset=8
         (get_local $2)
        )
        (i64.const -5003134530400288768)
        (get_local $3)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (get_local $6)
        )
       )
      )
      (get_local $2)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 120)
    )
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954592ES9_Ly1ELb0EE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $9)
   (i64.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $7
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (block $label$2
     (br_if $label$2
      (i32.ne
       (tee_local $5
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const 120)
         )
        )
       )
       (i32.const -1)
      )
     )
     (set_local $5
      (call $db_idx128_find_primary
       (i64.load
        (tee_local $5
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const -5003134530400288767)
       (get_local $9)
       (i64.load
        (get_local $7)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
       (i32.const 120)
      )
      (get_local $5)
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $6
        (call $db_idx128_previous
         (get_local $5)
         (i32.add
          (get_local $9)
          (i32.const 24)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1824)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $7
      (call $db_idx128_end
       (i64.load
        (tee_local $7
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $7)
       )
       (i64.const -5003134530400288767)
      )
     )
     (i32.const -1)
    )
    (i32.const 1760)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_idx128_previous
        (get_local $7)
        (i32.add
         (get_local $9)
         (i32.const 24)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1760)
   )
  )
  (set_local $2
   (i64.load offset=24
    (get_local $9)
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.eq
     (tee_local $8
      (i32.load
       (i32.add
        (tee_local $1
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$4
    (br_if $label$3
     (i64.eq
      (i64.load
       (i32.load
        (get_local $7)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $7)
    )
    (set_local $7
     (tee_local $5
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br_if $label$4
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $8)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $1)
     )
     (i32.const 112)
    )
    (br $label$5)
   )
   (set_local $7
    (i32.const 0)
   )
   (br_if $label$5
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $1)
       )
       (i64.load offset=8
        (get_local $1)
       )
       (i64.const -5003134530400288768)
       (get_local $2)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=108
      (tee_local $7
       (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (get_local $5)
       )
      )
     )
     (get_local $1)
    )
    (i32.const 112)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 120)
   )
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE11lower_boundERKSC_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx256_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288766)
       (get_local $10)
       (i32.const 2)
       (i32.add
        (get_local $10)
        (i32.const 40)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=40
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 124)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE11upper_boundERKSC_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx256_upperbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288766)
       (get_local $10)
       (i32.const 2)
       (i32.add
        (get_local $10)
        (i32.const 40)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=40
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 124)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1504)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $6
      (i32.load
       (i32.add
        (tee_local $8
         (i32.load offset=4
          (get_local $0)
         )
        )
        (i32.const 124)
       )
      )
     )
     (i32.const -1)
    )
   )
   (i64.store
    (i32.add
     (get_local $9)
     (i32.const 24)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $9)
     (i32.const 16)
    )
    (i64.const 0)
   )
   (i64.store offset=8
    (get_local $9)
    (i64.const 0)
   )
   (i64.store
    (get_local $9)
    (i64.const 0)
   )
   (set_local $6
    (call $db_idx256_find_primary
     (i64.load
      (tee_local $6
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $6)
     )
     (i64.const -5003134530400288766)
     (get_local $9)
     (i32.const 2)
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
     (i32.const 124)
    )
    (get_local $6)
   )
  )
  (i64.store
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx256_next
       (get_local $6)
       (get_local $9)
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load
     (get_local $9)
    )
   )
   (block $label$2
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $2
          (i32.load
           (i32.load
            (get_local $0)
           )
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $4
       (i32.load offset=24
        (get_local $2)
       )
      )
     )
    )
    (set_local $7
     (i32.add
      (get_local $8)
      (i32.const -24)
     )
    )
    (set_local $5
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (loop $label$3
     (br_if $label$2
      (i64.eq
       (i64.load
        (i32.load
         (get_local $7)
        )
       )
       (get_local $3)
      )
     )
     (set_local $8
      (get_local $7)
     )
     (set_local $7
      (tee_local $6
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
     (br_if $label$3
      (i32.ne
       (i32.add
        (get_local $6)
        (get_local $5)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (get_local $8)
       (get_local $4)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $7
         (i32.load
          (i32.add
           (get_local $8)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $2)
      )
      (i32.const 112)
     )
     (br $label$4)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (call $db_find_i64
          (i64.load
           (get_local $2)
          )
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const -5003134530400288768)
          (get_local $3)
         )
        )
       )
      )
      (get_local $2)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 124)
    )
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954608ESD_Ly2ELb0EE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i64.store offset=40
   (get_local $9)
   (i64.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $7
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (block $label$2
     (br_if $label$2
      (i32.ne
       (tee_local $5
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const 124)
         )
        )
       )
       (i32.const -1)
      )
     )
     (i64.store
      (i32.add
       (get_local $9)
       (i32.const 24)
      )
      (i64.const 0)
     )
     (i64.store
      (i32.add
       (get_local $9)
       (i32.const 16)
      )
      (i64.const 0)
     )
     (i64.store offset=8
      (get_local $9)
      (i64.const 0)
     )
     (i64.store
      (get_local $9)
      (i64.const 0)
     )
     (set_local $5
      (call $db_idx256_find_primary
       (i64.load
        (tee_local $5
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const -5003134530400288766)
       (get_local $9)
       (i32.const 2)
       (i64.load
        (get_local $7)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
       (i32.const 124)
      )
      (get_local $5)
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $6
        (call $db_idx256_previous
         (get_local $5)
         (i32.add
          (get_local $9)
          (i32.const 40)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1824)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $7
      (call $db_idx256_end
       (i64.load
        (tee_local $7
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $7)
       )
       (i64.const -5003134530400288766)
      )
     )
     (i32.const -1)
    )
    (i32.const 1760)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_idx256_previous
        (get_local $7)
        (i32.add
         (get_local $9)
         (i32.const 40)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1760)
   )
  )
  (set_local $2
   (i64.load offset=40
    (get_local $9)
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.eq
     (tee_local $8
      (i32.load
       (i32.add
        (tee_local $1
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$4
    (br_if $label$3
     (i64.eq
      (i64.load
       (i32.load
        (get_local $7)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $7)
    )
    (set_local $7
     (tee_local $5
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br_if $label$4
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $8)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $1)
     )
     (i32.const 112)
    )
    (br $label$5)
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=108
      (tee_local $7
       (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (call $db_find_i64
         (i64.load
          (get_local $1)
         )
         (i64.load offset=8
          (get_local $1)
         )
         (i64.const -5003134530400288768)
         (get_local $2)
        )
       )
      )
     )
     (get_local $1)
    )
    (i32.const 112)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 124)
   )
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 48)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE11lower_boundERKd (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx_double_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288765)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=8
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (i64.load
           (get_local $4)
          )
          (i64.load offset=8
           (get_local $4)
          )
          (i64.const -5003134530400288768)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 128)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE11upper_boundERKd (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx_double_upperbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288765)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=8
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (i64.load
           (get_local $4)
          )
          (i64.load offset=8
           (get_local $4)
          )
          (i64.const -5003134530400288768)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 128)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1504)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $6
      (i32.load
       (i32.add
        (tee_local $8
         (i32.load offset=4
          (get_local $0)
         )
        )
        (i32.const 128)
       )
      )
     )
     (i32.const -1)
    )
   )
   (set_local $6
    (call $db_idx_double_find_primary
     (i64.load
      (tee_local $6
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $6)
     )
     (i64.const -5003134530400288765)
     (i32.add
      (get_local $9)
      (i32.const 8)
     )
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
     (i32.const 128)
    )
    (get_local $6)
   )
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx_double_next
       (get_local $6)
       (i32.add
        (get_local $9)
        (i32.const 8)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load offset=8
     (get_local $9)
    )
   )
   (block $label$2
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $2
          (i32.load
           (i32.load
            (get_local $0)
           )
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $4
       (i32.load offset=24
        (get_local $2)
       )
      )
     )
    )
    (set_local $7
     (i32.add
      (get_local $8)
      (i32.const -24)
     )
    )
    (set_local $5
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (loop $label$3
     (br_if $label$2
      (i64.eq
       (i64.load
        (i32.load
         (get_local $7)
        )
       )
       (get_local $3)
      )
     )
     (set_local $8
      (get_local $7)
     )
     (set_local $7
      (tee_local $6
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
     (br_if $label$3
      (i32.ne
       (i32.add
        (get_local $6)
        (get_local $5)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (get_local $8)
       (get_local $4)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $7
         (i32.load
          (i32.add
           (get_local $8)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $2)
      )
      (i32.const 112)
     )
     (br $label$4)
    )
    (set_local $7
     (i32.const 0)
    )
    (br_if $label$4
     (i32.lt_s
      (tee_local $6
       (call $db_find_i64
        (i64.load
         (get_local $2)
        )
        (i64.load offset=8
         (get_local $2)
        )
        (i64.const -5003134530400288768)
        (get_local $3)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (get_local $6)
        )
       )
      )
      (get_local $2)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 128)
    )
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954624ESF_Ly3ELb0EE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i64.store offset=8
   (get_local $9)
   (i64.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $7
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (block $label$2
     (br_if $label$2
      (i32.ne
       (tee_local $5
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const 128)
         )
        )
       )
       (i32.const -1)
      )
     )
     (set_local $5
      (call $db_idx_double_find_primary
       (i64.load
        (tee_local $5
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const -5003134530400288765)
       (get_local $9)
       (i64.load
        (get_local $7)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
       (i32.const 128)
      )
      (get_local $5)
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $6
        (call $db_idx_double_previous
         (get_local $5)
         (i32.add
          (get_local $9)
          (i32.const 8)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1824)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $7
      (call $db_idx_double_end
       (i64.load
        (tee_local $7
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $7)
       )
       (i64.const -5003134530400288765)
      )
     )
     (i32.const -1)
    )
    (i32.const 1760)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_idx_double_previous
        (get_local $7)
        (i32.add
         (get_local $9)
         (i32.const 8)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1760)
   )
  )
  (set_local $2
   (i64.load offset=8
    (get_local $9)
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.eq
     (tee_local $8
      (i32.load
       (i32.add
        (tee_local $1
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$4
    (br_if $label$3
     (i64.eq
      (i64.load
       (i32.load
        (get_local $7)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $7)
    )
    (set_local $7
     (tee_local $5
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br_if $label$4
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $8)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $1)
     )
     (i32.const 112)
    )
    (br $label$5)
   )
   (set_local $7
    (i32.const 0)
   )
   (br_if $label$5
    (i32.lt_s
     (tee_local $5
      (call $db_find_i64
       (i64.load
        (get_local $1)
       )
       (i64.load offset=8
        (get_local $1)
       )
       (i64.const -5003134530400288768)
       (get_local $2)
      )
     )
     (i32.const 0)
    )
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=108
      (tee_local $7
       (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (get_local $5)
       )
      )
     )
     (get_local $1)
    )
    (i32.const 112)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 128)
   )
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE11lower_boundERKe (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx_long_double_lowerbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288764)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 24)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=24
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 132)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
 )
 (func $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE11upper_boundERKe (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $10
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (set_local $2
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.lt_s
     (tee_local $3
      (call $db_idx_long_double_upperbound
       (i64.load
        (tee_local $8
         (i32.load
          (get_local $1)
         )
        )
       )
       (i64.load offset=8
        (get_local $8)
       )
       (i64.const -5003134530400288764)
       (get_local $10)
       (i32.add
        (get_local $10)
        (i32.const 24)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=24
     (get_local $10)
    )
   )
   (block $label$1
    (br_if $label$1
     (i32.eq
      (tee_local $9
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load
           (get_local $1)
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $6
       (i32.load offset=24
        (get_local $4)
       )
      )
     )
    )
    (set_local $2
     (i32.add
      (get_local $9)
      (i32.const -24)
     )
    )
    (set_local $7
     (i32.sub
      (i32.const 0)
      (get_local $6)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i64.eq
       (i64.load
        (i32.load
         (get_local $2)
        )
       )
       (get_local $5)
      )
     )
     (set_local $9
      (get_local $2)
     )
     (set_local $2
      (tee_local $8
       (i32.add
        (get_local $2)
        (i32.const -24)
       )
      )
     )
     (br_if $label$2
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $7)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$3
    (block $label$4
     (br_if $label$4
      (i32.eq
       (get_local $9)
       (get_local $6)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $2
         (i32.load
          (i32.add
           (get_local $9)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $4)
      )
      (i32.const 112)
     )
     (br $label$3)
    )
    (set_local $2
     (i32.const 0)
    )
    (br_if $label$3
     (i32.lt_s
      (tee_local $8
       (call $db_find_i64
        (i64.load
         (get_local $4)
        )
        (i64.load offset=8
         (get_local $4)
        )
        (i64.const -5003134530400288768)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $2
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (get_local $8)
        )
       )
      )
      (get_local $4)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 132)
    )
    (get_local $3)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $2)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $eosio_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 1504)
  )
  (block $label$0
   (br_if $label$0
    (i32.ne
     (tee_local $6
      (i32.load
       (i32.add
        (tee_local $8
         (i32.load offset=4
          (get_local $0)
         )
        )
        (i32.const 132)
       )
      )
     )
     (i32.const -1)
    )
   )
   (set_local $6
    (call $db_idx_long_double_find_primary
     (i64.load
      (tee_local $6
       (i32.load
        (i32.load
         (get_local $0)
        )
       )
      )
     )
     (i64.load offset=8
      (get_local $6)
     )
     (i64.const -5003134530400288764)
     (get_local $9)
     (i64.load
      (get_local $8)
     )
    )
   )
   (i32.store
    (i32.add
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
     (i32.const 132)
    )
    (get_local $6)
   )
  )
  (i64.store
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx_long_double_next
       (get_local $6)
       (get_local $9)
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load
     (get_local $9)
    )
   )
   (block $label$2
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $2
          (i32.load
           (i32.load
            (get_local $0)
           )
          )
         )
         (i32.const 28)
        )
       )
      )
      (tee_local $4
       (i32.load offset=24
        (get_local $2)
       )
      )
     )
    )
    (set_local $7
     (i32.add
      (get_local $8)
      (i32.const -24)
     )
    )
    (set_local $5
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (loop $label$3
     (br_if $label$2
      (i64.eq
       (i64.load
        (i32.load
         (get_local $7)
        )
       )
       (get_local $3)
      )
     )
     (set_local $8
      (get_local $7)
     )
     (set_local $7
      (tee_local $6
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
     (br_if $label$3
      (i32.ne
       (i32.add
        (get_local $6)
        (get_local $5)
       )
       (i32.const -24)
      )
     )
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.eq
       (get_local $8)
       (get_local $4)
      )
     )
     (call $eosio_assert
      (i32.eq
       (i32.load offset=108
        (tee_local $7
         (i32.load
          (i32.add
           (get_local $8)
           (i32.const -24)
          )
         )
        )
       )
       (get_local $2)
      )
      (i32.const 112)
     )
     (br $label$4)
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (call $db_find_i64
          (i64.load
           (get_local $2)
          )
          (i64.load offset=8
           (get_local $2)
          )
          (i64.const -5003134530400288768)
          (get_local $3)
         )
        )
       )
      )
      (get_local $2)
     )
     (i32.const 112)
    )
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 132)
    )
    (get_local $1)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5indexILy4589348694149954640ESH_Ly4ELb0EE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i64.store offset=24
   (get_local $9)
   (i64.const 0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $7
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (block $label$2
     (br_if $label$2
      (i32.ne
       (tee_local $5
        (i32.load
         (i32.add
          (get_local $7)
          (i32.const 132)
         )
        )
       )
       (i32.const -1)
      )
     )
     (set_local $5
      (call $db_idx_long_double_find_primary
       (i64.load
        (tee_local $5
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $5)
       )
       (i64.const -5003134530400288764)
       (get_local $9)
       (i64.load
        (get_local $7)
       )
      )
     )
     (i32.store
      (i32.add
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 4)
        )
       )
       (i32.const 132)
      )
      (get_local $5)
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $6
        (call $db_idx_long_double_previous
         (get_local $5)
         (i32.add
          (get_local $9)
          (i32.const 24)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1824)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $7
      (call $db_idx_long_double_end
       (i64.load
        (tee_local $7
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
       )
       (i64.load offset=8
        (get_local $7)
       )
       (i64.const -5003134530400288764)
      )
     )
     (i32.const -1)
    )
    (i32.const 1760)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $6
       (call $db_idx_long_double_previous
        (get_local $7)
        (i32.add
         (get_local $9)
         (i32.const 24)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1760)
   )
  )
  (set_local $2
   (i64.load offset=24
    (get_local $9)
   )
  )
  (block $label$3
   (br_if $label$3
    (i32.eq
     (tee_local $8
      (i32.load
       (i32.add
        (tee_local $1
         (i32.load
          (i32.load
           (get_local $0)
          )
         )
        )
        (i32.const 28)
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $1)
      )
     )
    )
   )
   (set_local $7
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (set_local $4
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (loop $label$4
    (br_if $label$3
     (i64.eq
      (i64.load
       (i32.load
        (get_local $7)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $7)
    )
    (set_local $7
     (tee_local $5
      (i32.add
       (get_local $7)
       (i32.const -24)
      )
     )
    )
    (br_if $label$4
     (i32.ne
      (i32.add
       (get_local $5)
       (get_local $4)
      )
      (i32.const -24)
     )
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $8)
      (get_local $3)
     )
    )
    (call $eosio_assert
     (i32.eq
      (i32.load offset=108
       (tee_local $7
        (i32.load
         (i32.add
          (get_local $8)
          (i32.const -24)
         )
        )
       )
      )
      (get_local $1)
     )
     (i32.const 112)
    )
    (br $label$5)
   )
   (call $eosio_assert
    (i32.eq
     (i32.load offset=108
      (tee_local $7
       (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
        (get_local $1)
        (call $db_find_i64
         (i64.load
          (get_local $1)
         )
         (i64.load offset=8
          (get_local $1)
         )
         (i64.const -5003134530400288768)
         (get_local $2)
        )
       )
      )
     )
     (get_local $1)
    )
    (i32.const 112)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (get_local $7)
  )
  (i32.store
   (i32.add
    (get_local $7)
    (i32.const 132)
   )
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $2
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $1
       (i32.load offset=4
        (get_local $0)
       )
      )
     )
    )
    (call $eosio_assert
     (i32.xor
      (i32.shr_u
       (tee_local $1
        (call $db_previous_i64
         (i32.load offset=112
          (get_local $1)
         )
         (i32.add
          (get_local $2)
          (i32.const 8)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1712)
    )
    (br $label$0)
   )
   (call $eosio_assert
    (i32.ne
     (tee_local $1
      (call $db_end_i64
       (i64.load
        (tee_local $1
         (i32.load
          (get_local $0)
         )
        )
       )
       (i64.load offset=8
        (get_local $1)
       )
       (i64.const -5003134530400288768)
      )
     )
     (i32.const -1)
    )
    (i32.const 1648)
   )
   (call $eosio_assert
    (i32.xor
     (i32.shr_u
      (tee_local $1
       (call $db_previous_i64
        (get_local $1)
        (i32.add
         (get_local $2)
         (i32.const 8)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1648)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (call $_ZNK5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE31load_object_by_primary_iteratorEl
    (i32.load
     (get_local $0)
    )
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $2)
    (i32.const 16)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio11multi_indexILy13443609543309262848ENS_5token6recordEJNS_10indexed_byILy4589348694149954576EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_15get_secondary_1EvEEEEEENS3_ILy4589348694149954592ENS6_IS2_oXadL_ZNKS2_15get_secondary_2EvEEEEEENS3_ILy4589348694149954608ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_15get_secondary_3EvEEEEEENS3_ILy4589348694149954624ENS6_IS2_dXadL_ZNKS2_15get_secondary_4EvEEEEEENS3_ILy4589348694149954640ENS6_IS2_eXadL_ZNKS2_15get_secondary_5EvEEEEEEEE5eraseERKS2_ (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.eq
    (i32.load offset=108
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 1312)
  )
  (call $eosio_assert
   (i64.eq
    (i64.load
     (get_local $0)
    )
    (call $current_receiver)
   )
   (i32.const 1360)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $7
      (i32.load
       (tee_local $5
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
     )
     (tee_local $3
      (i32.load offset=24
       (get_local $0)
      )
     )
    )
   )
   (set_local $2
    (i64.load
     (get_local $1)
    )
   )
   (set_local $6
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $8
    (i32.add
     (get_local $7)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $8)
       )
      )
      (get_local $2)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (set_local $8
     (tee_local $4
      (i32.add
       (get_local $8)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $6)
      )
      (i32.const -24)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $7)
    (get_local $3)
   )
   (i32.const 1424)
  )
  (set_local $8
   (i32.add
    (get_local $7)
    (i32.const -24)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $7)
      (tee_local $4
       (i32.load
        (get_local $5)
       )
      )
     )
    )
    (set_local $3
     (i32.sub
      (i32.const 0)
      (get_local $4)
     )
    )
    (set_local $7
     (get_local $8)
    )
    (loop $label$4
     (set_local $6
      (i32.load
       (tee_local $8
        (i32.add
         (get_local $7)
         (i32.const 24)
        )
       )
      )
     )
     (i32.store
      (get_local $8)
      (i32.const 0)
     )
     (set_local $4
      (i32.load
       (get_local $7)
      )
     )
     (i32.store
      (get_local $7)
      (get_local $6)
     )
     (block $label$5
      (br_if $label$5
       (i32.eqz
        (get_local $4)
       )
      )
      (block $label$6
       (br_if $label$6
        (i32.eqz
         (i32.and
          (i32.load8_u offset=96
           (get_local $4)
          )
          (i32.const 1)
         )
        )
       )
       (call $_ZdlPv
        (i32.load
         (i32.add
          (get_local $4)
          (i32.const 104)
         )
        )
       )
      )
      (call $_ZdlPv
       (get_local $4)
      )
     )
     (i32.store
      (i32.add
       (get_local $7)
       (i32.const 16)
      )
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 40)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $7)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $7)
        (i32.const 32)
       )
      )
     )
     (set_local $7
      (get_local $8)
     )
     (br_if $label$4
      (i32.ne
       (i32.add
        (get_local $8)
        (get_local $3)
       )
       (i32.const -24)
      )
     )
    )
    (br_if $label$2
     (i32.eq
      (tee_local $7
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 28)
        )
       )
      )
      (get_local $8)
     )
    )
   )
   (loop $label$7
    (set_local $4
     (i32.load
      (tee_local $7
       (i32.add
        (get_local $7)
        (i32.const -24)
       )
      )
     )
    )
    (i32.store
     (get_local $7)
     (i32.const 0)
    )
    (block $label$8
     (br_if $label$8
      (i32.eqz
       (get_local $4)
      )
     )
     (block $label$9
      (br_if $label$9
       (i32.eqz
        (i32.and
         (i32.load8_u offset=96
          (get_local $4)
         )
         (i32.const 1)
        )
       )
      )
      (call $_ZdlPv
       (i32.load
        (i32.add
         (get_local $4)
         (i32.const 104)
        )
       )
      )
     )
     (call $_ZdlPv
      (get_local $4)
     )
    )
    (br_if $label$7
     (i32.ne
      (get_local $8)
      (get_local $7)
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 28)
   )
   (get_local $8)
  )
  (call $db_remove_i64
   (i32.load offset=112
    (get_local $1)
   )
  )
  (i32.store offset=4
   (get_local $9)
   (get_local $1)
  )
  (i32.store
   (get_local $9)
   (get_local $0)
  )
  (i32.store offset=8
   (get_local $9)
   (get_local $9)
  )
  (call $_ZNK5boost4hana6detail7on_eachIPZN5eosio11multi_indexILy13443609543309262848ENS3_5token6recordEJNS3_10indexed_byILy4589348694149954576ENS_11multi_index13const_mem_funIS6_yXadL_ZNKS6_15get_secondary_1EvEEEEEENS7_ILy4589348694149954592ENS9_IS6_oXadL_ZNKS6_15get_secondary_2EvEEEEEENS7_ILy4589348694149954608ENS9_IS6_NS3_9fixed_keyILj32EEEXadL_ZNKS6_15get_secondary_3EvEEEEEENS7_ILy4589348694149954624ENS9_IS6_dXadL_ZNKS6_15get_secondary_4EvEEEEEENS7_ILy4589348694149954640ENS9_IS6_eXadL_ZNKS6_15get_secondary_5EvEEEEEEEE5eraseERKS6_EUlRT_E_EclIJRNS0_5tupleIJNS0_9type_implINSM_5indexILy4589348694149954576ESA_Ly0ELb0EEEE1_ENSW_INSX_ILy4589348694149954576ESA_Ly0ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954592ESC_Ly1ELb0EEEE1_ENSW_INSX_ILy4589348694149954592ESC_Ly1ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954608ESG_Ly2ELb0EEEE1_ENSW_INSX_ILy4589348694149954608ESG_Ly2ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954624ESI_Ly3ELb0EEEE1_ENSW_INSX_ILy4589348694149954624ESI_Ly3ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954640ESK_Ly4ELb0EEEE1_ENSW_INSX_ILy4589348694149954640ESK_Ly4ELb1EEEE1_EEEEEEEvDpOT_
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (i32.add
    (get_local $0)
    (i32.const 36)
   )
   (i32.add
    (get_local $0)
    (i32.const 37)
   )
   (i32.add
    (get_local $0)
    (i32.const 38)
   )
   (i32.add
    (get_local $0)
    (i32.const 39)
   )
   (i32.add
    (get_local $0)
    (i32.const 40)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 16)
   )
  )
 )
 (func $_ZNK5boost4hana6detail7on_eachIPZN5eosio11multi_indexILy13443609543309262848ENS3_5token6recordEJNS3_10indexed_byILy4589348694149954576ENS_11multi_index13const_mem_funIS6_yXadL_ZNKS6_15get_secondary_1EvEEEEEENS7_ILy4589348694149954592ENS9_IS6_oXadL_ZNKS6_15get_secondary_2EvEEEEEENS7_ILy4589348694149954608ENS9_IS6_NS3_9fixed_keyILj32EEEXadL_ZNKS6_15get_secondary_3EvEEEEEENS7_ILy4589348694149954624ENS9_IS6_dXadL_ZNKS6_15get_secondary_4EvEEEEEENS7_ILy4589348694149954640ENS9_IS6_eXadL_ZNKS6_15get_secondary_5EvEEEEEEEE5eraseERKS6_EUlRT_E_EclIJRNS0_5tupleIJNS0_9type_implINSM_5indexILy4589348694149954576ESA_Ly0ELb0EEEE1_ENSW_INSX_ILy4589348694149954576ESA_Ly0ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954592ESC_Ly1ELb0EEEE1_ENSW_INSX_ILy4589348694149954592ESC_Ly1ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954608ESG_Ly2ELb0EEEE1_ENSW_INSX_ILy4589348694149954608ESG_Ly2ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954624ESI_Ly3ELb0EEEE1_ENSW_INSX_ILy4589348694149954624ESI_Ly3ELb1EEEE1_EEEERNSV_IJNSW_INSX_ILy4589348694149954640ESK_Ly4ELb0EEEE1_ENSW_INSX_ILy4589348694149954640ESK_Ly4ELb1EEEE1_EEEEEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (param $4 i32) (param $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.gt_s
      (tee_local $8
       (i32.load offset=116
        (tee_local $6
         (i32.load offset=4
          (tee_local $7
           (i32.load
            (get_local $0)
           )
          )
         )
        )
       )
      )
      (i32.const -1)
     )
    )
    (br_if $label$0
     (i32.lt_s
      (tee_local $8
       (call $db_idx64_find_primary
        (i64.load
         (tee_local $8
          (i32.load
           (get_local $7)
          )
         )
        )
        (i64.load offset=8
         (get_local $8)
        )
        (i64.const -5003134530400288768)
        (get_local $9)
        (i64.load
         (get_local $6)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx64_remove
    (get_local $8)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.gt_s
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $6
          (i32.load offset=4
           (tee_local $7
            (i32.load
             (get_local $0)
            )
           )
          )
         )
         (i32.const 120)
        )
       )
      )
      (i32.const -1)
     )
    )
    (br_if $label$2
     (i32.lt_s
      (tee_local $8
       (call $db_idx128_find_primary
        (i64.load
         (tee_local $8
          (i32.load
           (get_local $7)
          )
         )
        )
        (i64.load offset=8
         (get_local $8)
        )
        (i64.const -5003134530400288767)
        (get_local $9)
        (i64.load
         (get_local $6)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx128_remove
    (get_local $8)
   )
  )
  (block $label$4
   (block $label$5
    (br_if $label$5
     (i32.gt_s
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $6
          (i32.load offset=4
           (tee_local $7
            (i32.load
             (get_local $0)
            )
           )
          )
         )
         (i32.const 124)
        )
       )
      )
      (i32.const -1)
     )
    )
    (set_local $8
     (i32.load
      (get_local $7)
     )
    )
    (i64.store
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i64.const 0)
    )
    (i64.store
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
     (i64.const 0)
    )
    (i64.store offset=8
     (get_local $9)
     (i64.const 0)
    )
    (i64.store
     (get_local $9)
     (i64.const 0)
    )
    (br_if $label$4
     (i32.lt_s
      (tee_local $8
       (call $db_idx256_find_primary
        (i64.load
         (get_local $8)
        )
        (i64.load offset=8
         (get_local $8)
        )
        (i64.const -5003134530400288766)
        (get_local $9)
        (i32.const 2)
        (i64.load
         (get_local $6)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx256_remove
    (get_local $8)
   )
  )
  (block $label$6
   (block $label$7
    (br_if $label$7
     (i32.gt_s
      (tee_local $8
       (i32.load
        (i32.add
         (tee_local $6
          (i32.load offset=4
           (tee_local $7
            (i32.load
             (get_local $0)
            )
           )
          )
         )
         (i32.const 128)
        )
       )
      )
      (i32.const -1)
     )
    )
    (br_if $label$6
     (i32.lt_s
      (tee_local $8
       (call $db_idx_double_find_primary
        (i64.load
         (tee_local $8
          (i32.load
           (get_local $7)
          )
         )
        )
        (i64.load offset=8
         (get_local $8)
        )
        (i64.const -5003134530400288765)
        (get_local $9)
        (i64.load
         (get_local $6)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx_double_remove
    (get_local $8)
   )
  )
  (block $label$8
   (block $label$9
    (br_if $label$9
     (i32.gt_s
      (tee_local $0
       (i32.load
        (i32.add
         (tee_local $7
          (i32.load offset=4
           (tee_local $8
            (i32.load
             (get_local $0)
            )
           )
          )
         )
         (i32.const 132)
        )
       )
      )
      (i32.const -1)
     )
    )
    (br_if $label$8
     (i32.lt_s
      (tee_local $0
       (call $db_idx_long_double_find_primary
        (i64.load
         (tee_local $0
          (i32.load
           (get_local $8)
          )
         )
        )
        (i64.load offset=8
         (get_local $0)
        )
        (i64.const -5003134530400288764)
        (get_local $9)
        (i64.load
         (get_local $7)
        )
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx_long_double_remove
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 32)
   )
  )
 )
 (func $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNS_5token6recordE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (get_local $1)
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 1)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.const 2)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 2)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 304)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 16)
   )
  )
  (call $_ZN5eosiolsINS_10datastreamIPcEEEERT_S5_RKNSt3__112basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEE
   (get_local $0)
   (i32.add
    (get_local $1)
    (i32.const 96)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNS_5token6recordE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (i32.load offset=4
      (get_local $0)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $1)
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 16)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 1)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 2)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 2)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 80)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 16)
   )
  )
  (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE
   (get_local $0)
   (i32.add
    (get_local $1)
    (i32.const 96)
   )
  )
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 32)
    )
   )
  )
  (i32.store offset=24
   (get_local $7)
   (i32.const 0)
  )
  (i64.store offset=16
   (get_local $7)
   (i64.const 0)
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__16vectorIcNS7_9allocatorIcEEEE
    (get_local $0)
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (block $label$6
         (block $label$7
          (block $label$8
           (br_if $label$8
            (i32.ne
             (tee_local $5
              (i32.load offset=20
               (get_local $7)
              )
             )
             (tee_local $4
              (i32.load offset=16
               (get_local $7)
              )
             )
            )
           )
           (br_if $label$7
            (i32.and
             (i32.load8_u
              (get_local $1)
             )
             (i32.const 1)
            )
           )
           (i32.store16
            (get_local $1)
            (i32.const 0)
           )
           (set_local $4
            (i32.add
             (get_local $1)
             (i32.const 8)
            )
           )
           (br $label$6)
          )
          (i32.store
           (i32.add
            (get_local $7)
            (i32.const 8)
           )
           (i32.const 0)
          )
          (i64.store
           (get_local $7)
           (i64.const 0)
          )
          (br_if $label$0
           (i32.ge_u
            (tee_local $2
             (i32.sub
              (get_local $5)
              (get_local $4)
             )
            )
            (i32.const -16)
           )
          )
          (br_if $label$5
           (i32.ge_u
            (get_local $2)
            (i32.const 11)
           )
          )
          (i32.store8
           (get_local $7)
           (i32.shl
            (get_local $2)
            (i32.const 1)
           )
          )
          (set_local $6
           (i32.or
            (get_local $7)
            (i32.const 1)
           )
          )
          (br_if $label$4
           (get_local $2)
          )
          (br $label$3)
         )
         (i32.store8
          (i32.load offset=8
           (get_local $1)
          )
          (i32.const 0)
         )
         (i32.store offset=4
          (get_local $1)
          (i32.const 0)
         )
         (set_local $4
          (i32.add
           (get_local $1)
           (i32.const 8)
          )
         )
        )
        (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
         (get_local $1)
         (i32.const 0)
        )
        (i32.store
         (get_local $4)
         (i32.const 0)
        )
        (i64.store align=4
         (get_local $1)
         (i64.const 0)
        )
        (br_if $label$2
         (tee_local $4
          (i32.load offset=16
           (get_local $7)
          )
         )
        )
        (br $label$1)
       )
       (set_local $6
        (call $_Znwj
         (tee_local $5
          (i32.and
           (i32.add
            (get_local $2)
            (i32.const 16)
           )
           (i32.const -16)
          )
         )
        )
       )
       (i32.store
        (get_local $7)
        (i32.or
         (get_local $5)
         (i32.const 1)
        )
       )
       (i32.store offset=8
        (get_local $7)
        (get_local $6)
       )
       (i32.store offset=4
        (get_local $7)
        (get_local $2)
       )
      )
      (set_local $3
       (get_local $2)
      )
      (set_local $5
       (get_local $6)
      )
      (loop $label$9
       (i32.store8
        (get_local $5)
        (i32.load8_u
         (get_local $4)
        )
       )
       (set_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
       (set_local $4
        (i32.add
         (get_local $4)
         (i32.const 1)
        )
       )
       (br_if $label$9
        (tee_local $3
         (i32.add
          (get_local $3)
          (i32.const -1)
         )
        )
       )
      )
      (set_local $6
       (i32.add
        (get_local $6)
        (get_local $2)
       )
      )
     )
     (i32.store8
      (get_local $6)
      (i32.const 0)
     )
     (block $label$10
      (block $label$11
       (br_if $label$11
        (i32.and
         (i32.load8_u
          (get_local $1)
         )
         (i32.const 1)
        )
       )
       (i32.store16
        (get_local $1)
        (i32.const 0)
       )
       (br $label$10)
      )
      (i32.store8
       (i32.load offset=8
        (get_local $1)
       )
       (i32.const 0)
      )
      (i32.store offset=4
       (get_local $1)
       (i32.const 0)
      )
     )
     (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj
      (get_local $1)
      (i32.const 0)
     )
     (i32.store
      (i32.add
       (get_local $1)
       (i32.const 8)
      )
      (i32.load
       (i32.add
        (get_local $7)
        (i32.const 8)
       )
      )
     )
     (i64.store align=4
      (get_local $1)
      (i64.load
       (get_local $7)
      )
     )
     (br_if $label$1
      (i32.eqz
       (tee_local $4
        (i32.load offset=16
         (get_local $7)
        )
       )
      )
     )
    )
    (i32.store offset=20
     (get_local $7)
     (get_local $4)
    )
    (call $_ZdlPv
     (get_local $4)
    )
   )
   (i32.store offset=4
    (i32.const 0)
    (i32.add
     (get_local $7)
     (i32.const 32)
    )
   )
   (return
    (get_local $0)
   )
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (get_local $7)
  )
  (unreachable)
 )
 (func $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__16vectorIcNS7_9allocatorIcEEEE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (set_local $5
   (i32.load offset=4
    (get_local $0)
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (set_local $6
   (i64.const 0)
  )
  (set_local $2
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
  )
  (set_local $3
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
  )
  (loop $label$0
   (call $eosio_assert
    (i32.lt_u
     (get_local $5)
     (i32.load
      (get_local $2)
     )
    )
    (i32.const 1872)
   )
   (set_local $4
    (i32.load8_u
     (tee_local $5
      (i32.load
       (get_local $3)
      )
     )
    )
   )
   (i32.store
    (get_local $3)
    (tee_local $5
     (i32.add
      (get_local $5)
      (i32.const 1)
     )
    )
   )
   (set_local $6
    (i64.or
     (i64.extend_u/i32
      (i32.shl
       (i32.and
        (get_local $4)
        (i32.const 127)
       )
       (tee_local $7
        (i32.and
         (get_local $7)
         (i32.const 255)
        )
       )
      )
     )
     (get_local $6)
    )
   )
   (set_local $7
    (i32.add
     (get_local $7)
     (i32.const 7)
    )
   )
   (br_if $label$0
    (i32.shr_u
     (get_local $4)
     (i32.const 7)
    )
   )
  )
  (block $label$1
   (block $label$2
    (br_if $label$2
     (i32.le_u
      (tee_local $3
       (i32.wrap/i64
        (get_local $6)
       )
      )
      (tee_local $2
       (i32.sub
        (tee_local $7
         (i32.load offset=4
          (get_local $1)
         )
        )
        (tee_local $4
         (i32.load
          (get_local $1)
         )
        )
       )
      )
     )
    )
    (call $_ZNSt3__16vectorIcNS_9allocatorIcEEE8__appendEj
     (get_local $1)
     (i32.sub
      (get_local $3)
      (get_local $2)
     )
    )
    (set_local $5
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (set_local $7
     (i32.load
      (i32.add
       (get_local $1)
       (i32.const 4)
      )
     )
    )
    (set_local $4
     (i32.load
      (get_local $1)
     )
    )
    (br $label$1)
   )
   (br_if $label$1
    (i32.ge_u
     (get_local $3)
     (get_local $2)
    )
   )
   (i32.store
    (i32.add
     (get_local $1)
     (i32.const 4)
    )
    (tee_local $7
     (i32.add
      (get_local $4)
      (get_local $3)
     )
    )
   )
  )
  (call $eosio_assert
   (i32.ge_u
    (i32.sub
     (i32.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
     (get_local $5)
    )
    (tee_local $5
     (i32.sub
      (get_local $7)
      (get_local $4)
     )
    )
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $4)
    (i32.load
     (tee_local $7
      (i32.add
       (get_local $0)
       (i32.const 4)
      )
     )
    )
    (get_local $5)
   )
  )
  (i32.store
   (get_local $7)
   (i32.add
    (i32.load
     (get_local $7)
    )
    (get_local $5)
   )
  )
  (get_local $0)
 )
 (func $_ZN5eosio5token11testtrxauthEy (type $FUNCSIG$vij) (param $0 i32) (param $1 i64)
 )
 (func $apply (param $0 i64) (param $1 i64) (param $2 i64)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (local $7 i64)
  (local $8 i64)
  (local $9 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $9
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 208)
    )
   )
  )
  (set_local $6
   (i64.const 0)
  )
  (set_local $5
   (i64.const 59)
  )
  (set_local $4
   (i32.const 1952)
  )
  (set_local $7
   (i64.const 0)
  )
  (loop $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i64.gt_u
          (get_local $6)
          (i64.const 6)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $3
             (i32.load8_s
              (get_local $4)
             )
            )
            (i32.const -97)
           )
           (i32.const 255)
          )
          (i32.const 25)
         )
        )
        (set_local $3
         (i32.add
          (get_local $3)
          (i32.const 165)
         )
        )
        (br $label$3)
       )
       (set_local $8
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $6)
         (i64.const 11)
        )
       )
       (br $label$1)
      )
      (set_local $3
       (select
        (i32.add
         (get_local $3)
         (i32.const 208)
        )
        (i32.const 0)
        (i32.lt_u
         (i32.and
          (i32.add
           (get_local $3)
           (i32.const -49)
          )
          (i32.const 255)
         )
         (i32.const 5)
        )
       )
      )
     )
     (set_local $8
      (i64.shr_s
       (i64.shl
        (i64.extend_u/i32
         (get_local $3)
        )
        (i64.const 56)
       )
       (i64.const 56)
      )
     )
    )
    (set_local $8
     (i64.shl
      (i64.and
       (get_local $8)
       (i64.const 31)
      )
      (i64.and
       (get_local $5)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $4
    (i32.add
     (get_local $4)
     (i32.const 1)
    )
   )
   (set_local $6
    (i64.add
     (get_local $6)
     (i64.const 1)
    )
   )
   (set_local $7
    (i64.or
     (get_local $8)
     (get_local $7)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $5
      (i64.add
       (get_local $5)
       (i64.const -5)
      )
     )
     (i64.const -6)
    )
   )
  )
  (block $label$6
   (br_if $label$6
    (i64.ne
     (get_local $7)
     (get_local $2)
    )
   )
   (set_local $6
    (i64.const 0)
   )
   (set_local $5
    (i64.const 59)
   )
   (set_local $4
    (i32.const 1968)
   )
   (set_local $7
    (i64.const 0)
   )
   (loop $label$7
    (block $label$8
     (block $label$9
      (block $label$10
       (block $label$11
        (block $label$12
         (br_if $label$12
          (i64.gt_u
           (get_local $6)
           (i64.const 4)
          )
         )
         (br_if $label$11
          (i32.gt_u
           (i32.and
            (i32.add
             (tee_local $3
              (i32.load8_s
               (get_local $4)
              )
             )
             (i32.const -97)
            )
            (i32.const 255)
           )
           (i32.const 25)
          )
         )
         (set_local $3
          (i32.add
           (get_local $3)
           (i32.const 165)
          )
         )
         (br $label$10)
        )
        (set_local $8
         (i64.const 0)
        )
        (br_if $label$9
         (i64.le_u
          (get_local $6)
          (i64.const 11)
         )
        )
        (br $label$8)
       )
       (set_local $3
        (select
         (i32.add
          (get_local $3)
          (i32.const 208)
         )
         (i32.const 0)
         (i32.lt_u
          (i32.and
           (i32.add
            (get_local $3)
            (i32.const -49)
           )
           (i32.const 255)
          )
          (i32.const 5)
         )
        )
       )
      )
      (set_local $8
       (i64.shr_s
        (i64.shl
         (i64.extend_u/i32
          (get_local $3)
         )
         (i64.const 56)
        )
        (i64.const 56)
       )
      )
     )
     (set_local $8
      (i64.shl
       (i64.and
        (get_local $8)
        (i64.const 31)
       )
       (i64.and
        (get_local $5)
        (i64.const 4294967295)
       )
      )
     )
    )
    (set_local $4
     (i32.add
      (get_local $4)
      (i32.const 1)
     )
    )
    (set_local $6
     (i64.add
      (get_local $6)
      (i64.const 1)
     )
    )
    (set_local $7
     (i64.or
      (get_local $8)
      (get_local $7)
     )
    )
    (br_if $label$7
     (i64.ne
      (tee_local $5
       (i64.add
        (get_local $5)
        (i64.const -5)
       )
      )
      (i64.const -6)
     )
    )
   )
   (call $eosio_assert
    (i64.eq
     (get_local $7)
     (get_local $1)
    )
    (i32.const 1984)
   )
  )
  (block $label$13
   (block $label$14
    (br_if $label$14
     (i64.eq
      (get_local $1)
      (get_local $0)
     )
    )
    (set_local $6
     (i64.const 0)
    )
    (set_local $5
     (i64.const 59)
    )
    (set_local $4
     (i32.const 1952)
    )
    (set_local $7
     (i64.const 0)
    )
    (loop $label$15
     (block $label$16
      (block $label$17
       (block $label$18
        (block $label$19
         (block $label$20
          (br_if $label$20
           (i64.gt_u
            (get_local $6)
            (i64.const 6)
           )
          )
          (br_if $label$19
           (i32.gt_u
            (i32.and
             (i32.add
              (tee_local $3
               (i32.load8_s
                (get_local $4)
               )
              )
              (i32.const -97)
             )
             (i32.const 255)
            )
            (i32.const 25)
           )
          )
          (set_local $3
           (i32.add
            (get_local $3)
            (i32.const 165)
           )
          )
          (br $label$18)
         )
         (set_local $8
          (i64.const 0)
         )
         (br_if $label$17
          (i64.le_u
           (get_local $6)
           (i64.const 11)
          )
         )
         (br $label$16)
        )
        (set_local $3
         (select
          (i32.add
           (get_local $3)
           (i32.const 208)
          )
          (i32.const 0)
          (i32.lt_u
           (i32.and
            (i32.add
             (get_local $3)
             (i32.const -49)
            )
            (i32.const 255)
           )
           (i32.const 5)
          )
         )
        )
       )
       (set_local $8
        (i64.shr_s
         (i64.shl
          (i64.extend_u/i32
           (get_local $3)
          )
          (i64.const 56)
         )
         (i64.const 56)
        )
       )
      )
      (set_local $8
       (i64.shl
        (i64.and
         (get_local $8)
         (i64.const 31)
        )
        (i64.and
         (get_local $5)
         (i64.const 4294967295)
        )
       )
      )
     )
     (set_local $4
      (i32.add
       (get_local $4)
       (i32.const 1)
      )
     )
     (set_local $6
      (i64.add
       (get_local $6)
       (i64.const 1)
      )
     )
     (set_local $7
      (i64.or
       (get_local $8)
       (get_local $7)
      )
     )
     (br_if $label$15
      (i64.ne
       (tee_local $5
        (i64.add
         (get_local $5)
         (i64.const -5)
        )
       )
       (i64.const -6)
      )
     )
    )
    (br_if $label$13
     (i64.ne
      (get_local $7)
      (get_local $2)
     )
    )
   )
   (i64.store offset=200
    (get_local $9)
    (get_local $0)
   )
   (block $label$21
    (block $label$22
     (block $label$23
      (block $label$24
       (block $label$25
        (block $label$26
         (block $label$27
          (block $label$28
           (block $label$29
            (block $label$30
             (block $label$31
              (br_if $label$31
               (i64.gt_s
                (get_local $2)
                (i64.const -3841118729638772737)
               )
              )
              (br_if $label$30
               (i64.gt_s
                (get_local $2)
                (i64.const -3841125609434513409)
               )
              )
              (br_if $label$28
               (i64.eq
                (get_local $2)
                (i64.const -3841126159190327296)
               )
              )
              (br_if $label$27
               (i64.eq
                (get_local $2)
                (i64.const -3841126052645044224)
               )
              )
              (br_if $label$13
               (i64.ne
                (get_local $2)
                (i64.const -3841125867840536576)
               )
              )
              (i32.store offset=148
               (get_local $9)
               (i32.const 0)
              )
              (i32.store offset=144
               (get_local $9)
               (i32.const 1)
              )
              (i64.store offset=56 align=4
               (get_local $9)
               (i64.load offset=144
                (get_local $9)
               )
              )
              (drop
               (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
                (i32.add
                 (get_local $9)
                 (i32.const 200)
                )
                (i32.add
                 (get_local $9)
                 (i32.const 56)
                )
               )
              )
              (br $label$13)
             )
             (br_if $label$29
              (i64.gt_s
               (get_local $2)
               (i64.const -3617168760277827585)
              )
             )
             (br_if $label$26
              (i64.eq
               (get_local $2)
               (i64.const -3841118729638772736)
              )
             )
             (br_if $label$25
              (i64.eq
               (get_local $2)
               (i64.const -3841116954650440354)
              )
             )
             (br_if $label$13
              (i64.ne
               (get_local $2)
               (i64.const -3841116522779616768)
              )
             )
             (i32.store offset=108
              (get_local $9)
              (i32.const 0)
             )
             (i32.store offset=104
              (get_local $9)
              (i32.const 2)
             )
             (i64.store offset=96 align=4
              (get_local $9)
              (i64.load offset=104
               (get_local $9)
              )
             )
             (drop
              (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
               (i32.add
                (get_local $9)
                (i32.const 200)
               )
               (i32.add
                (get_local $9)
                (i32.const 96)
               )
              )
             )
             (br $label$13)
            )
            (br_if $label$24
             (i64.eq
              (get_local $2)
              (i64.const -3841125609434513408)
             )
            )
            (br_if $label$23
             (i64.eq
              (get_local $2)
              (i64.const -3841124327273005056)
             )
            )
            (br_if $label$13
             (i64.ne
              (get_local $2)
              (i64.const -3841120600428904448)
             )
            )
            (i32.store offset=124
             (get_local $9)
             (i32.const 0)
            )
            (i32.store offset=120
             (get_local $9)
             (i32.const 3)
            )
            (i64.store offset=80 align=4
             (get_local $9)
             (i64.load offset=120
              (get_local $9)
             )
            )
            (drop
             (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
              (i32.add
               (get_local $9)
               (i32.const 200)
              )
              (i32.add
               (get_local $9)
               (i32.const 80)
              )
             )
            )
            (br $label$13)
           )
           (br_if $label$22
            (i64.eq
             (get_local $2)
             (i64.const -3617168760277827584)
            )
           )
           (br_if $label$21
            (i64.eq
             (get_local $2)
             (i64.const 8516769789752901632)
            )
           )
           (br_if $label$13
            (i64.ne
             (get_local $2)
             (i64.const 5031766152489992192)
            )
           )
           (i32.store offset=196
            (get_local $9)
            (i32.const 0)
           )
           (i32.store offset=192
            (get_local $9)
            (i32.const 4)
           )
           (i64.store offset=8 align=4
            (get_local $9)
            (i64.load offset=192
             (get_local $9)
            )
           )
           (drop
            (call $_ZN5eosio14execute_actionINS_5tokenES1_JyNS_5assetEEEEbPT_MT0_FvDpT1_E
             (i32.add
              (get_local $9)
              (i32.const 200)
             )
             (i32.add
              (get_local $9)
              (i32.const 8)
             )
            )
           )
           (br $label$13)
          )
          (i32.store offset=172
           (get_local $9)
           (i32.const 0)
          )
          (i32.store offset=168
           (get_local $9)
           (i32.const 5)
          )
          (i64.store offset=32 align=4
           (get_local $9)
           (i64.load offset=168
            (get_local $9)
           )
          )
          (drop
           (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
            (i32.add
             (get_local $9)
             (i32.const 200)
            )
            (i32.add
             (get_local $9)
             (i32.const 32)
            )
           )
          )
          (br $label$13)
         )
         (i32.store offset=164
          (get_local $9)
          (i32.const 0)
         )
         (i32.store offset=160
          (get_local $9)
          (i32.const 6)
         )
         (i64.store offset=40 align=4
          (get_local $9)
          (i64.load offset=160
           (get_local $9)
          )
         )
         (drop
          (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
           (i32.add
            (get_local $9)
            (i32.const 200)
           )
           (i32.add
            (get_local $9)
            (i32.const 40)
           )
          )
         )
         (br $label$13)
        )
        (i32.store offset=140
         (get_local $9)
         (i32.const 0)
        )
        (i32.store offset=136
         (get_local $9)
         (i32.const 7)
        )
        (i64.store offset=64 align=4
         (get_local $9)
         (i64.load offset=136
          (get_local $9)
         )
        )
        (drop
         (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
          (i32.add
           (get_local $9)
           (i32.const 200)
          )
          (i32.add
           (get_local $9)
           (i32.const 64)
          )
         )
        )
        (br $label$13)
       )
       (i32.store offset=132
        (get_local $9)
        (i32.const 0)
       )
       (i32.store offset=128
        (get_local $9)
        (i32.const 8)
       )
       (i64.store offset=72 align=4
        (get_local $9)
        (i64.load offset=128
         (get_local $9)
        )
       )
       (drop
        (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
         (i32.add
          (get_local $9)
          (i32.const 200)
         )
         (i32.add
          (get_local $9)
          (i32.const 72)
         )
        )
       )
       (br $label$13)
      )
      (i32.store offset=116
       (get_local $9)
       (i32.const 0)
      )
      (i32.store offset=112
       (get_local $9)
       (i32.const 9)
      )
      (i64.store offset=88 align=4
       (get_local $9)
       (i64.load offset=112
        (get_local $9)
       )
      )
      (drop
       (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
        (i32.add
         (get_local $9)
         (i32.const 200)
        )
        (i32.add
         (get_local $9)
         (i32.const 88)
        )
       )
      )
      (br $label$13)
     )
     (i32.store offset=156
      (get_local $9)
      (i32.const 0)
     )
     (i32.store offset=152
      (get_local $9)
      (i32.const 10)
     )
     (i64.store offset=48 align=4
      (get_local $9)
      (i64.load offset=152
       (get_local $9)
      )
     )
     (drop
      (call $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E
       (i32.add
        (get_local $9)
        (i32.const 200)
       )
       (i32.add
        (get_local $9)
        (i32.const 48)
       )
      )
     )
     (br $label$13)
    )
    (i32.store offset=180
     (get_local $9)
     (i32.const 0)
    )
    (i32.store offset=176
     (get_local $9)
     (i32.const 11)
    )
    (i64.store offset=24 align=4
     (get_local $9)
     (i64.load offset=176
      (get_local $9)
     )
    )
    (drop
     (call $_ZN5eosio14execute_actionINS_5tokenES1_JyyNS_5assetENSt3__112basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_E
      (i32.add
       (get_local $9)
       (i32.const 200)
      )
      (i32.add
       (get_local $9)
       (i32.const 24)
      )
     )
    )
    (br $label$13)
   )
   (i32.store offset=188
    (get_local $9)
    (i32.const 0)
   )
   (i32.store offset=184
    (get_local $9)
    (i32.const 12)
   )
   (i64.store offset=16 align=4
    (get_local $9)
    (i64.load offset=184
     (get_local $9)
    )
   )
   (drop
    (call $_ZN5eosio14execute_actionINS_5tokenES1_JyNS_5assetENSt3__112basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_E
     (i32.add
      (get_local $9)
      (i32.const 200)
     )
     (i32.add
      (get_local $9)
      (i32.const 16)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 208)
   )
  )
 )
 (func $_ZN5eosio14execute_actionINS_5tokenES1_JyNS_5assetEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i64)
  (local $5 i32)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (set_local $9
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $7)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $8
   (i32.load
    (get_local $1)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (set_local $5
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $3
      (call $action_data_size)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.lt_u
       (get_local $3)
       (i32.const 513)
      )
     )
     (set_local $5
      (call $malloc
       (get_local $3)
      )
     )
     (br $label$1)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $5
      (i32.sub
       (get_local $7)
       (i32.and
        (i32.add
         (get_local $3)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $5)
     (get_local $3)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $9)
    (i32.const 40)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=32
   (get_local $9)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $9)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 320)
  )
  (set_local $6
   (i64.const 5462355)
  )
  (block $label$3
   (loop $label$4
    (set_local $7
     (i32.const 0)
    )
    (br_if $label$3
     (i32.gt_u
      (i32.add
       (i32.shl
        (i32.wrap/i64
         (get_local $6)
        )
        (i32.const 24)
       )
       (i32.const -1073741825)
      )
      (i32.const 452984830)
     )
    )
    (block $label$5
     (br_if $label$5
      (i64.ne
       (i64.and
        (tee_local $6
         (i64.shr_u
          (get_local $6)
          (i64.const 8)
         )
        )
        (i64.const 255)
       )
       (i64.const 0)
      )
     )
     (loop $label$6
      (br_if $label$3
       (i64.ne
        (i64.and
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (br_if $label$6
       (i32.lt_s
        (tee_local $1
         (i32.add
          (get_local $1)
          (i32.const 1)
         )
        )
        (i32.const 7)
       )
      )
     )
    )
    (set_local $7
     (i32.const 1)
    )
    (br_if $label$4
     (i32.lt_s
      (tee_local $1
       (i32.add
        (get_local $1)
        (i32.const 1)
       )
      )
      (i32.const 7)
     )
    )
   )
  )
  (call $eosio_assert
   (get_local $7)
   (i32.const 32)
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $3)
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $9)
     (i32.const 24)
    )
    (get_local $5)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (tee_local $7
     (i32.and
      (get_local $3)
      (i32.const -8)
     )
    )
    (i32.const 8)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (tee_local $1
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 24)
      )
      (i32.const 8)
     )
    )
    (i32.add
     (get_local $5)
     (i32.const 8)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.ne
    (get_local $7)
    (i32.const 16)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 24)
     )
     (i32.const 16)
    )
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
    (i32.const 8)
   )
  )
  (block $label$7
   (br_if $label$7
    (i32.lt_u
     (get_local $3)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $5)
   )
  )
  (i64.store
   (tee_local $7
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 48)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (set_local $6
   (i64.load offset=24
    (get_local $9)
   )
  )
  (i64.store offset=48
   (get_local $9)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 64)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $7)
   )
  )
  (i64.store offset=64
   (get_local $9)
   (i64.load offset=48
    (get_local $9)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$8
   (br_if $label$8
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $8
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 80)
    )
    (i32.const 8)
   )
   (tee_local $4
    (i64.load
     (i32.add
      (i32.add
       (get_local $9)
       (i32.const 64)
      )
      (i32.const 8)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $9)
     (i32.const 8)
    )
    (i32.const 8)
   )
   (get_local $4)
  )
  (i64.store offset=80
   (get_local $9)
   (tee_local $4
    (i64.load offset=64
     (get_local $9)
    )
   )
  )
  (i64.store offset=8
   (get_local $9)
   (get_local $4)
  )
  (call_indirect (type $FUNCSIG$viji)
   (get_local $1)
   (get_local $6)
   (i32.add
    (get_local $9)
    (i32.const 8)
   )
   (get_local $8)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $9)
    (i32.const 96)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_5tokenES1_JyNS_5assetENSt3__112basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 80)
    )
   )
  )
  (i32.store offset=60
   (tee_local $5
    (get_local $4)
   )
   (get_local $0)
  )
  (i32.store offset=48
   (get_local $5)
   (i32.load
    (get_local $1)
   )
  )
  (i32.store offset=52
   (get_local $5)
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (set_local $0
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $2
      (call $action_data_size)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.lt_u
       (get_local $2)
       (i32.const 513)
      )
     )
     (set_local $0
      (call $malloc
       (get_local $2)
      )
     )
     (br $label$1)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $0
      (i32.sub
       (get_local $4)
       (i32.and
        (i32.add
         (get_local $2)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $0)
     (get_local $2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $5)
    (i32.const 24)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=16
   (get_local $5)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $5)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 320)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (block $label$3
   (block $label$4
    (loop $label$5
     (br_if $label$4
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$6
      (br_if $label$6
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$7
       (br_if $label$4
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$7
        (i32.lt_s
         (tee_local $1
          (i32.add
           (get_local $1)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$5
      (i32.lt_s
       (tee_local $1
        (i32.add
         (get_local $1)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$3)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 32)
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=32
   (get_local $5)
   (i64.const 0)
  )
  (i32.store offset=64
   (get_local $5)
   (get_local $0)
  )
  (i32.store offset=72
   (get_local $5)
   (tee_local $1
    (i32.add
     (get_local $0)
     (get_local $2)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $2)
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $5)
     (i32.const 8)
    )
    (get_local $0)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (get_local $1)
     (tee_local $4
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 8)
     )
     (i32.const 8)
    )
    (get_local $4)
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (get_local $1)
     (tee_local $4
      (i32.add
       (get_local $0)
       (i32.const 16)
      )
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 8)
     )
     (i32.const 16)
    )
    (get_local $4)
    (i32.const 8)
   )
  )
  (i32.store offset=68
   (get_local $5)
   (i32.add
    (get_local $0)
    (i32.const 24)
   )
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE
    (i32.add
     (get_local $5)
     (i32.const 64)
    )
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 8)
     )
     (i32.const 24)
    )
   )
  )
  (block $label$8
   (br_if $label$8
    (i32.lt_u
     (get_local $2)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $0)
   )
  )
  (i32.store offset=68
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 48)
   )
  )
  (i32.store offset=64
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 60)
   )
  )
  (call $_ZN5boost4mp116detail16tuple_apply_implIRZN5eosio14execute_actionINS3_5tokenES5_JyNS3_5assetENSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_EEUlDpT_E_RNS7_5tupleIJyS6_SD_EEEJLj0ELj1ELj2EEEEDTclclsr3stdE7forwardISE_Efp_Espclsr3stdE3getIXT1_EEclsr3stdE7forwardISG_Efp0_EEEEOSE_OSG_NS0_16integer_sequenceIjJXspT1_EEEE
   (i32.add
    (get_local $5)
    (i32.const 64)
   )
   (i32.add
    (get_local $5)
    (i32.const 8)
   )
  )
  (block $label$9
   (br_if $label$9
    (i32.eqz
     (i32.and
      (i32.load8_u offset=32
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $5)
      (i32.const 40)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 80)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_5tokenES1_JyyNS_5assetENSt3__112basic_stringIcNS3_11char_traitsIcEENS3_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i32.store offset=60
   (tee_local $5
    (get_local $4)
   )
   (get_local $0)
  )
  (i32.store offset=48
   (get_local $5)
   (i32.load
    (get_local $1)
   )
  )
  (i32.store offset=52
   (get_local $5)
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (set_local $0
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $2
      (call $action_data_size)
     )
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.lt_u
       (get_local $2)
       (i32.const 513)
      )
     )
     (set_local $0
      (call $malloc
       (get_local $2)
      )
     )
     (br $label$1)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $0
      (i32.sub
       (get_local $4)
       (i32.and
        (i32.add
         (get_local $2)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $0)
     (get_local $2)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $5)
    (i32.const 24)
   )
   (i64.const 1398362884)
  )
  (i64.store offset=8
   (get_local $5)
   (i64.const 0)
  )
  (i64.store
   (get_local $5)
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $5)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.const 1)
   (i32.const 320)
  )
  (set_local $3
   (i64.const 5462355)
  )
  (block $label$3
   (block $label$4
    (loop $label$5
     (br_if $label$4
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $3)
         )
         (i32.const 24)
        )
        (i32.const -1073741825)
       )
       (i32.const 452984830)
      )
     )
     (block $label$6
      (br_if $label$6
       (i64.ne
        (i64.and
         (tee_local $3
          (i64.shr_u
           (get_local $3)
           (i64.const 8)
          )
         )
         (i64.const 255)
        )
        (i64.const 0)
       )
      )
      (loop $label$7
       (br_if $label$4
        (i64.ne
         (i64.and
          (tee_local $3
           (i64.shr_u
            (get_local $3)
            (i64.const 8)
           )
          )
          (i64.const 255)
         )
         (i64.const 0)
        )
       )
       (br_if $label$7
        (i32.lt_s
         (tee_local $1
          (i32.add
           (get_local $1)
           (i32.const 1)
          )
         )
         (i32.const 7)
        )
       )
      )
     )
     (set_local $4
      (i32.const 1)
     )
     (br_if $label$5
      (i32.lt_s
       (tee_local $1
        (i32.add
         (get_local $1)
         (i32.const 1)
        )
       )
       (i32.const 7)
      )
     )
     (br $label$3)
    )
   )
   (set_local $4
    (i32.const 0)
   )
  )
  (call $eosio_assert
   (get_local $4)
   (i32.const 32)
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 40)
   )
   (i32.const 0)
  )
  (i64.store offset=32
   (get_local $5)
   (i64.const 0)
  )
  (i32.store offset=68
   (get_local $5)
   (get_local $0)
  )
  (i32.store offset=64
   (get_local $5)
   (get_local $0)
  )
  (i32.store offset=72
   (get_local $5)
   (i32.add
    (get_local $0)
    (get_local $2)
   )
  )
  (i32.store offset=80
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 64)
   )
  )
  (i32.store offset=88
   (get_local $5)
   (get_local $5)
  )
  (call $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyyN5eosio5assetENS6_12basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEEEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyyS9_SF_EEERT_SO_RNS7_IJDpT0_EEEEUlSO_E_EEvRKSN_RKT0_
   (i32.add
    (get_local $5)
    (i32.const 88)
   )
   (i32.add
    (get_local $5)
    (i32.const 80)
   )
  )
  (block $label$8
   (br_if $label$8
    (i32.lt_u
     (get_local $2)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $0)
   )
  )
  (i32.store offset=68
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 48)
   )
  )
  (i32.store offset=64
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 60)
   )
  )
  (call $_ZN5boost4mp116detail16tuple_apply_implIRZN5eosio14execute_actionINS3_5tokenES5_JyyNS3_5assetENSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_EEUlDpT_E_RNS7_5tupleIJyyS6_SD_EEEJLj0ELj1ELj2ELj3EEEEDTclclsr3stdE7forwardISE_Efp_Espclsr3stdE3getIXT1_EEclsr3stdE7forwardISG_Efp0_EEEEOSE_OSG_NS0_16integer_sequenceIjJXspT1_EEEE
   (i32.add
    (get_local $5)
    (i32.const 64)
   )
   (get_local $5)
  )
  (block $label$9
   (br_if $label$9
    (i32.eqz
     (i32.and
      (i32.load8_u offset=32
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $5)
      (i32.const 40)
     )
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 96)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5eosio14execute_actionINS_5tokenES1_JyEEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (set_local $6
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $4)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $5
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.eqz
        (tee_local $1
         (call $action_data_size)
        )
       )
      )
      (br_if $label$2
       (i32.lt_u
        (get_local $1)
        (i32.const 513)
       )
      )
      (set_local $4
       (call $malloc
        (get_local $1)
       )
      )
      (br $label$1)
     )
     (set_local $4
      (i32.const 0)
     )
     (br $label$0)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $4
      (i32.sub
       (get_local $4)
       (i32.and
        (i32.add
         (get_local $1)
         (i32.const 15)
        )
        (i32.const -16)
       )
      )
     )
    )
   )
   (drop
    (call $read_action_data
     (get_local $4)
     (get_local $1)
    )
   )
  )
  (i64.store offset=8
   (get_local $6)
   (i64.const 0)
  )
  (call $eosio_assert
   (i32.gt_u
    (get_local $1)
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $6)
     (i32.const 8)
    )
    (get_local $4)
    (i32.const 8)
   )
  )
  (set_local $3
   (i64.load offset=8
    (get_local $6)
   )
  )
  (block $label$4
   (br_if $label$4
    (i32.lt_u
     (get_local $1)
     (i32.const 513)
    )
   )
   (call $free
    (get_local $4)
   )
  )
  (set_local $1
   (i32.add
    (get_local $0)
    (i32.shr_s
     (get_local $2)
     (i32.const 1)
    )
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (i32.and
      (get_local $2)
      (i32.const 1)
     )
    )
   )
   (set_local $5
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $5)
     )
    )
   )
  )
  (call_indirect (type $FUNCSIG$vij)
   (get_local $1)
   (get_local $3)
   (get_local $5)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 16)
   )
  )
  (i32.const 1)
 )
 (func $_ZN5boost6fusion6detail17for_each_unrolledILi4EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJyyN5eosio5assetENS6_12basic_stringIcNS6_11char_traitsIcEENS6_9allocatorIcEEEEEEELi0EEEZNS8_rsINS8_10datastreamIPKcEEJyyS9_SF_EEERT_SO_RNS7_IJDpT0_EEEEUlSO_E_EEvRKSN_RKT0_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (get_local $2)
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (set_local $0
   (i32.load
    (get_local $0)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (tee_local $3
       (i32.load
        (get_local $1)
       )
      )
     )
     (i32.load offset=4
      (get_local $3)
     )
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 16)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $3)
     )
     (i32.const 8)
    )
   )
  )
  (call $eosio_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 416)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 24)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 8)
   )
  )
  (drop
   (call $_ZN5eosiorsINS_10datastreamIPKcEEEERT_S6_RNSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEE
    (i32.load
     (get_local $1)
    )
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
   )
  )
 )
 (func $_ZN5boost4mp116detail16tuple_apply_implIRZN5eosio14execute_actionINS3_5tokenES5_JyyNS3_5assetENSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_EEUlDpT_E_RNS7_5tupleIJyyS6_SD_EEEJLj0ELj1ELj2ELj3EEEEDTclclsr3stdE7forwardISE_Efp_Espclsr3stdE3getIXT1_EEclsr3stdE7forwardISG_Efp0_EEEEOSE_OSG_NS0_16integer_sequenceIjJXspT1_EEEE (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i64)
  (local $4 i32)
  (local $5 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $5
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $5)
    (i32.const 44)
   )
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 28)
    )
   )
  )
  (i32.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 32)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i32.store offset=32
   (get_local $5)
   (i32.load offset=16
    (get_local $1)
   )
  )
  (i32.store offset=36
   (get_local $5)
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 20)
    )
   )
  )
  (set_local $3
   (i64.load offset=8
    (get_local $1)
   )
  )
  (set_local $2
   (i64.load
    (get_local $1)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $5)
     (i32.const 48)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $4)
   )
  )
  (i64.store offset=48
   (get_local $5)
   (i64.load offset=32
    (get_local $5)
   )
  )
  (set_local $0
   (i32.add
    (i32.load
     (i32.load
      (get_local $0)
     )
    )
    (i32.shr_s
     (tee_local $4
      (i32.load offset=4
       (tee_local $1
        (i32.load offset=4
         (get_local $0)
        )
       )
      )
     )
     (i32.const 1)
    )
   )
  )
  (set_local $1
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (i32.and
      (get_local $4)
      (i32.const 1)
     )
    )
   )
   (set_local $1
    (i32.load
     (i32.add
      (i32.load
       (get_local $0)
      )
      (get_local $1)
     )
    )
   )
  )
  (i64.store
   (tee_local $4
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 80)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $5)
      (i32.const 48)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store offset=80
   (get_local $5)
   (i64.load offset=48
    (get_local $5)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (get_local $5)
     (i32.const 64)
    )
    (i32.add
     (get_local $5)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $5)
    (i32.const 8)
   )
   (i64.load
    (get_local $4)
   )
  )
  (i64.store
   (get_local $5)
   (i64.load offset=80
    (get_local $5)
   )
  )
  (call_indirect (type $FUNCSIG$vijjii)
   (get_local $0)
   (get_local $2)
   (get_local $3)
   (get_local $5)
   (i32.add
    (get_local $5)
    (i32.const 64)
   )
   (get_local $1)
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (i32.and
      (i32.load8_u offset=64
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load offset=72
     (get_local $5)
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eqz
     (i32.and
      (i32.load8_u offset=16
       (get_local $5)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load offset=24
     (get_local $5)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $5)
    (i32.const 96)
   )
  )
 )
 (func $_ZN5boost4mp116detail16tuple_apply_implIRZN5eosio14execute_actionINS3_5tokenES5_JyNS3_5assetENSt3__112basic_stringIcNS7_11char_traitsIcEENS7_9allocatorIcEEEEEEEbPT_MT0_FvDpT1_EEUlDpT_E_RNS7_5tupleIJyS6_SD_EEEJLj0ELj1ELj2EEEEDTclclsr3stdE7forwardISE_Efp_Espclsr3stdE3getIXT1_EEclsr3stdE7forwardISG_Efp0_EEEEOSE_OSG_NS0_16integer_sequenceIjJXspT1_EEEE (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i32)
  (local $4 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $4
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (i32.store
   (i32.add
    (i32.add
     (get_local $4)
     (i32.const 32)
    )
    (i32.const 12)
   )
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 20)
    )
   )
  )
  (i32.store
   (tee_local $3
    (i32.add
     (i32.add
      (get_local $4)
      (i32.const 32)
     )
     (i32.const 8)
    )
   )
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (i32.store offset=32
   (get_local $4)
   (i32.load offset=8
    (get_local $1)
   )
  )
  (i32.store offset=36
   (get_local $4)
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 12)
    )
   )
  )
  (set_local $2
   (i64.load
    (get_local $1)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (get_local $4)
     (i32.const 16)
    )
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $4)
     (i32.const 48)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $3)
   )
  )
  (i64.store offset=48
   (get_local $4)
   (i64.load offset=32
    (get_local $4)
   )
  )
  (set_local $0
   (i32.add
    (i32.load
     (i32.load
      (get_local $0)
     )
    )
    (i32.shr_s
     (tee_local $3
      (i32.load offset=4
       (tee_local $1
        (i32.load offset=4
         (get_local $0)
        )
       )
      )
     )
     (i32.const 1)
    )
   )
  )
  (set_local $1
   (i32.load
    (get_local $1)
   )
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (i32.and
      (get_local $3)
      (i32.const 1)
     )
    )
   )
   (set_local $1
    (i32.load
     (i32.add
      (i32.load
       (get_local $0)
      )
      (get_local $1)
     )
    )
   )
  )
  (i64.store
   (tee_local $3
    (i32.add
     (i32.add
      (get_local $4)
      (i32.const 80)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (i32.add
      (get_local $4)
      (i32.const 48)
     )
     (i32.const 8)
    )
   )
  )
  (i64.store offset=80
   (get_local $4)
   (i64.load offset=48
    (get_local $4)
   )
  )
  (drop
   (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_
    (i32.add
     (get_local $4)
     (i32.const 64)
    )
    (i32.add
     (get_local $4)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $4)
    (i32.const 8)
   )
   (i64.load
    (get_local $3)
   )
  )
  (i64.store
   (get_local $4)
   (i64.load offset=80
    (get_local $4)
   )
  )
  (call_indirect (type $FUNCSIG$vijii)
   (get_local $0)
   (get_local $2)
   (get_local $4)
   (i32.add
    (get_local $4)
    (i32.const 64)
   )
   (get_local $1)
  )
  (block $label$1
   (br_if $label$1
    (i32.eqz
     (i32.and
      (i32.load8_u offset=64
       (get_local $4)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load offset=72
     (get_local $4)
    )
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eqz
     (i32.and
      (i32.load8_u offset=16
       (get_local $4)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load offset=24
     (get_local $4)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $4)
    (i32.const 96)
   )
  )
 )
 (func $malloc (param $0 i32) (result i32)
  (call $_ZN5eosio14memory_manager6mallocEm
   (i32.const 2048)
   (get_local $0)
  )
 )
 (func $_ZN5eosio14memory_manager6mallocEm (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (local $11 i32)
  (local $12 i32)
  (local $13 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $1)
    )
   )
   (block $label$1
    (br_if $label$1
     (tee_local $13
      (i32.load offset=8384
       (get_local $0)
      )
     )
    )
    (set_local $13
     (i32.const 16)
    )
    (i32.store
     (i32.add
      (get_local $0)
      (i32.const 8384)
     )
     (i32.const 16)
    )
   )
   (set_local $2
    (select
     (i32.sub
      (i32.add
       (get_local $1)
       (i32.const 8)
      )
      (tee_local $2
       (i32.and
        (i32.add
         (get_local $1)
         (i32.const 4)
        )
        (i32.const 7)
       )
      )
     )
     (get_local $1)
     (get_local $2)
    )
   )
   (block $label$2
    (block $label$3
     (block $label$4
      (br_if $label$4
       (i32.ge_u
        (tee_local $10
         (i32.load offset=8388
          (get_local $0)
         )
        )
        (get_local $13)
       )
      )
      (set_local $1
       (i32.add
        (i32.add
         (get_local $0)
         (i32.mul
          (get_local $10)
          (i32.const 12)
         )
        )
        (i32.const 8192)
       )
      )
      (block $label$5
       (br_if $label$5
        (get_local $10)
       )
       (br_if $label$5
        (i32.load
         (tee_local $13
          (i32.add
           (get_local $0)
           (i32.const 8196)
          )
         )
        )
       )
       (i32.store
        (get_local $1)
        (i32.const 8192)
       )
       (i32.store
        (get_local $13)
        (get_local $0)
       )
      )
      (set_local $10
       (i32.add
        (get_local $2)
        (i32.const 4)
       )
      )
      (loop $label$6
       (block $label$7
        (br_if $label$7
         (i32.gt_u
          (i32.add
           (tee_local $13
            (i32.load offset=8
             (get_local $1)
            )
           )
           (get_local $10)
          )
          (i32.load
           (get_local $1)
          )
         )
        )
        (i32.store
         (tee_local $13
          (i32.add
           (i32.load offset=4
            (get_local $1)
           )
           (get_local $13)
          )
         )
         (i32.or
          (i32.and
           (i32.load
            (get_local $13)
           )
           (i32.const -2147483648)
          )
          (get_local $2)
         )
        )
        (i32.store
         (tee_local $1
          (i32.add
           (get_local $1)
           (i32.const 8)
          )
         )
         (i32.add
          (i32.load
           (get_local $1)
          )
          (get_local $10)
         )
        )
        (i32.store
         (get_local $13)
         (i32.or
          (i32.load
           (get_local $13)
          )
          (i32.const -2147483648)
         )
        )
        (br_if $label$3
         (tee_local $1
          (i32.add
           (get_local $13)
           (i32.const 4)
          )
         )
        )
       )
       (br_if $label$6
        (tee_local $1
         (call $_ZN5eosio14memory_manager16next_active_heapEv
          (get_local $0)
         )
        )
       )
      )
     )
     (set_local $4
      (i32.sub
       (i32.const 2147483644)
       (get_local $2)
      )
     )
     (set_local $11
      (i32.add
       (get_local $0)
       (i32.const 8392)
      )
     )
     (set_local $12
      (i32.add
       (get_local $0)
       (i32.const 8384)
      )
     )
     (set_local $13
      (tee_local $3
       (i32.load offset=8392
        (get_local $0)
       )
      )
     )
     (loop $label$8
      (call $eosio_assert
       (i32.eq
        (i32.load
         (i32.add
          (tee_local $1
           (i32.add
            (get_local $0)
            (i32.mul
             (get_local $13)
             (i32.const 12)
            )
           )
          )
          (i32.const 8200)
         )
        )
        (i32.load
         (tee_local $5
          (i32.add
           (get_local $1)
           (i32.const 8192)
          )
         )
        )
       )
       (i32.const 10448)
      )
      (set_local $13
       (i32.add
        (tee_local $6
         (i32.load
          (i32.add
           (get_local $1)
           (i32.const 8196)
          )
         )
        )
        (i32.const 4)
       )
      )
      (loop $label$9
       (set_local $7
        (i32.add
         (get_local $6)
         (i32.load
          (get_local $5)
         )
        )
       )
       (set_local $1
        (i32.and
         (tee_local $9
          (i32.load
           (tee_local $8
            (i32.add
             (get_local $13)
             (i32.const -4)
            )
           )
          )
         )
         (i32.const 2147483647)
        )
       )
       (block $label$10
        (br_if $label$10
         (i32.lt_s
          (get_local $9)
          (i32.const 0)
         )
        )
        (block $label$11
         (br_if $label$11
          (i32.ge_u
           (get_local $1)
           (get_local $2)
          )
         )
         (loop $label$12
          (br_if $label$11
           (i32.ge_u
            (tee_local $10
             (i32.add
              (get_local $13)
              (get_local $1)
             )
            )
            (get_local $7)
           )
          )
          (br_if $label$11
           (i32.lt_s
            (tee_local $10
             (i32.load
              (get_local $10)
             )
            )
            (i32.const 0)
           )
          )
          (br_if $label$12
           (i32.lt_u
            (tee_local $1
             (i32.add
              (i32.add
               (get_local $1)
               (i32.and
                (get_local $10)
                (i32.const 2147483647)
               )
              )
              (i32.const 4)
             )
            )
            (get_local $2)
           )
          )
         )
        )
        (i32.store
         (get_local $8)
         (i32.or
          (select
           (get_local $1)
           (get_local $2)
           (i32.lt_u
            (get_local $1)
            (get_local $2)
           )
          )
          (i32.and
           (get_local $9)
           (i32.const -2147483648)
          )
         )
        )
        (block $label$13
         (br_if $label$13
          (i32.le_u
           (get_local $1)
           (get_local $2)
          )
         )
         (i32.store
          (i32.add
           (get_local $13)
           (get_local $2)
          )
          (i32.and
           (i32.add
            (get_local $4)
            (get_local $1)
           )
           (i32.const 2147483647)
          )
         )
        )
        (br_if $label$2
         (i32.ge_u
          (get_local $1)
          (get_local $2)
         )
        )
       )
       (br_if $label$9
        (i32.lt_u
         (tee_local $13
          (i32.add
           (i32.add
            (get_local $13)
            (get_local $1)
           )
           (i32.const 4)
          )
         )
         (get_local $7)
        )
       )
      )
      (set_local $1
       (i32.const 0)
      )
      (i32.store
       (get_local $11)
       (tee_local $13
        (select
         (i32.const 0)
         (tee_local $13
          (i32.add
           (i32.load
            (get_local $11)
           )
           (i32.const 1)
          )
         )
         (i32.eq
          (get_local $13)
          (i32.load
           (get_local $12)
          )
         )
        )
       )
      )
      (br_if $label$8
       (i32.ne
        (get_local $13)
        (get_local $3)
       )
      )
     )
    )
    (return
     (get_local $1)
    )
   )
   (i32.store
    (get_local $8)
    (i32.or
     (i32.load
      (get_local $8)
     )
     (i32.const -2147483648)
    )
   )
   (return
    (get_local $13)
   )
  )
  (i32.const 0)
 )
 (func $_ZN5eosio14memory_manager16next_active_heapEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (set_local $1
   (i32.load offset=8388
    (get_local $0)
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.load8_u offset=10534
       (i32.const 0)
      )
     )
    )
    (set_local $7
     (i32.load offset=10536
      (i32.const 0)
     )
    )
    (br $label$0)
   )
   (set_local $7
    (current_memory)
   )
   (i32.store8 offset=10534
    (i32.const 0)
    (i32.const 1)
   )
   (i32.store offset=10536
    (i32.const 0)
    (tee_local $7
     (i32.shl
      (get_local $7)
      (i32.const 16)
     )
    )
   )
  )
  (set_local $3
   (get_local $7)
  )
  (block $label$2
   (block $label$3
    (block $label$4
     (block $label$5
      (br_if $label$5
       (i32.le_u
        (tee_local $2
         (i32.shr_u
          (i32.add
           (get_local $7)
           (i32.const 65535)
          )
          (i32.const 16)
         )
        )
        (tee_local $8
         (current_memory)
        )
       )
      )
      (drop
       (grow_memory
        (i32.sub
         (get_local $2)
         (get_local $8)
        )
       )
      )
      (set_local $8
       (i32.const 0)
      )
      (br_if $label$4
       (i32.ne
        (get_local $2)
        (current_memory)
       )
      )
      (set_local $3
       (i32.load offset=10536
        (i32.const 0)
       )
      )
     )
     (set_local $8
      (i32.const 0)
     )
     (i32.store offset=10536
      (i32.const 0)
      (get_local $3)
     )
     (br_if $label$4
      (i32.lt_s
       (get_local $7)
       (i32.const 0)
      )
     )
     (set_local $2
      (i32.add
       (get_local $0)
       (i32.mul
        (get_local $1)
        (i32.const 12)
       )
      )
     )
     (set_local $7
      (i32.sub
       (i32.sub
        (i32.add
         (get_local $7)
         (select
          (i32.const 65536)
          (i32.const 131072)
          (tee_local $6
           (i32.lt_u
            (tee_local $8
             (i32.and
              (get_local $7)
              (i32.const 65535)
             )
            )
            (i32.const 64513)
           )
          )
         )
        )
        (select
         (get_local $8)
         (i32.and
          (get_local $7)
          (i32.const 131071)
         )
         (get_local $6)
        )
       )
       (get_local $7)
      )
     )
     (block $label$6
      (br_if $label$6
       (i32.load8_u offset=10534
        (i32.const 0)
       )
      )
      (set_local $3
       (current_memory)
      )
      (i32.store8 offset=10534
       (i32.const 0)
       (i32.const 1)
      )
      (i32.store offset=10536
       (i32.const 0)
       (tee_local $3
        (i32.shl
         (get_local $3)
         (i32.const 16)
        )
       )
      )
     )
     (set_local $2
      (i32.add
       (get_local $2)
       (i32.const 8192)
      )
     )
     (br_if $label$3
      (i32.lt_s
       (get_local $7)
       (i32.const 0)
      )
     )
     (set_local $6
      (get_local $3)
     )
     (block $label$7
      (br_if $label$7
       (i32.le_u
        (tee_local $8
         (i32.shr_u
          (i32.add
           (i32.add
            (tee_local $5
             (i32.and
              (i32.add
               (get_local $7)
               (i32.const 7)
              )
              (i32.const -8)
             )
            )
            (get_local $3)
           )
           (i32.const 65535)
          )
          (i32.const 16)
         )
        )
        (tee_local $4
         (current_memory)
        )
       )
      )
      (drop
       (grow_memory
        (i32.sub
         (get_local $8)
         (get_local $4)
        )
       )
      )
      (br_if $label$3
       (i32.ne
        (get_local $8)
        (current_memory)
       )
      )
      (set_local $6
       (i32.load offset=10536
        (i32.const 0)
       )
      )
     )
     (i32.store offset=10536
      (i32.const 0)
      (i32.add
       (get_local $6)
       (get_local $5)
      )
     )
     (br_if $label$3
      (i32.eq
       (get_local $3)
       (i32.const -1)
      )
     )
     (br_if $label$2
      (i32.eq
       (i32.add
        (tee_local $6
         (i32.load
          (i32.add
           (tee_local $1
            (i32.add
             (get_local $0)
             (i32.mul
              (get_local $1)
              (i32.const 12)
             )
            )
           )
           (i32.const 8196)
          )
         )
        )
        (tee_local $8
         (i32.load
          (get_local $2)
         )
        )
       )
       (get_local $3)
      )
     )
     (block $label$8
      (br_if $label$8
       (i32.eq
        (get_local $8)
        (tee_local $1
         (i32.load
          (tee_local $5
           (i32.add
            (get_local $1)
            (i32.const 8200)
           )
          )
         )
        )
       )
      )
      (i32.store
       (tee_local $6
        (i32.add
         (get_local $6)
         (get_local $1)
        )
       )
       (i32.or
        (i32.and
         (i32.load
          (get_local $6)
         )
         (i32.const -2147483648)
        )
        (i32.add
         (i32.sub
          (i32.const -4)
          (get_local $1)
         )
         (get_local $8)
        )
       )
      )
      (i32.store
       (get_local $5)
       (i32.load
        (get_local $2)
       )
      )
      (i32.store
       (get_local $6)
       (i32.and
        (i32.load
         (get_local $6)
        )
        (i32.const 2147483647)
       )
      )
     )
     (i32.store
      (tee_local $2
       (i32.add
        (get_local $0)
        (i32.const 8388)
       )
      )
      (tee_local $2
       (i32.add
        (i32.load
         (get_local $2)
        )
        (i32.const 1)
       )
      )
     )
     (i32.store
      (i32.add
       (tee_local $0
        (i32.add
         (get_local $0)
         (i32.mul
          (get_local $2)
          (i32.const 12)
         )
        )
       )
       (i32.const 8196)
      )
      (get_local $3)
     )
     (i32.store
      (tee_local $8
       (i32.add
        (get_local $0)
        (i32.const 8192)
       )
      )
      (get_local $7)
     )
    )
    (return
     (get_local $8)
    )
   )
   (block $label$9
    (br_if $label$9
     (i32.eq
      (tee_local $8
       (i32.load
        (get_local $2)
       )
      )
      (tee_local $7
       (i32.load
        (tee_local $1
         (i32.add
          (tee_local $3
           (i32.add
            (get_local $0)
            (i32.mul
             (get_local $1)
             (i32.const 12)
            )
           )
          )
          (i32.const 8200)
         )
        )
       )
      )
     )
    )
    (i32.store
     (tee_local $3
      (i32.add
       (i32.load
        (i32.add
         (get_local $3)
         (i32.const 8196)
        )
       )
       (get_local $7)
      )
     )
     (i32.or
      (i32.and
       (i32.load
        (get_local $3)
       )
       (i32.const -2147483648)
      )
      (i32.add
       (i32.sub
        (i32.const -4)
        (get_local $7)
       )
       (get_local $8)
      )
     )
    )
    (i32.store
     (get_local $1)
     (i32.load
      (get_local $2)
     )
    )
    (i32.store
     (get_local $3)
     (i32.and
      (i32.load
       (get_local $3)
      )
      (i32.const 2147483647)
     )
    )
   )
   (i32.store offset=8384
    (get_local $0)
    (tee_local $3
     (i32.add
      (i32.load
       (tee_local $7
        (i32.add
         (get_local $0)
         (i32.const 8388)
        )
       )
      )
      (i32.const 1)
     )
    )
   )
   (i32.store
    (get_local $7)
    (get_local $3)
   )
   (return
    (i32.const 0)
   )
  )
  (i32.store
   (get_local $2)
   (i32.add
    (get_local $8)
    (get_local $7)
   )
  )
  (get_local $2)
 )
 (func $free (param $0 i32)
  (local $1 i32)
  (local $2 i32)
  (local $3 i32)
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (get_local $0)
     )
    )
    (br_if $label$1
     (i32.lt_s
      (tee_local $2
       (i32.load offset=10432
        (i32.const 0)
       )
      )
      (i32.const 1)
     )
    )
    (set_local $3
     (i32.const 10240)
    )
    (set_local $1
     (i32.add
      (i32.mul
       (get_local $2)
       (i32.const 12)
      )
      (i32.const 10240)
     )
    )
    (loop $label$2
     (br_if $label$1
      (i32.eqz
       (tee_local $2
        (i32.load
         (i32.add
          (get_local $3)
          (i32.const 4)
         )
        )
       )
      )
     )
     (block $label$3
      (br_if $label$3
       (i32.gt_u
        (i32.add
         (get_local $2)
         (i32.const 4)
        )
        (get_local $0)
       )
      )
      (br_if $label$0
       (i32.gt_u
        (i32.add
         (get_local $2)
         (i32.load
          (get_local $3)
         )
        )
        (get_local $0)
       )
      )
     )
     (br_if $label$2
      (i32.lt_u
       (tee_local $3
        (i32.add
         (get_local $3)
         (i32.const 12)
        )
       )
       (get_local $1)
      )
     )
    )
   )
   (return)
  )
  (i32.store
   (tee_local $3
    (i32.add
     (get_local $0)
     (i32.const -4)
    )
   )
   (i32.and
    (i32.load
     (get_local $3)
    )
    (i32.const 2147483647)
   )
  )
 )
 (func $_Znwj (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (block $label$0
   (br_if $label$0
    (tee_local $0
     (call $malloc
      (tee_local $1
       (select
        (get_local $0)
        (i32.const 1)
        (get_local $0)
       )
      )
     )
    )
   )
   (loop $label$1
    (set_local $0
     (i32.const 0)
    )
    (br_if $label$0
     (i32.eqz
      (tee_local $2
       (i32.load offset=10540
        (i32.const 0)
       )
      )
     )
    )
    (call_indirect (type $FUNCSIG$v)
     (get_local $2)
    )
    (br_if $label$1
     (i32.eqz
      (tee_local $0
       (call $malloc
        (get_local $1)
       )
      )
     )
    )
   )
  )
  (get_local $0)
 )
 (func $_ZdlPv (param $0 i32)
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $0)
    )
   )
   (call $free
    (get_local $0)
   )
  )
 )
 (func $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv (param $0 i32)
  (call $abort)
  (unreachable)
 )
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE7reserveEj (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (block $label$0
   (br_if $label$0
    (i32.ge_u
     (get_local $1)
     (i32.const -16)
    )
   )
   (set_local $2
    (i32.const 10)
   )
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.and
       (tee_local $5
        (i32.load8_u
         (get_local $0)
        )
       )
       (i32.const 1)
      )
     )
    )
    (set_local $2
     (i32.add
      (i32.and
       (tee_local $5
        (i32.load
         (get_local $0)
        )
       )
       (i32.const -2)
      )
      (i32.const -1)
     )
    )
   )
   (block $label$2
    (block $label$3
     (br_if $label$3
      (i32.and
       (get_local $5)
       (i32.const 1)
      )
     )
     (set_local $3
      (i32.shr_u
       (i32.and
        (get_local $5)
        (i32.const 254)
       )
       (i32.const 1)
      )
     )
     (br $label$2)
    )
    (set_local $3
     (i32.load offset=4
      (get_local $0)
     )
    )
   )
   (set_local $4
    (i32.const 10)
   )
   (block $label$4
    (br_if $label$4
     (i32.lt_u
      (tee_local $1
       (select
        (get_local $3)
        (get_local $1)
        (i32.gt_u
         (get_local $3)
         (get_local $1)
        )
       )
      )
      (i32.const 11)
     )
    )
    (set_local $4
     (i32.add
      (i32.and
       (i32.add
        (get_local $1)
        (i32.const 16)
       )
       (i32.const -16)
      )
      (i32.const -1)
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eq
      (get_local $4)
      (get_local $2)
     )
    )
    (block $label$6
     (block $label$7
      (br_if $label$7
       (i32.ne
        (get_local $4)
        (i32.const 10)
       )
      )
      (set_local $6
       (i32.const 1)
      )
      (set_local $1
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (set_local $2
       (i32.load offset=8
        (get_local $0)
       )
      )
      (set_local $7
       (i32.const 0)
      )
      (br $label$6)
     )
     (set_local $1
      (call $_Znwj
       (i32.add
        (get_local $4)
        (i32.const 1)
       )
      )
     )
     (block $label$8
      (br_if $label$8
       (i32.gt_u
        (get_local $4)
        (get_local $2)
       )
      )
      (br_if $label$5
       (i32.eqz
        (get_local $1)
       )
      )
     )
     (block $label$9
      (br_if $label$9
       (i32.and
        (tee_local $5
         (i32.load8_u
          (get_local $0)
         )
        )
        (i32.const 1)
       )
      )
      (set_local $7
       (i32.const 1)
      )
      (set_local $2
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (set_local $6
       (i32.const 0)
      )
      (br $label$6)
     )
     (set_local $2
      (i32.load offset=8
       (get_local $0)
      )
     )
     (set_local $6
      (i32.const 1)
     )
     (set_local $7
      (i32.const 1)
     )
    )
    (block $label$10
     (block $label$11
      (br_if $label$11
       (i32.and
        (get_local $5)
        (i32.const 1)
       )
      )
      (set_local $5
       (i32.shr_u
        (i32.and
         (get_local $5)
         (i32.const 254)
        )
        (i32.const 1)
       )
      )
      (br $label$10)
     )
     (set_local $5
      (i32.load offset=4
       (get_local $0)
      )
     )
    )
    (block $label$12
     (br_if $label$12
      (i32.eqz
       (tee_local $5
        (i32.add
         (get_local $5)
         (i32.const 1)
        )
       )
      )
     )
     (drop
      (call $memcpy
       (get_local $1)
       (get_local $2)
       (get_local $5)
      )
     )
    )
    (block $label$13
     (br_if $label$13
      (i32.eqz
       (get_local $6)
      )
     )
     (call $_ZdlPv
      (get_local $2)
     )
    )
    (block $label$14
     (br_if $label$14
      (i32.eqz
       (get_local $7)
      )
     )
     (i32.store offset=4
      (get_local $0)
      (get_local $3)
     )
     (i32.store offset=8
      (get_local $0)
      (get_local $1)
     )
     (i32.store
      (get_local $0)
      (i32.or
       (i32.add
        (get_local $4)
        (i32.const 1)
       )
       (i32.const 1)
      )
     )
     (return)
    )
    (i32.store8
     (get_local $0)
     (i32.shl
      (get_local $3)
      (i32.const 1)
     )
    )
   )
   (return)
  )
  (call $abort)
  (unreachable)
 )
 (func $_ZNKSt3__120__vector_base_commonILb1EE20__throw_length_errorEv (param $0 i32)
  (call $abort)
  (unreachable)
 )
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2ERKS5_ (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (i64.store align=4
   (get_local $0)
   (i64.const 0)
  )
  (i32.store
   (tee_local $3
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.and
     (i32.load8_u
      (get_local $1)
     )
     (i32.const 1)
    )
   )
   (i64.store align=4
    (get_local $0)
    (i64.load align=4
     (get_local $1)
    )
   )
   (i32.store
    (get_local $3)
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 8)
     )
    )
   )
   (return
    (get_local $0)
   )
  )
  (block $label$1
   (br_if $label$1
    (i32.ge_u
     (tee_local $3
      (i32.load offset=4
       (get_local $1)
      )
     )
     (i32.const -16)
    )
   )
   (set_local $2
    (i32.load offset=8
     (get_local $1)
    )
   )
   (block $label$2
    (block $label$3
     (block $label$4
      (br_if $label$4
       (i32.ge_u
        (get_local $3)
        (i32.const 11)
       )
      )
      (i32.store8
       (get_local $0)
       (i32.shl
        (get_local $3)
        (i32.const 1)
       )
      )
      (set_local $1
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (br_if $label$3
       (get_local $3)
      )
      (br $label$2)
     )
     (set_local $1
      (call $_Znwj
       (tee_local $4
        (i32.and
         (i32.add
          (get_local $3)
          (i32.const 16)
         )
         (i32.const -16)
        )
       )
      )
     )
     (i32.store
      (get_local $0)
      (i32.or
       (get_local $4)
       (i32.const 1)
      )
     )
     (i32.store offset=8
      (get_local $0)
      (get_local $1)
     )
     (i32.store offset=4
      (get_local $0)
      (get_local $3)
     )
    )
    (drop
     (call $memcpy
      (get_local $1)
      (get_local $2)
      (get_local $3)
     )
    )
   )
   (i32.store8
    (i32.add
     (get_local $1)
     (get_local $3)
    )
    (i32.const 0)
   )
   (return
    (get_local $0)
   )
  )
  (call $abort)
  (unreachable)
 )
 (func $memcmp (param $0 i32) (param $1 i32) (param $2 i32) (result i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (set_local $5
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (get_local $2)
    )
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.ne
       (tee_local $3
        (i32.load8_u
         (get_local $0)
        )
       )
       (tee_local $4
        (i32.load8_u
         (get_local $1)
        )
       )
      )
     )
     (set_local $1
      (i32.add
       (get_local $1)
       (i32.const 1)
      )
     )
     (set_local $0
      (i32.add
       (get_local $0)
       (i32.const 1)
      )
     )
     (br_if $label$2
      (tee_local $2
       (i32.add
        (get_local $2)
        (i32.const -1)
       )
      )
     )
     (br $label$0)
    )
   )
   (set_local $5
    (i32.sub
     (get_local $3)
     (get_local $4)
    )
   )
  )
  (get_local $5)
 )
 (func $__wasm_nullptr (type $FUNCSIG$v)
  (unreachable)
 )
)

)=====";
