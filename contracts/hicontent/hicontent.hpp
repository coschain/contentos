#pragma once
#include <cosiolib/eosio.hpp>
#include <cosiolib/content.hpp>
#include <cosiolib/content_operation.hpp>

namespace eosio {

   class hicontent : public contract {
      public:
         hicontent( action_name self ):contract(self){}

      void query() {

         {
            print("total account on chain : ",  database_api().get_account_count() , "\n");
         }

         {
            vector<string8> res = database_api().get_active_witnesses();
            for ( auto x : res ) print("witness name: ", x, "\n");
         }

         {
            dynamic_global_property_api_obj dgp = database_api().get_dynamic_global_properties();
            print("dgp: average_block_size: ", dgp.average_block_size, "\n");
            print("dgp: head_block_number:", dgp.head_block_number, "\n");
            print("dgp: current_witness: ", dgp.current_witness, "\n");
         }

         {
            vector<string> names;
            names.push_back( "initminer" );

            vector<extended_account> aobjs =  database_api().get_accounts(names);
            if ( aobjs.size() > 0 ){
               extended_account aobj = aobjs[0];
               print("initminer last post time: ", aobj.last_root_post.utc_seconds, "\n" );
            }

         }

         {
            print("******** start query get_state ******** \n ");
            state st =  database_api().get_state("/title1/@initminer/perm3");

            if ( st.content.size() > 0 ) print("comment body: ", st.content.begin()->second.body, "\n" );
            if ( st.accounts.size() > 0 ) print("accounts name: ", st.accounts.begin()->first, "\n" );


            print("market_data size: ", st.market_data.size(), "\n" );
            print("witnesses size: ", st.witnesses.size(), "\n" );
            print("discussion_idx size: ", st.discussion_idx.size(), "\n" );

            print("next_shuffle_block_num: ", (int)st.witness_schedule.next_shuffle_block_num, "\n" );
            print("timeshare_weight: ", (int)st.witness_schedule.timeshare_weight, "\n" );
            print("hardfork_required_witnesses: ", (int)st.witness_schedule.hardfork_required_witnesses, "\n" );

            print("******** end query get_state ******** \n ");
         }


         {
            vector<applied_operation> ops = database_api().get_ops_in_block( 57, false);

            print("ops.size(): ", ops.size(), "\n" );
            for (auto apply_op : ops )
            {
               if ( apply_op.op.contains<vm_operation>() ){
                  vm_operation& vmop = apply_op.op.get<vm_operation>();
                  print("vm_operation contract_name: ", vmop.contract_name, " ** action_name :" , vmop.action_name.to_string().c_str(), "\n" );
               }
            }
         }

         {
            vector<signed_block_api_obj> blks = database_api().get_block( 57);
            print("get_block size: ", blks.size() , "\n");
            for ( auto blk : blks ){
               print("block info trxs: ", blk.transactions.size() , "\n");

               for ( auto trx :  blk.transactions ){
                  print("trx info-status: ", trx.invoice.status , "\n");
                  print("trx info-sigsize: ", trx.sig_trx.signatures.size() , "\n");
                  print("trx info-opsize: ", trx.sig_trx.operations.size() , "\n");
               }
            }
         }

         {
            vector<follow_api_obj> fobjs = follow_api().get_followers( ".initminer", "", 1, 10);
            print("get_followers size: ", fobjs.size() , "\n");
            for ( auto fobj : fobjs ){
               print("follower: ", fobj.follower, "\t following: ", fobj.following , "\t what:", fobj.what[0], "\n");
            }
         }

        {
            transfer_operation op;
            op.from = "initminer";
            op.to = "yykingking";
            op.amount = asset(12222);
            op.memo = "FROM VM CALL";

            send_inline_operation(op);
            print("send_transfer_operation success\n");

        }
        {
            vm_operation op;
            op.caller = "initminer";
            op.contract_name = "contento";
            op.action_name = "reqauthx";

            //send_inline_operation(op);
            print("skip vm_operation success\n");

        }

        {
            hardfork_operation op;
            op.hardfork_id = 10;

            //send_inline_operation(op);
            print("send hardfork_operation success\n");
        }
      }

      private:
   };

} /// namespace eosio
