const char* const eosio_token_abi = R"=====(
{
  "____comment": "This file was generated by eosio-abigen. DO NOT EDIT - 2018-08-10T05:47:12",
  "version": "eosio::abi/1.0",
  "types": [],
  "structs": [{
      "name": "create",
      "base": "",
      "fields": [{
          "name": "issuer",
          "type": "name"
        },{
          "name": "maximum_supply",
          "type": "asset"
        }
      ]
    },{
      "name": "issue",
      "base": "",
      "fields": [{
          "name": "to",
          "type": "name"
        },{
          "name": "quantity",
          "type": "asset"
        },{
          "name": "memo",
          "type": "string"
        }
      ]
    },{
      "name": "transfer",
      "base": "",
      "fields": [{
          "name": "from",
          "type": "name"
        },{
          "name": "to",
          "type": "name"
        },{
          "name": "quantity",
          "type": "asset"
        },{
          "name": "memo",
          "type": "string"
        }
      ]
    },{
      "name": "testcb",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testchain",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testfloat",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testcrypto",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testprint",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testsystemapi",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testmem",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    },{
      "name": "testdb",
      "base": "",
      "fields": [{
          "name": "name",
          "type": "name"
        }
      ]
    }
  ],
  "actions": [{
      "name": "create",
      "type": "create",
      "ricardian_contract": ""
    },{
      "name": "issue",
      "type": "issue",
      "ricardian_contract": ""
    },{
      "name": "transfer",
      "type": "transfer",
      "ricardian_contract": ""
    },{
      "name": "testcb",
      "type": "testcb",
      "ricardian_contract": ""
    },{
      "name": "testchain",
      "type": "testchain",
      "ricardian_contract": ""
    },{
      "name": "testfloat",
      "type": "testfloat",
      "ricardian_contract": ""
    },{
      "name": "testcrypto",
      "type": "testcrypto",
      "ricardian_contract": ""
    },{
      "name": "testprint",
      "type": "testprint",
      "ricardian_contract": ""
    },{
      "name": "testsystemapi",
      "type": "testsystemapi",
      "ricardian_contract": ""
    },{
      "name": "testmem",
      "type": "testmem",
      "ricardian_contract": ""
    },{
      "name": "testdb",
      "type": "testdb",
      "ricardian_contract": ""
    }
  ],
  "tables": [],
  "ricardian_clauses": [],
  "error_messages": [],
  "abi_extensions": []
}
)=====";
