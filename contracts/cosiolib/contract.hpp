#pragma once

namespace cosio {

class contract {
   public:
      contract( account_name n ):_self(n){}
      
      inline account_name get_self()const { return _self; }

   protected:
      account_name _self;
};

} /// namespace cosio
