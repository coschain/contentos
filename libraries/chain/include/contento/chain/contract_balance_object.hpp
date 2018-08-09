#pragma once

namespace contento { namespace chain {

    class contract_balance_object : public object< contract_balance_object_type, contract_balance_object >
    {
        contract_balance_object() = delete;

        public:
        template< typename Constructor, typename Allocator >
            contract_balance_object(Constructor&& c, allocator< Allocator > a){
                c(*this);
            }

        id_type           id;
        account_name contract_name;
        asset             coc_balance = asset( 0, COC_SYMBOL );
        asset             vesting_balance = asset( 0, VESTS_SYMBOL );
    };

    //multi_index
    struct by_name;
    typedef multi_index_container<
        contract_balance_object,
        indexed_by<
            ordered_unique< tag< by_id >,
        member< contract_balance_object, contract_balance_id_type, &contract_balance_object::id > >,
        ordered_unique< tag< by_name >,
        member< contract_balance_object, account_name_type, &contract_balance_object::contract_name > >
            >,
        allocator< contract_balance_object >
            > contract_balance_index;

}}

FC_REFLECT( contento::chain::contract_balance_object,(id)(contract_name)(coc_balance)(vesting_balance))
CHAINBASE_SET_INDEX_TYPE( contento::chain::contract_balance_object, contento::chain::contract_balance_index )
