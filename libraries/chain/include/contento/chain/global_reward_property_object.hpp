#pragma once
#include <fc/uint128.hpp>
#include <contento/chain/contento_object_types.hpp>
#include <contento/chain/contento_objects.hpp>
#include <contento/protocol/asset.hpp>
namespace contento { namespace chain {
    
    using contento::protocol::asset;
    using contento::protocol::price;
    
    class dynamic_global_reward_property_object : public object <
    dynamic_global_reward_property_object_type, dynamic_global_reward_property_object>
    {
    public:
        template < typename Constructor, typename Allocator >
        dynamic_global_reward_property_object( Constructor&& c, allocator< Allocator > a)
        {
            c(*this);
        }
        
        dynamic_global_reward_property_object() {}
        
        id_type         id;
        asset               subject_reward_balance = asset( 0, COC_SYMBOL);
        uint128_t           subject_recent_claims = 0;
        uint128_t           subject_content_constant = 0;
        curve_id            subject_reward_curve = linear;
        asset               comment_reward_balance = asset( 0, COC_SYMBOL );
        uint128_t           comment_recent_claims = 0;
        uint128_t           comment_content_constant = 0;
        curve_id            comment_reward_curve = square_root;
        asset               other_reward_balance = asset( 0, COC_SYMBOL );
        uint128_t           tick=0;
        time_point_sec      subject_last_update;
        time_point_sec      comment_last_update;
        
    };
    
    typedef multi_index_container<
    dynamic_global_reward_property_object,
    indexed_by<
    ordered_unique< tag< by_id>,
    member< dynamic_global_reward_property_object, dynamic_global_reward_property_object::id_type, &dynamic_global_reward_property_object::id > >
    >,
    allocator< dynamic_global_reward_property_object >
    > dynamic_global_reward_property_index;
    
} } // steemit::chain
FC_REFLECT( contento::chain::dynamic_global_reward_property_object,
           (id)
           (subject_reward_balance)
           (subject_recent_claims)
           (subject_content_constant)
           (subject_reward_curve)
           (comment_reward_balance)
           (comment_recent_claims)
           (comment_content_constant)
           (comment_reward_curve)
           (other_reward_balance)
           (tick)
           (subject_last_update)
           (comment_last_update)
           )
CHAINBASE_SET_INDEX_TYPE( contento::chain::dynamic_global_reward_property_object, contento::chain::dynamic_global_reward_property_index )
