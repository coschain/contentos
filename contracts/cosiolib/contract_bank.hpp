#pragma once
#include <cosiolib/contract_bank.h>

namespace cosio {

    inline asset get_contract_balance() {
        asset a;
        get_contract_balance_internal(a);
        return a;
    }

    inline asset get_value() {
        int64_t val = get_value_internal();
        asset a(val);
        return a;
    }
}
