(module
 (type $FUNCSIG$viiii (func (param i32 i32 i32 i32)))
 (type $FUNCSIG$vii (func (param i32 i32)))
 (type $FUNCSIG$v (func))
 (type $FUNCSIG$j (func (result i64)))
 (type $FUNCSIG$iiii (func (param i32 i32 i32) (result i32)))
 (type $FUNCSIG$vi (func (param i32)))
 (type $FUNCSIG$i (func (result i32)))
 (type $FUNCSIG$iii (func (param i32 i32) (result i32)))
 (type $FUNCSIG$iiijij (func (param i32 i32 i64 i32 i64) (result i32)))
 (type $FUNCSIG$iiijiij (func (param i32 i32 i64 i32 i32 i64) (result i32)))
 (type $FUNCSIG$iiijj (func (param i32 i32 i64 i64) (result i32)))
 (type $FUNCSIG$iiijiii (func (param i32 i32 i64 i32 i32 i32) (result i32)))
 (type $FUNCSIG$iijijii (func (param i32 i64 i32 i64 i32 i32) (result i32)))
 (type $FUNCSIG$iijiji (func (param i32 i64 i32 i64 i32) (result i32)))
 (type $FUNCSIG$iiij (func (param i32 i32 i64) (result i32)))
 (import "env" "abort" (func $abort))
 (import "env" "action_data_size" (func $action_data_size (result i32)))
 (import "env" "contento_assert" (func $contento_assert (param i32 i32)))
 (import "env" "current_contract_name" (func $current_contract_name (param i32)))
 (import "env" "current_receiver" (func $current_receiver (param i32)))
 (import "env" "current_time" (func $current_time (result i64)))
 (import "env" "db_end_i64" (func $db_end_i64 (param i32 i32 i64) (result i32)))
 (import "env" "db_find_i64" (func $db_find_i64 (param i32 i32 i64 i64) (result i32)))
 (import "env" "db_get_i64" (func $db_get_i64 (param i32 i32 i32) (result i32)))
 (import "env" "db_idx256_find_primary" (func $db_idx256_find_primary (param i32 i32 i64 i32 i32 i64) (result i32)))
 (import "env" "db_idx256_lowerbound" (func $db_idx256_lowerbound (param i32 i32 i64 i32 i32 i32) (result i32)))
 (import "env" "db_idx256_next" (func $db_idx256_next (param i32 i32) (result i32)))
 (import "env" "db_idx256_remove" (func $db_idx256_remove (param i32)))
 (import "env" "db_idx256_store" (func $db_idx256_store (param i32 i64 i32 i64 i32 i32) (result i32)))
 (import "env" "db_idx64_find_primary" (func $db_idx64_find_primary (param i32 i32 i64 i32 i64) (result i32)))
 (import "env" "db_idx64_remove" (func $db_idx64_remove (param i32)))
 (import "env" "db_idx64_store" (func $db_idx64_store (param i32 i64 i32 i64 i32) (result i32)))
 (import "env" "db_lowerbound_i64" (func $db_lowerbound_i64 (param i32 i32 i64 i64) (result i32)))
 (import "env" "db_previous_i64" (func $db_previous_i64 (param i32 i32) (result i32)))
 (import "env" "db_remove_i64" (func $db_remove_i64 (param i32)))
 (import "env" "db_store_i64" (func $db_store_i64 (param i32 i64 i32 i64 i32 i32) (result i32)))
 (import "env" "memcpy" (func $memcpy (param i32 i32 i32) (result i32)))
 (import "env" "prints" (func $prints (param i32)))
 (import "env" "prints_l" (func $prints_l (param i32 i32)))
 (import "env" "read_action_data" (func $read_action_data (param i32 i32) (result i32)))
 (table 3 3 anyfunc)
 (elem (i32.const 0) $__wasm_nullptr $_ZN7storage10placeofferE6namex_RKN5cosio5assetERK11checksum256 $_ZN7storage11cancelofferERK11checksum256)
 (memory $0 1)
 (data (i32.const 4) "\d0e\00\00")
 (data (i32.const 16) "onerror\00")
 (data (i32.const 32) "onerror action\'s are only valid from the \"eosio\" system account\00")
 (data (i32.const 96) "read\00")
 (data (i32.const 112) "unexpected error in fixed_key constructor\00")
 (data (i32.const 160) "offer does not exists\00")
 (data (i32.const 192) "unable to cancel offer\00")
 (data (i32.const 224) "cannot pass end iterator to erase\00")
 (data (i32.const 272) "[storage]-> \00")
 (data (i32.const 288) " removed 1 record in table \"offer\"\00")
 (data (i32.const 352) "object passed to erase is not in multi_index\00")
 (data (i32.const 400) "cannot erase objects in table of another contract\00")
 (data (i32.const 464) "attempt to remove object that was not in multi_index\00")
 (data (i32.const 528) "cannot increment end iterator\00")
 (data (i32.const 560) "object passed to iterator_to is not in multi_index\00")
 (data (i32.const 624) "error reading iterator\00")
 (data (i32.const 656) "magnitude of asset amount must be less than 2^62\00")
 (data (i32.const 720) "invalid symbol name\00")
 (data (i32.const 752) "only core token allowed\00")
 (data (i32.const 784) "invalid bet\00")
 (data (i32.const 800) "must bet positive quantity\00")
 (data (i32.const 832) "offer with this commitment already exist\00")
 (data (i32.const 880) " placed 1 record in table \"offer\"\00")
 (data (i32.const 928) "cannot create objects in table of another contract\00")
 (data (i32.const 992) "next primary key in table is at autoincrement limit\00")
 (data (i32.const 1056) "write\00")
 (data (i32.const 1072) "cannot decrement end iterator when the table is empty\00")
 (data (i32.const 1136) "cannot decrement iterator at beginning of table\00")
 (data (i32.const 9584) "malloc_from_freed was designed to only be called after _heap was completely allocated\00")
 (export "memory" (memory $0))
 (export "now" (func $now))
 (export "_ZN5cosio17convert_name_u128E6namex_" (func $_ZN5cosio17convert_name_u128E6namex_))
 (export "_ZN5cosio17convert_u128_nameENS_9uint128_xE" (func $_ZN5cosio17convert_u128_nameENS_9uint128_xE))
 (export "_ZeqRK11checksum256S1_" (func $_ZeqRK11checksum256S1_))
 (export "_ZeqRK11checksum160S1_" (func $_ZeqRK11checksum160S1_))
 (export "_ZneRK11checksum160S1_" (func $_ZneRK11checksum160S1_))
 (export "_ZeqRK6namex_S1_" (func $_ZeqRK6namex_S1_))
 (export "_ZneRK6namex_S1_" (func $_ZneRK6namex_S1_))
 (export "_ZN5cosio12require_authERKNS_16permission_levelE" (func $_ZN5cosio12require_authERKNS_16permission_levelE))
 (export "_ZN5cosio20get_current_receiverEv" (func $_ZN5cosio20get_current_receiverEv))
 (export "_ZN5cosio25get_current_contract_nameEv" (func $_ZN5cosio25get_current_contract_nameEv))
 (export "apply" (func $apply))
 (export "malloc" (func $malloc))
 (export "free" (func $free))
 (export "memcmp" (func $memcmp))
 (export "strlen" (func $strlen))
 (func $now (result i32)
  (i32.wrap/i64
   (i64.div_u
    (call $current_time)
    (i64.const 1000000)
   )
  )
 )
 (func $_ZN5cosio17convert_name_u128E6namex_ (param $0 i32) (param $1 i32)
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (get_local $0)
    (get_local $1)
    (i32.const 16)
   )
  )
 )
 (func $_ZN5cosio17convert_u128_nameENS_9uint128_xE (param $0 i32) (param $1 i32)
  (drop
   (call $memcpy
    (get_local $0)
    (get_local $1)
    (i32.const 16)
   )
  )
 )
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
 (func $_ZeqRK6namex_S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.eqz
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 16)
   )
  )
 )
 (func $_ZneRK6namex_S1_ (param $0 i32) (param $1 i32) (result i32)
  (i32.ne
   (call $memcmp
    (get_local $0)
    (get_local $1)
    (i32.const 16)
   )
   (i32.const 0)
  )
 )
 (func $_ZN5cosio12require_authERKNS_16permission_levelE (param $0 i32)
 )
 (func $_ZN5cosio20get_current_receiverEv (param $0 i32)
  (local $1 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $1
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (call $current_receiver
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $1)
   (i64.load offset=8
    (get_local $1)
   )
  )
  (i64.store offset=16
   (get_local $1)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=48
   (get_local $1)
   (i64.load offset=16
    (get_local $1)
   )
  )
  (i64.store offset=40
   (get_local $1)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $1)
   (i64.load offset=24
    (get_local $1)
   )
  )
  (i64.store offset=32
   (get_local $1)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (i64.store offset=8
   (get_local $0)
   (i64.load offset=40
    (get_local $1)
   )
  )
  (i64.store
   (get_local $0)
   (i64.load offset=32
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $1)
    (i32.const 64)
   )
  )
 )
 (func $_ZN5cosio25get_current_contract_nameEv (param $0 i32)
  (local $1 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $1
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 64)
    )
   )
  )
  (call $current_contract_name
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $0)
   (i64.const 0)
  )
  (i64.store
   (get_local $0)
   (i64.const 0)
  )
  (i64.store offset=24
   (get_local $1)
   (i64.load offset=8
    (get_local $1)
   )
  )
  (i64.store offset=16
   (get_local $1)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=48
   (get_local $1)
   (i64.load offset=16
    (get_local $1)
   )
  )
  (i64.store offset=40
   (get_local $1)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $1)
   (i64.load offset=24
    (get_local $1)
   )
  )
  (i64.store offset=32
   (get_local $1)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 32)
    )
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (i64.store offset=8
   (get_local $0)
   (i64.load offset=40
    (get_local $1)
   )
  )
  (i64.store
   (get_local $0)
   (i64.load offset=32
    (get_local $1)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $1)
    (i32.const 64)
   )
  )
 )
 (func $apply (param $0 i64) (param $1 i64) (param $2 i64)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i64)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
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
     (i32.const 240)
    )
   )
  )
  (call $current_receiver
   (i32.add
    (get_local $15)
    (i32.const 208)
   )
  )
  (i64.store offset=152
   (get_local $15)
   (i64.load offset=216
    (get_local $15)
   )
  )
  (i64.store offset=144
   (get_local $15)
   (i64.load offset=208
    (get_local $15)
   )
  )
  (i64.store offset=48
   (get_local $15)
   (i64.load offset=144
    (get_local $15)
   )
  )
  (set_local $12
   (i64.const 0)
  )
  (i64.store offset=232
   (get_local $15)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $15)
   (i64.load offset=152
    (get_local $15)
   )
  )
  (i64.store offset=224
   (get_local $15)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $15)
     (i32.const 224)
    )
    (i32.add
     (get_local $15)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (set_local $4
   (i64.load offset=232
    (get_local $15)
   )
  )
  (set_local $3
   (i64.load offset=224
    (get_local $15)
   )
  )
  (call $current_contract_name
   (i32.add
    (get_local $15)
    (i32.const 208)
   )
  )
  (i64.store offset=152
   (get_local $15)
   (i64.load offset=216
    (get_local $15)
   )
  )
  (i64.store offset=144
   (get_local $15)
   (i64.load offset=208
    (get_local $15)
   )
  )
  (i64.store offset=48
   (get_local $15)
   (i64.load offset=144
    (get_local $15)
   )
  )
  (i64.store offset=232
   (get_local $15)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $15)
   (i64.load offset=152
    (get_local $15)
   )
  )
  (i64.store offset=224
   (get_local $15)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $15)
     (i32.const 224)
    )
    (i32.add
     (get_local $15)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (set_local $6
   (i64.load offset=232
    (get_local $15)
   )
  )
  (set_local $5
   (i64.load offset=224
    (get_local $15)
   )
  )
  (set_local $11
   (i64.const 59)
  )
  (set_local $10
   (i32.const 16)
  )
  (set_local $13
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
          (get_local $12)
          (i64.const 6)
         )
        )
        (br_if $label$4
         (i32.gt_u
          (i32.and
           (i32.add
            (tee_local $7
             (i32.load8_s
              (get_local $10)
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
        (br $label$3)
       )
       (set_local $14
        (i64.const 0)
       )
       (br_if $label$2
        (i64.le_u
         (get_local $12)
         (i64.const 11)
        )
       )
       (br $label$1)
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
     (set_local $14
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
    (set_local $14
     (i64.shl
      (i64.and
       (get_local $14)
       (i64.const 31)
      )
      (i64.and
       (get_local $11)
       (i64.const 4294967295)
      )
     )
    )
   )
   (set_local $10
    (i32.add
     (get_local $10)
     (i32.const 1)
    )
   )
   (set_local $12
    (i64.add
     (get_local $12)
     (i64.const 1)
    )
   )
   (set_local $13
    (i64.or
     (get_local $14)
     (get_local $13)
    )
   )
   (br_if $label$0
    (i64.ne
     (tee_local $11
      (i64.add
       (get_local $11)
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
     (get_local $13)
     (get_local $2)
    )
   )
   (call $contento_assert
    (i32.and
     (i64.eqz
      (get_local $5)
     )
     (i64.eq
      (get_local $6)
      (i64.const 478510542693)
     )
    )
    (i32.const 32)
   )
  )
  (block $label$7
   (block $label$8
    (block $label$9
     (br_if $label$9
      (i64.ne
       (get_local $5)
       (get_local $3)
      )
     )
     (br_if $label$8
      (i64.eq
       (get_local $6)
       (get_local $4)
      )
     )
    )
    (set_local $12
     (i64.const 0)
    )
    (set_local $11
     (i64.const 59)
    )
    (set_local $10
     (i32.const 16)
    )
    (set_local $13
     (i64.const 0)
    )
    (loop $label$10
     (block $label$11
      (block $label$12
       (block $label$13
        (block $label$14
         (block $label$15
          (br_if $label$15
           (i64.gt_u
            (get_local $12)
            (i64.const 6)
           )
          )
          (br_if $label$14
           (i32.gt_u
            (i32.and
             (i32.add
              (tee_local $7
               (i32.load8_s
                (get_local $10)
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
          (br $label$13)
         )
         (set_local $14
          (i64.const 0)
         )
         (br_if $label$12
          (i64.le_u
           (get_local $12)
           (i64.const 11)
          )
         )
         (br $label$11)
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
       (set_local $14
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
      (set_local $14
       (i64.shl
        (i64.and
         (get_local $14)
         (i64.const 31)
        )
        (i64.and
         (get_local $11)
         (i64.const 4294967295)
        )
       )
      )
     )
     (set_local $10
      (i32.add
       (get_local $10)
       (i32.const 1)
      )
     )
     (set_local $12
      (i64.add
       (get_local $12)
       (i64.const 1)
      )
     )
     (set_local $13
      (i64.or
       (get_local $14)
       (get_local $13)
      )
     )
     (br_if $label$10
      (i64.ne
       (tee_local $11
        (i64.add
         (get_local $11)
         (i64.const -5)
        )
       )
       (i64.const -6)
      )
     )
    )
    (br_if $label$7
     (i64.ne
      (get_local $13)
      (get_local $2)
     )
    )
   )
   (i64.store offset=56
    (get_local $15)
    (get_local $4)
   )
   (i64.store offset=48
    (get_local $15)
    (get_local $3)
   )
   (drop
    (call $memcpy
     (i32.add
      (get_local $15)
      (i32.const 32)
     )
     (i32.add
      (get_local $15)
      (i32.const 48)
     )
     (i32.const 16)
    )
   )
   (i64.store offset=160
    (get_local $15)
    (tee_local $12
     (i64.load offset=32
      (get_local $15)
     )
    )
   )
   (i64.store offset=168
    (get_local $15)
    (tee_local $14
     (i64.load offset=40
      (get_local $15)
     )
    )
   )
   (i64.store offset=216
    (get_local $15)
    (get_local $14)
   )
   (i64.store offset=208
    (get_local $15)
    (get_local $12)
   )
   (i64.store offset=224
    (get_local $15)
    (tee_local $12
     (i64.load offset=208
      (get_local $15)
     )
    )
   )
   (i64.store offset=232
    (get_local $15)
    (tee_local $14
     (i64.load offset=216
      (get_local $15)
     )
    )
   )
   (i64.store offset=56
    (get_local $15)
    (get_local $14)
   )
   (i64.store offset=48
    (get_local $15)
    (get_local $12)
   )
   (i32.store offset=64
    (get_local $15)
    (i32.const 300)
   )
   (i32.store offset=204
    (get_local $15)
    (i32.load offset=60
     (get_local $15)
    )
   )
   (i32.store offset=200
    (get_local $15)
    (i32.load offset=56
     (get_local $15)
    )
   )
   (i32.store offset=196
    (get_local $15)
    (i32.load offset=52
     (get_local $15)
    )
   )
   (i32.store offset=192
    (get_local $15)
    (i32.load offset=48
     (get_local $15)
    )
   )
   (i64.store offset=184
    (get_local $15)
    (i64.load offset=56
     (get_local $15)
    )
   )
   (i64.store offset=176
    (get_local $15)
    (i64.load offset=48
     (get_local $15)
    )
   )
   (i64.store offset=144
    (get_local $15)
    (i64.load offset=176
     (get_local $15)
    )
   )
   (i64.store offset=152
    (get_local $15)
    (i64.load offset=184
     (get_local $15)
    )
   )
   (i64.store offset=232
    (get_local $15)
    (i64.load offset=200
     (get_local $15)
    )
   )
   (i64.store offset=224
    (get_local $15)
    (i64.load offset=192
     (get_local $15)
    )
   )
   (i64.store
    (i32.add
     (get_local $15)
     (i32.const 88)
    )
    (i64.load offset=232
     (get_local $15)
    )
   )
   (i64.store offset=80
    (get_local $15)
    (i64.load offset=224
     (get_local $15)
    )
   )
   (i64.store
    (i32.add
     (get_local $15)
     (i32.const 104)
    )
    (i64.load offset=152
     (get_local $15)
    )
   )
   (i64.store
    (i32.add
     (get_local $15)
     (i32.const 96)
    )
    (i64.load offset=144
     (get_local $15)
    )
   )
   (i64.store
    (i32.add
     (get_local $15)
     (i32.const 112)
    )
    (i64.const -1)
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 120)
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 124)
    )
    (i32.const 0)
   )
   (i32.store
    (i32.add
     (get_local $15)
     (i32.const 128)
    )
    (i32.const 0)
   )
   (i32.store16
    (i32.add
     (get_local $15)
     (i32.const 132)
    )
    (i32.const 0)
   )
   (block $label$16
    (block $label$17
     (br_if $label$17
      (i64.eq
       (get_local $2)
       (i64.const 4730614996631465472)
      )
     )
     (br_if $label$16
      (i64.ne
       (get_local $2)
       (i64.const -6031299216216309760)
      )
     )
     (i32.store offset=28
      (get_local $15)
      (i32.const 0)
     )
     (i32.store offset=24
      (get_local $15)
      (i32.const 1)
     )
     (i64.store align=4
      (get_local $15)
      (i64.load offset=24
       (get_local $15)
      )
     )
     (drop
      (call $_ZN5cosio14execute_actionI7storageS1_J6namex_RKNS_5assetERK11checksum256EEEbPT_MT0_FvDpT1_E
       (i32.add
        (get_local $15)
        (i32.const 48)
       )
       (get_local $15)
      )
     )
     (br $label$16)
    )
    (i32.store offset=20
     (get_local $15)
     (i32.const 0)
    )
    (i32.store offset=16
     (get_local $15)
     (i32.const 2)
    )
    (i64.store offset=8 align=4
     (get_local $15)
     (i64.load offset=16
      (get_local $15)
     )
    )
    (drop
     (call $_ZN5cosio14execute_actionI7storageS1_JRK11checksum256EEEbPT_MT0_FvDpT1_E
      (i32.add
       (get_local $15)
       (i32.const 48)
      )
      (i32.add
       (get_local $15)
       (i32.const 8)
      )
     )
    )
   )
   (br_if $label$7
    (i32.eqz
     (tee_local $8
      (i32.load
       (i32.add
        (get_local $15)
        (i32.const 120)
       )
      )
     )
    )
   )
   (block $label$18
    (block $label$19
     (br_if $label$19
      (i32.eq
       (tee_local $10
        (i32.load
         (tee_local $9
          (i32.add
           (get_local $15)
           (i32.const 124)
          )
         )
        )
       )
       (get_local $8)
      )
     )
     (loop $label$20
      (set_local $7
       (i32.load
        (tee_local $10
         (i32.add
          (get_local $10)
          (i32.const -24)
         )
        )
       )
      )
      (i32.store
       (get_local $10)
       (i32.const 0)
      )
      (block $label$21
       (br_if $label$21
        (i32.eqz
         (get_local $7)
        )
       )
       (call $_ZdlPv
        (get_local $7)
       )
      )
      (br_if $label$20
       (i32.ne
        (get_local $8)
        (get_local $10)
       )
      )
     )
     (set_local $10
      (i32.load
       (i32.add
        (get_local $15)
        (i32.const 120)
       )
      )
     )
     (br $label$18)
    )
    (set_local $10
     (get_local $8)
    )
   )
   (i32.store
    (get_local $9)
    (get_local $8)
   )
   (call $_ZdlPv
    (get_local $10)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $15)
    (i32.const 240)
   )
  )
 )
 (func $_ZN7storage10placeofferE6namex_RKN5cosio5assetERK11checksum256 (type $FUNCSIG$viiii) (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (local $8 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (call $contento_assert
   (i64.eq
    (i64.load offset=8
     (get_local $2)
    )
    (i64.const 1129267971)
   )
   (i32.const 752)
  )
  (set_local $7
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i64.gt_u
     (i64.add
      (i64.load
       (get_local $2)
      )
      (i64.const 4611686018427387903)
     )
     (i64.const 9223372036854775806)
    )
   )
   (set_local $5
    (i64.shr_u
     (i64.load
      (i32.add
       (get_local $2)
       (i32.const 8)
      )
     )
     (i64.const 8)
    )
   )
   (set_local $6
    (i32.const 0)
   )
   (block $label$1
    (loop $label$2
     (br_if $label$1
      (i32.gt_u
       (i32.add
        (i32.shl
         (i32.wrap/i64
          (get_local $5)
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
         (tee_local $5
          (i64.shr_u
           (get_local $5)
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
          (tee_local $5
           (i64.shr_u
            (get_local $5)
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
     (set_local $7
      (i32.const 1)
     )
     (br_if $label$2
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
     (br $label$0)
    )
   )
   (set_local $7
    (i32.const 0)
   )
  )
  (call $contento_assert
   (get_local $7)
   (i32.const 784)
  )
  (call $contento_assert
   (i64.gt_s
    (i64.load
     (get_local $2)
    )
    (i64.const 0)
   )
   (i32.const 800)
  )
  (call $contento_assert
   (i32.xor
    (call $_ZNK7storage9has_offerERK11checksum256
     (get_local $0)
     (get_local $3)
    )
    (i32.const 1)
   )
   (i32.const 832)
  )
  (i64.store offset=24
   (get_local $8)
   (i64.load
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=16
   (get_local $8)
   (i64.load
    (get_local $0)
   )
  )
  (i32.store offset=92
   (get_local $8)
   (get_local $3)
  )
  (i32.store offset=84
   (get_local $8)
   (get_local $2)
  )
  (i32.store offset=80
   (get_local $8)
   (get_local $0)
  )
  (i32.store offset=88
   (get_local $8)
   (get_local $1)
  )
  (i64.store offset=8
   (get_local $8)
   (i64.load offset=24
    (get_local $8)
   )
  )
  (i64.store
   (get_local $8)
   (i64.load offset=16
    (get_local $8)
   )
  )
  (call $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE7emplaceIZNS1_10placeofferE6namex_RKNS_5assetERK11checksum256EUlRT_E_EENSD_14const_iteratorESF_OSM_
   (i32.add
    (get_local $8)
    (i32.const 40)
   )
   (i32.add
    (get_local $0)
    (i32.const 32)
   )
   (get_local $8)
   (i32.add
    (get_local $8)
    (i32.const 80)
   )
  )
  (i64.store offset=56
   (get_local $8)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=48
   (get_local $8)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=80
   (get_local $8)
   (i64.load offset=48
    (get_local $8)
   )
  )
  (i64.store offset=72
   (get_local $8)
   (i64.const 0)
  )
  (i64.store offset=88
   (get_local $8)
   (i64.load offset=56
    (get_local $8)
   )
  )
  (i64.store offset=64
   (get_local $8)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $8)
     (i32.const 64)
    )
    (i32.add
     (get_local $8)
     (i32.const 80)
    )
    (i32.const 16)
   )
  )
  (set_local $5
   (i64.load offset=64
    (get_local $8)
   )
  )
  (set_local $4
   (i64.load offset=72
    (get_local $8)
   )
  )
  (call $prints
   (i32.const 272)
  )
  (i64.store offset=88
   (get_local $8)
   (get_local $4)
  )
  (i64.store offset=80
   (get_local $8)
   (get_local $5)
  )
  (call $_ZNK5cosio5namex9to_stringEv
   (i32.add
    (get_local $8)
    (i32.const 64)
   )
   (i32.add
    (get_local $8)
    (i32.const 80)
   )
  )
  (call $prints_l
   (select
    (i32.load offset=72
     (get_local $8)
    )
    (i32.or
     (i32.add
      (get_local $8)
      (i32.const 64)
     )
     (i32.const 1)
    )
    (tee_local $0
     (i32.and
      (tee_local $6
       (i32.load8_u offset=64
        (get_local $8)
       )
      )
      (i32.const 1)
     )
    )
   )
   (select
    (i32.load offset=68
     (get_local $8)
    )
    (i32.shr_u
     (get_local $6)
     (i32.const 1)
    )
    (get_local $0)
   )
  )
  (block $label$5
   (br_if $label$5
    (i32.eqz
     (i32.and
      (i32.load8_u offset=64
       (get_local $8)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (i32.add
       (get_local $8)
       (i32.const 64)
      )
      (i32.const 8)
     )
    )
   )
  )
  (call $prints
   (i32.const 880)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 96)
   )
  )
 )
 (func $_ZN5cosio14execute_actionI7storageS1_J6namex_RKNS_5assetERK11checksum256EEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (local $9 i32)
  (local $10 i32)
  (set_local $10
   (tee_local $8
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 224)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $8)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $9
   (i32.load
    (get_local $1)
   )
  )
  (set_local $1
   (i32.const 0)
  )
  (set_local $6
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
     (set_local $6
      (call $malloc
       (get_local $3)
      )
     )
     (br $label$1)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $6
      (i32.sub
       (get_local $8)
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
     (get_local $6)
     (get_local $3)
    )
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=16
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=32
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=40
   (get_local $10)
   (i64.const 1129267971)
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 656)
  )
  (set_local $4
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
  )
  (set_local $7
   (i64.const 4411203)
  )
  (block $label$3
   (loop $label$4
    (set_local $8
     (i32.const 0)
    )
    (br_if $label$3
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
    (block $label$5
     (br_if $label$5
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
     (loop $label$6
      (br_if $label$3
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
    (set_local $8
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
  (call $contento_assert
   (get_local $8)
   (i32.const 720)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 72)
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 64)
   )
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (get_local $10)
    (i32.const 56)
   )
   (i64.const 0)
  )
  (i64.store offset=48
   (get_local $10)
   (i64.const 0)
  )
  (i32.store offset=180
   (get_local $10)
   (get_local $6)
  )
  (i32.store offset=176
   (get_local $10)
   (get_local $6)
  )
  (i32.store offset=184
   (get_local $10)
   (i32.add
    (get_local $6)
    (get_local $3)
   )
  )
  (i32.store offset=208
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 176)
   )
  )
  (i32.store offset=80
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 16)
   )
  )
  (call $_ZN5boost6fusion6detail17for_each_unrolledILi3EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJ6namex_N5cosio5assetE11checksum256EEELi0EEEZNS9_rsINS9_10datastreamIPKcEEJS8_SA_SB_EEERT_SK_RNS7_IJDpT0_EEEEUlSK_E_EEvRKSJ_RKT0_
   (i32.add
    (get_local $10)
    (i32.const 80)
   )
   (i32.add
    (get_local $10)
    (i32.const 208)
   )
  )
  (set_local $1
   (i32.add
    (get_local $10)
    (i32.const 48)
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
    (get_local $6)
   )
  )
  (i64.store
   (tee_local $8
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 112)
     )
     (i32.const 8)
    )
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=128
   (get_local $10)
   (i64.load offset=16
    (get_local $10)
   )
  )
  (i64.store offset=136
   (get_local $10)
   (i64.load offset=24
    (get_local $10)
   )
  )
  (i64.store offset=112
   (get_local $10)
   (i64.load
    (get_local $4)
   )
  )
  (i64.store
   (tee_local $6
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 80)
     )
     (i32.const 24)
    )
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store
   (tee_local $3
    (i32.add
     (i32.add
      (get_local $10)
      (i32.const 80)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=80
   (get_local $10)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=88
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 176)
    )
    (i32.const 24)
   )
   (i64.load
    (get_local $6)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 176)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $3)
   )
  )
  (i64.store offset=184
   (get_local $10)
   (i64.load offset=88
    (get_local $10)
   )
  )
  (i64.store offset=176
   (get_local $10)
   (i64.load offset=80
    (get_local $10)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 160)
    )
    (i32.const 8)
   )
   (i64.load
    (get_local $8)
   )
  )
  (i64.store offset=160
   (get_local $10)
   (i64.load offset=112
    (get_local $10)
   )
  )
  (i64.store offset=152
   (get_local $10)
   (i64.load offset=136
    (get_local $10)
   )
  )
  (i64.store offset=144
   (get_local $10)
   (i64.load offset=128
    (get_local $10)
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
   (set_local $9
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $9)
     )
    )
   )
  )
  (i64.store offset=208
   (get_local $10)
   (tee_local $7
    (i64.load offset=144
     (get_local $10)
    )
   )
  )
  (i64.store offset=216
   (get_local $10)
   (tee_local $5
    (i64.load offset=152
     (get_local $10)
    )
   )
  )
  (i64.store
   (get_local $10)
   (get_local $7)
  )
  (i64.store offset=8
   (get_local $10)
   (get_local $5)
  )
  (call_indirect (type $FUNCSIG$viiii)
   (get_local $1)
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 160)
   )
   (i32.add
    (get_local $10)
    (i32.const 176)
   )
   (get_local $9)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 224)
   )
  )
  (i32.const 1)
 )
 (func $_ZN7storage11cancelofferERK11checksum256 (type $FUNCSIG$vii) (param $0 i32) (param $1 i32)
  (local $2 i64)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 80)
    )
   )
  )
  (i32.store offset=40
   (get_local $7)
   (i32.add
    (get_local $0)
    (i32.const 32)
   )
  )
  (set_local $2
   (i64.load offset=24
    (get_local $1)
   )
  )
  (set_local $3
   (i64.load offset=16
    (get_local $1)
   )
  )
  (set_local $4
   (i64.load offset=8
    (get_local $1)
   )
  )
  (set_local $5
   (i64.load
    (get_local $1)
   )
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store offset=8
   (get_local $7)
   (get_local $5)
  )
  (i64.store
   (get_local $7)
   (get_local $4)
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store
   (i32.add
    (get_local $7)
    (i32.const 24)
   )
   (get_local $3)
  )
  (i64.store offset=16
   (get_local $7)
   (get_local $2)
  )
  (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb0EE11lower_boundERKSA_
   (i32.add
    (get_local $7)
    (i32.const 64)
   )
   (i32.add
    (get_local $7)
    (i32.const 40)
   )
   (get_local $7)
  )
  (set_local $0
   (i32.add
    (get_local $7)
    (i32.const 40)
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (tee_local $1
       (i32.load offset=68
        (get_local $7)
       )
      )
     )
    )
    (set_local $4
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 72)
      )
     )
    )
    (set_local $5
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 64)
      )
     )
    )
    (set_local $2
     (i64.load
      (i32.add
       (get_local $1)
       (i32.const 56)
      )
     )
    )
    (set_local $3
     (i64.load offset=48
      (get_local $1)
     )
    )
    (call $contento_assert
     (i32.const 1)
     (i32.const 112)
    )
    (call $contento_assert
     (i32.const 1)
     (i32.const 112)
    )
    (br_if $label$1
     (i64.ne
      (i64.or
       (i64.xor
        (get_local $2)
        (i64.load
         (get_local $7)
        )
       )
       (i64.xor
        (get_local $3)
        (i64.load offset=8
         (get_local $7)
        )
       )
      )
      (i64.const 0)
     )
    )
    (set_local $1
     (i32.const 0)
    )
    (br_if $label$0
     (i64.ne
      (i64.or
       (i64.xor
        (i64.load
         (i32.add
          (get_local $7)
          (i32.const 16)
         )
        )
        (get_local $4)
       )
       (i64.xor
        (i64.load
         (i32.add
          (get_local $7)
          (i32.const 24)
         )
        )
        (get_local $5)
       )
      )
      (i64.const 0)
     )
    )
    (set_local $1
     (i32.load offset=68
      (get_local $7)
     )
    )
    (set_local $0
     (i32.load offset=64
      (get_local $7)
     )
    )
    (br $label$0)
   )
   (set_local $1
    (i32.const 0)
   )
  )
  (call $contento_assert
   (tee_local $6
    (i32.ne
     (get_local $1)
     (i32.const 0)
    )
   )
   (i32.const 160)
  )
  (call $contento_assert
   (i64.eqz
    (i64.load offset=80
     (get_local $1)
    )
   )
   (i32.const 192)
  )
  (i64.store
   (get_local $7)
   (i64.or
    (i64.shl
     (i64.extend_u/i32
      (get_local $1)
     )
     (i64.const 32)
    )
    (i64.extend_u/i32
     (get_local $0)
    )
   )
  )
  (call $contento_assert
   (get_local $6)
   (i32.const 224)
  )
  (drop
   (call $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb0EE14const_iteratorppEv
    (get_local $7)
   )
  )
  (call $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5eraseERKS2_
   (i32.load offset=40
    (get_local $7)
   )
   (get_local $1)
  )
  (i64.store offset=56
   (get_local $7)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=48
   (get_local $7)
   (i64.load offset=16
    (get_local $1)
   )
  )
  (i64.store
   (get_local $7)
   (i64.load offset=48
    (get_local $7)
   )
  )
  (i64.store offset=72
   (get_local $7)
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $7)
   (i64.load offset=56
    (get_local $7)
   )
  )
  (i64.store offset=64
   (get_local $7)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $7)
     (i32.const 64)
    )
    (get_local $7)
    (i32.const 16)
   )
  )
  (set_local $2
   (i64.load offset=64
    (get_local $7)
   )
  )
  (set_local $3
   (i64.load offset=72
    (get_local $7)
   )
  )
  (call $prints
   (i32.const 272)
  )
  (i64.store offset=8
   (get_local $7)
   (get_local $3)
  )
  (i64.store
   (get_local $7)
   (get_local $2)
  )
  (call $_ZNK5cosio5namex9to_stringEv
   (i32.add
    (get_local $7)
    (i32.const 64)
   )
   (get_local $7)
  )
  (call $prints_l
   (select
    (i32.load offset=72
     (get_local $7)
    )
    (i32.or
     (i32.add
      (get_local $7)
      (i32.const 64)
     )
     (i32.const 1)
    )
    (tee_local $0
     (i32.and
      (tee_local $1
       (i32.load8_u offset=64
        (get_local $7)
       )
      )
      (i32.const 1)
     )
    )
   )
   (select
    (i32.load offset=68
     (get_local $7)
    )
    (i32.shr_u
     (get_local $1)
     (i32.const 1)
    )
    (get_local $0)
   )
  )
  (block $label$2
   (br_if $label$2
    (i32.eqz
     (i32.and
      (i32.load8_u offset=64
       (get_local $7)
      )
      (i32.const 1)
     )
    )
   )
   (call $_ZdlPv
    (i32.load
     (i32.add
      (get_local $7)
      (i32.const 72)
     )
    )
   )
  )
  (call $prints
   (i32.const 288)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 80)
   )
  )
 )
 (func $_ZN5cosio14execute_actionI7storageS1_JRK11checksum256EEEbPT_MT0_FvDpT1_E (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i32)
  (set_local $7
   (tee_local $5
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
   (get_local $5)
  )
  (set_local $2
   (i32.load offset=4
    (get_local $1)
   )
  )
  (set_local $6
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
      (set_local $5
       (call $malloc
        (get_local $1)
       )
      )
      (br $label$1)
     )
     (set_local $5
      (i32.const 0)
     )
     (br $label$0)
    )
    (i32.store offset=4
     (i32.const 0)
     (tee_local $5
      (i32.sub
       (get_local $5)
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
     (get_local $5)
     (get_local $1)
    )
   )
  )
  (i64.store
   (tee_local $3
    (i32.add
     (get_local $7)
     (i32.const 24)
    )
   )
   (i64.const 0)
  )
  (i64.store
   (tee_local $4
    (i32.add
     (get_local $7)
     (i32.const 16)
    )
   )
   (i64.const 0)
  )
  (i64.store offset=8
   (get_local $7)
   (i64.const 0)
  )
  (i64.store
   (get_local $7)
   (i64.const 0)
  )
  (call $contento_assert
   (i32.gt_u
    (get_local $1)
    (i32.const 31)
   )
   (i32.const 96)
  )
  (drop
   (call $memcpy
    (get_local $7)
    (get_local $5)
    (i32.const 32)
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
    (get_local $5)
   )
  )
  (i64.store
   (tee_local $1
    (i32.add
     (i32.add
      (get_local $7)
      (i32.const 32)
     )
     (i32.const 24)
    )
   )
   (i64.load
    (get_local $3)
   )
  )
  (i64.store
   (tee_local $5
    (i32.add
     (i32.add
      (get_local $7)
      (i32.const 32)
     )
     (i32.const 16)
    )
   )
   (i64.load
    (get_local $4)
   )
  )
  (i64.store offset=40
   (get_local $7)
   (i64.load offset=8
    (get_local $7)
   )
  )
  (i64.store offset=32
   (get_local $7)
   (i64.load
    (get_local $7)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $7)
     (i32.const 64)
    )
    (i32.const 24)
   )
   (i64.load
    (get_local $1)
   )
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $7)
     (i32.const 64)
    )
    (i32.const 16)
   )
   (i64.load
    (get_local $5)
   )
  )
  (i64.store offset=72
   (get_local $7)
   (i64.load offset=40
    (get_local $7)
   )
  )
  (i64.store offset=64
   (get_local $7)
   (i64.load offset=32
    (get_local $7)
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
   (set_local $6
    (i32.load
     (i32.add
      (i32.load
       (get_local $1)
      )
      (get_local $6)
     )
    )
   )
  )
  (call_indirect (type $FUNCSIG$vii)
   (get_local $1)
   (i32.add
    (get_local $7)
    (i32.const 64)
   )
   (get_local $6)
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 96)
   )
  )
  (i32.const 1)
 )
 (func $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb0EE11lower_boundERKSA_ (param $0 i32) (param $1 i32) (param $2 i32)
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
     (i32.const 144)
    )
   )
  )
  (i64.store offset=104
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
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
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=72
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=64
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=48
   (get_local $10)
   (i32.load
    (tee_local $2
     (i32.load
      (get_local $1)
     )
    )
   )
  )
  (i32.store offset=60
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store offset=56
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=52
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i64.store offset=32
   (get_local $10)
   (i64.load offset=16
    (get_local $2)
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=16
   (get_local $10)
   (i64.load offset=48
    (get_local $10)
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.load offset=56
    (get_local $10)
   )
  )
  (i64.store
   (get_local $10)
   (i64.load offset=32
    (get_local $10)
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load offset=40
    (get_local $10)
   )
  )
  (i64.store offset=128
   (get_local $10)
   (i64.load
    (get_local $10)
   )
  )
  (i64.store offset=136
   (get_local $10)
   (i64.load offset=8
    (get_local $10)
   )
  )
  (i64.store offset=120
   (get_local $10)
   (i64.load offset=24
    (get_local $10)
   )
  )
  (i64.store offset=112
   (get_local $10)
   (i64.load offset=16
    (get_local $10)
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
       (i32.add
        (get_local $10)
        (i32.const 112)
       )
       (i32.add
        (get_local $10)
        (i32.const 128)
       )
       (i64.const -6712989628304982015)
       (i32.add
        (get_local $10)
        (i32.const 64)
       )
       (i32.const 2)
       (i32.add
        (get_local $10)
        (i32.const 104)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=104
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
         (i32.const 44)
        )
       )
      )
      (tee_local $6
       (i32.load offset=40
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
     (call $contento_assert
      (i32.eq
       (i32.load offset=88
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
      (i32.const 560)
     )
     (br $label$3)
    )
    (call $contento_assert
     (i32.eq
      (i32.load offset=88
       (tee_local $2
        (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (get_local $4)
          (i32.add
           (get_local $4)
           (i32.const 16)
          )
          (i64.const -6712989628304982016)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 560)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 100)
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
    (i32.const 144)
   )
  )
 )
 (func $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb0EE14const_iteratorppEv (param $0 i32) (result i32)
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
     (i32.const 96)
    )
   )
  )
  (set_local $7
   (i32.const 0)
  )
  (call $contento_assert
   (i32.ne
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 0)
   )
   (i32.const 528)
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
        (i32.const 100)
       )
      )
     )
     (i32.const -1)
    )
   )
   (i64.store
    (i32.add
     (i32.add
      (get_local $9)
      (i32.const 32)
     )
     (i32.const 24)
    )
    (i64.const 0)
   )
   (i64.store
    (i32.add
     (get_local $9)
     (i32.const 48)
    )
    (i64.const 0)
   )
   (i64.store offset=40
    (get_local $9)
    (i64.const 0)
   )
   (i64.store offset=32
    (get_local $9)
    (i64.const 0)
   )
   (i64.store offset=16
    (get_local $9)
    (i64.load
     (tee_local $6
      (i32.load
       (i32.load
        (get_local $0)
       )
      )
     )
    )
   )
   (i64.store offset=24
    (get_local $9)
    (i64.load
     (i32.add
      (get_local $6)
      (i32.const 8)
     )
    )
   )
   (i64.store offset=8
    (get_local $9)
    (i64.load
     (i32.add
      (get_local $6)
      (i32.const 24)
     )
    )
   )
   (i64.store
    (get_local $9)
    (i64.load offset=16
     (get_local $6)
    )
   )
   (set_local $3
    (i64.load
     (get_local $8)
    )
   )
   (i64.store offset=80
    (get_local $9)
    (i64.load
     (get_local $9)
    )
   )
   (i64.store offset=88
    (get_local $9)
    (i64.load offset=8
     (get_local $9)
    )
   )
   (i64.store offset=72
    (get_local $9)
    (i64.load offset=24
     (get_local $9)
    )
   )
   (i64.store offset=64
    (get_local $9)
    (i64.load offset=16
     (get_local $9)
    )
   )
   (set_local $6
    (call $db_idx256_find_primary
     (i32.add
      (get_local $9)
      (i32.const 64)
     )
     (i32.add
      (get_local $9)
      (i32.const 80)
     )
     (i64.const -6712989628304982015)
     (i32.add
      (get_local $9)
      (i32.const 32)
     )
     (i32.const 2)
     (get_local $3)
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
     (i32.const 100)
    )
    (get_local $6)
   )
  )
  (i64.store offset=32
   (get_local $9)
   (i64.const 0)
  )
  (block $label$1
   (br_if $label$1
    (i32.lt_s
     (tee_local $1
      (call $db_idx256_next
       (get_local $6)
       (i32.add
        (get_local $9)
        (i32.const 32)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $3
    (i64.load offset=32
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
         (i32.const 44)
        )
       )
      )
      (tee_local $4
       (i32.load offset=40
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
     (call $contento_assert
      (i32.eq
       (i32.load offset=88
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
      (i32.const 560)
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
        (get_local $2)
        (i32.add
         (get_local $2)
         (i32.const 16)
        )
        (i64.const -6712989628304982016)
        (get_local $3)
       )
      )
      (i32.const 0)
     )
    )
    (call $contento_assert
     (i32.eq
      (i32.load offset=88
       (tee_local $7
        (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $2)
         (get_local $6)
        )
       )
      )
      (get_local $2)
     )
     (i32.const 560)
    )
   )
   (i32.store
    (i32.add
     (get_local $7)
     (i32.const 100)
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
    (i32.const 96)
   )
  )
  (get_local $0)
 )
 (func $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5eraseERKS2_ (param $0 i32) (param $1 i32)
  (local $2 i64)
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
     (i32.const 64)
    )
   )
  )
  (call $contento_assert
   (i32.eq
    (i32.load offset=88
     (get_local $1)
    )
    (get_local $0)
   )
   (i32.const 352)
  )
  (call $current_receiver
   (get_local $10)
  )
  (i64.store offset=24
   (get_local $10)
   (i64.load offset=8
    (get_local $10)
   )
  )
  (i64.store offset=16
   (get_local $10)
   (i64.load
    (get_local $10)
   )
  )
  (i64.store offset=48
   (get_local $10)
   (i64.load offset=16
    (get_local $10)
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $10)
   (i64.load offset=24
    (get_local $10)
   )
  )
  (i64.store offset=32
   (get_local $10)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $10)
     (i32.const 32)
    )
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (set_local $2
   (i64.load offset=32
    (get_local $10)
   )
  )
  (set_local $5
   (i64.load offset=40
    (get_local $10)
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=16
   (get_local $10)
   (i64.load
    (get_local $0)
   )
  )
  (i64.store offset=48
   (get_local $10)
   (i64.load offset=16
    (get_local $10)
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $10)
   (i64.load offset=24
    (get_local $10)
   )
  )
  (i64.store offset=32
   (get_local $10)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $10)
     (i32.const 32)
    )
    (i32.add
     (get_local $10)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (call $contento_assert
   (i32.and
    (i64.eq
     (get_local $2)
     (i64.load offset=32
      (get_local $10)
     )
    )
    (i64.eq
     (get_local $5)
     (i64.load offset=40
      (get_local $10)
     )
    )
   )
   (i32.const 400)
  )
  (block $label$0
   (br_if $label$0
    (i32.eq
     (tee_local $8
      (i32.load
       (tee_local $6
        (i32.add
         (get_local $0)
         (i32.const 44)
        )
       )
      )
     )
     (tee_local $3
      (i32.load offset=40
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
   (set_local $7
    (i32.sub
     (i32.const 0)
     (get_local $3)
    )
   )
   (set_local $9
    (i32.add
     (get_local $8)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i64.eq
      (i64.load
       (i32.load
        (get_local $9)
       )
      )
      (get_local $2)
     )
    )
    (set_local $8
     (get_local $9)
    )
    (set_local $9
     (tee_local $4
      (i32.add
       (get_local $9)
       (i32.const -24)
      )
     )
    )
    (br_if $label$1
     (i32.ne
      (i32.add
       (get_local $4)
       (get_local $7)
      )
      (i32.const -24)
     )
    )
   )
  )
  (call $contento_assert
   (i32.ne
    (get_local $8)
    (get_local $3)
   )
   (i32.const 464)
  )
  (set_local $9
   (i32.add
    (get_local $8)
    (i32.const -24)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.eq
      (get_local $8)
      (tee_local $4
       (i32.load
        (get_local $6)
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
    (set_local $8
     (get_local $9)
    )
    (loop $label$4
     (set_local $7
      (i32.load
       (tee_local $9
        (i32.add
         (get_local $8)
         (i32.const 24)
        )
       )
      )
     )
     (i32.store
      (get_local $9)
      (i32.const 0)
     )
     (set_local $4
      (i32.load
       (get_local $8)
      )
     )
     (i32.store
      (get_local $8)
      (get_local $7)
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
       (get_local $8)
       (i32.const 16)
      )
      (i32.load
       (i32.add
        (get_local $8)
        (i32.const 40)
       )
      )
     )
     (i64.store
      (i32.add
       (get_local $8)
       (i32.const 8)
      )
      (i64.load
       (i32.add
        (get_local $8)
        (i32.const 32)
       )
      )
     )
     (set_local $8
      (get_local $9)
     )
     (br_if $label$4
      (i32.ne
       (i32.add
        (get_local $9)
        (get_local $3)
       )
       (i32.const -24)
      )
     )
    )
    (br_if $label$2
     (i32.eq
      (tee_local $8
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 44)
        )
       )
      )
      (get_local $9)
     )
    )
   )
   (loop $label$6
    (set_local $4
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
      (get_local $9)
      (get_local $8)
     )
    )
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 44)
   )
   (get_local $9)
  )
  (call $db_remove_i64
   (i32.load
    (i32.add
     (get_local $1)
     (i32.const 92)
    )
   )
  )
  (i32.store offset=52
   (get_local $10)
   (get_local $1)
  )
  (i32.store offset=48
   (get_local $10)
   (get_local $0)
  )
  (i32.store offset=32
   (get_local $10)
   (i32.add
    (get_local $10)
    (i32.const 48)
   )
  )
  (call $_ZNK5boost4hana6detail7on_eachIPZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS3_10indexed_byILy4229443000054317056ENS_11multi_index13const_mem_funIS6_yXadL_ZNKS6_6by_betEvEEEEEENS7_ILy4982431883047354368ENS9_IS6_NS3_9fixed_keyILj32EEEXadL_ZNKS6_13by_commitmentEvEEEEEEEE5eraseERKS6_EUlRT_E_EclIJRNS0_5tupleIJNS0_9type_implINSG_5indexILy4229443000054317056ESA_Ly0ELb0EEEE1_ENSQ_INSR_ILy4229443000054317056ESA_Ly0ELb1EEEE1_EEEERNSP_IJNSQ_INSR_ILy4982431883047354368ESE_Ly1ELb0EEEE1_ENSQ_INSR_ILy4982431883047354368ESE_Ly1ELb1EEEE1_EEEEEEEvDpOT_
   (i32.add
    (get_local $10)
    (i32.const 32)
   )
   (i32.add
    (get_local $0)
    (i32.const 52)
   )
   (i32.add
    (get_local $0)
    (i32.const 53)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $10)
    (i32.const 64)
   )
  )
 )
 (func $_ZNK5cosio5namex9to_stringEv (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i64)
  (i64.store align=4
   (get_local $0)
   (i64.const 0)
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 8)
   )
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.ge_u
     (tee_local $2
      (call $strlen
       (i32.const 336)
      )
     )
     (i32.const -16)
    )
   )
   (block $label$1
    (block $label$2
     (block $label$3
      (br_if $label$3
       (i32.ge_u
        (get_local $2)
        (i32.const 11)
       )
      )
      (i32.store8
       (get_local $0)
       (i32.shl
        (get_local $2)
        (i32.const 1)
       )
      )
      (set_local $4
       (i32.add
        (get_local $0)
        (i32.const 1)
       )
      )
      (br_if $label$2
       (get_local $2)
      )
      (br $label$1)
     )
     (set_local $4
      (call $_Znwj
       (tee_local $3
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
      (get_local $0)
      (i32.or
       (get_local $3)
       (i32.const 1)
      )
     )
     (i32.store offset=8
      (get_local $0)
      (get_local $4)
     )
     (i32.store offset=4
      (get_local $0)
      (get_local $2)
     )
    )
    (drop
     (call $memcpy
      (get_local $4)
      (i32.const 336)
      (get_local $2)
     )
    )
   )
   (i32.store8
    (i32.add
     (get_local $4)
     (get_local $2)
    )
    (i32.const 0)
   )
   (set_local $5
    (i64.load offset=8
     (get_local $1)
    )
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i64.eqz
       (tee_local $6
        (i64.load
         (get_local $1)
        )
       )
      )
     )
     (br_if $label$5
      (i64.eqz
       (get_local $5)
      )
     )
     (loop $label$6
      (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9push_backEc
       (get_local $0)
       (i32.shr_s
        (i32.shl
         (i32.wrap/i64
          (get_local $5)
         )
         (i32.const 24)
        )
        (i32.const 24)
       )
      )
      (br_if $label$6
       (i64.ne
        (tee_local $5
         (i64.shr_u
          (get_local $5)
          (i64.const 8)
         )
        )
        (i64.const 0)
       )
      )
     )
     (loop $label$7
      (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9push_backEc
       (get_local $0)
       (i32.shr_s
        (i32.shl
         (i32.wrap/i64
          (get_local $6)
         )
         (i32.const 24)
        )
        (i32.const 24)
       )
      )
      (br_if $label$7
       (i32.eqz
        (i64.eqz
         (tee_local $6
          (i64.shr_u
           (get_local $6)
           (i64.const 8)
          )
         )
        )
       )
      )
      (br $label$4)
     )
    )
    (br_if $label$4
     (i64.ne
      (get_local $6)
      (i64.const 0)
     )
    )
    (br_if $label$4
     (i64.eqz
      (get_local $5)
     )
    )
    (loop $label$8
     (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9push_backEc
      (get_local $0)
      (i32.shr_s
       (i32.shl
        (i32.wrap/i64
         (get_local $5)
        )
        (i32.const 24)
       )
       (i32.const 24)
      )
     )
     (br_if $label$8
      (i64.ne
       (tee_local $5
        (i64.shr_u
         (get_local $5)
         (i64.const 8)
        )
       )
       (i64.const 0)
      )
     )
    )
   )
   (return)
  )
  (call $_ZNKSt3__121__basic_string_commonILb1EE20__throw_length_errorEv
   (get_local $0)
  )
  (unreachable)
 )
 (func $_ZNK5boost4hana6detail7on_eachIPZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS3_10indexed_byILy4229443000054317056ENS_11multi_index13const_mem_funIS6_yXadL_ZNKS6_6by_betEvEEEEEENS7_ILy4982431883047354368ENS9_IS6_NS3_9fixed_keyILj32EEEXadL_ZNKS6_13by_commitmentEvEEEEEEEE5eraseERKS6_EUlRT_E_EclIJRNS0_5tupleIJNS0_9type_implINSG_5indexILy4229443000054317056ESA_Ly0ELb0EEEE1_ENSQ_INSR_ILy4229443000054317056ESA_Ly0ELb1EEEE1_EEEERNSP_IJNSQ_INSR_ILy4982431883047354368ESE_Ly1ELb0EEEE1_ENSQ_INSR_ILy4982431883047354368ESE_Ly1ELb1EEEE1_EEEEEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i64)
  (local $6 i32)
  (local $7 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $7
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 96)
    )
   )
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.gt_s
      (tee_local $6
       (i32.load offset=96
        (tee_local $3
         (i32.load offset=4
          (tee_local $4
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
    (i64.store offset=16
     (get_local $7)
     (i64.load
      (tee_local $6
       (i32.load
        (get_local $4)
       )
      )
     )
    )
    (i64.store offset=24
     (get_local $7)
     (i64.load
      (i32.add
       (get_local $6)
       (i32.const 8)
      )
     )
    )
    (i64.store offset=8
     (get_local $7)
     (i64.load
      (i32.add
       (get_local $6)
       (i32.const 24)
      )
     )
    )
    (i64.store
     (get_local $7)
     (i64.load offset=16
      (get_local $6)
     )
    )
    (set_local $5
     (i64.load
      (get_local $3)
     )
    )
    (i64.store offset=32
     (get_local $7)
     (i64.load
      (get_local $7)
     )
    )
    (i64.store offset=40
     (get_local $7)
     (i64.load offset=8
      (get_local $7)
     )
    )
    (i64.store offset=88
     (get_local $7)
     (i64.load offset=24
      (get_local $7)
     )
    )
    (i64.store offset=80
     (get_local $7)
     (i64.load offset=16
      (get_local $7)
     )
    )
    (br_if $label$0
     (i32.lt_s
      (tee_local $6
       (call $db_idx64_find_primary
        (i32.add
         (get_local $7)
         (i32.const 80)
        )
        (i32.add
         (get_local $7)
         (i32.const 32)
        )
        (i64.const -6712989628304982016)
        (i32.add
         (get_local $7)
         (i32.const 64)
        )
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx64_remove
    (get_local $6)
   )
  )
  (block $label$2
   (block $label$3
    (br_if $label$3
     (i32.gt_s
      (tee_local $0
       (i32.load
        (i32.add
         (tee_local $4
          (i32.load offset=4
           (tee_local $6
            (i32.load
             (get_local $0)
            )
           )
          )
         )
         (i32.const 100)
        )
       )
      )
      (i32.const -1)
     )
    )
    (set_local $0
     (i32.load
      (get_local $6)
     )
    )
    (i64.store
     (i32.add
      (i32.add
       (get_local $7)
       (i32.const 32)
      )
      (i32.const 24)
     )
     (i64.const 0)
    )
    (i64.store
     (i32.add
      (get_local $7)
      (i32.const 48)
     )
     (i64.const 0)
    )
    (i64.store offset=40
     (get_local $7)
     (i64.const 0)
    )
    (i64.store offset=32
     (get_local $7)
     (i64.const 0)
    )
    (i64.store offset=24
     (get_local $7)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 8)
      )
     )
    )
    (i64.store offset=16
     (get_local $7)
     (i64.load
      (get_local $0)
     )
    )
    (i64.store offset=8
     (get_local $7)
     (i64.load
      (i32.add
       (get_local $0)
       (i32.const 24)
      )
     )
    )
    (i64.store
     (get_local $7)
     (i64.load offset=16
      (get_local $0)
     )
    )
    (set_local $5
     (i64.load
      (get_local $4)
     )
    )
    (i64.store offset=80
     (get_local $7)
     (i64.load
      (get_local $7)
     )
    )
    (i64.store offset=88
     (get_local $7)
     (i64.load offset=8
      (get_local $7)
     )
    )
    (i64.store offset=72
     (get_local $7)
     (i64.load offset=24
      (get_local $7)
     )
    )
    (i64.store offset=64
     (get_local $7)
     (i64.load offset=16
      (get_local $7)
     )
    )
    (br_if $label$2
     (i32.lt_s
      (tee_local $0
       (call $db_idx256_find_primary
        (i32.add
         (get_local $7)
         (i32.const 64)
        )
        (i32.add
         (get_local $7)
         (i32.const 80)
        )
        (i64.const -6712989628304982015)
        (i32.add
         (get_local $7)
         (i32.const 32)
        )
        (i32.const 2)
        (get_local $5)
       )
      )
      (i32.const 0)
     )
    )
   )
   (call $db_idx256_remove
    (get_local $0)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $7)
    (i32.const 96)
   )
  )
 )
 (func $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
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
     (tee_local $6
      (i32.load
       (i32.add
        (get_local $0)
        (i32.const 44)
       )
      )
     )
     (tee_local $2
      (i32.load offset=40
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
   (set_local $5
    (i32.add
     (get_local $6)
     (i32.const -24)
    )
   )
   (loop $label$1
    (br_if $label$0
     (i32.eq
      (i32.load
       (i32.add
        (get_local $5)
        (i32.const 16)
       )
      )
      (get_local $1)
     )
    )
    (set_local $6
     (get_local $5)
    )
    (set_local $5
     (tee_local $4
      (i32.add
       (get_local $5)
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
      (get_local $6)
      (get_local $2)
     )
    )
    (set_local $4
     (i32.load
      (i32.add
       (get_local $6)
       (i32.const -24)
      )
     )
    )
    (br $label$2)
   )
   (call $contento_assert
    (i32.xor
     (i32.shr_u
      (tee_local $5
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
    (i32.const 624)
   )
   (block $label$4
    (block $label$5
     (br_if $label$5
      (i32.lt_u
       (get_local $5)
       (i32.const 513)
      )
     )
     (set_local $4
      (call $malloc
       (get_local $5)
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
         (get_local $5)
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
     (get_local $5)
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
     (get_local $5)
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.lt_u
      (get_local $5)
      (i32.const 513)
     )
    )
    (call $free
     (get_local $4)
    )
   )
   (set_local $3
    (i32.add
     (get_local $0)
     (i32.const 40)
    )
   )
   (i64.store offset=40
    (tee_local $4
     (call $_Znwj
      (i32.const 112)
     )
    )
    (i64.const 1129267971)
   )
   (i64.store offset=32
    (get_local $4)
    (i64.const 0)
   )
   (call $contento_assert
    (i32.const 1)
    (i32.const 656)
   )
   (set_local $7
    (i64.const 4411203)
   )
   (set_local $5
    (i32.const 0)
   )
   (block $label$7
    (block $label$8
     (loop $label$9
      (br_if $label$8
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
      (block $label$10
       (br_if $label$10
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
       (loop $label$11
        (br_if $label$8
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
        (br_if $label$11
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
      (set_local $6
       (i32.const 1)
      )
      (br_if $label$9
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
      (br $label$7)
     )
    )
    (set_local $6
     (i32.const 0)
    )
   )
   (call $contento_assert
    (get_local $6)
    (i32.const 720)
   )
   (i32.store offset=88
    (get_local $4)
    (get_local $0)
   )
   (i64.store offset=80
    (get_local $4)
    (i64.const 0)
   )
   (drop
    (call $_ZrsIN5cosio10datastreamIPKcEEERT_S6_RN7storage5offerE
     (i32.add
      (get_local $8)
      (i32.const 32)
     )
     (get_local $4)
    )
   )
   (i32.store offset=96
    (get_local $4)
    (i32.const -1)
   )
   (i32.store offset=92
    (get_local $4)
    (get_local $1)
   )
   (i32.store offset=100
    (get_local $4)
    (i32.const -1)
   )
   (i32.store offset=24
    (get_local $8)
    (get_local $4)
   )
   (i64.store offset=16
    (get_local $8)
    (tee_local $7
     (i64.load
      (get_local $4)
     )
    )
   )
   (i32.store offset=12
    (get_local $8)
    (tee_local $6
     (i32.load offset=92
      (get_local $4)
     )
    )
   )
   (block $label$12
    (block $label$13
     (br_if $label$13
      (i32.ge_u
       (tee_local $5
        (i32.load
         (tee_local $1
          (i32.add
           (get_local $0)
           (i32.const 44)
          )
         )
        )
       )
       (i32.load
        (i32.add
         (get_local $0)
         (i32.const 48)
        )
       )
      )
     )
     (i64.store offset=8
      (get_local $5)
      (get_local $7)
     )
     (i32.store offset=16
      (get_local $5)
      (get_local $6)
     )
     (i32.store offset=24
      (get_local $8)
      (i32.const 0)
     )
     (i32.store
      (get_local $5)
      (get_local $4)
     )
     (i32.store
      (get_local $1)
      (i32.add
       (get_local $5)
       (i32.const 24)
      )
     )
     (br $label$12)
    )
    (call $_ZNSt3__16vectorIN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS1_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_6by_betEvEEEEEENS5_ILy4982431883047354368ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_13by_commitmentEvEEEEEEEE8item_ptrENS_9allocatorISG_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSF_4itemENS_14default_deleteISM_EEEERyRlEEEvDpOT_
     (get_local $3)
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
   (set_local $5
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
     (get_local $5)
    )
   )
   (call $_ZdlPv
    (get_local $5)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
  )
  (get_local $4)
 )
 (func $_ZrsIN5cosio10datastreamIPKcEEERT_S6_RN7storage5offerE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $contento_assert
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
   (i32.const 96)
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
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 96)
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
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 96)
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
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 96)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 40)
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
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 31)
   )
   (i32.const 96)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 32)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 32)
    )
   )
  )
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 96)
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
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (get_local $0)
 )
 (func $_ZNSt3__16vectorIN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS1_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_6by_betEvEEEEEENS5_ILy4982431883047354368ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_13by_commitmentEvEEEEEEEE8item_ptrENS_9allocatorISG_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSF_4itemENS_14default_deleteISM_EEEERyRlEEEvDpOT_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
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
 (func $_ZN5boost6fusion6detail17for_each_unrolledILi3EE4callINS0_18std_tuple_iteratorINSt3__15tupleIJ6namex_N5cosio5assetE11checksum256EEELi0EEEZNS9_rsINS9_10datastreamIPKcEEJS8_SA_SB_EEERT_SK_RNS7_IJDpT0_EEEEUlSK_E_EEvRKSJ_RKT0_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (call $contento_assert
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
    (i32.const 15)
   )
   (i32.const 96)
  )
  (drop
   (call $memcpy
    (get_local $2)
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 16)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 16)
   )
  )
  (set_local $0
   (i32.load
    (get_local $0)
   )
  )
  (call $contento_assert
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
   (i32.const 96)
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
  (call $contento_assert
   (i32.gt_u
    (i32.sub
     (i32.load offset=8
      (get_local $3)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 96)
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
  (call $contento_assert
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
    (i32.const 31)
   )
   (i32.const 96)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $0)
     (i32.const 32)
    )
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 32)
   )
  )
  (i32.store offset=4
   (get_local $3)
   (i32.add
    (i32.load offset=4
     (get_local $3)
    )
    (i32.const 32)
   )
  )
 )
 (func $_ZNK7storage9has_offerERK11checksum256 (param $0 i32) (param $1 i32) (result i32)
  (local $2 i64)
  (local $3 i64)
  (local $4 i64)
  (local $5 i64)
  (local $6 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $6
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
    )
   )
  )
  (i32.store offset=32
   (get_local $6)
   (i32.add
    (get_local $0)
    (i32.const 32)
   )
  )
  (set_local $2
   (i64.load offset=24
    (get_local $1)
   )
  )
  (set_local $3
   (i64.load offset=16
    (get_local $1)
   )
  )
  (set_local $4
   (i64.load offset=8
    (get_local $1)
   )
  )
  (set_local $5
   (i64.load
    (get_local $1)
   )
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store offset=8
   (get_local $6)
   (get_local $5)
  )
  (i64.store
   (get_local $6)
   (get_local $4)
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store
   (i32.add
    (get_local $6)
    (i32.const 24)
   )
   (get_local $3)
  )
  (i64.store offset=16
   (get_local $6)
   (get_local $2)
  )
  (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb1EE11lower_boundERKSA_
   (i32.add
    (get_local $6)
    (i32.const 40)
   )
   (i32.add
    (get_local $6)
    (i32.const 32)
   )
   (get_local $6)
  )
  (set_local $0
   (i32.const 0)
  )
  (block $label$0
   (br_if $label$0
    (i32.eqz
     (tee_local $1
      (i32.load offset=44
       (get_local $6)
      )
     )
    )
   )
   (set_local $4
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 72)
     )
    )
   )
   (set_local $5
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 64)
     )
    )
   )
   (set_local $2
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 56)
     )
    )
   )
   (set_local $3
    (i64.load offset=48
     (get_local $1)
    )
   )
   (call $contento_assert
    (i32.const 1)
    (i32.const 112)
   )
   (call $contento_assert
    (i32.const 1)
    (i32.const 112)
   )
   (br_if $label$0
    (i64.ne
     (i64.or
      (i64.xor
       (get_local $2)
       (i64.load
        (get_local $6)
       )
      )
      (i64.xor
       (get_local $3)
       (i64.load offset=8
        (get_local $6)
       )
      )
     )
     (i64.const 0)
    )
   )
   (br_if $label$0
    (i64.ne
     (i64.or
      (i64.xor
       (i64.load
        (i32.add
         (get_local $6)
         (i32.const 16)
        )
       )
       (get_local $4)
      )
      (i64.xor
       (i64.load
        (i32.add
         (get_local $6)
         (i32.const 24)
        )
       )
       (get_local $5)
      )
     )
     (i64.const 0)
    )
   )
   (set_local $0
    (i32.ne
     (i32.load offset=44
      (get_local $6)
     )
     (i32.const 0)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $6)
    (i32.const 48)
   )
  )
  (get_local $0)
 )
 (func $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE7emplaceIZNS1_10placeofferE6namex_RKNS_5assetERK11checksum256EUlRT_E_EENSD_14const_iteratorESF_OSM_ (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32)
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
  (call $current_receiver
   (get_local $8)
  )
  (i64.store offset=24
   (get_local $8)
   (i64.load offset=8
    (get_local $8)
   )
  )
  (i64.store offset=16
   (get_local $8)
   (i64.load
    (get_local $8)
   )
  )
  (i64.store offset=48
   (get_local $8)
   (i64.load offset=16
    (get_local $8)
   )
  )
  (i64.store offset=40
   (get_local $8)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $8)
   (i64.load offset=24
    (get_local $8)
   )
  )
  (i64.store offset=32
   (get_local $8)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $8)
     (i32.const 32)
    )
    (i32.add
     (get_local $8)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (set_local $6
   (i64.load offset=32
    (get_local $8)
   )
  )
  (set_local $4
   (i64.load offset=40
    (get_local $8)
   )
  )
  (i64.store offset=24
   (get_local $8)
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=16
   (get_local $8)
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=48
   (get_local $8)
   (i64.load offset=16
    (get_local $8)
   )
  )
  (i64.store offset=40
   (get_local $8)
   (i64.const 0)
  )
  (i64.store offset=56
   (get_local $8)
   (i64.load offset=24
    (get_local $8)
   )
  )
  (i64.store offset=32
   (get_local $8)
   (i64.const 0)
  )
  (drop
   (call $memcpy
    (i32.add
     (get_local $8)
     (i32.const 32)
    )
    (i32.add
     (get_local $8)
     (i32.const 48)
    )
    (i32.const 16)
   )
  )
  (call $contento_assert
   (i32.and
    (i64.eq
     (get_local $6)
     (i64.load offset=32
      (get_local $8)
     )
    )
    (i64.eq
     (get_local $4)
     (i64.load offset=40
      (get_local $8)
     )
    )
   )
   (i32.const 928)
  )
  (i32.store offset=52
   (get_local $8)
   (get_local $3)
  )
  (i32.store offset=48
   (get_local $8)
   (get_local $1)
  )
  (i32.store offset=56
   (get_local $8)
   (get_local $2)
  )
  (i64.store offset=40
   (tee_local $3
    (call $_Znwj
     (i32.const 112)
    )
   )
   (i64.const 1129267971)
  )
  (i64.store offset=32
   (get_local $3)
   (i64.const 0)
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 656)
  )
  (set_local $6
   (i64.const 4411203)
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
          (get_local $6)
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
      (loop $label$4
       (br_if $label$1
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
     (set_local $7
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
   (set_local $7
    (i32.const 0)
   )
  )
  (call $contento_assert
   (get_local $7)
   (i32.const 720)
  )
  (i32.store offset=88
   (get_local $3)
   (get_local $1)
  )
  (i64.store offset=80
   (get_local $3)
   (i64.const 0)
  )
  (call $_ZZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE7emplaceIZNS1_10placeofferE6namex_RKNS_5assetERK11checksum256EUlRT_E_EENSD_14const_iteratorESF_OSM_ENKUlSN_E_clINSD_4itemEEEDaSN_
   (i32.add
    (get_local $8)
    (i32.const 48)
   )
   (get_local $3)
  )
  (i32.store offset=32
   (get_local $8)
   (get_local $3)
  )
  (i64.store offset=48
   (get_local $8)
   (tee_local $6
    (i64.load
     (get_local $3)
    )
   )
  )
  (i32.store offset=16
   (get_local $8)
   (tee_local $7
    (i32.load offset=92
     (get_local $3)
    )
   )
  )
  (block $label$5
   (block $label$6
    (br_if $label$6
     (i32.ge_u
      (tee_local $2
       (i32.load
        (tee_local $5
         (i32.add
          (get_local $1)
          (i32.const 44)
         )
        )
       )
      )
      (i32.load
       (i32.add
        (get_local $1)
        (i32.const 48)
       )
      )
     )
    )
    (i64.store offset=8
     (get_local $2)
     (get_local $6)
    )
    (i32.store offset=16
     (get_local $2)
     (get_local $7)
    )
    (i32.store offset=32
     (get_local $8)
     (i32.const 0)
    )
    (i32.store
     (get_local $2)
     (get_local $3)
    )
    (i32.store
     (get_local $5)
     (i32.add
      (get_local $2)
      (i32.const 24)
     )
    )
    (br $label$5)
   )
   (call $_ZNSt3__16vectorIN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS1_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS4_yXadL_ZNKS4_6by_betEvEEEEEENS5_ILy4982431883047354368ENS8_IS4_NS1_9fixed_keyILj32EEEXadL_ZNKS4_13by_commitmentEvEEEEEEEE8item_ptrENS_9allocatorISG_EEE24__emplace_back_slow_pathIJNS_10unique_ptrINSF_4itemENS_14default_deleteISM_EEEERyRlEEEvDpOT_
    (i32.add
     (get_local $1)
     (i32.const 40)
    )
    (i32.add
     (get_local $8)
     (i32.const 32)
    )
    (i32.add
     (get_local $8)
     (i32.const 48)
    )
    (i32.add
     (get_local $8)
     (i32.const 16)
    )
   )
  )
  (i32.store offset=4
   (get_local $0)
   (get_local $3)
  )
  (i32.store
   (get_local $0)
   (get_local $1)
  )
  (set_local $2
   (i32.load offset=32
    (get_local $8)
   )
  )
  (i32.store offset=32
   (get_local $8)
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
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $8)
    (i32.const 64)
   )
  )
 )
 (func $_ZZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE7emplaceIZNS1_10placeofferE6namex_RKNS_5assetERK11checksum256EUlRT_E_EENSD_14const_iteratorESF_OSM_ENKUlSN_E_clINSD_4itemEEEDaSN_ (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (local $5 i32)
  (local $6 i32)
  (local $7 i64)
  (local $8 i32)
  (local $9 i64)
  (local $10 i64)
  (local $11 i64)
  (local $12 i64)
  (local $13 i32)
  (local $14 i32)
  (set_local $13
   (tee_local $14
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 112)
    )
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (get_local $14)
  )
  (set_local $2
   (i32.load
    (get_local $0)
   )
  )
  (block $label$0
   (br_if $label$0
    (i64.ne
     (tee_local $7
      (i64.load
       (tee_local $8
        (i32.add
         (tee_local $4
          (i32.load
           (tee_local $3
            (i32.load offset=4
             (get_local $0)
            )
           )
          )
         )
         (i32.const 64)
        )
       )
      )
     )
     (i64.const -1)
    )
   )
   (set_local $7
    (i64.const 0)
   )
   (block $label$1
    (br_if $label$1
     (i32.lt_s
      (tee_local $6
       (call $db_lowerbound_i64
        (tee_local $5
         (i32.add
          (get_local $4)
          (i32.const 32)
         )
        )
        (i32.add
         (get_local $4)
         (i32.const 48)
        )
        (i64.const -6712989628304982016)
        (i64.const 0)
       )
      )
      (i32.const 0)
     )
    )
    (drop
     (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl
      (get_local $5)
      (get_local $6)
     )
    )
    (i32.store offset=52
     (get_local $13)
     (i32.const 0)
    )
    (i32.store offset=48
     (get_local $13)
     (get_local $5)
    )
    (set_local $7
     (select
      (i64.const -2)
      (i64.add
       (tee_local $7
        (i64.load
         (i32.load offset=4
          (call $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE14const_iteratormmEv
           (i32.add
            (get_local $13)
            (i32.const 48)
           )
          )
         )
        )
       )
       (i64.const 1)
      )
      (i64.gt_u
       (get_local $7)
       (i64.const -3)
      )
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $4)
     (i32.const 64)
    )
    (get_local $7)
   )
  )
  (call $contento_assert
   (i64.lt_u
    (get_local $7)
    (i64.const -2)
   )
   (i32.const 992)
  )
  (i64.store
   (get_local $1)
   (i64.load
    (get_local $8)
   )
  )
  (i64.store offset=32
   (get_local $1)
   (i64.load
    (tee_local $4
     (i32.load offset=4
      (get_local $3)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 40)
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=16
   (get_local $1)
   (i64.load
    (tee_local $4
     (i32.load offset=8
      (get_local $3)
     )
    )
   )
  )
  (i64.store
   (i32.add
    (get_local $1)
    (i32.const 24)
   )
   (i64.load
    (i32.add
     (get_local $4)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=48
   (get_local $1)
   (i64.load
    (tee_local $3
     (i32.load offset=12
      (get_local $3)
     )
    )
   )
  )
  (i64.store
   (tee_local $4
    (i32.add
     (get_local $1)
     (i32.const 72)
    )
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
    (get_local $1)
    (i32.const 64)
   )
   (i64.load
    (i32.add
     (get_local $3)
     (i32.const 16)
    )
   )
  )
  (i64.store
   (tee_local $8
    (i32.add
     (get_local $1)
     (i32.const 56)
    )
   )
   (i64.load
    (i32.add
     (get_local $3)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=80
   (get_local $1)
   (i64.const 0)
  )
  (i32.store offset=4
   (i32.const 0)
   (tee_local $3
    (i32.add
     (tee_local $14
      (get_local $14)
     )
     (i32.const -80)
    )
   )
  )
  (i32.store offset=4
   (get_local $13)
   (get_local $3)
  )
  (i32.store
   (get_local $13)
   (get_local $3)
  )
  (i32.store offset=8
   (get_local $13)
   (get_local $14)
  )
  (drop
   (call $_ZlsIN5cosio10datastreamIPcEEERT_S5_RKN7storage5offerE
    (get_local $13)
    (get_local $1)
   )
  )
  (i32.store offset=92
   (get_local $1)
   (call $db_store_i64
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
    (i64.const -6712989628304982016)
    (i32.load offset=8
     (get_local $0)
    )
    (tee_local $7
     (i64.load
      (get_local $1)
     )
    )
    (get_local $3)
    (i32.const 80)
   )
  )
  (block $label$2
   (br_if $label$2
    (i64.lt_u
     (get_local $7)
     (i64.load offset=32
      (get_local $2)
     )
    )
   )
   (i64.store
    (i32.add
     (get_local $2)
     (i32.const 32)
    )
    (select
     (i64.const -2)
     (i64.add
      (get_local $7)
      (i64.const 1)
     )
     (i64.gt_u
      (get_local $7)
      (i64.const -3)
     )
    )
   )
  )
  (set_local $0
   (i32.load
    (i32.add
     (get_local $0)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=32
   (get_local $13)
   (i64.load offset=16
    (get_local $2)
   )
  )
  (i64.store offset=40
   (get_local $13)
   (i64.load
    (tee_local $3
     (i32.add
      (get_local $2)
      (i32.const 24)
     )
    )
   )
  )
  (i64.store offset=24
   (get_local $13)
   (i64.load
    (tee_local $14
     (i32.add
      (get_local $0)
      (i32.const 8)
     )
    )
   )
  )
  (i64.store offset=16
   (get_local $13)
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (i64.store offset=80
   (get_local $13)
   (i64.load offset=32
    (get_local $1)
   )
  )
  (i64.store offset=48
   (get_local $13)
   (i64.load offset=16
    (get_local $13)
   )
  )
  (i64.store offset=56
   (get_local $13)
   (i64.load offset=24
    (get_local $13)
   )
  )
  (i64.store offset=104
   (get_local $13)
   (i64.load offset=40
    (get_local $13)
   )
  )
  (i64.store offset=96
   (get_local $13)
   (i64.load offset=32
    (get_local $13)
   )
  )
  (i32.store offset=96
   (get_local $1)
   (call $db_idx64_store
    (i32.add
     (get_local $13)
     (i32.const 96)
    )
    (i64.const -6712989628304982016)
    (i32.add
     (get_local $13)
     (i32.const 48)
    )
    (get_local $7)
    (i32.add
     (get_local $13)
     (i32.const 80)
    )
   )
  )
  (i64.store offset=32
   (get_local $13)
   (i64.load offset=16
    (get_local $2)
   )
  )
  (i64.store offset=24
   (get_local $13)
   (i64.load
    (get_local $14)
   )
  )
  (i64.store offset=40
   (get_local $13)
   (i64.load
    (get_local $3)
   )
  )
  (i64.store offset=16
   (get_local $13)
   (i64.load
    (get_local $0)
   )
  )
  (set_local $7
   (i64.load
    (get_local $1)
   )
  )
  (set_local $9
   (i64.load
    (get_local $4)
   )
  )
  (set_local $10
   (i64.load
    (i32.add
     (get_local $1)
     (i32.const 64)
    )
   )
  )
  (set_local $11
   (i64.load
    (get_local $8)
   )
  )
  (set_local $12
   (i64.load offset=48
    (get_local $1)
   )
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store offset=56
   (get_local $13)
   (get_local $12)
  )
  (i64.store offset=48
   (get_local $13)
   (get_local $11)
  )
  (call $contento_assert
   (i32.const 1)
   (i32.const 112)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $13)
     (i32.const 48)
    )
    (i32.const 24)
   )
   (get_local $10)
  )
  (i64.store offset=64
   (get_local $13)
   (get_local $9)
  )
  (i64.store offset=96
   (get_local $13)
   (i64.load offset=16
    (get_local $13)
   )
  )
  (i64.store offset=104
   (get_local $13)
   (i64.load offset=24
    (get_local $13)
   )
  )
  (i64.store offset=88
   (get_local $13)
   (i64.load offset=40
    (get_local $13)
   )
  )
  (i64.store offset=80
   (get_local $13)
   (i64.load offset=32
    (get_local $13)
   )
  )
  (i32.store
   (i32.add
    (get_local $1)
    (i32.const 100)
   )
   (call $db_idx256_store
    (i32.add
     (get_local $13)
     (i32.const 80)
    )
    (i64.const -6712989628304982015)
    (i32.add
     (get_local $13)
     (i32.const 96)
    )
    (get_local $7)
    (i32.add
     (get_local $13)
     (i32.const 48)
    )
    (i32.const 2)
   )
  )
  (i32.store offset=4
   (i32.const 0)
   (i32.add
    (get_local $13)
    (i32.const 112)
   )
  )
 )
 (func $_ZN5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE14const_iteratormmEv (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (i32.store offset=4
   (i32.const 0)
   (tee_local $2
    (i32.sub
     (i32.load offset=4
      (i32.const 0)
     )
     (i32.const 48)
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
    (call $contento_assert
     (i32.xor
      (i32.shr_u
       (tee_local $1
        (call $db_previous_i64
         (i32.load offset=92
          (get_local $1)
         )
         (i32.add
          (get_local $2)
          (i32.const 40)
         )
        )
       )
       (i32.const 31)
      )
      (i32.const 1)
     )
     (i32.const 1136)
    )
    (br $label$0)
   )
   (i32.store offset=16
    (get_local $2)
    (i32.load
     (tee_local $1
      (i32.load
       (get_local $0)
      )
     )
    )
   )
   (i32.store offset=28
    (get_local $2)
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 12)
     )
    )
   )
   (i32.store offset=24
    (get_local $2)
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 8)
     )
    )
   )
   (i32.store offset=20
    (get_local $2)
    (i32.load
     (i32.add
      (get_local $1)
      (i32.const 4)
     )
    )
   )
   (i64.store offset=8
    (get_local $2)
    (i64.load
     (i32.add
      (get_local $1)
      (i32.const 24)
     )
    )
   )
   (i64.store
    (get_local $2)
    (i64.load offset=16
     (get_local $1)
    )
   )
   (call $contento_assert
    (i32.ne
     (tee_local $1
      (call $db_end_i64
       (i32.add
        (get_local $2)
        (i32.const 16)
       )
       (get_local $2)
       (i64.const -6712989628304982016)
      )
     )
     (i32.const -1)
    )
    (i32.const 1072)
   )
   (call $contento_assert
    (i32.xor
     (i32.shr_u
      (tee_local $1
       (call $db_previous_i64
        (get_local $1)
        (i32.add
         (get_local $2)
         (i32.const 40)
        )
       )
      )
      (i32.const 31)
     )
     (i32.const 1)
    )
    (i32.const 1072)
   )
  )
  (i32.store
   (i32.add
    (get_local $0)
    (i32.const 4)
   )
   (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl
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
    (i32.const 48)
   )
  )
  (get_local $0)
 )
 (func $_ZlsIN5cosio10datastreamIPcEEERT_S5_RKN7storage5offerE (param $0 i32) (param $1 i32) (result i32)
  (local $2 i32)
  (call $contento_assert
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
   (i32.const 1056)
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
  (call $contento_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 15)
   )
   (i32.const 1056)
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
  (call $contento_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 1056)
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
  (call $contento_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 1056)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 40)
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
  (call $contento_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 31)
   )
   (i32.const 1056)
  )
  (drop
   (call $memcpy
    (i32.load offset=4
     (get_local $0)
    )
    (i32.add
     (get_local $1)
     (i32.const 48)
    )
    (i32.const 32)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (tee_local $2
    (i32.add
     (i32.load offset=4
      (get_local $0)
     )
     (i32.const 32)
    )
   )
  )
  (call $contento_assert
   (i32.gt_s
    (i32.sub
     (i32.load offset=8
      (get_local $0)
     )
     (get_local $2)
    )
    (i32.const 7)
   )
   (i32.const 1056)
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
    (i32.const 8)
   )
  )
  (i32.store offset=4
   (get_local $0)
   (i32.add
    (i32.load offset=4
     (get_local $0)
    )
    (i32.const 8)
   )
  )
  (get_local $0)
 )
 (func $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE5indexILy4982431883047354368ESB_Ly1ELb1EE11lower_boundERKSA_ (param $0 i32) (param $1 i32) (param $2 i32)
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
     (i32.const 144)
    )
   )
  )
  (i64.store offset=104
   (get_local $10)
   (i64.const 0)
  )
  (i64.store
   (i32.add
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
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
    (i32.add
     (get_local $10)
     (i32.const 64)
    )
    (i32.const 16)
   )
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 16)
    )
   )
  )
  (i64.store offset=72
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i64.store offset=64
   (get_local $10)
   (i64.load
    (get_local $2)
   )
  )
  (i32.store offset=48
   (get_local $10)
   (i32.load
    (tee_local $2
     (i32.load
      (get_local $1)
     )
    )
   )
  )
  (i32.store offset=60
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 12)
    )
   )
  )
  (i32.store offset=56
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 8)
    )
   )
  )
  (i32.store offset=52
   (get_local $10)
   (i32.load
    (i32.add
     (get_local $2)
     (i32.const 4)
    )
   )
  )
  (i64.store offset=32
   (get_local $10)
   (i64.load offset=16
    (get_local $2)
   )
  )
  (i64.store offset=40
   (get_local $10)
   (i64.load
    (i32.add
     (get_local $2)
     (i32.const 24)
    )
   )
  )
  (i64.store offset=16
   (get_local $10)
   (i64.load offset=48
    (get_local $10)
   )
  )
  (i64.store offset=24
   (get_local $10)
   (i64.load offset=56
    (get_local $10)
   )
  )
  (i64.store
   (get_local $10)
   (i64.load offset=32
    (get_local $10)
   )
  )
  (i64.store offset=8
   (get_local $10)
   (i64.load offset=40
    (get_local $10)
   )
  )
  (i64.store offset=128
   (get_local $10)
   (i64.load
    (get_local $10)
   )
  )
  (i64.store offset=136
   (get_local $10)
   (i64.load offset=8
    (get_local $10)
   )
  )
  (i64.store offset=120
   (get_local $10)
   (i64.load offset=24
    (get_local $10)
   )
  )
  (i64.store offset=112
   (get_local $10)
   (i64.load offset=16
    (get_local $10)
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
       (i32.add
        (get_local $10)
        (i32.const 112)
       )
       (i32.add
        (get_local $10)
        (i32.const 128)
       )
       (i64.const -6712989628304982015)
       (i32.add
        (get_local $10)
        (i32.const 64)
       )
       (i32.const 2)
       (i32.add
        (get_local $10)
        (i32.const 104)
       )
      )
     )
     (i32.const 0)
    )
   )
   (set_local $5
    (i64.load offset=104
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
         (i32.const 44)
        )
       )
      )
      (tee_local $6
       (i32.load offset=40
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
     (call $contento_assert
      (i32.eq
       (i32.load offset=88
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
      (i32.const 560)
     )
     (br $label$3)
    )
    (call $contento_assert
     (i32.eq
      (i32.load offset=88
       (tee_local $2
        (call $_ZNK5cosio11multi_indexILy11733754445404569600EN7storage5offerEJNS_10indexed_byILy4229443000054317056EN5boost11multi_index13const_mem_funIS2_yXadL_ZNKS2_6by_betEvEEEEEENS3_ILy4982431883047354368ENS6_IS2_NS_9fixed_keyILj32EEEXadL_ZNKS2_13by_commitmentEvEEEEEEEE31load_object_by_primary_iteratorEl
         (get_local $4)
         (call $db_find_i64
          (get_local $4)
          (i32.add
           (get_local $4)
           (i32.const 16)
          )
          (i64.const -6712989628304982016)
          (get_local $5)
         )
        )
       )
      )
      (get_local $4)
     )
     (i32.const 560)
    )
   )
   (i32.store
    (i32.add
     (get_local $2)
     (i32.const 100)
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
    (i32.const 144)
   )
  )
 )
 (func $malloc (param $0 i32) (result i32)
  (call $_ZN5cosio14memory_manager6mallocEm
   (i32.const 1184)
   (get_local $0)
  )
 )
 (func $_ZN5cosio14memory_manager6mallocEm (param $0 i32) (param $1 i32) (result i32)
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
         (call $_ZN5cosio14memory_manager16next_active_heapEv
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
      (call $contento_assert
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
       (i32.const 9584)
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
 (func $_ZN5cosio14memory_manager16next_active_heapEv (param $0 i32) (result i32)
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
      (i32.load8_u offset=9670
       (i32.const 0)
      )
     )
    )
    (set_local $7
     (i32.load offset=9672
      (i32.const 0)
     )
    )
    (br $label$0)
   )
   (set_local $7
    (current_memory)
   )
   (i32.store8 offset=9670
    (i32.const 0)
    (i32.const 1)
   )
   (i32.store offset=9672
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
       (i32.load offset=9672
        (i32.const 0)
       )
      )
     )
     (set_local $8
      (i32.const 0)
     )
     (i32.store offset=9672
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
       (i32.load8_u offset=9670
        (i32.const 0)
       )
      )
      (set_local $3
       (current_memory)
      )
      (i32.store8 offset=9670
       (i32.const 0)
       (i32.const 1)
      )
      (i32.store offset=9672
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
       (i32.load offset=9672
        (i32.const 0)
       )
      )
     )
     (i32.store offset=9672
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
       (i32.load offset=9568
        (i32.const 0)
       )
      )
      (i32.const 1)
     )
    )
    (set_local $3
     (i32.const 9376)
    )
    (set_local $1
     (i32.add
      (i32.mul
       (get_local $2)
       (i32.const 12)
      )
      (i32.const 9376)
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
       (i32.load offset=9676
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
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9push_backEc (param $0 i32) (param $1 i32)
  (local $2 i32)
  (local $3 i32)
  (local $4 i32)
  (block $label$0
   (block $label$1
    (block $label$2
     (block $label$3
      (block $label$4
       (block $label$5
        (br_if $label$5
         (i32.eqz
          (tee_local $2
           (i32.and
            (tee_local $4
             (i32.load8_u
              (get_local $0)
             )
            )
            (i32.const 1)
           )
          )
         )
        )
        (br_if $label$4
         (i32.eq
          (tee_local $4
           (i32.load offset=4
            (get_local $0)
           )
          )
          (tee_local $3
           (i32.add
            (i32.and
             (i32.load
              (get_local $0)
             )
             (i32.const -2)
            )
            (i32.const -1)
           )
          )
         )
        )
        (br $label$3)
       )
       (set_local $3
        (i32.const 10)
       )
       (br_if $label$3
        (i32.ne
         (tee_local $4
          (i32.shr_u
           (get_local $4)
           (i32.const 1)
          )
         )
         (i32.const 10)
        )
       )
      )
      (call $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9__grow_byEjjjjjj
       (get_local $0)
       (get_local $3)
       (i32.const 1)
       (get_local $3)
       (get_local $3)
       (i32.const 0)
       (i32.const 0)
      )
      (br_if $label$2
       (i32.and
        (i32.load8_u
         (get_local $0)
        )
        (i32.const 1)
       )
      )
      (br $label$1)
     )
     (br_if $label$1
      (i32.eqz
       (get_local $2)
      )
     )
    )
    (i32.store offset=4
     (get_local $0)
     (i32.add
      (get_local $4)
      (i32.const 1)
     )
    )
    (set_local $0
     (i32.load offset=8
      (get_local $0)
     )
    )
    (br $label$0)
   )
   (i32.store8
    (get_local $0)
    (i32.add
     (i32.shl
      (get_local $4)
      (i32.const 1)
     )
     (i32.const 2)
    )
   )
   (set_local $0
    (i32.add
     (get_local $0)
     (i32.const 1)
    )
   )
  )
  (i32.store8 offset=1
   (tee_local $0
    (i32.add
     (get_local $0)
     (get_local $4)
    )
   )
   (i32.const 0)
  )
  (i32.store8
   (get_local $0)
   (get_local $1)
  )
 )
 (func $_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9__grow_byEjjjjjj (param $0 i32) (param $1 i32) (param $2 i32) (param $3 i32) (param $4 i32) (param $5 i32) (param $6 i32)
  (local $7 i32)
  (local $8 i32)
  (local $9 i32)
  (block $label$0
   (br_if $label$0
    (i32.lt_u
     (i32.sub
      (i32.const -17)
      (get_local $1)
     )
     (get_local $2)
    )
   )
   (block $label$1
    (block $label$2
     (br_if $label$2
      (i32.and
       (i32.load8_u
        (get_local $0)
       )
       (i32.const 1)
      )
     )
     (set_local $8
      (i32.add
       (get_local $0)
       (i32.const 1)
      )
     )
     (br $label$1)
    )
    (set_local $8
     (i32.load offset=8
      (get_local $0)
     )
    )
   )
   (set_local $9
    (i32.const -17)
   )
   (block $label$3
    (br_if $label$3
     (i32.gt_u
      (get_local $1)
      (i32.const 2147483622)
     )
    )
    (set_local $9
     (i32.const 11)
    )
    (br_if $label$3
     (i32.lt_u
      (tee_local $2
       (select
        (tee_local $7
         (i32.shl
          (get_local $1)
          (i32.const 1)
         )
        )
        (tee_local $2
         (i32.add
          (get_local $2)
          (get_local $1)
         )
        )
        (i32.lt_u
         (get_local $2)
         (get_local $7)
        )
       )
      )
      (i32.const 11)
     )
    )
    (set_local $9
     (i32.and
      (i32.add
       (get_local $2)
       (i32.const 16)
      )
      (i32.const -16)
     )
    )
   )
   (set_local $2
    (call $_Znwj
     (get_local $9)
    )
   )
   (block $label$4
    (br_if $label$4
     (i32.eqz
      (get_local $4)
     )
    )
    (drop
     (call $memcpy
      (get_local $2)
      (get_local $8)
      (get_local $4)
     )
    )
   )
   (block $label$5
    (br_if $label$5
     (i32.eqz
      (tee_local $3
       (i32.sub
        (i32.sub
         (get_local $3)
         (get_local $5)
        )
        (get_local $4)
       )
      )
     )
    )
    (drop
     (call $memcpy
      (i32.add
       (i32.add
        (get_local $2)
        (get_local $4)
       )
       (get_local $6)
      )
      (i32.add
       (i32.add
        (get_local $8)
        (get_local $4)
       )
       (get_local $5)
      )
      (get_local $3)
     )
    )
   )
   (block $label$6
    (br_if $label$6
     (i32.eq
      (get_local $1)
      (i32.const 10)
     )
    )
    (call $_ZdlPv
     (get_local $8)
    )
   )
   (i32.store offset=8
    (get_local $0)
    (get_local $2)
   )
   (i32.store
    (get_local $0)
    (i32.or
     (get_local $9)
     (i32.const 1)
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
 (func $strlen (param $0 i32) (result i32)
  (local $1 i32)
  (local $2 i32)
  (set_local $2
   (get_local $0)
  )
  (block $label$0
   (block $label$1
    (br_if $label$1
     (i32.eqz
      (i32.and
       (get_local $0)
       (i32.const 3)
      )
     )
    )
    (set_local $2
     (get_local $0)
    )
    (loop $label$2
     (br_if $label$0
      (i32.eqz
       (i32.load8_u
        (get_local $2)
       )
      )
     )
     (br_if $label$2
      (i32.and
       (tee_local $2
        (i32.add
         (get_local $2)
         (i32.const 1)
        )
       )
       (i32.const 3)
      )
     )
    )
   )
   (set_local $2
    (i32.add
     (get_local $2)
     (i32.const -4)
    )
   )
   (loop $label$3
    (br_if $label$3
     (i32.eqz
      (i32.and
       (i32.and
        (i32.xor
         (tee_local $1
          (i32.load
           (tee_local $2
            (i32.add
             (get_local $2)
             (i32.const 4)
            )
           )
          )
         )
         (i32.const -1)
        )
        (i32.add
         (get_local $1)
         (i32.const -16843009)
        )
       )
       (i32.const -2139062144)
      )
     )
    )
   )
   (br_if $label$0
    (i32.eqz
     (i32.and
      (get_local $1)
      (i32.const 255)
     )
    )
   )
   (loop $label$4
    (br_if $label$4
     (i32.load8_u
      (tee_local $2
       (i32.add
        (get_local $2)
        (i32.const 1)
       )
      )
     )
    )
   )
  )
  (i32.sub
   (get_local $2)
   (get_local $0)
  )
 )
 (func $__wasm_nullptr (type $FUNCSIG$v)
  (unreachable)
 )
)
